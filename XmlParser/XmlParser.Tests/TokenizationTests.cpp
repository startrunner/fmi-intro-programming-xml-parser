#include "pch.h"
#include <tuple>
#include <string>
#include <sstream>
#include "example_xml.h"

#include "../XmlParser/token.h"
#include "../XmlParser/xml_token_stream.h"

using namespace std;

TEST(Tokenization, ExampleXml) 
{
    std::stringstream xmlStream{ exampleXml };
    text_token_stream tokenStream{ xmlStream };

    size_t i = 0;
    while (!tokenStream.eof() && i < exampleTokens.size())
    {
        auto currentToken = tokenStream.next_token();
        EXPECT_EQ((int)exampleTokens[i].first, (int)currentToken.type);
        if (exampleTokens[i].second != "")
        {
            EXPECT_EQ(exampleTokens[i].second, currentToken.text());
        }
        i++;
    }

    EXPECT_EQ(1, 1);
    EXPECT_TRUE(true);
}

TEST(XMLTokenization, ExampleXml)
{
    stringstream text{ exampleXml };
    text_token_stream tokenStream{ text };
    xml_token_stream xmlTokenStream{ tokenStream };

    size_t i = 0;
    while (!xmlTokenStream.eof() && i < exampleXmlTokens.size())
    {
        auto currentToken = xmlTokenStream.next_token();
        EXPECT_EQ((int)exampleXmlTokens[i].first, (int)currentToken.type);
        EXPECT_EQ(exampleXmlTokens[i].second, currentToken.text());
        i++;
    }
}