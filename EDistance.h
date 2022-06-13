// Copyright 2022 Ahmed Shahen
#pragma once
#include "Matrix.h"
#include <iostream>
#include <algorithm>
#include <string>

class EDistance {
 public:
    explicit EDistance(std::string seq1, std::string seq2);
    static int penalty(char a, char b);
    int optDistance();
    std::string alignment();
    void printMatrix();
    ~EDistance();
 private:
    std::string x;
    std::string y;
    Matrix* opt;
};
