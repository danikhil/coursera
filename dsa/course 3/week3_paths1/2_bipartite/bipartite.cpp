#include <iostream>
#include <vector>
#include <queue>
#include <math.h>
#include <stdlib.h>
#include <algorithm>

using std::max;
using std::min;
using std::queue;
using std::vector;

struct DisjointSet
{
  int root;
  vector<int> child;
  int weight;
  int parity;
};

void initializeDS(vector<DisjointSet> &dsu, int n)
{
  dsu.resize(n);
  for (int i = 0; i < n; i++)
  {
    dsu[i].root = i;
    dsu[i].weight = 1;
    dsu[i].parity = -1;
  }
}

int find_root(vector<DisjointSet> &dsu, int node)
{
  while (dsu[node].root != node)
  {
    dsu[node].root = dsu[dsu[node].root].root;
    node = dsu[node].root;
  }
  return node;
}

void bfs_reverse_parity(vector<DisjointSet> &dsu, int node)
{
  vector<int> visited(dsu.size(), 0);
  dsu[node].parity ^= 1;
  queue<int> q;
  q.push(node);
  while (!q.empty())
  {
    int k = q.front();
    visited[k] = 1;
    q.pop();
    for (int i = 0; i < dsu[k].child.size(); i++)
    {
      if (!visited[dsu[k].child[i]])
      {
        dsu[dsu[k].child[i]].parity ^= 1;
        q.push(dsu[k].child[i]);
      }
    }
  }
}

bool set_union(vector<DisjointSet> &dsu, int x, int y)
{
  //std::cout << x << ' ' << y << ' ' << dsu[x].parity << ' ' << dsu[y].parity << '\n';
  int root_x = find_root(dsu, x);
  int root_y = find_root(dsu, y);
  if (root_x == root_y)
  {
    if (dsu[x].parity == dsu[y].parity)
      return false;
    else
    {
      return true;
    }
  }
  else if (dsu[root_x].weight < dsu[root_y].weight)
  {
    dsu[root_y].root = root_x;
    dsu[root_x].weight += dsu[root_y].weight;
    if (dsu[root_x].parity == dsu[root_y].parity && dsu[root_y].parity == -1)
    {
      dsu[root_x].parity = 0;
      dsu[root_y].parity = 1;
    }
    else if (dsu[root_x].parity == -1)
    {
      dsu[root_x].parity = dsu[y].parity ^ 1;
    }
    else if (dsu[root_y].parity == -1)
    {
      dsu[root_y].parity = dsu[x].parity ^ 1;
    }
    else if (dsu[x].parity == dsu[y].parity)
    {
      bfs_reverse_parity(dsu, root_x);
    }
    dsu[root_x].child.push_back(root_y);
    dsu[root_y].child.push_back(root_x);
  }
  else
  {
    dsu[root_x].root = root_y;
    dsu[root_y].weight + dsu[root_x].weight;
    if (dsu[root_x].parity == dsu[root_y].parity && dsu[root_y].parity == -1)
    {
      dsu[root_x].parity = 0;
      dsu[root_y].parity = 1;
    }
    else if (dsu[root_x].parity == -1)
    {
      dsu[root_x].parity = dsu[y].parity ^ 1;
    }
    else if (dsu[root_y].parity == -1)
    {
      dsu[root_y].parity = dsu[x].parity ^ 1;
    }
    else if (dsu[x].parity == dsu[y].parity)
    {
      bfs_reverse_parity(dsu, root_y);
    }
    dsu[root_y].child.push_back(root_x);
    dsu[root_x].child.push_back(root_y);
  }
  return true;
}

int bipartite(vector<vector<int>> &adj)
{
  vector<DisjointSet> dsu;
  initializeDS(dsu, adj.size());
  int s = true;
  for (int i = 0; i < adj.size(); i++)
  {
    for (auto j : adj[i])
    {
      s = s && set_union(dsu, i, j);
      if (!s)
        return (int)s;
    }
  }
  return (int)s;
}

int main()
{
  int n, m;
  std::cin >> n >> m;
  vector<vector<int>> adj(n, vector<int>());
  for (int i = 0; i < m; i++)
  {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }
  std::cout << bipartite(adj);
}
