#include "utils.h"
#include <iostream>
using namespace std;
string EnterLine()
{


	string line;
	INPUT_LINE(cin, line);
	return line;
}
void MenuEditPipe()
{
	cout << "1. Edit one pipe\n" << "2. Edit pipe package\n"
		<< "3. Edit all pipes\n" << "4. Delete\n"
		<< "0. Back to menu\n";
}
void MenuEditPackageP()
{
	cout << "1. Search by name\n" << "2. Search by status\n" << "0. Back to menu\n";
}

void MenuEditByFilter()
{
	std::cout << "1. Change the status to the opposite\n"
		<< "2. Change the status to the \"In repair\"\n"
		<< "3. Change the status to the \"In working condition\"\n"
		<< "0. Back to menu\n";
}

void MenuEditStation()
{
	std::cout << "1. Edit one station\n" << "2. Edit station package\n" << "3. Edit all station\n"
		<< "4. Delete\n" << "0. Back to menu\n";
}
void MenuEditPackageCS()
{
	cout << "1. Search by name\n" << "2. Search by percentage of unused shops\n" << "0. Back to menu\n";
}
void MenuConnectingStations()
{
	cout << "1. Connect stations\n" << "2. Topological sorting\n" << "3. Delete connection\n" << "4. View Topological sorting\n" << "0. Back to menu\n";
}