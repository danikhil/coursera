#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <queue>
#include <math.h>

using std::cin;
using std::cout;
using std::queue;
using std::vector;

bool dfs(vector<vector<int>> &adj, int cur, vector<int> &visited, vector<int> &recStack)
{
  if (visited[cur] == 0)
  {
    visited[cur] = recStack[cur] = 1;
    for (auto node : adj[cur])
    {
      if (!visited[node] && dfs(adj, node, visited, recStack))
        return 1;
      else if (recStack[node])
        return 1;
    }
  }
  recStack[cur] = 0;
  return 0;
}

int acyclic(vector<vector<int>> &adj)
{
  //write your code here
  vector<int> visited(adj.size(), 0);
  vector<int> recStack(adj.size(), 0);
  for (int i = 0; i < adj.size(); i++)
    if (!visited[i])
      if (dfs(adj, i, visited, recStack))
        return true;
  return false;
}

int main()
{
  size_t n, m;
  cin >> n >> m;
  vector<vector<int>> adj(n, vector<int>());
  for (size_t i = 0; i < m; i++)
  {
    int x, y;
    cin >> x >> y;
    adj[x - 1].push_back(y - 1);
  }
  cout << acyclic(adj);
}
