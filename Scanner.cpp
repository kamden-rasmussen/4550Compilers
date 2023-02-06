#include "Scanner.h"

ScannerClass::ScannerClass(std::string input)
    : mFileName(input), mLineNumber(1)
{
    MSG("initializing ScannerClass constructor");
    mFin.open(mFileName, std::ios::binary);
    if (!mFin)
    {
        std::cout << "could not open: " << input << std::endl;
        exit(EXIT_FAILURE);
    }
}

ScannerClass::~ScannerClass()
{
    MSG("closing the file stream");
    mFin.close();
}

int ScannerClass::getLineNumber()
{
    return mLineNumber;
}

TokenClass ScannerClass::getNextToken()
{
    StateMachineClass sm = StateMachineClass();
    MachineState state;
    char nextChar;
    TokenType type;
    std::string lexeme = "";
    do
    {
        nextChar = this->mFin.get();
        // MSG("nextChar: " << nextChar);
        state = sm.UpdateState(nextChar, type);
        lexeme += nextChar;
        if (state == START_STATE)
        {
            lexeme = "";
        }
        if (nextChar == '\n' && state != CANTMOVE_STATE)
        {
            this->mLineNumber++;
        }
    } while (state != CANTMOVE_STATE);

    this->mFin.unget();
    lexeme.pop_back();
    if (type == BAD_TOKEN)
    {
        std::cerr << "Error. BAD_TOKEN from lexeme " << lexeme;
        exit(EXIT_FAILURE);
    }
    TokenClass token = TokenClass(type, lexeme);
    token.CheckReserved();
    return token;
}

TokenClass ScannerClass::peekNextToken()
{
    std::streampos pos = mFin.tellg();
    int line = mLineNumber;
    TokenClass token = getNextToken();
    if (!mFin)
    {
        mFin.clear();
    }
    mFin.seekg(pos);
    mLineNumber = line;
    return token;
}