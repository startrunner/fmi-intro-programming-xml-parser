#include "pch.h"
#include "context_node.h"

context_node::context_node(const xml_node & node)
{
    this->name = node.name;
    for (const auto &x : node.attributes)
    {
        context_attribute attribute{ x.second, false };
        attributes[x.first] = attribute;
    }
    this->content = node.content;
    this->children = { node.children.begin(), node.children.end() };
    this->isSelected = false;
}
