#include <iostream>
#include <string>
using namespace std;

int main(){
  string a;
  cout << "Welcome to PACMAN Alpha Edition!" << endl << "Enter a number for options, or Press Enter to exit" << endl; 
  getline (cin,a);
  if (a=="1")
    cout << "play" << endl;
  if (a=="2")
    cout << "stats" << endl;
  cout << "bye" << endl;
  return 0;
}
