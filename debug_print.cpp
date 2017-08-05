﻿#include "debug_print.h"
#include "types.h"
#include "xsb.h"
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
    for (auto row=m.zero(); row<m.row_size(); ++row) {
        for (auto col=m.zero(); col<m.col_size(); ++col) {
            auto e = m.get(Pos(row, col));
            cout<<XSB::e_to_char(e);
            cout<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
}
