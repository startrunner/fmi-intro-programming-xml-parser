#include "pch.h"
#include "xml_context.h"
#include <ostream>
#include <iostream>
using namespace std;

const string PRINT_INDENTATION = " ";

void print(ostream &stream, const context_node &node, int indentation);
void print_content(ostream &stream, const string &content, int indentation);
vector<context_node*> get_selected_nodes(vector<context_node> &nodes);

void xml_context::print(std::ostream &stream) const
{
    stream << "DOCUMENT STATE: " << endl;
    for (const context_node &node : this->nodes)
    {
        ::print(stream, node, 1);
    }

    vector<string> selectedAttributeValues = get_selected_attribute_values();
    if (!selectedAttributeValues.empty())
    {
        stream << "SELECTED ATTRIBUTE VALUES: ";
        for (int i = 0; i < selectedAttributeValues.size(); i++)
        {
            bool isLast = (i + 1 == selectedAttributeValues.size());

            stream << selectedAttributeValues[i];
            if (!isLast)stream << ", ";
        }
        stream << endl;
    }

    stream << "END DOCUMENT" << endl;
}

void print(ostream &stream, const context_node &node, int indentation)
{
    for (int i = 0; i < indentation; i++)stream << PRINT_INDENTATION;
    stream << node.name << ' ';
    if (node.isSelected) cout << "<- SELECTED ";
    stream << "{" << endl;

    for (const auto &attribute : node.attributes)
    {
        for (int i = 0; i < indentation + 1; i++)
        {
            stream << PRINT_INDENTATION;
        }
        stream << attribute.first << ": " << attribute.second.value;
        if (attribute.second.isSelected)
        {
            stream << " <- SELECTED";
        }

        stream << endl;
    }

    for (const context_node &child : node.children)
    {
        print(stream, child, indentation + 1);
    }

    print_content(stream, node.content, indentation + 1);

    for (int i = 0; i < indentation; i++)stream << PRINT_INDENTATION;
    stream << "}" << endl;
}

void print_content(ostream &stream, const string &content, int indentation)
{
    for (int i = 0; i < content.size(); i++)
    {
        char c = content[i];
        if (c == '\n')stream << endl;
        if (i == 0 || c == '\n')
        {
            for (int i = 0; i < indentation; i++)stream << PRINT_INDENTATION;
        }
        if (c != '\n')
        {
            if(c=='\\')stream<<"\\";
            else stream << c;
        }
    }
    stream << endl;
}

bool passing(const context_node &node, int nodeIndex, const xpath_query_segment &segment)
{
    if (
        segment.elementName != nullptr &&
        segment.elementName != "*" &&
        segment.elementName != "**"&&
        segment.elementName != node.name
        )return false;

    if (segment.index != nullptr && segment.index != nodeIndex)return false;
    for (const string &existenceRequirement : segment.attributeExistenceRequirements)
    {
        auto found = node.attributes.find(existenceRequirement);
        if (found == node.attributes.end())return false;
    }
    for (const auto &filter : segment.attributeValueFiters)
    {
        auto found = node.attributes.find(filter.attributeName);
        if (found == node.attributes.end())return false;
        if (!filter.execute(found->second.value))return false;
    }

    return true;
}

void select(context_node &relativeTo, int relativeToIndex, const xpath_query &query, int segmentIndex)
{
    if (!passing(relativeTo, relativeToIndex, query.segments[segmentIndex]))return;

    for (const string &attributeSelector : query.segments[segmentIndex].attributeSelectors)
    {
        auto foundAttribute = relativeTo.attributes.find(attributeSelector);
        if (foundAttribute != relativeTo.attributes.end())
        {
            relativeTo.attributes[foundAttribute->first] = context_attribute{
                relativeTo.attributes[foundAttribute->first].value, true
            };
        }
    }

    if (query.segments[segmentIndex].elementName == "**")
    {
        for (int i = 0; i < relativeTo.children.size(); i++)
        {
            select(relativeTo.children[i], i, query, segmentIndex);
        }
    }

    if (segmentIndex + 1 == query.segments.size())
    {
        relativeTo.isSelected = true;
        return;
    }

    for (int i = 0; i < relativeTo.children.size(); i++)
    {
        select(relativeTo.children[i], i, query, segmentIndex + 1);
    }
}

void xml_context::update_selection(const xpath_query & query)
{
    vector<context_node*> selectedNodes = get_selected_nodes(nodes);
    reset_selection();

    if (query.relativeToRoot || selectedNodes.empty())
    {
        int nodeI = 0;
        for (context_node &rootNode : nodes)
        {
            select(rootNode, nodeI, query, 0);
            nodeI++;
        }
    }
    else
    {
        for (context_node *selected : selectedNodes)
        {
            int childI = 0;
            for (context_node &child : selected->children)
            {
                select(child, childI, query, 0);
                childI++;
            }
        }
    }
}

void get_selected_nodes(vector<context_node*> &addTo, vector<context_node> &nodes)
{
    for (auto &node : nodes)
    {
        get_selected_nodes(addTo, node.children);
        if (node.isSelected)addTo.push_back(&node);
    }
}

vector<context_node*> get_selected_nodes(vector<context_node> &nodes)
{
    vector<context_node*> selected;
    ::get_selected_nodes(selected, nodes);
    return selected;
}


void reset_selection(context_node &node)
{
    node.isSelected = false;
    vector<pair<string, context_attribute>> attributes = { node.attributes.begin(), node.attributes.end() };
    for (auto &x : attributes)
    {
        x.second.isSelected = false;
        node.attributes[x.first] = x.second;
    }

    for (auto &child : node.children)reset_selection(child);
}

void xml_context::reset_selection()
{
    for (auto &node : nodes)::reset_selection(node);
}

void get_selected_attribute_values(vector<string> &addTo, const context_node &node)
{
    for (const auto &attribute : node.attributes)
    {
        if (attribute.second.isSelected)
        {
            addTo.push_back(attribute.second.value);
        }
    }

    for (const context_node &child : node.children)get_selected_attribute_values(addTo, child);
}

std::vector<std::string> xml_context::get_selected_attribute_values()const
{
    vector<string> result;
    for (const context_node &rootNode : nodes)
    {
        ::get_selected_attribute_values(result, rootNode);
    }
    return result;
}
