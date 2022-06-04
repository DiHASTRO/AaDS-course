#include "Transformators.hpp"

SetString SetTransformator::operator()(SetString first)
{
  first.unionSets(forUnion);
  return first;
}
