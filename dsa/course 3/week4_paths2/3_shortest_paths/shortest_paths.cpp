#include <iostream>
#include <vector>
#include <queue>
#include <limits.h>
#include <math.h>
#include <algorithm>

using std::max;
using std::min;
using std::vector;

using std::pair;
using std::priority_queue;
using std::queue;

#define INF 0x3f3f3f3f;

void shortest_paths(vector<vector<int>> &adj, vector<vector<int>> &cost, int s, vector<long long> &dist, vector<int> &reachable, vector<int> &shortest)
{
  //write your code here

  queue<int> q;
  vector<int> visited(adj.size(), 0);
  dist[s] = 0;
  reachable[s] = 1;
  for (int i = 0; i < adj.size(); i++)
  {
    for (int u = 0; u < adj.size(); u++)
    {
      for (int v = 0; v < adj[u].size(); v++)
      {
        int m = adj[u][v];
        if (dist[u] != std::numeric_limits<long long>::max() && dist[u] + cost[u][v] < dist[m])
        {
          reachable[m] = 1;
          dist[m] = dist[u] + cost[u][v];
          if (i == adj.size() - 1)
          {
            //std::cout << adj[u][v] << '\n';
            q.push(m);
            visited[m] = 1;
            shortest[m] = 0;
          }
        }
      }
    }
  }

  while (!q.empty())
  {
    int n = q.front();
    q.pop();
    for (auto i : adj[n])
    {
      if (!visited[i])
      {
        q.push(i);
        visited[i] = 1;
        shortest[i] = 0;
      }
    }
  }
}

int main()
{
  int n, m, s;
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
  std::cin >> s;
  s--;
  vector<long long> distance(n, std::numeric_limits<long long>::max());
  vector<int> reachable(n, 0);
  vector<int> shortest(n, 1);
  shortest_paths(adj, cost, s, distance, reachable, shortest);
  for (int i = 0; i < n; i++)
  {
    if (!reachable[i])
    {
      std::cout << "*\n";
    }
    else if (!shortest[i])
    {
      std::cout << "-\n";
    }
    else
    {
      std::cout << distance[i] << "\n";
    }
  }
}
