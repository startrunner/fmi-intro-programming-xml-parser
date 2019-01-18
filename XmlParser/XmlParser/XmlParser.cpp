#include "pch.h"
#include <iostream>
#include <fstream>
#include "xml_node.h"
#include "text_token_stream.h"
#include "token.h"

using namespace std;
int main()
{
	while (true) {
		string command;
		cin >> command;
		if (command == "tokenize")
		{
			cout << "enter filename on a single line:";
			string filename;
			getline(cin, filename);
			getline(cin, filename);
			ifstream str;
			str.open(filename);
			if (str.fail())
			{
				cout << filename << endl;
				cout << "opaaa";
				continue;
			}

			text_token_stream ts(str);
			while (!ts.eof())
			{
				token token = ts.next_token();
				cout << "type: " << (int)token.type << endl;
				cout << "is terminal: " << token.is_terminal() << endl;
				cout << "string value:" << endl;
				cout << '[' << token.text() << ']' << endl;
				cout << endl;
			}
		}
	};
}