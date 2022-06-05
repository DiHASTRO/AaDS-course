#ifndef EXECUTORS_HPP
#define EXECUTORS_HPP

#include <iosfwd>
#include <string>
#include "Dictionary.hpp"

void executeCommand(Dictionary&, const std::string&, std::ostream&, std::istream&);

#endif
