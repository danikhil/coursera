#include <cstdio>
#include <string>
#include <iostream>

using namespace std;

struct Node
{
	int index;
	char c;
	Node *next;

	Node(int index, char c, Node *next) : index(index), c(c), next(next) {}
};

class Rope
{
	std::string s;
	Node *str;

public:
	Rope(const std::string &s)
	{
		this->s = s;
		str = new Node(-1, 0, NULL);
		Node *it = str;
		for (int i = 0; i < s.length(); i++)
		{
			it->next = new Node(i, s[i], NULL);
			it = it->next;
		}
		// 		it=it->next;
		// 		if(it==NULL)
		// 		cout << "I'm here";
	}

	void update_index()
	{
		Node *it = str;
		int i = -1;
		while (it)
		{
			it->index = i++;
			it = it->next;
		}
	}

	void process(int i, int j, int k)
	{
		Node *left = NULL, *right = NULL, *pos = NULL, *it = str;
		if (k == i)
			return;
		if (k - 1 >= i)
			k += j - i;
		else
			k -= 1;
		while (it)
		{
			if (it->index == i - 1)
				left = it;
			if (it->index == j)
				right = it;
			if (it->index == k)
				pos = it;
			if (left && right && pos)
			{
				//cout << "I'm here";
				break;
			}
			it = it->next;
		}
		// cout << left->index <<'\n';
		// cout << right->c << '\n';
		// cout << pos->c << '\n';
		Node *tmp = pos->next;
		pos->next = left->next;
		left->next = right->next;
		right->next = tmp;
		update_index();
	}

	void result()
	{
		Node *it = str->next;
		while (it)
		{
			cout << it->c;
			it = it->next;
		}
	}
};

int main()
{
	std::ios_base::sync_with_stdio(0);
	std::string s;
	std::cin >> s;
	Rope rope(s);
	int actions;
	std::cin >> actions;
	for (int action_index = 0; action_index < actions; ++action_index)
	{
		int i, j, k;
		std::cin >> i >> j >> k;
		rope.process(i, j, k);
	}
	//cout << "I'm here too";
	rope.result();
}
