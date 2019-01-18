#pragma once
#include "pch.h"
#include "xml_node.h"
#include <set>
struct context_attribute
{
    bool isSelected = false;
    std::string value = "";
    context_attribute() {}
    context_attribute(const std::string &name, bool isSelected = false) :
        value(name), isSelected(isSelected) {}
    context_attribute(const context_attribute &toCopy) :
        value(toCopy.value), isSelected(toCopy.isSelected) {}
};
struct context_node
{
    std::string name;
    std::map<std::string, context_attribute> attributes;
    std::vector<context_node> children;
    std::string content;
    bool isSelected = false;

    context_node(const xml_node &node);
};