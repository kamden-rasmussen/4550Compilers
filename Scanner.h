#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include "Token.h"
#include "StateMachine.h"
#include "Debug.h"

class ScannerClass
{

public:
    ScannerClass(std::string input);
    ~ScannerClass();
    TokenClass GetNextToken();
    TokenClass PeekNextToken();
    int getLineNumber();

private:
    std::ifstream mFin;
    int mLineNumber;
    std::string mFileName;
};