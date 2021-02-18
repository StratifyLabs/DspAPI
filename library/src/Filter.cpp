// Copyright 2016-2021 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md

#include <printer/Printer.hpp>

#include "dsp/Filter.hpp"

namespace printer {

} // namespace printer

using namespace dsp;

HighPassFilterF32::HighPassFilterF32(float start, float r_value) {
  m_r_value = r_value;
  reset(start);
}

HighPassFilterF32 &HighPassFilterF32::reset(float start) {
  m_last_input = start;
  set_present_value(0.0f);
  return *this;
}

HighPassFilterF32 &HighPassFilterF32::set_r_value(float r_value) {
  m_r_value = r_value;
  return *this;
}

HighPassFilterF32 &HighPassFilterF32::calculate(float input) {
  m_present_value = input - m_r_value * m_last_input + m_present_value;
  m_last_input = input;
  return *this;
}

LowPassFilterF32::LowPassFilterF32(float start) : m_alpha(0.001f) {
  m_present_value = start;
}

LowPassFilterF32 &LowPassFilterF32::calculate(float in) {
  m_present_value = in * (m_alpha) + m_present_value * (1.0f - m_alpha);
  return *this;
}

LowPassFilterF32 &LowPassFilterF32::reset(float start) {
  set_present_value(start);
  return *this;
}

