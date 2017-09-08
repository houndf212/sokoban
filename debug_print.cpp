﻿#include "debug_print.h"
#include "types.h"
#include "xsb.h"
#include "boardparam.h"
#include "movelist.h"
#include <iostream>
using namespace std;

template<>
void print(const Pos &p)
{
    cout<<"("<<p.row()<<","<<p.col()<<")"<<endl;
}

template<>
void print(const PosList &vec)
{
    cout<<"[";
    for (auto p : vec) {
        cout<<"("<<p.row()<<","<<p.col()<<"),";
    }
    cout<<"]"<<endl;
}

template<>
void print(const PosVector &vec)
{
    cout<<"[";
    for (auto p : vec) {
        cout<<"("<<p.row()<<","<<p.col()<<"),";
    }
    cout<<"]"<<endl;
}

template<>
void print(const IntMatrix &m)
{
    for (auto row=m.szero(); row<m.row_size(); ++row) {
        for (auto col=m.szero(); col<m.col_size(); ++col) {
            cout.width(2);
            cout<<m.get(Pos(row, col));
            cout<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
}

template<>
void print(const ElementsMatrix &m)
{
    for (auto row=m.szero(); row<m.row_size(); ++row) {
        for (auto col=m.szero(); col<m.col_size(); ++col) {
            auto e = m.get(Pos(row, col));
            cout<<XSB::e_to_char(e);
            cout<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
}

template<>
void print(const BoardParam &p)
{
    print(p.to_matrix());
}

template<>
void print(const MoveList &mlst)
{
    cout<<"[";
    for (auto d : mlst) {
        cout<<XSB::d_to_char(d)<<",";
    }
    cout<<"]"<<endl;
}
