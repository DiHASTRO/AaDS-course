#ifndef COMPARATORS_HPP
#define COMPARATORS_HPP

#include <string>

struct StringComparator
{
	bool operator()(const std::string&, const std::string&);
};

struct IntComparator
{
  bool operator()(int, int);
};

#endif
