#ifndef TRANSFORMATORS_HPP
#define TRANSFORMATORS_HPP

#include "SetString.hpp"

struct SetTransformator
{
  SetString forUnion;
  SetString operator()(SetString first);
};

#endif
