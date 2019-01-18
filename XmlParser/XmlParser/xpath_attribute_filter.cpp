#include "pch.h"
#include "xpath_attribute_filter.h"
using namespace std;

bool xpath_attribute_filter::execute(const string & documentValue)const
{
    bool value = false;
    switch (this->filterType)
    {
    case xpath_filter_type::EQUALS_NUMERIC:
        value=stof(documentValue) == stof(queryValue);
        break;
    case xpath_filter_type::EQUALS_TEXT:
        value= documentValue == queryValue;
        break;
    case xpath_filter_type::GREATER_THAN_NUMERIC:
        value= stof(documentValue) > stof(queryValue);
        break;
    case xpath_filter_type::GREATER_THAN_TEXT:
        value = documentValue > queryValue;
        break;
    case xpath_filter_type::LESS_THAN_NUMERIC:
        value = stof(documentValue) < stof(queryValue);
        break;
    case xpath_filter_type::LESS_THAN_TEXT:
        value = documentValue < queryValue;
        break;
    default:
        throw runtime_error("Enum value not handled.");
    }
    return value;
}

bool xpath_attribute_filter::operator!=(const xpath_attribute_filter & other) const
{
    return
        attributeName != other.attributeName ||
        filterType != other.filterType ||
        queryValue != other.queryValue;
}
