#ifndef XSB_H
#define XSB_H
#include "types.h"
#include <string>

//描述 xsb格式

namespace XSB
{
char e_to_char(Elements e);
Elements char_to_e(char c);

char d_to_char(Direction d);
Direction char_to_d(char c);

//给外围无用的floor设置为wall
void replace_outer_floor(ElementsMatrix &m);

//去掉多余的墙
ElementsMatrix remove_outer_wall(ElementsMatrix m);

ElementsMatrix from_file(const char *filestr);
void to_file(const ElementsMatrix &m, const char *filestr);
std::string to_string(const ElementsMatrix &m);

}

#endif // XSB_H
