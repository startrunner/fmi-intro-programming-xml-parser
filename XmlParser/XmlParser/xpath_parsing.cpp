#include "pch.h"
#include <sstream>
#include "xpath_parsing.h"
#include "text_token_stream.h"
#include "xpath_token_stream.h"
using namespace std;

bool remove_forward_slashes(cached_token_stream &tokenStream);
bool try_parse_segment(cached_token_stream &tokenStream, xpath_query_segment &segment);
xpath_query parse_xpath_query(cached_token_stream &tokenStream);
bool try_parse_attribute_filter(cached_token_stream &tokenStream, xpath_attribute_filter &filter);
bool try_parse_index(cached_token_stream &tokenStream, optional<int> &index);
bool try_parse_identifier(cached_token_stream &tokenStream, string &identifier, bool allowAsterisk = false);
bool try_parse_attribute_selector(cached_token_stream &tokenStream, string &attributeSelector);
bool try_parse_qualifier_set(
    cached_token_stream &tokenStream,
    optional<int> &index,
    vector<string> &attributeSelectors,
    vector<string> &mandatoryAttributes,
    vector<xpath_attribute_filter> &attributeFilters
);

xpath_query parse_xpath_query(const std::string & queryString)
{
    stringstream queryStringStream{ queryString };
    return parse_xpath_query(queryStringStream);
}

xpath_query parse_xpath_query(std::istream &queryStringStream)
{
    text_token_stream textTokenStream{ queryStringStream };
    xpath_token_stream xpathTokenStream{ textTokenStream };
    cached_token_stream cachedTokenStream{ xpathTokenStream };
    return parse_xpath_query(cachedTokenStream);
}

xpath_query parse_xpath_query(cached_token_stream &tokenStream)
{
    if (tokenStream.eof())throw runtime_error("empty xpath request!");

    bool isRelativeToRoot = (tokenStream.peek(0).type == token_type::FORWARD_SLASH);

    vector<xpath_query_segment> segments;

    xpath_query_segment segment;
    remove_forward_slashes(tokenStream);
    while (try_parse_segment(tokenStream, segment))
    {
        segments.push_back(segment);
        remove_forward_slashes(tokenStream);
    }

    return xpath_query{ isRelativeToRoot, segments };
}

bool remove_forward_slashes(cached_token_stream &tokenStream)
{
    while (tokenStream.try_cache(1) && tokenStream.peek(0).type == token_type::FORWARD_SLASH)
    {
        tokenStream.next_token();
    }
    return !tokenStream.eof();
}

bool try_parse_segment(cached_token_stream &tokenStream, xpath_query_segment &segment)
{
    string identifier;
    if (!try_parse_identifier(tokenStream, identifier, true))return false;

    segment.index = nullptr;
    segment.attributeSelectors.clear();
    segment.attributeExistenceRequirements.clear();
    segment.attributeValueFiters.clear();

    try_parse_qualifier_set(
        tokenStream,
        segment.index,
        segment.attributeSelectors,
        segment.attributeExistenceRequirements,
        segment.attributeValueFiters
    );
    segment.elementName = identifier;
}


bool try_parse_qualifier_set(
    cached_token_stream &tokenStream,
    optional<int> &index,
    vector<string> &attributeSelectors,
    vector<string> &mandatoryAttributes,
    vector<xpath_attribute_filter> &attributeFilters
)
{
    bool validOpeningSquare =
        tokenStream.try_cache(1) &&
        tokenStream.peek(0).type == token_type::OPENING_SQUARE;
    if (!validOpeningSquare)return false;

    bool immediatelyClosed =
        tokenStream.try_cache(2) &&
        tokenStream.peek(1).type == token_type::CLOSING_SQUARE;

    if (immediatelyClosed)
    {
        for (int i = 0; i < 2; i++)tokenStream.next_token();
        return true;
    }

    string mandatoryAttribute;
    string attributeSelector;
    xpath_attribute_filter filter;
    bool parsedAnything;
    token openingSquare = tokenStream.next_token();

    do
    {
        if (try_parse_attribute_selector(tokenStream, attributeSelector))
        {
            attributeSelectors.push_back(attributeSelector);
        }
        else if (try_parse_attribute_filter(tokenStream, filter))
        {
            attributeFilters.push_back(filter);
        }
        else if (try_parse_identifier(tokenStream, mandatoryAttribute))
        {
            mandatoryAttributes.push_back(mandatoryAttribute);
        }
        else if (try_parse_index(tokenStream, index)) {}
        ///...
        else throw runtime_error("unexpected tokens");
    } while (!tokenStream.eof() && tokenStream.peek(0).type != token_type::CLOSING_SQUARE);

    if (tokenStream.eof())throw runtime_error("unexpected eof");
    token closingSquare = tokenStream.next_token();
    return true;
}

