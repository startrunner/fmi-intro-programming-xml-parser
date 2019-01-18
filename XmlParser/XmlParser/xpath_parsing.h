#pragma once
#include "pch.h"
#include <string>
#include "xpath_query.h"
#include "xpath_token_stream.h"

xpath_query parse_xpath_query(const std::string &queryString);
xpath_query parse_xpath_query(std::istream &queryStringStream);
