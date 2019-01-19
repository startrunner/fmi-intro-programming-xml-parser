#include "pch.h"
#include <stack>
#include <string>
#include <sstream>
#include "xml_parsing.h"
#include "tokenization.h"
#include "text_token_stream.h"
#include "xml_token_stream.h"
#include "cached_token_stream.h"
using namespace std;

string get_literal_value(token);
bool try_parse_content(cached_token_stream &tokenStream, string &content);
bool try_parse_node_footer(cached_token_stream &tokenStream, string openingTagName);
bool try_parse_attribute(cached_token_stream &tokenStream, string &key, string &value);
bool try_parse_node_header(cached_token_stream &tokenStream, string &tagName, map<string, string> &attributes);
bool try_parse_child_or_content(cached_token_stream &tokenStream, stringstream &content, vector<xml_node> &children);

vector<xml_node> parse_document(const string & xml)
{
    stringstream xmlStream{ xml };
    return parse_document(xmlStream);
}

vector<xml_node> parse_document(istream & xmlStream)
{
    text_token_stream tokenStream{ xmlStream };
    xml_token_stream xmlTokenStream{ tokenStream };
    return parse_document(xmlTokenStream);
}

bool try_parse_node(cached_token_stream &tokenStream, xml_node &node);
vector<xml_node> parse_document(xml_token_stream & tokenStream)
{
    vector<xml_node> nodes;

    xml_node node;
    cached_token_stream cachedStream{ tokenStream };
    while (try_parse_node(cachedStream, node))
    {
        nodes.push_back(node);
        node = xml_node{};
    }
    return nodes;
}

bool try_parse_node(cached_token_stream &tokenStream, xml_node &node)
{
    string tagName;
    map<string, string> attributes;
    vector<xml_node> children;
    stringstream content;

    if (!try_parse_node_header(tokenStream, tagName, attributes))return false;
    while (try_parse_child_or_content(tokenStream, content, children)) {}
    if (!try_parse_node_footer(tokenStream, tagName))
    {
        throw runtime_error("tag '" + tagName + "' not closed properly");
    }

    node.name = tagName;
    node.content = content.str();
    node.children = children;
    node.attributes = attributes;
    return true;
}

bool try_parse_child_or_content(cached_token_stream &tokenStream, stringstream &content, vector<xml_node> &children)
{
    xml_node child;
    string contentPiece;

    if (try_parse_node(tokenStream, child))
    {
        children.push_back(child);
        return true;
    }
    else if (try_parse_content(tokenStream, contentPiece))
    {
        content << contentPiece << ' ';
        return true;
    }
    else return false;
}

bool try_parse_content(cached_token_stream &tokenStream, string &content)
{
    content = "";
    if (!tokenStream.try_cache(1))return false;
    if (tokenStream.peek(0).type != token_type::CONTENT)return false;

    token contentToken = tokenStream.next_token();
    content = contentToken.text();
    return true;
}

bool try_parse_node_header(cached_token_stream &tokenStream, string &tagName, map<string, string> &attributes)
{
    tagName = "";
    attributes.clear();

    if (!tokenStream.try_cache(2))return false;
    if (tokenStream.peek(0).type != token_type::OPENING_SHARP)return false;
    if (tokenStream.peek(1).type != token_type::IDENTIFIER)return false;
    
    token opening = tokenStream.next_token();
    token identifier = tokenStream.next_token();

    tagName = identifier.text();
    for (string key, value; try_parse_attribute(tokenStream, key, value);)
    {
        attributes[key] = value;
    }

    bool tagClosed =
        tokenStream.try_cache(1) &&
        tokenStream.peek(0).type == token_type::CLOSING_SHARP;

    if (!tagClosed)throw runtime_error("tag header of '" + identifier.text() + "' not closed.");
    token terminatingBracket = tokenStream.next_token();

    return true;
}

bool try_parse_node_footer(cached_token_stream &tokenStream, string openingTagName)
{
    if (!tokenStream.try_cache(4))return false;
    bool success =
        tokenStream.peek(0).type == token_type::OPENING_SHARP&&
        tokenStream.peek(1).type == token_type::FORWARD_SLASH&&
        tokenStream.peek(2).type == token_type::IDENTIFIER&&
        tokenStream.peek(2).text() == openingTagName &&
        tokenStream.peek(3).type == token_type::CLOSING_SHARP;

    if (success)for (int i = 0; i < 4; i++)tokenStream.next_token();

    return success;
}

bool try_parse_attribute(cached_token_stream &tokenStream, string &key, string &value)
{
    if (!tokenStream.try_cache(1))return false;
    if (tokenStream.peek(0).type != token_type::IDENTIFIER)return false;

    bool hasExplicitValue =
        tokenStream.try_cache(3) &&
        tokenStream.peek(1).type == token_type::EQUALS_SIGN &&
        (tokenStream.peek(2).type == token_type::LITERAL_NUMBER || tokenStream.peek(2).type == token_type::LITERAL_STRING);

    token identifier = tokenStream.next_token();
    key = identifier.text();

    if (hasExplicitValue)
    {
        token assignment = tokenStream.next_token();
        token literal = tokenStream.next_token();
        value = literal.get_literal_value();
    }
    else value = "1";

    return true;
}