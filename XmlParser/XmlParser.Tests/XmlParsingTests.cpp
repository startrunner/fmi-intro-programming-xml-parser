#include "pch.h"
#include <vector>
#include "example_xml.h"

#include "../XmlParser/xml_parsing.h"

#pragma once


TEST(XMLParsing, ExampleXml)
{
    std::vector<xml_node> parsed = parse_document(exampleXml);
    ASSERT_EQ(1, parsed.size());
    ASSERT_EQ(exampleNode, parsed.front());
}