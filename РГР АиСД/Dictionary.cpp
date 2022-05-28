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
    SetString trans = translations.at(english);
    if (!trans.deleteItem(russian))
    {
      return false;
    }
    return true;
  }
  catch (const std::invalid_argument&)
  {
    return false;
  }
}

bool Dictionary::deleteWord(const std::string& english)
{
  return translations.remove(english);
}

bool Dictionary::translate(const std::string& english)
{
  /*try
  {
    translations.at(english);
  }*/
  return true;
}

void Dictionary::print(std::ostream& out)
{
  translations.printValues(out);
}
