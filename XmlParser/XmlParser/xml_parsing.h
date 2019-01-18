#pragma once
#include "xml_node.h"
#include "xml_token_stream.h"
std::vector<xml_node> parse_document(const std::string &xml);
std::vector<xml_node> parse_document(std::istream &xmlStream);
std::vector<xml_node> parse_document(xml_token_stream &tokenStream);