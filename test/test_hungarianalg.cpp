#include "hungarianalg.h"
#include <ctime>
#include <cstdlib>
typedef HungarianAlg<IntMatrix::value_type> Hun;

IntMatrix rand_matrix()
{
    std::srand(std::time(0));
    IntMatrix m;
    m.resize(4, 4);

    for (auto row=m.szero(); row<m.row_size(); ++row) {
        for (auto col=m.szero(); col<m.col_size(); ++col) {
            Pos p(row, col);
            int val = rand() % 100;
            m.set(p, val);
        }
    }
    return m;
}


void test_minimize()
{
    auto m = rand_matrix();
    print(m);

    Hun::minimize_row(m);
    print(m);

    Hun::minimize_col(m);
    print(m);
}
void test_HungarianAlg()
{
    test_minimize();
}
