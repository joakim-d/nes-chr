#ifndef id0B8ADC5DEAFA4054B2C8E5E9BF225BB4_H
#define id0B8ADC5DEAFA4054B2C8E5E9BF225BB4_H

#include <stdint.h>

/*!
 * \brief The Pos class
 */
//! TODO DOCUMENTING!!!

class Pos {
public:
  Pos(){}
  Pos(int32_t x, int32_t y) : x(x), y(y){}

  Pos& operator+=(const Pos& rhs);
  Pos& operator-=(const Pos& rhs);

  int32_t x{};
  int32_t y{};
};

#endif // id0B8ADC5DEAFA4054B2C8E5E9BF225BB4_H
