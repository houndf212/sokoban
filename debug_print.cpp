#include "debug_print.h"
#include "types.h"
#include "consoleboard.h"
#include <iostream>
using namespace std;

template<>
void print(const Pos &p)
{
    cout<<"("<<p.row()<<","<<p.col()<<")"<<endl;
}

template<>
void print(const ElementsMatrix &m)
{
    for (auto row=0; row<m.row_size(); ++row) {
        for (auto col=0; col<m.col_size(); ++col) {
            auto e = m.get(Pos(row, col));
            cout<<ConsoleBoard::to_char(e);
            cout<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
}
