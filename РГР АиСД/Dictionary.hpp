#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP

#include "RBT.hpp"
#include "Set.hpp"
#include "Comparators.hpp"

class Dictionary
{
public:
  bool insertTranslate(const std::string& english, const std::string& russian);
  bool deleteTranslate(const std::string& english, const std::string& russian);
  bool deleteWord(const std::string& english);
  bool translate(const std::string& english, std::ostream& out);
  void print(std::ostream& out);

  bool empty() const;
private:
  using SetString = Set< std::string, StringComparator >;
  RBT< std::string, SetString, StringComparator > translations;
};

#endif
