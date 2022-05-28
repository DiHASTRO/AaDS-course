#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP

#include "RBT.hpp"
#include "SetString.hpp"
#include "Comparators.hpp"

class Dictionary
{
public:
  bool insertTranslate(const std::string& english, const std::string& russian);
  bool deleteTranslate(const std::string& english, const std::string& russian);
  bool deleteWord(const std::string& english);
  bool translate(const std::string& english, std::ostream& out);
  void print(std::ostream& out);
private:
  RBT< std::string, SetString, StringComparator > translations;
};

#endif
