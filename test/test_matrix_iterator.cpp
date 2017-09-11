#include "types.h"
#include "debug_print.h"

void test_set(IntMatrix &mat)
{
    auto pair = mat.range();
    int n=1;
    for (auto it=pair.first; it!=pair.second; ++it) {
        *it = n++;
    }
}

void test_get(const IntMatrix &mat)
{
    auto pair = mat.range();
    for (auto it=pair.first; it!=pair.second; ++it) {
        qDebug() << *it;
    }
}

void test_for_set(IntMatrix &mat)
{
    int n=10;
    for (auto& v : mat) {
        v = n;
        n+=10;
    }
}

void test_for_get(const IntMatrix &mat)
{
    for (auto& v : mat) {
        qDebug() << v;
    }
}
void test_matrix_iterator()
{
    IntMatrix mat;
    mat.resize(3, 3);

    test_set(mat);
    print(mat);
    test_get(mat);

    test_for_set(mat);
    print(mat);
    test_for_get(mat);
}
