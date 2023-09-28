#include <iostream>
#include <fstream>

using namespace std;

int main()
{
  ofstream outfile("test.txt");

  int n = 100;
  int m = 4;
  int k = 5;
  outfile << n << " " << m << " " << k << endl;

  bool first = true;
  for (int i = 0; i < m; i++)
  {
    if (first)
      outfile << rand() % 100;
    outfile << " " << rand() % 100;
  }

  outfile.close();
  return 0;
}