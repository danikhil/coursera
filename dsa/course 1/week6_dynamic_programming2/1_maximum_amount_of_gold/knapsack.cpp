#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using std::vector;

int optimal_weight(int W, const vector<int> &w)
{
  vector<vector<int>> dp(w.size() + 1);

  for (int i = 0; i <= w.size(); i++)
  {
    dp[i].resize(W + 1);
  }

  for (int i = 0; i <= w.size(); i++)
  {
    for (int j = 0; j <= W; j++)
    {
      if (i == 0 || j == 0)
        dp[i][j] = 0;
      else if (w[i - 1] <= j)
        dp[i][j] = std::max(w[i - 1] + dp[i - 1][j - w[i - 1]], dp[i - 1][j]);
      else
      {
        dp[i][j] = dp[i - 1][j];
      }
    }
  }
  return dp[w.size()][W];
}

int main()
{
  int n, W;
  std::cin >> W >> n;
  vector<int> w(n);
  for (int i = 0; i < n; i++)
  {
    std::cin >> w[i];
  }
  std::cout << optimal_weight(W, w) << '\n';
}
