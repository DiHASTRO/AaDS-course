#include "Transformators.hpp"

SetString SetTransformator::operator()(SetString first, SetString last)
{
  first.unionSets(last);
  return first;
}