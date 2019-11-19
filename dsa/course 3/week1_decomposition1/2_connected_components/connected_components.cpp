#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <queue>
#include <deque>
#include <bitset>
#include <iterator>
#include <list>
#include <stack>
#include <map>
#include <set>
#include <functional>
#include <numeric>
#include <utility>
#include <limits>
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

using std::pair;
using std::vector;

struct DisjoinSet
{
  int root;
  int ele;
  int weight;
};

int find_root(vector<DisjoinSet> &dsu, int node)
{
  while (dsu[node].root != node)
  {
    dsu[node].root = dsu[dsu[node].root].root;
    node = dsu[node].root;
  }
  return node;
}

void set_union(vector<DisjoinSet> &dsu, int x, int y)
{
  int root_x = find_root(dsu, x);
  int root_y = find_root(dsu, y);
  if (root_x == root_y)
    return;
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
}

int number_of_components(vector<DisjoinSet> &dsu)
{
  int res = 0;
  std::map<int, bool> mp;
  for (int i = 0; i < dsu.size(); i++)
  {
    int root = find_root(dsu, i);
    if (mp.find(root) == mp.end())
    {
      mp[root] = true;
      res++;
    }
  }
  return res;
}

int main()
{
  size_t n, m;
  std::cin >> n >> m;
  vector<DisjoinSet> dsu(n);
  for (int i = 0; i < n; i++)
  {
    dsu[i].root = dsu[i].ele = i;
    dsu[i].weight = 1;
  }
  for (size_t i = 0; i < m; i++)
  {
    int x, y;
    std::cin >> x >> y;
    set_union(dsu, x - 1, y - 1);
  }
  std::cout << number_of_components(dsu);
}
