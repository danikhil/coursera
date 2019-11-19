#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include <climits>
#include <cmath>

using std::string;
using std::vector;

long long eval(long long a, long long b, char op)
{
  //std::cout << op << '\n';
  //std::cout << a << ' ' << b << '\n';
  if (op == '*')
  {
    return a * b;
  }
  else if (op == '+')
  {
    return a + b;
  }
  else if (op == '-')
  {
    return a - b;
  }
  else
  {
    assert(0);
  }
}

long long get_maximum_value(const string &exp)
{
  //write your code here
  vector<long long> v;
  char s[30];
  int k = 0;
  for (int i = 0; i < exp.size(); i++)
  {
    if (exp[i] >= 48 && exp[i] < 58)
    {
      v.push_back(exp[i] - 48);
    }
    else
    {
      s[k++] = exp[i];
    }
  }
  // for (auto i : s)
  //   std::cout << i << ' ';
  // std::cout << '\n';
  long long max[v.size()][v.size()];
  long long min[v.size()][v.size()];

  for (int i = 0; i < v.size(); i++)
  {
    for (int j = 0; j < v.size(); j++)
    {
      max[i][j] = INT_MIN;
      min[i][j] = INT_MAX;
    }
  }
  for (int i = 0; i < v.size(); i++)
  {
    max[i][i] = min[i][i] = v[i];
  }

  for (int i = 1; i < v.size(); i++)
  {
    for (int j = 0; j < v.size() - i; j++)
    {
      int p = j + i;
      for (int k = j; k < p; k++)
      {
        //std::cout << j << ' ' << p << '\n';
        max[j][p] = std::max(max[j][p], eval(max[j][k], max[k + 1][p], s[k]));
        max[j][p] = std::max(max[j][p], eval(max[j][k], min[k + 1][p], s[k]));
        max[j][p] = std::max(max[j][p], eval(min[j][k], min[k + 1][p], s[k]));
        max[j][p] = std::max(max[j][p], eval(min[j][k], max[k + 1][p], s[k]));
        min[j][p] = std::min(min[j][p], eval(max[j][k], max[k + 1][p], s[k]));
        min[j][p] = std::min(min[j][p], eval(max[j][k], min[k + 1][p], s[k]));
        min[j][p] = std::min(min[j][p], eval(min[j][k], min[k + 1][p], s[k]));
        min[j][p] = std::min(min[j][p], eval(min[j][k], max[k + 1][p], s[k]));
      }
    }
  }
  // for (int i = 0; i < v.size(); i++)
  // {
  //   for (int j = i; j < v.size(); j++)
  //   {
  //     std::cout << max[i][j] << ' ';
  //   }
  //   std::cout << '\n';
  // }
  // for (int i = 0; i < v.size(); i++)
  // {
  //   for (int j = i; j < v.size(); j++)
  //   {
  //     std::cout << min[i][j] << ' ';
  //   }
  //   std::cout << '\n';
  // }
  return max[0][v.size() - 1];
}

int main()
{
  string s;
  std::cin >> s;
  std::cout << get_maximum_value(s) << '\n';
}
