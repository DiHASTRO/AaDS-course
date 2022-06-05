#include "Executors.hpp"
#include <iostream>
#include "errorsRaisers.hpp"

void executeCommand(Dictionary& dict, const std::string& command, std::ostream& out, std::istream& in)
{
  if (command == "INSERT")
  {
    std::string eng;
    out << "English: ";
    in >> eng;
    std::string rus;
    out << "Russian: ";
    in >> rus;

    dict.insertTranslate(eng, rus);
  }
  else if (command == "PRINT_ALL")
  {
    if (!dict.empty())
    {
      dict.print(out);
    }
    else
    {
      raiseEmptyDicitonary();
    }
  }
  else if (command == "DELETE_ENGLISH")
  {
    std::string eng;
    out << "English: ";
    in >> eng;
    if (!dict.deleteWord(eng))
    {
      raiseUnexistingWord();
    }
  }
  else if (command == "TRANSLATE")
  {
    std::string eng;
    out << "English: ";
    in >> eng;
    if (!dict.translate(eng, out))
    {
      raiseUnexistingWord();
    }
  }
  else if (command == "DELETE_TRANSLATE")
  {
    std::string eng;
    out << "English: ";
    in >> eng;
    std::string rus;
    out << "Russian: ";
    in >> rus;
    if (!dict.deleteTranslate(eng, rus))
    {
      raiseUnexistingWord();
    }
  }
  else
  {
    raiseUnexistingCommand();
  }
}
