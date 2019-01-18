#pragma once
#include "pch.h"
#include <deque>
#include "token_stream.h"
class text_token_stream : public token_stream
{
    int row = 1, column = 1;
    std::istream *text;

public:
    text_token_stream(std::istream &text) :
        text(&text) {}

    virtual bool eof()override;

    virtual token next_token() override;
};