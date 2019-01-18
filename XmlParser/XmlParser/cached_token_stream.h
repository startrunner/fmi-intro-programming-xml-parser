#pragma once
#include "pch.h"
#include <deque>

#include "token_stream.h"

class cached_token_stream : public token_stream
{
    token_stream *innerStream;
    std::deque<token> peekCache;

public:
    cached_token_stream(token_stream &innerStream) :
        innerStream(&innerStream) {}

    virtual bool eof() override;
    virtual token next_token() override;

    bool try_cache(int count);
    token peek(int index);
};
