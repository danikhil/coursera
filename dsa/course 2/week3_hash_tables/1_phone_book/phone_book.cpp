#include <iostream>
#include <vector>
#include <string>
#include <map>

using std::cin;
using std::cout;
using std::map;
using std::string;
using std::vector;

int main()
{
    map<int, string> phonebook;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        string s;
        cin >> s;
        if (s == "add")
        {
            int num;
            string name;
            cin >> num >> name;
            phonebook[num] = name;
        }
        else if (s == "find")
        {
            int num;
            cin >> num;
            if (phonebook.find(num) == phonebook.end())
            {
                cout << "not found";
            }
            else
            {
                cout << phonebook[num];
            }
            cout << '\n';
        }
        else
        {
            int num;
            cin >> num;
            phonebook.erase(num);
        }
    }
    return 0;
}
