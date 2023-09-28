#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int main()
{
  bool debug = true;
  ifstream infile("input.txt");

  // parsing first line
  int n, m, k;
  if (debug)
    infile >> n >> m >> k;
  else
    cin >> n >> m >> k;

  // parsing passengers
  vector<int> c(n + 1, 0);
  if (debug)
  {
    for (int i = 1; i <= n; i++)
    {
      infile >> c[i];
    }
  }
  else
  {
    for (int i = 1; i <= n; i++)
    {
      cin >> c[i];
    }
  }

  // precomputing wait times where wait[i][j] is wait of passengers i,...,j with buses at i and j
  int wait[n + 1][n + m];

  for (int i = 0; i <= n; i++)
  {
    for (int j = 0; j <= n - 1 + m; j++)
    {
      wait[i][j] = 0;
      for (int l = i + 1; l < j; l++)
      {
        wait[i][j] += c[l] * (j - l);
      }
      cout << "wait(" << i << ", " << j << ") = " << wait[i][j] << endl;
    }
    cout << endl;
  }

  // opt[i][j] = min wait time for passengers arriving times i = 0,...,n-1 with j buses scheduled 0,...,
  int opt[n + m + 1][k + 1];

  for (int r = 0; r <= k; r++)
  {
    opt[0][r] = 0;
  }

  for (int r = 1; r <= k; r++)
  {
    // we start at j=2 since j=1 was already computed
    for (int j = 1; j <= n + m - 1; j++)
    {
      if (r == 1 || (r > 1 && j <= m))
      {
        opt[j][r] = wait[0][j];
      }
      else
      {
        int minimum = INT_MAX;

        for (int i = 0; i <= j - m; i++)
        {
          minimum = min(wait[i][j] + opt[i][r - 1], minimum);
        }
        opt[j][r] = minimum;
      }
      cout << "opt(" << j << ", " << r << ") = " << opt[j][r] << endl;
    }
    cout << endl;
  }

  int nonzero_c = n;
  for (int i = n; i >= 1; i--)
  {
    if (i == 0)
    {
      nonzero_c--;
    }
    else
    {
      break;
    }
  }

  int minimum = INT_MAX;
  int curr_j, num_buses = 0;
  for (int j = nonzero_c; j < nonzero_c + m; j++)
  {
    if (opt[j][k] < minimum)
    {
      minimum = opt[j][k];
      curr_j = j;
      num_buses = k - 1;
    }
  }
  // printing total wait time
  cout << minimum << endl;

  // backtracing

  vector<int> bus_stops;
  bus_stops.push_back(curr_j);

  int min_i = 0;
  int min_wait = INT_MAX;

  while (curr_j > m && num_buses > 0)
  {
    for (int i = 0; i <= curr_j - m; i++)
    {
      if (wait[i][curr_j] + opt[i][num_buses - 1] < min_wait)
      {
        min_wait = wait[i][curr_j] + opt[i][num_buses - 1];
        min_i = i;
      }
    }
    bus_stops.push_back(min_i);
    curr_j = min_i;
    num_buses--;
  }

  reverse(bus_stops.begin(), bus_stops.end());
  bool first = true;
  for (int i = 0; i < bus_stops.size(); i++)
  {
    if (first)
    {
      cout << bus_stops[i];
      first = false;
    }
    else
      cout << " " << bus_stops[i];
  }
  cout << endl;

  return 0;
}