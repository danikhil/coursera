#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <climits>
#include <cmath>

using std::vector;

int max_n(int a = 0, int b = 0, int c = 0, int d = 0, int e = 0, int f = 0, int g = 0)
{
  return std::max(a, std::max(b, std::max(c, std::max(d, std::max(e, std::max(f, g))))));
}

int lcs3(vector<int> &a, vector<int> &b, vector<int> &c)
{
  //write your code here
  int l1 = a.size(), l2 = b.size(), l3 = c.size();
  int dp[l1 + 1][l2 + 1][l3 + 1];
  memset(dp, 0, (l1 + 1) * (l2 + 1) * (l3 + 1) * sizeof(int));
  for (int i = 1; i <= l1; i++)
  {
    for (int j = 1; j <= l2; j++)
    {
      for (int k = 1; k <= l3; k++)
      {
        if (a[i - 1] == b[j - 1] && a[i - 1] == c[k - 1])
          dp[i][j][k] = 1 + dp[i - 1][j - 1][k - 1];
        else
          dp[i][j][k] = max_n(dp[i - 1][j][k], dp[i][j - 1][k], dp[i][j][k - 1], dp[i - 1][j - 1][k], dp[i - 1][j][k - 1], dp[i][j - 1][k - 1]);
      }
    }
  }
  return dp[l1][l2][l3];
}

int main()
{
  size_t an;
  std::cin >> an;
  vector<int> a(an);
  for (size_t i = 0; i < an; i++)
  {
    std::cin >> a[i];
  }
  size_t bn;
  std::cin >> bn;
  vector<int> b(bn);
  for (size_t i = 0; i < bn; i++)
  {
    std::cin >> b[i];
  }
  size_t cn;
  std::cin >> cn;
  vector<int> c(cn);
  for (size_t i = 0; i < cn; i++)
  {
    std::cin >> c[i];
  }
  std::cout << lcs3(a, b, c) << std::endl;
}
