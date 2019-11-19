#include <algorithm>
#include <iostream>
#include <vector>
#include <limits.h>
using std::cin;
using std::cout;
using std::endl;
using std::vector;

struct Node
{
  long key;
  int left;
  int right;

  Node() : key(0), left(-1), right(-1) {}
  Node(int key_, int left_, int right_) : key(key_), left(left_), right(right_) {}
};

void set_flag(const vector<Node> &tree, int i, long min, long max, bool &flg)
{
  if (i == -1)
    return;
  if (tree[i].key < min || tree[i].key >= max)
  {
    flg = false;
    return;
  }

  set_flag(tree, tree[i].left, min, tree[i].key, flg);

  set_flag(tree, tree[i].right, tree[i].key, max, flg);
}

bool IsBinarySearchTree(const vector<Node> &tree)
{
  // Implement correct algorithm here
  if (tree.size() <= 1)
    return true;
  bool flg = true;
  long min = LONG_MIN, max = LONG_MAX;
  set_flag(tree, 0, min, max, flg);
  return flg;
}

int main()
{
  int nodes;
  cin >> nodes;
  vector<Node> tree;
  for (int i = 0; i < nodes; ++i)
  {
    long key;
    int left, right;
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
