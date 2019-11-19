#include <algorithm>
#include <iostream>
#include <vector>
#include <stack>

using std::pair;
using std::stack;
using std::vector;

#define INF 0x3f3f3f3f;

vector<vector<int>> reverse_edges(vector<vector<int>> &adj)
{
  vector<vector<int>> radj(adj.size());
  for (int i = 0; i < adj.size(); i++)
  {
    for (auto n : adj[i])
    {
      radj[n].push_back(i);
    }
  }
  return radj;
}

void dfs(vector<vector<int>> &adj, int cur, vector<int> &visited, stack<int> &st)
{
  visited[cur] = 1;
  for (int n : adj[cur])
  {
    if (!visited[n])
    {
      dfs(adj, n, visited, st);
    }
  }
  st.push(cur);
}

int number_of_strongly_connected_components(vector<vector<int>> adj)
{
  int result = 0;
  //write your code here
  stack<int> st;
  vector<int> visited(adj.size(), 0);

  for (int i = 0; i < adj.size(); i++)
  {
    if (!visited[i])
    {
      dfs(adj, i, visited, st);
    }
  }
  vector<vector<int>> radj = reverse_edges(adj);
  std::fill(visited.begin(), visited.end(), 0);

  while (!st.empty())
  {
    int cur = st.top();
    st.pop();
    if (!visited[cur])
    {
      stack<int> cst;
      dfs(radj, cur, visited, cst);
      result++;
    }
  }
  return result;
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
  }
  std::cout << number_of_strongly_connected_components(adj);
}
