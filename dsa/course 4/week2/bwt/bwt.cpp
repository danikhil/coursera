#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

string BWT(const string& text) {

  vector<string> v;

  int l = text.size(),k=1;
  for(int i=l-1;i>=0;i--)
  {
    v.push_back(text.substr(i,k++));
  }

  sort(v.begin(), v.end());

  string result="";

  for(auto i:v)
  {
    int s=i.size();
    result += text[(2*l-s-1)%l];
  }

  return result;
}

int main() {
  string text;
  cin >> text;
  cout << BWT(text) << endl;
  return 0;
}