// arrays as parameters
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <string>
#include <algorithm>
#include <chrono>
#include <ctime>  
using namespace std;

void advance_one_day (vector<int> &arg);

void generatenewlanternfish (vector<int> &arg);

vector<int> inputFile (string fileName);

int main () {

  vector<int> lanternfish = inputFile("example.txt");
  
  int days_to_evaluate;
  cout << "How many days to observe? ";
  cin >> days_to_evaluate;

  cout << "Initial state: ";
  for (int i = 0; i < lanternfish.size(); i++)
      cout << lanternfish[i] << " ";
  cout << "\n";
  
  std::chrono::duration<double> elapsed_seconds;
  for (int i=0; i<days_to_evaluate; ++i) {
    sort(lanternfish.begin(), lanternfish.end());      
    advance_one_day(lanternfish);
    generatenewlanternfish(lanternfish);
  }
  cout << "After " + to_string(days_to_evaluate) + " days there are " + to_string(lanternfish.size()) + " lanternfish.";
  cout << "\n";

  return 0;
}

vector<int> inputFile (string fileName){
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
  return initialState;
}

void generatenewlanternfish (vector<int> &arg) {
  for (int n=0; n<arg.size(); n++){
    if(arg[n] < 0) {
      arg[n] = 6;
      arg.push_back(8);
    } else {
      break;
    }
  }
}

void advance_one_day (vector<int> &arg) {
  for (int n=0; n < arg.size(); n++)
    arg[n]--;
}
