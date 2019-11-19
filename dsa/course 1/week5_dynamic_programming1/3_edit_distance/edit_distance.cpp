#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <climits>
#include <cmath>

using std::vector;

using std::string;

int edit_distance(const string &str1, const string &str2)
{
  int l1 = str1.size();
  int l2 = str2.size();
  int dp[l1 + 1][l2 + 1];
  for (int i = 0; i <= l2; i++)
    dp[0][i] = i;
  for (int i = 0; i <= l1; i++)
    dp[i][0] = i;
  for (int i = 1; i <= l1; i++)
  {
    for (int j = 1; j <= l2; j++)
    {
      if (str1[i - 1] == str2[j - 1])
        dp[i][j] = std::min(dp[i - 1][j - 1], 1 + std::min(dp[i - 1][j], dp[i][j - 1]));
      else
      {
        dp[i][j] = std::min(1 + dp[i - 1][j - 1], 1 + std::min(dp[i - 1][j], dp[i][j - 1]));
      }
    }
  }
  return dp[l1][l2];
}

int main()
{

  string str1;
  string str2;
  std::cin >> str1 >> str2;
  std::cout << edit_distance(str1, str2) << std::endl;
  return 0;
}
