#include "assignmentproblem.h"
#include <iostream>
using namespace std;

IntMatrix get_m()
{
    IntMatrix m;
    m.resize(5, 5);
    int arr[5*5] = {
        12, 7, 9, 7, 9,
        8, 9, 6, 6, 6,
        7, 17, 12, 14, 9,
        15, 14, 6, 6, 10,
        4, 10, 7, 10, 9
    };

    int index = 0;
    for (auto &v: m) {
        v = arr[index++];
    }
    return m;
}

void test_assignmentproblem()
{
    IntMatrix m = get_m();
    auto p = AssignmentProblem::min_assignment<int>(m);
    cout<<"weight: "<<p.second<<endl;
    print(p.first);
}
