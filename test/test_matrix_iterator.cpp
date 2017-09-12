#include "types.h"
#include "debug_print.h"

void test_set(IntMatrix &mat)
{
    auto pair = mat.range();
    int n=1;
    for (auto it=pair.begin; it!=pair.end; ++it) {
        *it = n++;
    }
}

void test_get(const IntMatrix &mat)
{
    auto pair = mat.range();
    for (auto it=pair.begin; it!=pair.end; ++it) {
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

void test_row_set(IntMatrix &mat)
{
    int n=100;
    auto range = mat.row_range(0);
    for (auto it=range.begin; it!=range.end; ++it) {
        *it = n;
        n+=100;
    }
}

void test_row_get(const IntMatrix &mat)
{
    auto range = mat.row_range(0);
    for (auto it=range.begin; it!=range.end; ++it) {
        qDebug() << *it;
    }
}

void test_col_set(IntMatrix &mat)
{
    int n=1000;
    auto range = mat.col_range(1);
    for (auto it=range.begin; it!=range.end; ++it) {
        *it = n;
        n+=1000;
    }
}

void test_col_get(const IntMatrix &mat)
{
    auto range = mat.col_range(1);
    for (auto it=range.begin; it!=range.end; ++it) {
        qDebug() << *it;
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

    test_row_set(mat);
    print(mat);
    test_row_get(mat);

    test_col_set(mat);
    print(mat);
    test_col_get(mat);

}
