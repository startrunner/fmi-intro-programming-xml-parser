#include "pch.h"
#include "xpath_query_segment.h"

bool xpath_query_segment::operator!=(const xpath_query_segment & other) const
{
    return
        index != other.index ||
        elementName != other.elementName ||
        attributeValueFiters != other.attributeValueFiters ||
        attributeExistenceRequirements != other.attributeExistenceRequirements ||
        attributeSelectors != other.attributeSelectors;
}
