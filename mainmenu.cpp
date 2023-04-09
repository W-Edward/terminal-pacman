#include <iostream>
using namespace std;

int main(){
	cout << "    ***********************************" << endl;
	cout << "      Welcome to Pac-Man Alpha Edition " << endl;
	cout << "    ***********************************" << endl;
	cout << "	" << endl;
	cout << "		Please input your option :" << endl;
	cout << "	1. Play The Pac-Man Game !" << endl;
	cout << "	2. View The Game Statistics" << endl;
	cout << "	3. View The Staff Credits" << endl;
	cout << "	4. Exit The Main Menu" << endl;
	cout << "	" << endl;
	cout << "* Expand your terminal for a better game experience!" << endl;
	cout << "	" << endl;
	cout << " Input your option (1/2/3/4) :";
	int option;
	cin >> option;
	if ((option>=1) && (option<=4))
		cout << "Valid input, " << option << endl;
	else
		cout << "Invalid input, " << option << endl;
	return 0;
}
