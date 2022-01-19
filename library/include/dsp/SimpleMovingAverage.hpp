//
// Created by Tyler Gilbert on 1/17/22.
//

#ifndef DSPAPI_DSP_SIMPLEMOVINGAVERAGE_HPP
#define DSPAPI_DSP_SIMPLEMOVINGAVERAGE_HPP

#include "SimpleRingBuffer.hpp"

namespace dsp {

template <typename Type, size_t Count>
class SimpleMovingAverage : public api::ExecutionContext {
public:
  API_NO_DISCARD constexpr size_t count() const { return Count; }
  SimpleMovingAverage &set_coefficient(uint8_t) { return *this; }

  SimpleMovingAverage &calculate(Type input) {
    sum += input;
    sum -= buffer.back();
    buffer.push(input);
    return *this;
  }

  API_NO_DISCARD Type present_value() const { return sum / Count; }

private:
  SimpleRingBuffer<Type, Count> buffer;
  int32_t sum = 0;
};

} // namespace dsp

#endif // DSPAPI_DSP_SIMPLEMOVINGAVERAGE_HPP
