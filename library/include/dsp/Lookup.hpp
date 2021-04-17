/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see
             // LICENSE.md for rights.

#ifndef SAPI_CALC_LOOKUP_HPP_
#define SAPI_CALC_LOOKUP_HPP_

#include <api/api.hpp>

namespace dsp {

template <typename T> class Lookup : public api::ExecutionContext {
public:
  /*! A pointer to a table with x and y values
                           alternating, x values must be in ascending order */
  /*! The number of entries in the table */
  Lookup(const T *table, u32 count
  ) {
    m_table = table;
    m_count = count;
  }

  T calculate(T x) {
    unsigned int p1, p2;
    unsigned int i;
    T delta_x, delta_y;
    T output;

    i = 0;
    while ((x > m_table[i + 2]) && (i < (m_count - 2) * 2)) {
      i += 2;
    }

    p1 = i;
    p2 = i + 2;

    // now calculate the slope between the y values
    delta_x = m_table[p1] - m_table[p2];
    if (delta_x == 0) {
      return m_table[p1 + 1];
    }
    delta_y = m_table[p1 + 1] - m_table[p2 + 1];
    output =
        ((x - m_table[p1]) * delta_y + delta_x / 2) / delta_x + m_table[p1 + 1];

    return output;
  }

private:
  const T *m_table;
  unsigned int m_count;
};

} // namespace dsp

#endif /* SAPI_CALC_LOOKUP_HPP_ */
