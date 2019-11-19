#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <algorithm>

using std::cin;
using std::cout;
using std::max_element;
using std::string;
using std::vector;

class StackWithMax
{
    vector<int> stack;
    int maxE;

public:
    void Push(int value)
    {

        if (stack.empty())
        {
            this->maxE = value;
            stack.push_back(value);
        }
        else if (value <= maxE)
        {
            stack.push_back(value);
        }
        else
        {
            stack.push_back(2 * value - maxE);
            this->maxE = value;
        }
    }

    void
    Pop()
    {
        assert(stack.size());
        if (stack.back() > maxE)
        {
            this->maxE = 2 * this->maxE - stack.back();
        }
        stack.pop_back();
    }

    int Max() const
    {
        assert(stack.size());
        return maxE;
    }
};

int main()
{
    int num_queries = 0;
    cin >> num_queries;

    string query;
    string value;

    StackWithMax stack;

    for (int i = 0; i < num_queries; ++i)
    {
        cin >> query;
        if (query == "push")
        {
            cin >> value;
            stack.Push(std::stoi(value));
        }
        else if (query == "pop")
        {
            stack.Pop();
        }
        else if (query == "max")
        {
            cout << stack.Max() << "\n";
        }
        else
        {
            assert(0);
        }
    }
    return 0;
}