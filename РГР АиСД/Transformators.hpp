#ifndef TRANSFORMATORS_HPP
#define TRANSFORMATORS_HPP

#include "SetString.hpp"

struct SetTransformator
{
  const SetString& forUnion;
  SetString operator()(SetString first, SetString last);
};

#endif
