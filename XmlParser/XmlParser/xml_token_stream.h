#pragma once
#include <deque>
#include "tokenization.h"
#include "text_token_stream.h"
#include "cached_token_stream.h"

class xml_token_stream : public token_stream
{
    int reverseBracketDepth = 0;
    cached_token_stream innerStream;

    void* handle = nullptr;

public:
    xml_token_stream(token_stream &innerStream) :
        innerStream(innerStream), reverseBracketDepth(0) {}

    virtual bool eof() override;
    virtual token next_token() override;

    ~xml_token_stream() { delete handle; }
private:
    bool is_in_content_mode()const;
    void skip_whitespace();
};