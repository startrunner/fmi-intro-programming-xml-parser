#pragma once
#include "pch.h"
#include "optional.h"
#include "xpath_query_segment.h"

struct xpath_query
{
    bool relativeToRoot;
    std::vector<xpath_query_segment> segments;

public:
    xpath_query(bool isRelativeToRoot, std::vector<xpath_query_segment> segments) :
        relativeToRoot(isRelativeToRoot), segments(segments) {}

    bool operator !=(const xpath_query &other)const;
    bool operator ==(const xpath_query &other)const { return !(*this != other); }
};