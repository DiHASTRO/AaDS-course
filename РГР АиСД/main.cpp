// #define TREE_OUT

#ifdef TREE_OUT
  #define COLORFUL
#endif

#include <iostream>
#include "Dictionary.hpp"
#include "Executors.hpp"

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
  numbers.printTree(std::cout);
  std::cout << '\n' << numbers.at(10) << '\n';
#else
  Dictionary dict;

  while (!std::cin.eof())
  {
    std::string command = "";
    std::cout << "Command: ";
    std::cin >> command;
    try
    {
      executeCommand(dict, command, std::cout, std::cin);
    }
    catch (const std::invalid_argument& e)
    {
      std::cerr << e.what() << '\n';
    }
  }
#endif
  return 0;
}
