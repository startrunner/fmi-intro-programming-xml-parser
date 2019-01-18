#pragma once
#include "pch.h"
#include <map>
#include <vector>
#include <string>
struct xml_node
{
    std::string name = "";
    std::map<std::string, std::string> attributes = {};
    std::vector<xml_node> children = {};
    std::string content = "";

    explicit xml_node() = default;
    xml_node(std::string name);
    xml_node(std::string name, std::map<std::string, std::string> attributes, std::string content = "");
    xml_node(std::string name, std::map<std::string, std::string> attributes, std::vector<xml_node> children);
    xml_node(const xml_node &toCopy);

    bool operator ==(const xml_node &other)const { return !(*this != other); }
    bool operator !=(const xml_node &node)const;

    ~xml_node() = default;
};

