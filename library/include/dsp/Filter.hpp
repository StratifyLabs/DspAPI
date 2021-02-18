// Copyright 2011-2021 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md for
// rights.

#ifndef DSPAPI_DSP_FILTER_HPP_
#define DSPAPI_DSP_FILTER_HPP_

#include <sdk/types.h>

#include <api/macros.hpp>

namespace dsp {

template <class Derived, typename FundamentalType> class SimpleFilter {
public:
  SimpleFilter() : m_present_value() {}

  virtual Derived &calculate(FundamentalType a) = 0;
  FundamentalType present_value() const { return m_present_value; }

protected:
  void set_present_value(const FundamentalType &value) {
    m_present_value = value;
  }

  FundamentalType m_present_value;
};

#define LOW_PASS_FILTER_S32_ALPHA(x) ((u16)(x * 65535))
#define LOW_PASS_FILTER_S16_ALPHA(x) ((u8)(x * 255))

template <class Derived, typename intsmall, typename intmedium,
          typename intlarge>
class LowPassFilter : public SimpleFilter<Derived, intmedium> {
public:
  LowPassFilter(intmedium start) : m_average(start) {}
  static intmedium small_max() { return 1 << (8 * sizeof(intsmall)); }

  Derived &set_alpha(intsmall value) {
    m_alpha = value;
    return get_return(*this);
  }

  Derived &calculate(intmedium in) override {
    intlarge tmp0;
    tmp0 = (intlarge)in * (m_alpha) +
           (intlarge)m_average * (small_max() - m_alpha);
    m_average = (intmedium)(((intlarge)tmp0 + (intlarge)small_max()) >>
                            (sizeof(intsmall) * 8));
    return reinterpret_cast<Derived &>(*this);
  }

  Derived &reset(intmedium v) {
    m_average = v;
    return reinterpret_cast<Derived &>(*this);
  }

private:
  intmedium m_average;
  intsmall m_alpha;
};

class LowPassFilterS32 : public LowPassFilter<LowPassFilterS32, u16, s32, s64> {
public:
  LowPassFilterS32(s32 start = 0) : LowPassFilter(start) {}
};

class LowPassFilterS16 : public LowPassFilter<LowPassFilterS16, u8, s16, s32> {
public:
  LowPassFilterS16(s16 start = 0) : LowPassFilter(start) {}
};

class LowPassFilterU32 : public LowPassFilter<LowPassFilterU32, u16, u32, u64> {
public:
  LowPassFilterU32(u32 start = 0) : LowPassFilter(start) {}
};

class LowPassFilterU16 : public LowPassFilter<LowPassFilterU16, u8, u16, u32> {
public:
  LowPassFilterU16(u16 start = 0) : LowPassFilter(start) {}
};

class LowPassFilterF32 : public SimpleFilter<LowPassFilterF32, float> {
public:
  LowPassFilterF32(float start = 0.0f);

  LowPassFilterF32 &set_alpha(float value) {
    m_alpha = value;
    return *this;
  }

  float calculate_alpha(float sampling_frequency, float magnitude = 0.5f);

  LowPassFilterF32 &reset(float start);
  LowPassFilterF32 &calculate(float in) override;

private:
  float m_alpha;
};

class HighPassFilterF32 : public SimpleFilter<HighPassFilterF32, float> {
public:
  HighPassFilterF32(float start, float r_value);

  HighPassFilterF32 &reset(float start);
  HighPassFilterF32 &set_r_value(float r_value);
  HighPassFilterF32 &set_initial_input(float value) {
    m_last_input = value;
    return *this;
  }
  HighPassFilterF32 &calculate(float input) override;

private:
  float m_last_input;
  float m_r_value;
};

} // namespace dsp

#endif /* DSPAPI_DSP_FILTER_HPP_ */
