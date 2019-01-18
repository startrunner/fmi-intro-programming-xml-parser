#pragma once
#include "pch.h"
#include "example_xpath.h"
#include "../XmlParser/text_token_stream.h"
using namespace std;

TEST(XPathParsing, ParseExample1)
{
    xpath_query parsed = parse_xpath_query(exampleXpath1);
    ASSERT_EQ(exampleQuery1, parsed);
}

TEST(XPathParsing, ParseExample2)
{
    auto parsed = parse_xpath_query(exampleXpath2);;
    ASSERT_EQ(exampleQuery2, parsed);
}

TEST(XPathParsing, ParseExample3)
{
    auto parsed = parse_xpath_query(exampleXpath3);;
    ASSERT_EQ(exampleQuery3, parsed);
}
