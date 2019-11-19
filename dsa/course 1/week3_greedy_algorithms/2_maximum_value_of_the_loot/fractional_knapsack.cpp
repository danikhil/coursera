#include <iostream>
#include <vector>
#include <algorithm>

using std::pair;
using std::vector;

bool compa(pair<double, int> &a, pair<double, int> &b)
{
  if (a.first > b.first)
    return true;
  else
    return false;
}

double get_optimal_value(int capacity, vector<int> weights, vector<int> values)
{
  double value = 0.0;

  vector<pair<double, int>> v;
  for (int i = 0; i < weights.size(); i++)
  {
    v.push_back({values[i] * 1.0 / weights[i], weights[i]});
  }

  sort(v.begin(), v.end(), compa);

  for (auto i : v)
  {
    if (i.second <= capacity)
    {
      value += i.first * i.second;
      capacity -= i.second;
    }
    else
    {
      value += i.first * capacity;
      break;
    }
  }

  return value;
}

int main()
{
  int n;
  int capacity;
  std::cin >> n >> capacity;
  vector<int> values(n);
  vector<int> weights(n);
  for (int i = 0; i < n; i++)
  {
    std::cin >> values[i] >> weights[i];
  }

  double optimal_value = get_optimal_value(capacity, weights, values);

  std::cout.precision(10);
  std::cout << optimal_value << std::endl;
  return 0;
}
