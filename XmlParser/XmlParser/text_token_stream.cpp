#include "pch.h"
#include "token.h"
#include "text_token_stream.h"
using namespace std;

const unordered_map<char, token_type> TERMINAL_CHARS = {
    {'<', token_type::OPENING_SHARP},
    {'>', token_type::CLOSING_SHARP},
    {'[', token_type::OPENING_SQUARE},
    {']', token_type::CLOSING_SQUARE},
    {'@', token_type::AT_SIGN},
    {'=', token_type::EQUALS_SIGN},
    {'/', token_type::FORWARD_SLASH},
    {'*', token_type::ASTERISK}
};

string parse_generic(
    istream &text,
    function<bool(char)> continuationRule,
    int &row, int &column
);

string parse_text_literal(istream &text, int &row, int &column);

string parse_single_char(
    istream &text,
    int &row, int &column
);


bool text_token_stream::eof() { return text->eof(); }

token text_token_stream::next_token()
{
    if (text->eof())
    {
        throw runtime_error("EOF reached; Cannot parse any more tokens.");
    }

    char nextChar = text->peek();
    auto foundTerminal = TERMINAL_CHARS.find(nextChar);

    if (foundTerminal != TERMINAL_CHARS.end())
    {
        text->get();
        return token(
            foundTerminal->second,
            text_position(row, column++, 1)
        );
    }
    else if (isspace(nextChar))
    {
        int tokenRow = row, tokenColumn = column;
        string spaceText = parse_generic(*text, isspace, row, column);
        return token(
            token_type::WHITESPACE,
            text_position(tokenRow, tokenColumn, spaceText.size()),
            spaceText
        );
    }
    else if (isalpha(nextChar) || nextChar == '_')
    {
        int tokenRow = row, tokenColumn = column;
        string identifierText = parse_generic(
            *text,
            [](char c) { return isalnum(c) || c == '_' || c == '-'; },
            row, column
        );
        return token(
            token_type::IDENTIFIER,
            text_position(tokenRow, tokenColumn, identifierText.size()),
            identifierText
        );
    }
    else if (isdigit(nextChar))
    {
        int tokenRow = row, tokenColumn = column;
        string numberText = parse_generic(
            *text,
            [](char c) {return isdigit(c) || c == '.'; },
            row, column
        );
        return token(
            token_type::LITERAL_NUMBER,
            text_position(tokenRow, tokenColumn, numberText.size()),
            numberText
        );
    }
    else if (nextChar == '\'' || nextChar == '"')
    {
        int tokenRow = row, tokenColumn = column;
        string textLiteralValue = parse_text_literal(*text, row, column);
        return token(
            token_type::LITERAL_STRING,
            text_position(tokenRow, tokenColumn, textLiteralValue.size()),
            textLiteralValue
        );
    }
    else
    {
        int tokenRow = row, tokenColumn = column;
        string tokenText = parse_single_char(*text, row, column);
        return token(
            token_type::UNKNOWN_CHARACTER,
            text_position(tokenRow, tokenColumn, tokenText.size()),
            tokenText
        );
    }
    //else throw runtime_error("unknown character '" + to_string(nextChar) + "'.");
}

string parse_single_char(
    istream &text,
    int &row, int &column
)
{
    char character = text.get();
    if (character == '\n') { row++; column = 1; }
    else column++;

    return to_string(character);
}

string parse_generic(
    istream &text,
    function<bool(char)> continuationRule,
    int &row, int &column
)
{
    stringstream result;

    while (!text.eof() && continuationRule(text.peek()))
    {
        char currentChar = text.get();
        if (currentChar == '\n') { row++; column = 1; }
        else column++;

        result << currentChar;
    }

    return result.str();
}

string parse_text_literal(istream &text, int &row, int &column)
{
    stringstream literalText;
    char quoteChar = text.get();
    literalText << quoteChar;
    char x;
    do
    {
        x = text.get();
        literalText << x;
    } while (x != quoteChar);

    return literalText.str();
}