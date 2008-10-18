#pragma once
#ifndef LEXER_H_
#define LEXER_H_
/*
 * $Id: Parser.h 143 2007-11-19 21:00:42Z michael.haupt $
 *
Copyright (c) 2007 Michael Haupt, Tobias Pape
Software Architecture Group, Hasso Plattner Institute, Potsdam, Germany
http://www.hpi.uni-potsdam.de/swa/

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
  */
#include <istream>
#include <string>
#include "../misc/defs.h"

typedef enum {
    NONE, Integer, Not, And, Or, Star, Div, Mod, Plus,
    Minus, Equal, More, Less, Comma, At, Per, NewBlock,
    EndBlock, Colon, Period, Exit, Assign, NewTerm, EndTerm, Pound,
    Primitive, Separator, STString, Identifier, Keyword, KeywordSequence,
    OperatorSequence
} Symbol;
static const char* symnames[] = {
    "NONE", "Integer", "Not", "And", "Or", "Star", "Div", "Mod", "Plus",
    "Minus", "Equal", "More", "Less", "Comma", "At", "Per", "NewBlock",
    "EndBlock", "Colon", "Period", "Exit", "Assign", "NewTerm", "EndTerm",
    "Pound", "Primitive", "Separator", "STString", "Identifier", "Keyword",
    "KeywordSequence", "OperatorSequence"
};

class Lexer {

public:
	Lexer(istream& file);
    Lexer(const pString& stream);
	~Lexer();
	Symbol      GetSym(void);
	Symbol      Peek(void);
	pString     GetText(void);
	pString     GetNextText(void);
	pString     GetRawBuffer(void);


private:
	int         fillBuffer(void);
	void        skipWhiteSpace(void);
	void        skipComment(void);	
	
	Lexer &operator=(const Lexer& /*src*/)
	{
	}

	istream& infile;

    pString stringInput;

	Symbol sym;
	char symc;
    //TODO: change this to a stream or something
	char text[BUFSIZ];

	bool peekDone;
	Symbol nextSym;
	char nextSymc;
    //^^
	char nextText[BUFSIZ];
	
	std::string buf;
	unsigned int bufp;
};

#endif
