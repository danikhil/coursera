#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <climits>

using std::vector;

vector<int> optimal_sequence(int n)
{
  std::vector<int> sequence;
  int dp[n + 1];
  memset(dp, 0, (n + 1) * sizeof(int));
  for (int i = 1; i <= n; i++)
  {
    dp[i] = dp[i - 1] + 1;
    if (i % 2 == 0)
      dp[i] = std::min(1 + dp[i / 2], dp[i]);
    if (i % 3 == 0)
      dp[i] = std::min(1 + dp[i / 3], dp[i]);
  }
  while (n > 1)
  {
    sequence.push_back(n);
    if (dp[n - 1] == dp[n] - 1)
      n -= 1;
    else if (n % 2 == 0 && (dp[n / 2] == dp[n] - 1))
      n /= 2;
    else if (n % 3 == 0 && (dp[n / 3] == dp[n] - 1))
      n /= 3;
  }
  sequence.push_back(1);
  return sequence;
}

int main()
{
  int n;
  std::cin >> n;
  vector<int> sequence = optimal_sequence(n);
  std::cout << sequence.size() - 1 << std::endl;
  for (int i = sequence.size() - 1; i >= 0; --i)
  {
    std::cout << sequence[i] << " ";
  }
}
