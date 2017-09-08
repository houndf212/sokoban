#ifndef HUNGARIANALG_H
#define HUNGARIANALG_H
#include "types.h"
#include <algorithm>

template<class T>
class HungarianAlg
{
public:
    void solve(const Basic_Resize_Matrix<T, type_size> &m)
    {
        assert(m.row_size() == m.col_size());
        const auto size = m.row_size();

        //复制矩阵用来操作
        matrix = m;

        mask_matrix.fill(NORMAL);

        //先设置全部未标记
        row_mask.resize(size);
        clear_mask(row_mask);

        col_mask.resize(size);
        clear_mask(col_mask);

        // Follow the steps
        int step = 1;
        while ( step ) {
            switch ( step ) {
            case 1:
                step = step1();
                // step is always 2
                break;
            case 2:
                step = step2();
                // step is always either 0 or 3
                break;
            case 3:
                step = step3();
                // step in [3, 4, 5]
                break;
            case 4:
                step = step4();
                // step is always 2
                break;
            case 5:
                step = step5();
                // step is always 3
                break;
            }
        }
    }
//private:
    static void clear_mask(std::vector<bool> &mask)
    {
        std::fill(begin(mask), end(mask), false);
    }
    static void minimize_row(Basic_Resize_Matrix<T, type_size> &m);
    static void minimize_col(Basic_Resize_Matrix<T, type_size> &m);

    bool find_uncovered_zero_in_matrix(type_size &row, type_size &col)
    {
        for (row=matrix.szero(); row<matrix.row_size(); ++row) {
            if (row_mask[row])
                continue;

            for (col=matrix.szero(); col<matrix.col_size(); ++col) {
                if (col_mask[col])
                    continue;

                if (matrix.get(Pos(row, col)) == 0)
                    return true;
            }
        }
        return false;
    }

    bool star_in_row(int row, int &col)
    {
        for (col=mask_matrix.szero(); col<mask_matrix.col_size(); ++col) {
            if (mask_matrix.get(Pos(row, col)) == STAR) {
                return true;
            }
        }
        return false;
    }

    T find_smallest_in_uncover() const
    {
        auto h = matrix.vmax();
        for (auto row=matrix.szero(); row<matrix.row_size(); ++row) {
            if (row_mask[row])
                continue;

            for (auto col=matrix.szero(); col<matrix.col_size(); ++col) {
                if (col_mask[col])
                    continue;
                assert(matrix.get(Pos(row, col))!=0);
                h = std::min(h, matrix.get(Pos(row, col)));
            }
        }

        return h;
    }

    int step1()
    {
        std::vector<bool> row_cover(matrix.row_size(), false);
        std::vector<bool> col_cover(matrix.col_size(), false);

        for (auto row=matrix.szero(); row<matrix.row_size(); ++row) {
            if (row_cover[row])
                continue;

            for (auto col=matrix.szero(); col<matrix.col_size(); ++col) {
                if (col_cover[col])
                    continue;

                Pos p(row, col);
                if (matrix.get(p) == 0) {
                    mask_matrix.set(p, STAR);
                    row_cover[row] = true;
                    col_cover[col] = true;
                }
            }
        }

        return 2;
    }

    int step2()
    {
        int covercount = 0;
        for (auto row=mask_matrix.szero(); row<mask_matrix.row_size(); ++row) {
            for (auto col=mask_matrix.szero(); col<mask_matrix.col_size(); ++col) {
                if (STAR == mask_matrix.get(Pos(row, col))) {
                    col_mask[col] = true;
                    ++covercount;
                }
            }
        }

        assert(matrix.row_size() == matrix.col_size());
        if (covercount >= matrix.row_size()) {
            return 0;
        }

        return 3;
    }

    int step3()
    {
        if (find_uncovered_zero_in_matrix(saverow, savecol))
            mask_matrix.set(Pos(saverow, savecol), PRIME);
        else
            return 5;

        int col = -1;
        if (star_in_row(saverow, col)) {
            row_mask[saverow] = true;
            col_mask[col] = false;
            return 3;
        }
        return 4;
    }

