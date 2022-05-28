#include "Comparators.hpp"

bool StringComparator::operator()(const std::string& first, const std::string& second)
{
	return first < second;
}
