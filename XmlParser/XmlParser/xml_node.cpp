#include "pch.h"
#include "xml_node.h"
using namespace std;

xml_node::xml_node(string name) { name = name; }

xml_node::xml_node(string name, map<string, string> attributes, string content)
{
    this->name = name;
    this->attributes = attributes;
    this->content = content;
}

xml_node::xml_node(string name, map<string, string> attributes, vector<xml_node> children)
{
    this->name = name;
    this->attributes = attributes;
    this->children = children;
}

xml_node::xml_node(const xml_node & toCopy)
{
    this->name = toCopy.name;
    this->attributes = toCopy.attributes;
    this->children = toCopy.children;
    this->content = toCopy.content;
}


bool xml_node::operator!=(const xml_node & node) const
{
    if (name != node.name)return true;
    if (children != node.children)return true;
    if (attributes != node.attributes)return true;
    return false;
}
