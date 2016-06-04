#include "pos.h"

Pos& Pos::operator +=(const Pos& rhs){
    x += rhs.x;
    y += rhs.y;
    return *this;
}

Pos& Pos::operator -=(const Pos& rhs){
    x -= rhs.x;
    y -= rhs.y;
}
