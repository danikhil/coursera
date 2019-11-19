#include <iostream>
#include <cmath>
#include <algorithm>
#include <climits>
#include <cstring>
#include <cstdlib>

using namespace std;

int str[1001];

int get_change(int m)
{
  //write your code here
  if (m < 0)
    return 1e4;
  if (m == 0)
    return 0;
  if (str[m - 1] == -1)
    str[m - 1] = get_change(m - 1);
  if (str[m - 3] == -1)
    str[m - 3] = get_change(m - 3);
  if (str[m - 4] == -1)
    str[m - 4] = get_change(m - 4);
  return min(1 + str[m - 1], min(1 + str[m - 3], 1 + str[m - 4]));
}

int main()
{
  memset(str, -1, 1001 * sizeof(int));
  int m;
  std::cin >> m;
  std::cout << get_change(m) << '\n';
}
