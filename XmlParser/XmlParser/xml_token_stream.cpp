#include "pch.h"
#include "xml_token_stream.h"
using namespace std;

bool isspace(const string &s)
{
    for (char c : s)if (!isspace(c))return false;
    return true;
}


string trim(const string &s)
{
    int firstNonSpace = s.size(), lastNonSpace = 0;
    for (int i = 0; i < s.size() && firstNonSpace == s.size(); i++)if (!isspace(s[i]))firstNonSpace = i;
    if (firstNonSpace == s.size())return "";
    for (int i = s.size() - 1; i >= 0 && lastNonSpace == 0; i--)if (!isspace(s[i]))lastNonSpace = i;
    return { s.begin() + firstNonSpace, s.begin() + lastNonSpace + 1 };
}

int max(int x, int y) { return (x > y) ? x : y; }

bool xml_token_stream::eof()
{
    if (innerStream.eof())return true;
    for (int i = 0; innerStream.try_cache(i + 1); i++)
    {
        if (innerStream.peek(i).type != token_type::WHITESPACE)return false;
    }
    return true;
}


token xml_token_stream::next_token()
{
    if (eof())throw runtime_error("inner stream->eof");

    if (is_in_content_mode())
    {
        innerStream.try_cache(10);
        stringstream contentStream{};
        auto firstTokenPosition = innerStream.peek(0).position;
        int contentTokens = 0;

        for (int i = 0; innerStream.try_cache(i + 1) && innerStream.peek(i).type != token_type::OPENING_SHARP;i++)
        {
            contentStream << innerStream.peek(i).text();
            contentTokens++;
        }

        string content = contentStream.str();

        if (!isspace(content))
        {
            for (int i = 0; i < contentTokens; i++)innerStream.next_token();
            token token{
                token_type::CONTENT,
                text_position(
                    firstTokenPosition.row,
                    firstTokenPosition.column,
                    content.size()
                ),
                trim(content)
            };
            ;
            return token;
        }
    }

    skip_whitespace();
    token token = innerStream.next_token();

    if (token.type == token_type::CLOSING_SHARP)reverseBracketDepth++;
    else if (token.type == token_type::OPENING_SHARP)reverseBracketDepth = max(reverseBracketDepth - 1, 0);


    return token;

}

bool xml_token_stream::is_in_content_mode() const
{
    return reverseBracketDepth != 0;
}

void xml_token_stream::skip_whitespace()
{
    while (!innerStream.eof())
    {
        auto peek = innerStream.peek(0);
        if (peek.type != token_type::WHITESPACE)break;
        innerStream.next_token();
    }
}