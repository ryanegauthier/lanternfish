// arrays as parameters
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;

void advance_one_day (vector<int> &arg);
//This will handle decrementing the timers for the lanternfish lifecycle

void generatenewlanternfish (vector<int> &arg);
//This generates new fish and resets the timer to 6 for all zeros from yesterday

vector<int> inputFile (string fileName);
//This takes in a CSV file (single line) of initial lanternfish timers and builds 
//the initial-state vector

int main () {

  //Update this file name for example/real life inputs
  vector<int> lanternfish = inputFile("example.txt");
  
  //Dynamic input for days to observe the life cycle of lanternfish school
  int days_to_evaluate;
  cout << "How many days to observe? ";
  cin >> days_to_evaluate;

  //Display initial state (from CSV file)
  cout << "Initial state: ";
  for (int i = 0; i <= lanternfish.size(); i++)
      cout << lanternfish[i] << " ";
  cout << endl;
  
  for (int i=0; i<days_to_evaluate; i++) {
    //Advance one day
    advance_one_day(lanternfish);
    //Sort for ease of traversing vector
    sort(lanternfish.begin(), lanternfish.end());      
    //If yesterday had any zeroes they will now be -1's reset the timer and generate a new fish @ 8
    generatenewlanternfish(lanternfish);
  }
  
  cout << "After " + to_string(days_to_evaluate) + " days there are " + to_string(lanternfish.size()) + " lanternfish.";
  cout << endl;

  return 0;
}

vector<int> inputFile (string fileName){
  //input CSV file and generate a vector of inital lanternfish timers 
  string line;
  string csv_values;
  ifstream myfile (fileName);
  if (myfile.is_open())
  {
    while ( getline (myfile,line) )
    {
      csv_values = line;
    }
    myfile.close();
  }

  else cout << "Unable to open file"; 

  vector<int> initialState;
  stringstream s_stream(csv_values); //create string stream from the string
  while(s_stream.good()) {
      string substr;
      getline(s_stream, substr, ','); //get first string delimited by comma
      initialState.push_back(stoi(substr));
  }
  //here's our starting vector of fish lifecycle timers
  return initialState;
}

void generatenewlanternfish (vector<int> &arg) {
  //traverse the lanternfish timer vector
  int allTimers = arg.size();
  for (int n=0; n<allTimers; n++){
    //only update the zeroes from yesterday
    if(arg[n] < 0) {
      arg[n] = 6;
      arg.push_back(8);
    } else {
      break;
    }
  }
}

void advance_one_day (vector<int> &arg) {
  int allTimers = arg.size();
  for (int n=0; n < allTimers; n++)
    arg[n]--;
}