    int step4()
    {
        PosVector seq;

        auto pos_in_vec = [&seq](const Pos& p) {
          return std::find(begin(seq), end(seq), p) != end(seq);
        };

        Pos z0(saverow, savecol);
        seq.push_back(z0);

        Pos z1(-1, -1);
        Pos z2n(-1, -1);

        type_size row;
        type_size col = savecol;

        bool madepair;
        do{
            madepair = false;
            for (row=0; row<mask_matrix.row_size(); ++row) {
                Pos p(row, col);
                if (mask_matrix.get(p) == STAR) {
                    z1 = p;
                    if (pos_in_vec(p))
                        continue;

                    madepair = true;
                    seq.push_back(z1);
                    break;
                }
            }

            if (!madepair)
                break;

            madepair = false;

            for (col=0; col<mask_matrix.col_size(); ++col) {
                Pos p(row, col);
                if (mask_matrix.get(p) == PRIME) {
                    z2n = p;
                    if (pos_in_vec(p))
                        continue;

                    madepair = true;
                    seq.push_back(z2n);
                    break;
                }
            }

        }while(madepair);

        for (const Pos &p : seq) {
            if (mask_matrix.get(p) == STAR)
                mask_matrix.set(p, NORMAL);
            else if (mask_matrix.get(p) == PRIME)
                mask_matrix.set(p, STAR);
        }

        for (auto row=mask_matrix.szero(); row<mask_matrix.row_size(); ++row) {
            for (auto col=mask_matrix.szero(); col<mask_matrix.col_size(); ++col) {
                Pos p(row, col);
                if (mask_matrix.get(p) == PRIME)
                    mask_matrix.set(p, NORMAL);
            }
        }

        clear_mask(row_mask);
        clear_mask(col_mask);
        return 2;
    }

    int step5()
    {
        auto h = find_smallest_in_uncover();

        for (auto row=matrix.szero(); row<matrix.row_size(); ++row) {
            if (row_mask[row]) {
                for (auto col=matrix.szero(); col<matrix.col_size(); ++col) {
                    Pos p(row, col);
                    matrix.set(p, matrix.get(p) + h);
                }
            }
        }

        for (auto col=matrix.szero(); col<matrix.col_size(); ++col) {
            if (!col_mask[col]) {
                for (auto row=matrix.szero(); row<matrix.row_size(); ++row) {
                    Pos p(row, col);
                    matrix.set(p, matrix.get(p) - h);
                }
            }
        }

        return 3;
    }

private:
    IntMatrix mask_matrix;
    Basic_Resize_Matrix<T, type_size> matrix;
    std::vector<bool> row_mask;
    std::vector<bool> col_mask;
    type_size saverow = 0;
    type_size savecol = 0;

private:
    static constexpr int NORMAL = 0;
    static constexpr int STAR   = 1;
    static constexpr int PRIME  = 2;
};

template<class T>
void HungarianAlg<T>::minimize_row(Basic_Resize_Matrix<T, type_size> &m)
{
    assert(m.row_size()>=2 && m.col_size()>=2);
    for (auto row=m.szero(); row<m.row_size(); ++row) {

        auto min_val = m.get(Pos(row, 0));
        for (auto col=m.szero(); col<m.col_size(); ++col) {
            min_val = std::min(min_val, m.get(Pos(row, col)));
        }

        for (auto col=m.szero(); col<m.col_size(); ++col) {
            Pos p(row, col);
            m.set(p, m.get(p)-min_val);
        }
    }
}

template<class T>
void HungarianAlg<T>::minimize_col(Basic_Resize_Matrix<T, type_size> &m)
{
    assert(m.row_size()>=2 && m.col_size()>=2);

    for (auto col=m.szero(); col<m.col_size(); ++col) {

        auto min_val = m.get(Pos(0, col));
        for (auto row=m.szero(); row<m.row_size(); ++row) {
            min_val = std::min(min_val, m.get(Pos(row, col)));
        }

        for (auto row=m.szero(); row<m.row_size(); ++row) {
            Pos p(row, col);
            m.set(p, m.get(p)-min_val);
        }
    }
}







#endif // HUNGARIANALG_H