const map<pair<token_type, token_type>, xpath_filter_type> comparisons{
    {{token_type::EQUALS_SIGN, token_type::LITERAL_NUMBER}, xpath_filter_type::EQUALS_NUMERIC},
    {{token_type::EQUALS_SIGN, token_type::LITERAL_STRING}, xpath_filter_type::EQUALS_TEXT},
    {{token_type::OPENING_SHARP, token_type::LITERAL_NUMBER}, xpath_filter_type::LESS_THAN_NUMERIC},
    {{token_type::OPENING_SHARP, token_type::LITERAL_STRING}, xpath_filter_type::LESS_THAN_TEXT},
    {{token_type::CLOSING_SHARP, token_type::LITERAL_NUMBER}, xpath_filter_type::GREATER_THAN_NUMERIC},
    {{token_type::OPENING_SHARP, token_type::LITERAL_STRING}, xpath_filter_type::GREATER_THAN_TEXT}
};

bool try_parse_attribute_filter(cached_token_stream &tokenStream, xpath_attribute_filter &filter)
{
    bool success =
        tokenStream.try_cache(3) &&
        tokenStream.peek(0).type == token_type::IDENTIFIER &&
        (tokenStream.peek(1).type == token_type::EQUALS_SIGN || tokenStream.peek(1).type == token_type::OPENING_SHARP || tokenStream.peek(1).type == token_type::CLOSING_SHARP) &&
        (tokenStream.peek(2).type == token_type::LITERAL_NUMBER || tokenStream.peek(2).type == token_type::LITERAL_STRING);
    if (!success)return false;

    token identifier = tokenStream.next_token();
    token comparison = tokenStream.next_token();
    token literal = tokenStream.next_token();

    filter.attributeName = identifier.text();
    filter.filterType = comparisons.at({ comparison.type, literal.type });
    filter.queryValue = literal.get_literal_value();
    return true;
}

bool try_parse_attribute_selector(cached_token_stream &tokenStream, string &attributeSelector)
{
    bool success =
        tokenStream.try_cache(2) &&
        tokenStream.peek(0).type == token_type::AT_SIGN&&
        tokenStream.peek(1).type == token_type::IDENTIFIER;
    if (!success)return false;

    token atSign = tokenStream.next_token();
    token identifier = tokenStream.next_token();
    attributeSelector = identifier.text();
    return true;
}

bool try_parse_index(cached_token_stream &tokenStream, optional<int> &index)
{
    bool success =
        tokenStream.try_cache(1) &&
        tokenStream.peek(0).type == token_type::LITERAL_NUMBER;
    if (!success)return false;

    index = stoi(tokenStream.next_token().text());
    return true;
}

bool try_parse_identifier(cached_token_stream &tokenStream, string &identifier, bool allowAsterisk)
{
    bool validIdentifier =
        tokenStream.try_cache(1) &&
        (tokenStream.peek(0).type == token_type::IDENTIFIER || (allowAsterisk &&tokenStream.peek(0).type == token_type::ASTERISK));
    if (!validIdentifier)return false;

    identifier = tokenStream.next_token().text();
    if (identifier == "*" && allowAsterisk)
    {
        if (tokenStream.try_cache(1) && tokenStream.peek(0).type == token_type::ASTERISK)
        {
            identifier += tokenStream.next_token().text();
        }
    }

    return true;

}
