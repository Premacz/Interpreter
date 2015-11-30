#ifndef SCANNER_Header
#define SCANNER_Header

#include <stdio.h>

#include "errors.h"
#include "token.h"
#include "deque.h"

#define TOKEN_COUNT 30

//Externs
extern FILE * file_p;

typedef enum
{
	CAPITAL_A = 65,
	CAPITAL_Z = 90,
	LETTER_A = 97,
	LETTER_Z = 122,
	ZERO = 48,
	NINE = 57
} ascii_borders;

// ASCII hodnoty, bílé znaky
// Zavedení názvů pro znaky pro lepší orientaci
typedef enum
{
	NEW_LINE = 10,
	TAB = 9,
	SPACE = 32
} white_chars;

// STAVY KONEČNÉHO AUTOMATU
// Popis stavů konečného automatu, mezi nimiž program přechází
typedef enum
{
	FM_START,
	FM_END,

	FM_SEMICOLON,
	FM_HASH,
	FM_STAR,
	FM_PLUS,
	FM_MINUS,
	FM_DIVIDE,
	FM_ASSIGN,
	FM_EQUAL,
	FM_GREATER,
	FM_LESS,
	FM_G_EQUAL,
	FM_L_EQUAL,
	FM_NOT_EQUAL,
	FM_COMMA,
	FM_CODEWORD,
	FM_KEYWORDS,
	FM_IDENTIFIER,
	FM_PAR_L,
	FM_PAR_R,
	FM_BRACE_L,
	FM_BRACE_R,
	FM_BRACKET_L,
	FM_BRACKET_R,
	FM_OR,
	FM_AND,
	FM_STRING,
	FM_ESC_SQ,
	FM_INTEGER,
	FM_DOUBLE,
	FM_NUMBER,
	FM_OCT_NUM,
	FM_HEX_NUM,
	FM_BIN_NUM,
	FM_DECREMENT,
	FM_INCREMENT,

	FM_COMMENT_SINGLELINE,
	FM_COMMENT_MULTILINE,
	FM_COMMENT_MULTILINE_END,

	FM_UNRECOGNIZED,
	//---------------------------------------------------------------------------

	/*, FM_BOOL_ ... && ||*/
} fm_states;

//Functions
void Scann(Deque tokenQueue);

static const char *key_words[KEYWORD_COUNT] = {"auto", "cin", "cout", "double",
 "else", "for", "if", "int", "return", "string", "bool", "do", "while",
 "true", "false"};

#if DEBUG
static const char *tokenNames[TOKEN_COUNT] =
	{"UNDEFINED", "EOF", "SEMICOLN", "STAR", "PLUS", "MINUS", "DEVIDE", "ASSIGN", "EQUEAL", "EQUAL_LESS",
		"EQUAL_GREATER","EQUEAL_NOT", "LESS", "GREATER", "COMMA", "PAR_L", "PAR_R", "BRACE_L", "BRACE_R", "INSERTION",
		"EXTRACTION", "INT", "DOUBLE", "CHAR", "KEYWORLD_STRING", "KEYWORLD_INT", "KEYWORLD_DOUBLE", "KEYWORLD_CHAR", "KEYWORLD_STRING", "KEYWORLD_VOID",
		};
#endif

#endif