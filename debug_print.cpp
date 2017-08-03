#include "debug_print.h"
#include "types.h"
#include <iostream>
using namespace std;

template<>
void print(const Pos &p)
{
    cout<<"("<<p.x()<<","<<p.y()<<")"<<endl;
}
