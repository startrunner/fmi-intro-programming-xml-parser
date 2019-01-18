#pragma once
#include <string>
#include "position_info.h"

enum class token_type : int
{
	IDENTIFIER, //pesho
	OPENING_SHARP, //<
	CLOSING_SHARP, //>
	OPENING_SQUARE, //[
	CLOSING_SQUARE, //]
	LITERAL_NUMBER, //42
	LITERAL_STRING, //"gosho"
	AT_SIGN, //@
	EQUALS_SIGN, //=
	WHITESPACE, //not black space
	FORWARD_SLASH, ///
    CONTENT,
    ASTERISK,//*
    UNKNOWN_CHARACTER,
};

