#include "Token.h"


TokenClass::TokenClass() {
    TokenType mType;
    string mLexeme;
}

TokenClass::TokenClass(TokenType type, const string & lexeme) {
    mType = type;
    mLexeme = lexeme;
}

// TokenType GetTokenType() const { return mType; }
TokenType TokenClass::GetTokenType() const {
    // MSG(gTokenTypeNames[mType]);
    return mType;
}

// const string & GetTokenTypeName() const { return gTokenTypeNames[mType]; }
const string &TokenClass::GetTokenTypeName() const {
    return gTokenTypeNames[mType];
}

// string GetLexeme() const { return mLexeme; }
string TokenClass::GetLexeme() const {
    return mLexeme;
}

// void CheckReserved();
void TokenClass::CheckReserved() {
    if (mLexeme == "void") {
        mType = VOID_TOKEN;
    } else if (mLexeme == "main") {
        mType = MAIN_TOKEN;
    } else if (mLexeme == "int") {
        mType = INT_TOKEN;
    } else if (mLexeme == "cout") {
        mType = COUT_TOKEN;
    } else if (mLexeme == "print") {
        mType = PRINT_TOKEN;
    } else if (mLexeme == "if") {
        mType = IF_TOKEN;
    } else if (mLexeme == "else") {
        mType = ELSE_TOKEN;
    } else if (mLexeme == "while") {
        mType = WHILE_TOKEN;
    } else if (mLexeme == "and"){
        mType = AND_TOKEN;
    }
}

const string & TokenClass::GetTokenTypeName(TokenType type) {
    return gTokenTypeNames[type];
}

std::ostream &operator<<(std::ostream &out, const TokenClass &tc)
{
    out << tc.GetTokenTypeName() << " " << tc.GetLexeme();
    return out;
}