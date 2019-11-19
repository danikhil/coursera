#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

using std::pair;
using std::vector;

bool dfs(const vector<vector<int>> &adj, int current, int destination, vector<bool> &visited)
{
  if (current == destination)
    return true;
  visited[current] = true;
  bool s = false;
  for (auto i : adj[current])
  {
    if (!visited[i])
      s = s || dfs(adj, i, destination, visited);
  }
  return s;
}

int reach(vector<vector<int>> &adj, int x, int y)
{
  //write your code here
  vector<bool> visited(adj.size(), false);
  return dfs(adj, x, y, visited);
}

int main()
{
  size_t n, m;
  std::cin >> n >> m;
  vector<vector<int>> adj(n, vector<int>());
  for (size_t i = 0; i < m; i++)
  {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }
  int x, y;
  std::cin >> x >> y;
  std::cout << reach(adj, x - 1, y - 1);
}
