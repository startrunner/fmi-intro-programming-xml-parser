#pragma once
#include "token.h"
class token_stream
{
public:
    virtual bool eof() = 0;
    virtual token next_token() = 0;
};