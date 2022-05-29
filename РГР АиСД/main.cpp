// #define TEST_MODE

#ifdef TREE_OUT
#define COLORFUL
#endif

#include <iostream>
#include <functional>
#include "RBT.hpp"
#include "SetString.hpp"
#include "Dictionary.hpp"


int main()
{
#ifdef TEST_MODE
  RBT< int, int, IntComparator > numbers;
  for (int i = 0; i < 1000000; i++)
  {
    iter = 0;
    numbers.insert(i, i);
    if (i % 10000 == 0)
    {
      std::cout << iter << '\n';
    }
  }
#elif defined TREE_OUT
  RBT< int, int, IntComparator > numbers;
  for (int i = 0; i < 100; i++)
  {
    numbers.insert(i, i);
  }
  numbers.printTree(std::cout);
#else
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
      if (!dict.empty())
      {
        dict.print(std::cout);
      }
      else
      {
        std::cout << "<DICTIONARY IS EMPTY>\n";
      }
    }
    else if (command == "DELETE_ENGLISH")
    {
      std::string eng;
      std::cout << "English: ";
      std::cin >> eng;
      if (!dict.deleteWord(eng))
      {
        std::cout << "<NO SUCH WORD>\n";
      }
    }
    else if (command == "TRANSLATE")
    {
      std::string eng;
      std::cout << "English: ";
      std::cin >> eng;
      if (!dict.translate(eng, std::cout))
      {
        std::cout << "<NO SUCH WORD>\n";
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
        std::cout << "<NO SUCH WORD>\n";
      }
    }
    else
    {
      std::cout << "<NO SUCH COMMAND>\n";
    }
  }
#endif
  return 0;
}
