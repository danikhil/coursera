#include <algorithm>
#include <iostream>
#include <vector>
#include <map>

using std::vector;
std::map<int, int> mp;

int get_majority_element(vector<int> &a, int left, int right)
{
  for (int i : a)
  {
    if (mp.find(i) == mp.end())
      mp.insert({i, 1});
    else
    {
      mp[i]++;
      if (mp[i] > right / 2)
        return mp[i];
    }
  }
  return -1;
}

int main()
{
  int n;
  std::cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < a.size(); ++i)
  {
    std::cin >> a[i];
  }
  std::cout << (get_majority_element(a, 0, a.size()) != -1) << '\n';
}
