#include "StateMachine.h"
#include <cctype>
using namespace std;

StateMachineClass::StateMachineClass(){

    mCurrentState = START_STATE;
    for (int i = 0; i < LAST_STATE; i++)
        for (int j = 0; j < LAST_CHAR; j++)
            this->mLegalMoves[i][j] = CANTMOVE_STATE;

    this->mLegalMoves[START_STATE][DIGIT_CHAR] = INTEGER_STATE;
    this->mLegalMoves[START_STATE][LETTER_CHAR] = IDENTIFIER_STATE;
    this->mLegalMoves[START_STATE][WHITESPACE_CHAR] = START_STATE;
    this->mLegalMoves[START_STATE][NEWLINE_CHAR] = START_STATE;

    this->mLegalMoves[START_STATE][LEFT_PAREN_CHAR] = LEFT_PAREN_STATE;
    this->mLegalMoves[START_STATE][RIGHT_PAREN_CHAR] = RIGHT_PAREN_STATE;
    this->mLegalMoves[START_STATE][LEFT_CURLY_CHAR] = LEFT_CURLY_STATE;
    this->mLegalMoves[START_STATE][RIGHT_CURLY_CHAR] = RIGHT_CURLY_STATE;

    this->mLegalMoves[START_STATE][EQUALS_CHAR] = ASSIGNMENT_STATE;
    this->mLegalMoves[ASSIGNMENT_STATE][EQUALS_CHAR] = EQUALS_STATE;
    this->mLegalMoves[START_STATE][PLUS_CHAR] = PLUS_STATE;
    this->mLegalMoves[PLUS_STATE][EQUALS_CHAR] = PEQUALS_STATE;
    this->mLegalMoves[START_STATE][MINUS_CHAR] = MINUS_STATE;
    this->mLegalMoves[MINUS_STATE][EQUALS_CHAR] = MEQUALS_STATE;
    this->mLegalMoves[START_STATE][FORWARD_SLASH_CHAR] = DIVIDE_STATE;

    this->mLegalMoves[START_STATE][AND_CHAR] = AND_TEMP_STATE;
    this->mLegalMoves[START_STATE][OR_CHAR] = OR_TEMP_STATE;

    // line comments
    this->mLegalMoves[DIVIDE_STATE][FORWARD_SLASH_CHAR] = LINE_COMMENT_STATE;
    for (int s = 0; s < LAST_CHAR; s++)
        this->mLegalMoves[LINE_COMMENT_STATE][s] = LINE_COMMENT_STATE;
    this->mLegalMoves[LINE_COMMENT_STATE][NEWLINE_CHAR] = START_STATE;

    // block comments
    this->mLegalMoves[DIVIDE_STATE][MULTIPLY_CHAR] = BLOCK_COMMENT_STATE;
    for (int s = 0; s < LAST_CHAR; s++){
        this->mLegalMoves[BLOCK_COMMENT_STATE][s] = BLOCK_COMMENT_STATE;
    }
    this->mLegalMoves[BLOCK_COMMENT_STATE][MULTIPLY_CHAR] = BLOCK_COMMENT_ENDING_STATE;
    for (int s = 0; s < LAST_CHAR; s++){
        this->mLegalMoves[BLOCK_COMMENT_ENDING_STATE][s] = BLOCK_COMMENT_STATE;
    }
    this->mLegalMoves[BLOCK_COMMENT_ENDING_STATE][MULTIPLY_CHAR] = BLOCK_COMMENT_ENDING_STATE;
    this->mLegalMoves[BLOCK_COMMENT_ENDING_STATE][FORWARD_SLASH_CHAR] = START_STATE;

    this->mLegalMoves[START_STATE][MULTIPLY_CHAR] = MULTIPLY_STATE;
    this->mLegalMoves[MULTIPLY_STATE][EQUALS_CHAR] = MULTIPLY_STATE;
    this->mLegalMoves[START_STATE][LESS_THEN_CHAR] = LESS_THEN_STATE;
    this->mLegalMoves[LESS_THEN_STATE][EQUALS_CHAR] = LESS_EQUAL_STATE;
    this->mLegalMoves[LESS_THEN_STATE][LESS_THEN_CHAR] = INSERTION_STATE;
    this->mLegalMoves[START_STATE][GREATER_THEN_CHAR] = GREATER_THEN_STATE;
    this->mLegalMoves[GREATER_THEN_STATE][EQUALS_CHAR] = GREATER_EQUAL_STATE;
    this->mLegalMoves[START_STATE][NOT_CHAR] = NOT_STATE;
    this->mLegalMoves[NOT_STATE][EQUALS_CHAR] = NOTEQUAL_STATE;

    this->mLegalMoves[AND_TEMP_STATE][AND_CHAR] = AND_STATE;
    this->mLegalMoves[OR_TEMP_STATE][OR_CHAR] = OR_STATE;

    this->mLegalMoves[START_STATE][SEMICOLON_CHAR] = SEMICOLON_STATE;
    this->mLegalMoves[INTEGER_STATE][DIGIT_CHAR] = INTEGER_STATE;
    this->mLegalMoves[IDENTIFIER_STATE][DIGIT_CHAR] = IDENTIFIER_STATE;
    this->mLegalMoves[IDENTIFIER_STATE][LETTER_CHAR] = IDENTIFIER_STATE;
    this->mLegalMoves[START_STATE][ENDFILE_CHAR] = ENDFILE_STATE;

    // Begin tokens
    for (int i = 0; i < LAST_STATE; i++){
        this->mCorrespondingTokenTypes[i] = BAD_TOKEN;
    }
    this->mCorrespondingTokenTypes[IDENTIFIER_STATE] = IDENTIFIER_TOKEN;
    this->mCorrespondingTokenTypes[INTEGER_STATE] = INTEGER_TOKEN;
    this->mCorrespondingTokenTypes[SEMICOLON_STATE] = SEMICOLON_TOKEN;

    this->mCorrespondingTokenTypes[LEFT_PAREN_STATE] = LEFT_PAREN_TOKEN;
    this->mCorrespondingTokenTypes[RIGHT_PAREN_STATE] = RIGHT_PAREN_TOKEN;
    this->mCorrespondingTokenTypes[LEFT_CURLY_STATE] = LEFT_CURLY_TOKEN;
    this->mCorrespondingTokenTypes[RIGHT_CURLY_STATE] = RIGHT_CURLY_TOKEN;

    this->mCorrespondingTokenTypes[LESS_THEN_STATE] = LESS_TOKEN;
    this->mCorrespondingTokenTypes[LESS_EQUAL_STATE] = LESS_EQUAL_TOKEN;
    this->mCorrespondingTokenTypes[GREATER_THEN_STATE] = GREATER_TOKEN;
    this->mCorrespondingTokenTypes[GREATER_EQUAL_STATE] = GREATER_EQUAL_TOKEN;
    this->mCorrespondingTokenTypes[EQUALS_STATE] = EQUAL_TOKEN;
    this->mCorrespondingTokenTypes[NOTEQUAL_STATE] = NOTEQUAL_TOKEN;

    this->mCorrespondingTokenTypes[AND_STATE] = AND_TOKEN;
    this->mCorrespondingTokenTypes[OR_STATE] = OR_TOKEN;

    this->mCorrespondingTokenTypes[INSERTION_STATE] = INSERTION_TOKEN;
    this->mCorrespondingTokenTypes[ASSIGNMENT_STATE] = ASSIGNMENT_TOKEN;

    this->mCorrespondingTokenTypes[PLUS_STATE] = PLUS_TOKEN;
    this->mCorrespondingTokenTypes[MINUS_STATE] = MINUS_TOKEN;
    this->mCorrespondingTokenTypes[DIVIDE_STATE] = DIVIDE_TOKEN;
    this->mCorrespondingTokenTypes[MULTIPLY_STATE] = TIMES_TOKEN;

    this->mCorrespondingTokenTypes[ENDFILE_STATE] = ENDFILE_TOKEN;
 
}
MachineState StateMachineClass::UpdateState(char currentCharacter, TokenType & previousTokenType){

    CharacterType charType;

    if (isalpha(currentCharacter))
        charType = LETTER_CHAR;
    else if (isdigit(currentCharacter))
        charType = DIGIT_CHAR;
    else if (currentCharacter == '\n')
        charType = NEWLINE_CHAR;
    else if (isspace(currentCharacter))
        charType = WHITESPACE_CHAR;
    else{
        switch (currentCharacter){
            case '(':
                charType = LEFT_PAREN_CHAR;
                break;
            case ')':
                charType = RIGHT_PAREN_CHAR;
                break;
            case '{':
                charType = LEFT_CURLY_CHAR;
                break;
            case '}':   
                charType = RIGHT_CURLY_CHAR;
                break;
            case ';':
                charType = SEMICOLON_CHAR;
                break;
            case '+':
                charType = PLUS_CHAR;
                break;
            case '-':
                charType = MINUS_CHAR;
                break;
            case '*':
                charType = MULTIPLY_CHAR;
                break;
            case '/':
                charType = FORWARD_SLASH_CHAR;
                break;
            case '<':
                charType = LESS_THEN_CHAR;
                break;
            case '>':
                charType = GREATER_THEN_CHAR;
                break;
            case '=':
                charType = EQUALS_CHAR;
                break;
            case '!':
                charType = NOT_CHAR;
                break;
            case '&':
                charType = AND_CHAR;
                break;
            case '|':
                charType = OR_CHAR;
                break;
            case EOF:
                charType = ENDFILE_CHAR;
                break;
            default:
                charType = BAD_CHAR;
                break;
        }
    }

	previousTokenType = mCorrespondingTokenTypes[mCurrentState];
	mCurrentState = mLegalMoves[mCurrentState][charType];
	return mCurrentState;
}