// arrays as parameters
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;

vector<uint64_t> separateIntoSchools (vector<uint64_t> &arg, int max_lifecycle);
//This will count the timers and separate the fish into schools based on timers

void advance_one_day (vector<uint64_t> &arg);
//This will handle decrementing the timers for the lanternfish lifecycle

void generatenewlanternfish (vector<uint64_t> &arg, uint64_t fishToGenerate, int recurring_lifecycle, int max_lifecycle);
//This generates new fish and resets the timer to 6 for all zeros from yesterday

vector<uint64_t> inputFile (string fileName);
//This takes in a CSV file (single line) of initial lanternfish timers and builds 
//the initial-state vector

int main () {

  //Update this file name for example/real life inputs
  vector<uint64_t> lanternfish = inputFile("fish.txt");
  
  //Dynamic input for days at start of the life cycle of lanternfish
  int initial_lifecycle;
  cout << "What is the initial lifecycle at 'birth'? ";
  cin >> initial_lifecycle;

  //Dynamic input for days to reset the life cycle of lanternfish
  int reset_lifecycle;
  cout << "What is the recurring lifecycle at 'birth'? ";
  cin >> reset_lifecycle;

  //Dynamic input for days to observe the life cycle of lanternfish school
  int days_to_evaluate;
  cout << "How many days to observe? ";
  cin >> days_to_evaluate;

  //Display initial state (from CSV file)
  cout << "Initial state: ";
  for (int i = 0; i < lanternfish.size(); i++)
      cout << lanternfish[i] << " ";
  cout << '\n';

  vector<uint64_t> timerSchools(initial_lifecycle);
  timerSchools = separateIntoSchools(lanternfish, initial_lifecycle);

  for (int i=0; i<days_to_evaluate; i++) {
    //store the zeroes from yesterday to not overwrite as we shift the schools of timers down
    uint64_t zeroes = timerSchools[0];
    //Advance one day (shift all timers down)
    advance_one_day(timerSchools);
    //If yesterday had any zeroes - reset the timer (to the recurring lifecycle) 
    //  and generate a new fish @ intitial_lifecycle
    generatenewlanternfish(timerSchools, zeroes, reset_lifecycle, initial_lifecycle);
  }

  uint64_t totalFish = 0;
  for (int i = 0; i < timerSchools.size(); i++)
  {
    //Add the "counts" of all the schools of timers at the end of the observation
    totalFish += timerSchools[i];
  }
  
  cout << "After " + to_string(days_to_evaluate) + " days there are " + to_string(totalFish) + " lanternfish.";
  cout << endl;

  return 0;
}

vector<uint64_t> inputFile (string fileName){
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

  vector<uint64_t> initialState;
  stringstream s_stream(csv_values); //create string stream from the string
  while(s_stream.good()) {
      string substr;
      getline(s_stream, substr, ','); //get first string delimited by comma
      initialState.push_back(stoi(substr));
  }
  //here's our starting vector of fish lifecycle timers
  return initialState;
}

void generatenewlanternfish (vector<uint64_t> &arg, uint64_t fishToGenerate, int reset_lifecycle, int initial_lifecycle) {
  //update the lanternfish timer vector using the zeroes from yesterday
  arg[reset_lifecycle] += fishToGenerate;
  arg[initial_lifecycle] = fishToGenerate;
}

void advance_one_day (vector<uint64_t> &arg) {
  //Move all the timer counts down a day
  int allTimers = arg.size();
  for (int n=0; n<(allTimers - 1); n++){
    arg[n] = arg[n+1];
  }
}

vector<uint64_t> separateIntoSchools (vector<uint64_t> &arg, int max_lifecycle) {
  //this function sets up the simple starting vector into a vector that holds the schools of fish 
  // that share the same timer on the first day
  vector<uint64_t> timerSchools;
  for (int n=0; n <= max_lifecycle; n++)
    timerSchools.push_back(count(arg.begin(), arg.end(), n));
  
  return timerSchools;
}
