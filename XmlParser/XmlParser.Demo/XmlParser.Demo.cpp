// XmlParser.Demo.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "pch.h"
#include <map>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <istream>
#include <functional>
#include "..\XmlParser\xml_context.h"
#include "..\XmlParser\xml_parsing.h"
#include "..\XmlParser\xpath_parsing.h"
using namespace std;

xml_context context;

void open();
void quit() { exit(0); }
void select();
string read_command_parameter();

map <string, function<void()>> commands{
    {"open", open},
    {"load", open},
    {"quit", quit},
    {"exit", quit},
    {"end", quit},
    {"select", select},
    {"query", select}
};


int main()
{
    while (cin.good())
    {
        string command;
        cin >> command;
        auto found = commands.find(command);
        if (found == commands.end())
        {
            cout << "Invalid command. try again." << endl;
        }
        else found->second();
    }
}

void open()
{
    while (cin.good())
    {
        string path = read_command_parameter();
        if (!filesystem::is_regular_file(path))
        {
            cout << "File does not exist! Try again." << endl;
        }
        else
        {
            ifstream fileStream{ path };
            vector<xml_node> parsed = parse_document(fileStream);
            context = { parsed };
            context.print(cout);
            return;
        }
    }

}

void select()
{
    string queryText = read_command_parameter();

    if (queryText == "reset")context.reset_selection();
    else
    {
        xpath_query query = parse_xpath_query(queryText);
        context.update_selection(query);
    }

    context.print(cout);
}

string read_command_parameter()
{
    string parameter;
    while (isspace(cin.peek()))cin.get();
    getline(cin, parameter);
    return parameter;
}
