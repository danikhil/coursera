#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;
using std::max;
using std::vector;

struct DisjoinSet
{
	int root;
	int weight;
};

int find_root(vector<DisjoinSet> &dsu, int node)
{
	while (dsu[node].root != node)
	{
		dsu[node].root = dsu[dsu[node].root].root;
		node = dsu[node].root;
	}
	return node;
}

void set_union(vector<DisjoinSet> &dsu, int x, int y, int *max_weight)
{
	int root_x = find_root(dsu, x);
	int root_y = find_root(dsu, y);
	if (root_x == root_y)
		return;
	if (dsu[root_x].weight < dsu[root_y].weight)
	{
		dsu[root_y].root = root_x;
		dsu[root_x].weight += dsu[root_y].weight;
		*max_weight = max(dsu[root_x].weight, *max_weight);
	}
	else
	{
		dsu[root_x].root = root_y;
		dsu[root_y].weight += dsu[root_x].weight;
		*max_weight = max(dsu[root_y].weight, *max_weight);
	}
}

int main()
{
	int n, m;
	cin >> n >> m;

	int max_weight = 0;
	vector<DisjoinSet> dsu(n);
	for (int i = 0; i < n; i++)
	{
		cin >> dsu[i].weight;
		dsu[i].root = i;
		max_weight = max(max_weight, dsu[i].weight);
	}
	for (int i = 0; i < m; i++)
	{
		int x, y;
		cin >> x >> y;
		set_union(dsu, x - 1, y - 1, &max_weight);
		cout << max_weight << '\n';
	}
	return 0;
}
