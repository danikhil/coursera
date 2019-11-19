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

using std::min;
using std::queue;
using std::vector;

int bfs(vector<vector<int>> &adj, int s, vector<int> &dist)
{
  queue<int> q;
  dist[s] = 0;
  q.push(s);
  vector<int> visited(adj.size(), 0);
  while (!q.empty())
  {
    int k = q.front();
    visited[k] = 1;
    q.pop();
    for (auto i : adj[k])
    {
      if (!visited[i])
      {
        dist[i] = min(dist[k] + 1, dist[i]);
        q.push(i);
      }
    }
  }
}

int distance(vector<vector<int>> &adj, int s, int t)
{
  //write your code here
  vector<int> dist(adj.size(), 1e7);
  bfs(adj, s, dist);
  if (dist[t] >= 1e7)
    return -1;
  else
    return dist[t];
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
  int s, t;
  std::cin >> s >> t;
  s--, t--;
  std::cout << distance(adj, s, t);
}
