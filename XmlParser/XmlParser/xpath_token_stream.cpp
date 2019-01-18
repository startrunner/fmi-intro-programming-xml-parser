#include "pch.h"
#include "xpath_token_stream.h"
using namespace std;

bool xpath_token_stream::eof()
{
    skip_whitespace();
    return innerStream.eof();
}

token xpath_token_stream::next_token()
{
    skip_whitespace();
    return innerStream.next_token();
}

void xpath_token_stream::skip_whitespace()
{
    while (!innerStream.eof() && innerStream.peek(0).type == token_type::WHITESPACE)
    {
        innerStream.next_token();
    }
}