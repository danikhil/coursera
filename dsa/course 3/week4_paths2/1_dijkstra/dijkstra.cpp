#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <math.h>

using std::pair;
using std::priority_queue;
using std::queue;
using std::vector;

void dijkstra(vector<vector<int>> &adj, vector<vector<int>> &cost, int s, vector<int> &dist)
{
  priority_queue<pair<int, int>, vector<pair<int, int>>, std::greater<pair<int, int>>> pq;
  dist[s] = 0;
  pq.push({0, s});
  while (!pq.empty())
  {
    int node = pq.top().second;
    pq.pop();
    for (int i = 0; i < adj[node].size(); i++)
    {
      if (dist[adj[node][i]] == -1 || dist[adj[node][i]] > dist[node] + cost[node][i])
      {
        dist[adj[node][i]] = dist[node] + cost[node][i];
        pq.push({dist[adj[node][i]], adj[node][i]});
      }
    }
  }
}

int distance(vector<vector<int>> &adj, vector<vector<int>> &cost, int s, int t)
{
  //write your code her
  vector<int> dist(adj.size(), -1);
  dijkstra(adj, cost, s, dist);
  return dist[t];
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
  int s, t;
  std::cin >> s >> t;
  s--, t--;
  std::cout << distance(adj, cost, s, t);
}
