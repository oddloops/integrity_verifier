#include <cctype>
#include <iostream>
#include <limits>
using namespace std;

#define RECORD_MODE 1
#define VERIFY_MODE 2
#define ATTEMPT_LIMITS 3

int main () {
  int attempts = 0;
  int modeSelected = -1;

  cout << "Please selected a mode:" << endl;
  cout << "(1) Record mode" << endl;
  cout << "(2) Verify mode" << endl;
  cout << "(Exit) Enter any key" << endl;
  cout << "Mode: ";
  cin >> modeSelected;

  while (!cin && attempts < ATTEMPT_LIMITS) {
    attempts++;
    cout << "Bad input." << endl;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Select mode: ";
    cin >> modeSelected;
  }

  if (modeSelected == RECORD_MODE) {
    cout << "Entering Record mode..." << endl;
  }
  else if (modeSelected == VERIFY_MODE) {
    cout << "Entering Verification mode..." << endl;
  }
  else {
    cout << "Exiting..."<< endl;
  }
  
  return 0;
}
