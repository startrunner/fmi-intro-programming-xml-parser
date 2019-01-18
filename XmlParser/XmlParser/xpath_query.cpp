#include "pch.h"
#include "xpath_query.h"
#pragma once

bool xpath_query::operator!=(const xpath_query & other) const
{
    return relativeToRoot != other.relativeToRoot || segments != other.segments;
}
