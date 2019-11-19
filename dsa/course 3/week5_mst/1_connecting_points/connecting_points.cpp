#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>

using std::pair;
using std::vector;

typedef pair<int, int> pi;

double sq(int x)
{
  return x * x;
}

double eu_distance(int x1, int x2, int y1, int y2)
{
  return sqrt(sq(x1 - x2) + sq(y1 - y2));
}

struct DisjoinSet
{
  int root;
  int weight;
};

void initialize_dsu(vector<DisjoinSet> &dsu, int n)
{
  for (int i = 0; i < n; i++)
  {
    dsu[i].root = i;
    dsu[i].weight = 1;
  }
}

int find_root(vector<DisjoinSet> &dsu, int node)
{
  while (dsu[node].root != node)
  {
    dsu[node].root = dsu[dsu[node].root].root;
    node = dsu[node].root;
  }
  return node;
}

int set_union(vector<DisjoinSet> &dsu, pi C)
{
  int x = C.first;
  int y = C.second;
  int root_x = find_root(dsu, x);
  int root_y = find_root(dsu, y);
  if (root_x == root_y)
    return 0;
  if (dsu[root_x].weight < dsu[root_y].weight)
  {
    dsu[root_y].root = root_x;
    dsu[root_x].weight += dsu[root_y].weight;
  }
  else
  {
    dsu[root_x].root = root_y;
    dsu[root_y].weight += dsu[root_x].weight;
  }
  return 1;
}

double kruskal(vector<DisjoinSet> &dsu, vector<pair<double, pi>> &v)
{
  double ans = 0;
  for (auto i : v)
  {
    if (set_union(dsu, i.second))
    {
      ans += i.first;
    }
  }
  return ans;
}

double minimum_distance(vector<int> x, vector<int> y)
{
  //write your code here
  vector<pair<double, pi>> v;
  for (int i = 0; i < x.size() - 1; i++)
  {
    for (int j = i + 1; j < x.size(); j++)
    {
      double d = eu_distance(x[i], x[j], y[i], y[j]);
      v.push_back({d, {i, j}});
    }
  }
  sort(v.begin(), v.end(), [](const pair<double, pi> &a, const pair<double, pi> &b) {
    return a.first < b.first;
  });

  vector<DisjoinSet> dsu(x.size());
  initialize_dsu(dsu, x.size());
  return kruskal(dsu, v);
}

int main()
{
  size_t n;
  std::cin >> n;
  vector<int> x(n), y(n);
  for (size_t i = 0; i < n; i++)
  {
    std::cin >> x[i] >> y[i];
  }
  std::cout << std::setprecision(10) << minimum_distance(x, y) << std::endl;
}
