#pragma once
#include "pch.h"
#include "optional.h"
#include "xpath_attribute_filter.h"
struct xpath_query_segment
{
    optional<int> index;
    optional<std::string> elementName;
    std::vector<xpath_attribute_filter> attributeValueFiters;
    std::vector<std::string> attributeExistenceRequirements;
    std::vector<std::string> attributeSelectors;

    bool operator !=(const xpath_query_segment &other)const;
    bool operator == (const xpath_query_segment &other)const { return !(*this != other); }

    xpath_query_segment(){}

    xpath_query_segment(
        std::vector<xpath_attribute_filter> attributeValueFilters,
        std::vector<std::string> attributeExistenceRequirements,
        std::vector<std::string> attributeSelectors
    ) :
        attributeValueFiters(attributeValueFilters),
        attributeExistenceRequirements(attributeExistenceRequirements), 
        attributeSelectors(attributeSelectors) {}

    xpath_query_segment(
        int index,
        std::vector<xpath_attribute_filter> attributeValueFilters,
        std::vector<std::string> attributeExistenceRequirements,
        std::vector<std::string> attributeSelectors
    ) :
        index(index),
        attributeValueFiters(attributeValueFilters),
        attributeExistenceRequirements(attributeExistenceRequirements),
        attributeSelectors(attributeSelectors) {}

    xpath_query_segment(
        std::string elementName,
        std::vector<xpath_attribute_filter> attributeValueFilters,
        std::vector<std::string> attributeExistenceRequirements,
        std::vector<std::string> attributeSelectors
    ) :
        elementName(elementName),
        attributeValueFiters(attributeValueFilters),
        attributeExistenceRequirements(attributeExistenceRequirements),
        attributeSelectors(attributeSelectors) {}

    xpath_query_segment(
        std::string elementName,
        int index,
        std::vector<xpath_attribute_filter> attributeValueFilters,
        std::vector<std::string> attributeExistenceRequirements,
        std::vector<std::string> attributeSelectors
    ) :
        index(index),
        elementName(elementName),
        attributeValueFiters(attributeValueFilters),
        attributeExistenceRequirements(attributeExistenceRequirements),
        attributeSelectors(attributeSelectors) {}
};