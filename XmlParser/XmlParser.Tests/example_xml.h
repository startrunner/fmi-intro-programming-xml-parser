#pragma once
#include "pch.h"
#include <tuple>
#include <string>
#include "../XmlParser/token.h"
#include "../XmlParser/xml_node.h"

const std::string  exampleXml{
    "<people>                                       \n"
    "    <person id = 0>                            \n"
    "       <name>   John Smith   </name>           \n"
    "       <address>USA</address>                  \n"
    "    </person>                                  \n"
    "    <person id = \"1\" egn = 1234567890>       \n"
    "       <name>Ivan Petrov</name>                \n"
    "       <address>Bulgaria</address>             \n"
    "    </person>                                  \n"
    "</people>                                      \n"
};

const xml_node exampleNode{
    "people",{},{
        xml_node{
            "person", {{"id", "0"}},{
                xml_node{"name", {}, "John Smith"},
                xml_node{"address", {}, "USA"}
            }
        },
        xml_node{
            "person", {{"id", "1"}, {"egn", "1234567890"}},{
                xml_node{"name", {}, "Ivan Petrov"},
                xml_node{"address", {}, "USA"}
            }
        },
    },
};

const std::vector<std::pair<token_type, std::string>> exampleTokens{
    {token_type::OPENING_SHARP, "<"},
    {token_type::IDENTIFIER, "people"},
    {token_type::CLOSING_SHARP, ">"},
    {token_type::WHITESPACE, {}},

    {token_type::OPENING_SHARP, "<"},
    {token_type::IDENTIFIER, "person"},
    {token_type::WHITESPACE, " "},
    {token_type::IDENTIFIER, "id"},
    {token_type::WHITESPACE, " "},
    {token_type::EQUALS_SIGN, "="},
    {token_type::WHITESPACE, " "},
    {token_type::LITERAL_NUMBER, "0"},
    {token_type::CLOSING_SHARP, ">"},
    {token_type::WHITESPACE, {}},

    {token_type::OPENING_SHARP, "<"},
    {token_type::IDENTIFIER, "name"},
    {token_type::CLOSING_SHARP, ">"},
    {token_type::WHITESPACE, "   "},
    {token_type::IDENTIFIER, "John"},
    {token_type::WHITESPACE, " "},
    {token_type::IDENTIFIER, "Smith"},
    {token_type::WHITESPACE, "   "},
    {token_type::OPENING_SHARP, "<"},
    {token_type::FORWARD_SLASH, "/"},
    {token_type::IDENTIFIER, "name"},
    {token_type::CLOSING_SHARP, ">"},
    {token_type::WHITESPACE, {}},

    {token_type::OPENING_SHARP, "<"},
    {token_type::IDENTIFIER, "address"},
    {token_type::CLOSING_SHARP, ">"},
    {token_type::IDENTIFIER, "USA"},
    {token_type::OPENING_SHARP, "<"},
    {token_type::FORWARD_SLASH, "/"},
    {token_type::IDENTIFIER, "address"},
    {token_type::CLOSING_SHARP, ">"},
    {token_type::WHITESPACE, ""},

    {token_type::OPENING_SHARP, "<"},
    {token_type::FORWARD_SLASH, "/"},
    {token_type::IDENTIFIER, "person"},
    {token_type::CLOSING_SHARP, ">"},
    {token_type::WHITESPACE, {}},

    {token_type::OPENING_SHARP, "<"},
    {token_type::IDENTIFIER, "person"},
    {token_type::WHITESPACE, ""},
    {token_type::IDENTIFIER, "id"},
    {token_type::WHITESPACE, " "},
    {token_type::EQUALS_SIGN, "="},
    {token_type::WHITESPACE, " "},
    {token_type::LITERAL_STRING, "\"1\""},
    {token_type::WHITESPACE, {}},
    {token_type::IDENTIFIER, "egn"},
    {token_type::WHITESPACE, {}},
    {token_type::EQUALS_SIGN, "="},
    {token_type::WHITESPACE, {}},
    {token_type::LITERAL_NUMBER, "1234567890"},
    {token_type::CLOSING_SHARP, ">"}
};

const std::vector<std::pair<token_type, std::string>> exampleXmlTokens{
    {token_type::OPENING_SHARP, "<"},
    {token_type::IDENTIFIER, "people"},
    {token_type::CLOSING_SHARP, ">"},
    {token_type::OPENING_SHARP, "<"},
    {token_type::IDENTIFIER, "person"},
    {token_type::IDENTIFIER, "id"},
    {token_type::EQUALS_SIGN, "="},
    {token_type::LITERAL_NUMBER, "0"},
    {token_type::CLOSING_SHARP, ">"},
    {token_type::OPENING_SHARP, "<"},
    {token_type::IDENTIFIER, "name"},
    {token_type::CLOSING_SHARP, ">"},
    {token_type::CONTENT, "John Smith"},
    {token_type::OPENING_SHARP, "<"},
    {token_type::FORWARD_SLASH, "/"},
    {token_type::IDENTIFIER, "name"},
    {token_type::CLOSING_SHARP, ">"},
    {token_type::OPENING_SHARP, "<"},
    {token_type::IDENTIFIER, "address"},
    {token_type::CLOSING_SHARP, ">"},
    {token_type::CONTENT, "USA"},
    {token_type::OPENING_SHARP, "<"},
    {token_type::FORWARD_SLASH, "/"},
    {token_type::IDENTIFIER, "address"},
    {token_type::CLOSING_SHARP, ">"}
};