#ifndef TRANSFORMATORS_HPP
#define TRANSFORMATORS_HPP

#include "Set.hpp"

template < typename T, typename Comp >
struct SetTransformator
{
  Set< T, Comp > forUnion;
  Set< T, Comp > operator()(Set< T, Comp > first)
  {
    first.unionSets(forUnion);
    return first;
  };
};

#endif
