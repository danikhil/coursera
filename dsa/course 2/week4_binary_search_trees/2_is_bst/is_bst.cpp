#include <algorithm>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

struct Node
{
  int key;
  int left;
  int right;

  Node() : key(0), left(-1), right(-1) {}
  Node(int key_, int left_, int right_) : key(key_), left(left_), right(right_) {}
};

void in_order(vector<int> &results, int node, const vector<Node> &tree)
{
  if (node == -1)
    return;

  in_order(results, tree[node].left, tree);
  results.push_back(tree[node].key);
  in_order(results, tree[node].right, tree);
}

bool IsBinarySearchTree(const vector<Node> &tree)
{
  // Implement correct algorithm here
  if (tree.size() == 0)
    return true;
  vector<int> result;
  in_order(result, 0, tree);
  for (int i = 1; i < result.size(); i++)
    if (result[i] < result[i - 1])
      return false;
  return true;
}

int main()
{
  int nodes;
  cin >> nodes;
  vector<Node> tree;
  for (int i = 0; i < nodes; ++i)
  {
    int key, left, right;
    cin >> key >> left >> right;
    tree.push_back(Node(key, left, right));
  }
  if (IsBinarySearchTree(tree))
  {
    cout << "CORRECT" << endl;
  }
  else
  {
    cout << "INCORRECT" << endl;
  }
  return 0;
}
