#pragma once
#include "pch.h"
#include "optional.h"

enum class xpath_filter_type
{
    EQUALS_NUMERIC,
    LESS_THAN_NUMERIC,
    GREATER_THAN_NUMERIC,
    EQUALS_TEXT,
    LESS_THAN_TEXT,
    GREATER_THAN_TEXT
};

struct xpath_attribute_filter
{
    std::string attributeName;
    xpath_filter_type filterType;
    std::string queryValue;

    bool execute(const std::string &documentValue)const;
    bool operator ==(const xpath_attribute_filter &other)const { return !(*this != other); }
    bool operator !=(const xpath_attribute_filter &other)const;

    xpath_attribute_filter() {}

    xpath_attribute_filter(
        std::string attributeName,
        xpath_filter_type filterType,
        std::string queryValue
    ) :
        attributeName(attributeName),
        filterType(filterType),
        queryValue(queryValue) {}
};