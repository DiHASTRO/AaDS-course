#define TREE_OUT

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
    numbers.insert(i, i * i);
    if (i % 10000 == 0)
    {
      std::cout << iter << '\n';
    }
  }
  std::cout << numbers.at(999999);
#elif defined TREE_OUT
  RBT< int, double, IntComparator > numbers;
  for (int i = 0; i < 100; i++)
  {
    numbers.insert(i, 1.0 * i * i);
  }
  for (int i = 0; i < 100; i++)
  {
    numbers.insert_or_transform(i, 1.0 * i * i, [&](double curr, double curr1)
      {
        curr = std::powl(curr, 1.5);
      });
  }

  numbers.printTree(std::cout);
  std::cout << '\n' << numbers.at(3) << '\n';
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
