#include "pch.h"
#include "token.h"
#include <unordered_map>
using namespace std;

const unordered_map<token_type, string> TERMINAL_VALUES{
    {token_type::EQUALS_SIGN, "="},
    {token_type::AT_SIGN, "@"},
    {token_type::OPENING_SHARP, "<"},
    {token_type::CLOSING_SHARP, ">"},
    {token_type::OPENING_SQUARE, "["},
    {token_type::CLOSING_SQUARE, "]"},
    {token_type::FORWARD_SLASH, "/"},
    {token_type::ASTERISK, "*"}
};

string token::text() const
{
    if (is_terminal())
    {
        auto result = TERMINAL_VALUES.find(this->type);
        if (result == TERMINAL_VALUES.end())throw runtime_error("Non-terminal token of type" + to_string((int)type) + " has no value!");
        return result->second;
    }
    return mText;
}

bool token::is_terminal()const { return mText.empty(); }

string token::get_literal_value() const
{
    if (type == token_type::LITERAL_NUMBER)return text();
    if (type == token_type::LITERAL_STRING)
    {
        string literalText = text();
        return { literalText.begin() + 1, literalText.end() - 1 };
    }
    else throw runtime_error("this token is not a literal");
}
