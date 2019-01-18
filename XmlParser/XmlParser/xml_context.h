#pragma once
#include "pch.h"
#include "xml_node.h"
#include "xpath_query.h"
#include "context_node.h"

class xml_context
{
    std::vector <context_node> nodes;
public:
    xml_context() {}
    xml_context(const std::vector<xml_node> &nodes) :
        nodes(nodes.begin(), nodes.end()) {}

    void print(std::ostream &to)const;
    void update_selection(const xpath_query &query);
    void reset_selection();
    std::vector<std::string> get_selected_attribute_values()const;
};