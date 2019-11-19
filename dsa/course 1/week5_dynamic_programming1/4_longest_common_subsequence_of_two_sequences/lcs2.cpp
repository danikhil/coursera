#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <climits>
#include <cmath>

using std::vector;

int lcs2(vector<int> &a, vector<int> &b)
{
  //write your code here
  int k = b.size();
  int s[2][k + 1];
  memset(s, 0, (2 * k + 2) * sizeof(int));
  for (int i = 1; i <= a.size(); i++)
  {
    for (int j = 1; j <= b.size(); j++)
    {
      if (a[i - 1] == b[j - 1])
      {
        s[i & 1][j] = s[(i - 1) & 1][j - 1] + 1;
      }
      else
      {
        s[i & 1][j] = std::max(s[(i - 1) & 1][j], s[i & 1][j - 1]);
      }
    }
  }
  return s[a.size() & 1][b.size()];
}

int main()
{
  size_t n;
  std::cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < n; i++)
  {
    std::cin >> a[i];
  }

  size_t m;
  std::cin >> m;
  vector<int> b(m);
  for (size_t i = 0; i < m; i++)
  {
    std::cin >> b[i];
  }

  std::cout << lcs2(a, b) << std::endl;
}
