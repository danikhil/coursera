#include <iostream>
#include <vector>
#include <queue>
#include <limits.h>
#include <math.h>
#include <algorithm>

using std::vector;

int isCycle(vector<vector<int>> &adj, vector<vector<int>> &cost, int src, vector<int> &dist)
{
  std::fill(dist.begin(), dist.end(), INT_MAX);
  dist[src] = 0;
  for (int i = 0; i < adj.size(); i++)
  {
    for (int u = 0; u < adj.size(); u++)
    {
      for (int v = 0; v < adj[u].size(); v++)
      {
        if (dist[u] != INT_MAX && dist[u] + cost[u][v] < dist[adj[u][v]])
        {
          dist[adj[u][v]] = dist[u] + cost[u][v];
          if (i == adj.size() - 1)
            return 1;
        }
      }
    }
  }
  return 0;
}

int negative_cycle(vector<vector<int>> &adj, vector<vector<int>> &cost)
{
  //write your code here
  vector<int> visited(adj.size(), 0);
  vector<int> dist(adj.size());

  for (int i = 0; i < adj.size(); i++)
  {
    if (!visited[i])
    {
      if (isCycle(adj, cost, i, dist))
        return 1;
      for (int i = 0; i < adj.size(); i++)
        if (dist[i] != INT_MAX)
          visited[i] = 1;
    }
  }
  return 0;
}

int main()
{
  int n, m;
  std::cin >> n >> m;
  vector<vector<int>> adj(n, vector<int>());
  vector<vector<int>> cost(n, vector<int>());
  for (int i = 0; i < m; i++)
  {
    int x, y, w;
    std::cin >> x >> y >> w;
    adj[x - 1].push_back(y - 1);
    cost[x - 1].push_back(w);
  }
  std::cout << negative_cycle(adj, cost);
}
