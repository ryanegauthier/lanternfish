// arrays as parameters
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;

vector<int> resettimer (vector<int> arg) {
  for (int n=0; n<arg.size(); ++n)
    if(arg[n] < 0)
      arg[n] = 6;
  return arg;
}

vector<int> generatenewlanternfish (vector<int> arg) {
  for (int n=0; n<arg.size(); n++)
    if(arg[n] < 0)
      arg.push_back(8);

  arg = resettimer(arg);
  return arg;
}

vector<int> advance_one_day (vector<int> arg) {
  int initialcount = arg.size();

  for (int n=0; n < initialcount; n++)
    arg[n]--;
    for (int n=0; n < initialcount; n++) {
      if(arg[n] >= 0)
        break;
      arg[n] = 6;
      arg.push_back(8);
    }
 
//   arg = generatenewlanternfish(arg);
  sort(arg.begin(), arg.end());  

  return arg;
}


int main ()
{
  string line;
  string csv_values;
  ifstream myfile ("example.txt");
  if (myfile.is_open())
  {
    while ( getline (myfile,line) )
    {
      csv_values = line;
    }
    myfile.close();
  }

  else cout << "Unable to open file"; 

  vector<int> lanternfish;
  stringstream s_stream(csv_values); //create string stream from the string
  while(s_stream.good()) {
      string substr;
      getline(s_stream, substr, ','); //get first string delimited by comma
      lanternfish.push_back(stoi(substr));
  }
    
    int days_to_evaluate;
    cout << "How many days to observe? ";
    cin >> days_to_evaluate;

    cout << "Initial state: ";
    for (int i = 0; i < lanternfish.size(); i++)
        cout << lanternfish[i] << " ";
    cout << "\n";

    for (int i=0; i<days_to_evaluate; ++i) {
      lanternfish = advance_one_day(lanternfish);
    //   cout << "After " + to_string(i+1) + " day(s): ";

    //   for (int i = 0; i < lanternfish.size(); i++)
    //     cout << lanternfish[i] << " ";
    //   cout << "\n";
    }

    //   for (int i = 0; i < lanternfish.size(); i++)
    //     cout << lanternfish[i] << " ";
    //   cout << "\n";
      cout << "After " + to_string(days_to_evaluate) + " days there are " + to_string(lanternfish.size()) + " lanternfish.";
      cout << "\n";

  return 0;
}