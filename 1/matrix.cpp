#include <iostream>
#include "matrix.h"

namespace mtr{

    void input(Matrix& matrix){
        std::cout << "Enter number of rows >> " << std::endl;
        try{
            matrix.rows = getNum<int>(0);
            std::cout << "Enter number of columns >> " << std::endl;
            matrix.columns = getNum<int>(0);
            matrix.indptr.push_back(0);
            int cnt = 0;
            for(int i = 0; i < matrix.rows; ++i){
                for(int j = 0; j < matrix.columns; ++j){
                    std::cout << "Enter the elements in [" << i+1 << "][" << j+1 << "] >>" << std::endl;
                    double p = getNum<double>(-400000000);
                    if(p != 0){ //in i line j column
                        matrix.data.push_back(p);
                        matrix.index.push_back(j);
                        ++cnt;
                    }
                }
                matrix.indptr.push_back(cnt);
            }

        }
        catch (...){
            throw;
        }
        return;
    }

    void output(const char* msg, const mtr::Matrix& mtr){
        std::cout << msg << std::endl;
        int a, b = 0;
        for(int i = 0; i < mtr.rows; ++i){
            a = mtr.indptr[i+1] - mtr.indptr[i];
            for(int j = 0; j < mtr.columns; ++j){
                if(b < static_cast<int>(mtr.index.size()) and a > 0 and mtr.index[b] == j){
                    std::cout << mtr.data[b] << ' ';
                    ++b;
                    --a;
                    continue;
                }
                std::cout << 0 << ' ';
            }
            std::cout << std::endl;
        }
    }

    void f1(const double& a, int& b, bool t){
        if(t) { //true
            if (a > 0) {
                ++b;
            }
            return;
        }
        if (a < 0) {
            ++b;
        }
    }

    void f2(int& max, int cnt, int& x, int i){
        if(max < cnt){
            max = cnt;
            x = i;
        }
    }

    void swap(mtr::Matrix& mtr, int x, int y, int shift){ //x - pointer to 1 word, y - pointer to 2 word
        // dist - distance between words, shift - num of elements to 2[y] word
        // x is righter from y
        if(!mtr.rows or !mtr.columns)
        	throw std::logic_error("Empty matrix");
        int cq1 = mtr.indptr[x+1] - mtr.indptr[x], cq2 = mtr.indptr[y+1] - mtr.indptr[y];
        int dist = mtr.indptr[x] - mtr.indptr[y];
        for(int i = 0; i < cq1; ++i){  // x to begin
            for(int j = dist+shift; j > shift; --j){
                mtr::swap(mtr.data[i+j], mtr.data[i+j-1]);
                mtr::swap(mtr.index[i+j], mtr.index[i+j-1]);
            }
        }


        for(int i = 0; i < cq2; ++i){ // y to end
            for(int j = shift+cq1+cq2; j < dist+shift+cq1; ++j){
                mtr::swap(mtr.data[j-i-1], mtr.data[j-i]);
                mtr::swap(mtr.index[j-i-1], mtr.index[j-i]);
            }
        }

    }

    void swap_(mtr::Matrix& mtr, int p, bool t){
    	if(!mtr.rows or !mtr.columns)
    		throw std::logic_error("Empty matrix");                    // p - №(row)-1
        Vector<int>& ptr = mtr.indptr;
        int cq = ptr[p+1] - ptr[p];
        int f = ptr[1] - ptr[0];
        int l = ptr[mtr.rows] - ptr[mtr.rows-1], z;
        if(t){ // positive

            swap(mtr, p, 0, 0);

            z = cq - f;
            ptr[1] = cq;
            for(int i = 2; i <= p; ++i){ // p = №(rows)-1
                ptr[i] += z;
            }
            return;
        }

        swap(mtr, (mtr.rows)-1, p, ptr[p]);

        z = l - cq;
        for(int i = p+1; i <= mtr.rows; ++i){ // p = №(rows)-1
            ptr[i] += z;
        }
        ptr[mtr.rows] = ptr[mtr.rows-1] + cq;
    }

    void minmax(mtr::Matrix& mtr){

        int pst_m = 0, ngt_m = 0;
        int ptr = 0, x = 0, y = 0;
        for(int i = 0; i < mtr.rows; ++i){
            int ngt_c = 0, pst_c = 0;
            for(int j = 0; j < mtr.indptr[i+1] - mtr.indptr[i]; ++j){ // numerous of values in [i] row
                f1(mtr.data[ptr],pst_c, true);
                f1(mtr.data[ptr], ngt_c, false);
                ++ptr;

            }
            f2(pst_m, pst_c, x, i); // x and y - №(row)-1
            f2(ngt_m, ngt_c, y, i);
        }
        // we have pointers x and y to rows with max number of positive and negative numerous
        swap_(mtr, x, true); //pst,
        swap_(mtr, y, false); //ngt
    }

}
