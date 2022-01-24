//
// Created by Tyler Gilbert on 1/17/22.
//

#ifndef DSPAPI_DSP_SIMPLERINGBUFFER_HPP
#define DSPAPI_DSP_SIMPLERINGBUFFER_HPP

#include <api/api.hpp>

namespace dsp {

template <typename Type, size_t Count>
class SimpleRingBuffer : public api::ExecutionContext {
public:
  SimpleRingBuffer() { flush(); }

  API_NO_DISCARD constexpr size_t count() const { return Count; }

  SimpleRingBuffer &push(Type value) {
    m_buffer[m_head] = value;
    m_head++;
    if (m_head == Count) {
      m_head = 0;
    }
    return *this;
  }

  Type back() const { return m_buffer[m_head]; }
  Type front() const { return at(0); }

  Type at(size_t offset) {
    const auto adjusted_offset
      = m_head > offset ? m_head - offset - 1 : Count + m_head - offset - 1;
    return m_buffer[adjusted_offset];
  }

  SimpleRingBuffer &flush() {
    for (auto &value : m_buffer) {
      value = {};
    }
    m_head = 0;
    return *this;
  }

private:
  size_t m_head = 0;
  std::array<Type, Count> m_buffer;
};

} // namespace dsp

#endif // DSPAPI_DSP_SIMPLERINGBUFFER_HPP
