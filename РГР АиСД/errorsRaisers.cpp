#include "errorsRaisers.hpp"
#include <stdexcept>

void raiseEmptyDicitonary()
{
  throw std::invalid_argument("<DICTIONARY IS EMPTY>\n");
}

void raiseUnexistingWord()
{
  throw std::invalid_argument("<NO SUCH WORD>\n");
}

void raiseUnexistingCommand()
{
  throw std::invalid_argument("<NO SUCH COMMAND>\n");
}
