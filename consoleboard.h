#ifndef CONSOLEBOARD_H
#define CONSOLEBOARD_H
#include "types.h"

namespace ConsoleBoard
{

char to_char(Elements e);
Elements to_element(char c);

ElementsMatrix from_file(const char *str);

}

#endif // CONSOLEBOARD_H
