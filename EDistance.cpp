// Copyright 2022 Ahmed Shaheen
#include "EDistance.h"
#include "Matrix.h"
#include <iostream>
#include <iomanip>

// valgrind ./EDistance

EDistance::EDistance(std::string seq1, std::string seq2) {
    x = seq1;
    y = seq2;
    opt = new Matrix(seq1.size()+1, seq2.size()+1);
    // std::cout << "sequence 1:" << x << std::endl;
    // std::cout << "sequence 2:" << y << std::endl;
}

int EDistance::penalty(char a, char b) {
    // Returns penalty cost for aligning chars a and b
    return(a == b ? 0 : 1);
}

int EDistance::optDistance() {
    // populates matrix based on having 2 strings and returns
    // optimal distance
    // use a nested loop that calculates opt[i][j]
    int i, j;              // size_t causes a seg fault
    int M = x.size();    // column
    int N = y.size();    // row

    for (i = M-1; i >= 0; i--) {
        opt->at(i, N) = 2 * (M-i);
    }
    for (j = N-1; j >= 0; j--) {
        opt->at(M, j) = 2 * (N-j);
    }

    // Lambda since min is only used once
    auto min = [](int a, int b, int c) -> int { return ((a <= b ) ?
    (a <= c ? a : c) : (b <= c ? b : c));};

    // populate rest of the matrix
    for (i = M-1; i >= 0; i--) {
        for (j = N-1; j >= 0; j--) {
            opt->at(i, j) = min(opt->at(i+1, j+1) + penalty(x.at(i), y.at(j)),
            opt->at(i+1, j) + 2, opt->at(i, j+1) + 2);
        }
    }
    return opt->at(0, 0);   // [0][0];
}

void EDistance::printMatrix() {   // To print OptDistance Matrix for debugging
    size_t i, j;
    for (i = 0; i < opt->height(); i++) {
        for (j = 0; j < opt->width(); j++) {
            std::cout << std::right << std::setw(3)
            << opt->at(i, j) << " ";   // from now on use at
        }
        std::cout << std::endl;
    }
}

std::string EDistance::alignment() {
    // Traces matrix and prints string of actual alignment
    int i = 0, j = 0;
    int M = x.size();
    int N = y.size();
    std::ostringstream ret_str;   // output stream

    while (i < M || j < N) {    // Moving towards opt[M][N]
        if (i < M && j < N && opt->at(i,
        j) == opt->at(i+1, j+1) + penalty(x[i], y[j])) {
            // case 1: matching x[i] with y[j], opt[i][j] = opt[i+1][j+1] + 1
            ret_str << x[i] << " " << y[j] << " " << penalty(x[i],
            y[j]) << std::endl;
            i++;
            j++;
        } else if (opt->at(i, j) == opt->at(i+1, j) + 2) {
            // case 2: matches x[i] with a gap, opt[i][j] = opt[i+1][j] + 2
            ret_str << x[i] << " - "  << "2\n";
            i++;
        } else if (opt->at(i, j) == opt->at(i, j+1) + 2) {
            // case 3: matches y[j] with a gap, opt[i][j] = opt[i][j+1] + 2
            ret_str << "- " << y[j] << " 2\n";
            j++;
        }
    }
    
    return ret_str.str();
}

EDistance::~EDistance() {
    delete opt;
}

