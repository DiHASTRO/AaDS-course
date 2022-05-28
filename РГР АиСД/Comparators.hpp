#ifndef COMPARATORS_HPP
#define COMPARATORS_HPP

#include <string>

struct StringComparator
{
	bool operator()(const std::string& first, const std::string& second);
};

#endif
