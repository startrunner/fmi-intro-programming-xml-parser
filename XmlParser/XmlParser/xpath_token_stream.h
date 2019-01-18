#pragma once
#include "pch.h"
#include <deque>

#include "token_stream.h"
#include "cached_token_stream.h"

class xpath_token_stream : public token_stream
{
    cached_token_stream innerStream;
public:
    xpath_token_stream(token_stream &innerStream) :
        innerStream(innerStream) {}

    virtual bool eof() override;
    virtual token next_token() override;
private:
    void skip_whitespace();
};
