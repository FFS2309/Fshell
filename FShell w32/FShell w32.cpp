// FShell w32.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//
#include <iostream>
#include <string>
#include <direct.h>
#include <stdio.h>
using namespace std;


void split(std::string str, std::string delimiters, std::string dest[]) {
	string retstr;
	size_t current;
	size_t next = -1;
	do
	{
		current = next + 1;
		next = str.find_first_of(delimiters, current);
		if (current > 0) {
			retstr.append(str.substr(current, next - current));
		}
		else {
			dest[0] = str.substr(current, next - current);
		}
	} while (next != string::npos);
}

string sgetcwd() {
	std::string result(1024, '\0');
	while (_getcwd(&result[0], result.size()) == 0) {
		if (errno != ERANGE) {
#if (_MSC_VER >= 1400)         // Check MSC version
#pragma warning(push)
#pragma warning(disable: 4996) // Disable deprecation
#endif 
			throw std::runtime_error(strerror(errno));
#if (_MSC_VER >= 1400)         // Check MSC version
#pragma warning(pop)           // Renable previous depreciations
#endif
		}
		result.resize(result.size() * 2);
	}
	result.resize(result.find('\0') - 1);
	return result;
}

string getLeadingText() {
	string rstr;
#if (_MSC_VER >= 1400)         // Check MSC version
#pragma warning(push)
#pragma warning(disable: 4996) // Disable deprecation
#endif 
	rstr.append(getenv("USERNAME"));
#if (_MSC_VER >= 1400)         // Check MSC version
#pragma warning(pop)           // Renable previous depreciations
#endif
	rstr.append(" ");
	rstr.append(sgetcwd().c_str());
	rstr.append("$");
	return rstr;
}

int main(char* args[], int* argc) {
	cout << "FShell v0.1w32" << endl;
	while (true) {
		bool matched = false;
	string cmd = "";
	cout << getLeadingText() << " ";
	getline(cin, cmd);
	string cmdargs[50];
	split(cmd, " ", cmdargs);
	string cmds[] = {"help", "echo", "test"};
	int cmdcount = (sizeof(cmds) / sizeof(cmds[0]));
	for (int i = 0; i < cmdcount; i++) {
		if (cmdargs[0] == cmds[i]) {
			switch (i) {
			default:
			case 0:
				cout << "Available commands:" << endl;
				for (int i = 0; i < cmdcount; i++) {
					cout << cmds[i] << endl;
				}
				break;
			case 1:
				for (int i = 1; i < (sizeof(cmdargs) / sizeof(cmdargs[0])); i++) {
					cout << cmdargs[i];
				}
				cout << endl;
				break;
			case 2:
				cout << "This command is entended to be a test command" << endl;
				break;
			}
		}
	}
	if (matched) {

	}
	else {
		system(cmd.c_str());
	}
	}
	return 0;
}
