#pragma once
#include "pch.h"
#include <tuple>
#include <string>

#include "../XmlParser/xpath_parsing.h"
#include "../XmlParser/xpath_query.h"

const std::string exampleXpath1 = "/people/person[id=0]/name";
const std::string exampleXpath2 = "/people/person[id id=\"0\"]/name";
const std::string exampleXpath3 = "people/**[@id]";

const xpath_query exampleQuery3{
    false,{
        xpath_query_segment{
            "people", {}, {}, {}
        },
        xpath_query_segment{
            "**",{}, {},{"id"}
        }
    }
};

const xpath_query exampleQuery2{
    true,{
        xpath_query_segment{
            "people", {}, {}, {}
        },
        xpath_query_segment{
            "person",
            {xpath_attribute_filter{"id", xpath_filter_type::EQUALS_TEXT, "0"}},
            {"id"},
            {}
        },
        xpath_query_segment{"name", {}, {}, {}}
    }
};

const xpath_query exampleQuery1{
    true,{
        xpath_query_segment{
            "people",{}, {}, {}
        },
        xpath_query_segment{
            "person",{xpath_attribute_filter("id", xpath_filter_type::EQUALS_NUMERIC, "0")}, {}, {}
        },
        xpath_query_segment{"name", {}, {}, {}}
    }
};

