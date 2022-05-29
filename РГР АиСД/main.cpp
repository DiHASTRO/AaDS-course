#include <iostream>
#include <functional>
#define TEST_MODE
#include "RBT.hpp"
#include "SetString.hpp"
#include "Dictionary.hpp"

int main()
{
  Dictionary dict;

  while (!std::cin.eof())
  {
    std::string command = "";
    std::cout << "Command: ";
    std::cin >> command;
    if (command == "INSERT")
    {
      std::string eng;
      std::cout << "English: ";
      std::cin >> eng;
      std::string rus;
      std::cout << "Russian: ";
      std::cin >> rus;

      dict.insertTranslate(eng, rus);
    }
    else if (command == "PRINT_ALL")
    {
      dict.print(std::cout);
    }
    else if (command == "DELETE_ENGLISH")
    {
      std::string eng;
      std::cout << "English: ";
      std::cin >> eng;
      if (!dict.deleteWord(eng))
      {
        std::cout << "No such word!\n";
      }
    }
    else if (command == "TRANSLATE")
    {
      std::string eng;
      std::cout << "English: ";
      std::cin >> eng;
      if (!dict.translate(eng, std::cout))
      {
        std::cout << "No such word!\n";
      }
    }
    else if (command == "DELETE_TRANSLATE")
    {
      std::string eng;
      std::cout << "English: ";
      std::cin >> eng;
      std::string rus;
      std::cout << "Russian: ";
      std::cin >> rus;
      if (!dict.deleteTranslate(eng, rus))
      {
        std::cout << "No such word!\n";
      }
    }
    else
    {
      std::cout << "No such command!\n";
    }
  }
  return 0;
}
