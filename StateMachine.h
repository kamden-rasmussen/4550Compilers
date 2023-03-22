#include "Token.h"

enum MachineState {
    START_STATE, 
    IDENTIFIER_STATE,
    INTEGER_STATE, 
    LINE_COMMENT_STATE,
    BLOCK_COMMENT_STATE,
    BLOCK_COMMENT_ENDING_STATE,

    LEFT_PAREN_STATE, 
    RIGHT_PAREN_STATE, 
    LEFT_CURLY_STATE, 
    RIGHT_CURLY_STATE, 
    SEMICOLON_STATE, 
    ASSIGNMENT_STATE, 

    PLUS_STATE,
    PEQUALS_STATE,
    MINUS_STATE, 
    MEQUALS_STATE,
    MULTIPLY_STATE,
    DIVIDE_STATE,
    EQUALS_STATE,
    NOT_STATE,
    NOTEQUAL_STATE,

    AND_STATE,
    OR_STATE,
    AND_TEMP_STATE,
    OR_TEMP_STATE,

    LESS_THEN_STATE,
    GREATER_THEN_STATE,
    LESS_EQUAL_STATE,
    GREATER_EQUAL_STATE,

    INSERTION_STATE, 
    
    ENDFILE_STATE, 
    CANTMOVE_STATE, 
    LAST_STATE
};

enum CharacterType {
	LETTER_CHAR, 
    DIGIT_CHAR, 
    WHITESPACE_CHAR, 
    FORWARD_SLASH_CHAR,

    LEFT_PAREN_CHAR,
    RIGHT_PAREN_CHAR,
    LEFT_CURLY_CHAR,
    RIGHT_CURLY_CHAR,

    SEMICOLON_CHAR,
    ASSIGNMENT_CHAR,

    PLUS_CHAR,
    MINUS_CHAR,
    EQUALS_CHAR,
    MULTIPLY_CHAR,
    NOT_CHAR,

    LESS_THEN_CHAR,
    GREATER_THEN_CHAR,

    AND_CHAR,
    OR_CHAR,

    NEWLINE_CHAR,
    ENDFILE_CHAR,
    BAD_CHAR,
	LAST_CHAR
};

class StateMachineClass
{
public:
	StateMachineClass();
	MachineState UpdateState(char currentCharacter, TokenType &
previousTokenType);

private:
	MachineState mCurrentState;

	// The matrix of legal moves:
	MachineState mLegalMoves[LAST_STATE][LAST_CHAR];

	// Which end-machine-states correspond to which token types.
	// (non end states correspond to the BAD_TOKEN token type)
	TokenType mCorrespondingTokenTypes[LAST_STATE];
};