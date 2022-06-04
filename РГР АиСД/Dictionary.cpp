#include "Dictionary.hpp"
#include "Transformators.hpp"

bool Dictionary::insertTranslate(const std::string& english, const std::string& russian)
{
  SetString temp;
  temp.insertItem(russian);
  translations.insert_or_transform(english, temp, SetTransformator{ temp });
  return true;
}

bool Dictionary::deleteTranslate(const std::string& english, const std::string& russian)
{
  try
  {
    SetString& trans = translations.at(english);
    if (!trans.deleteItem(russian))
    {
      return false;
    }
    return true;
  }
  catch (const std::out_of_range&)
  {
    return false;
  }
}

bool Dictionary::deleteWord(const std::string& english)
{
  return translations.remove(english);
}

bool Dictionary::translate(const std::string& english, std::ostream& out)
{
  try
  {
    SetString setStr;
    setStr = translations.at(english);
    out << setStr << '\n';
    return true;
  }
  catch (const std::out_of_range&)
  {
    return false;
  }
}

void Dictionary::print(std::ostream& out)
{
  translations.printValues(out);
}

bool Dictionary::empty() const
{
  return translations.empty();
}
