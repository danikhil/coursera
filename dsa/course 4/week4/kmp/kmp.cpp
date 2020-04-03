#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::string;
using std::vector;

// Find all occurrences of the pattern in the text and return a
// vector with all positions in the text (starting from 0) where 
// the pattern starts in the text.

vector<int> prefix_function(const string &pattern)
{
  int j=0,len=pattern.length(),i=1;

  vector<int> pf(len,0);
  while(i<len)
  {
    if(pattern[i]==pattern[j])
    {
      j++;
      pf[i]=j;
      i++;
    }
    else if(j)
    {
      j=pf[j-1];
    }
    else
    {
      pf[i]=0;
      i++;
    }
    
  }
  return pf;
}


vector<int> find_pattern(const string& pattern, const string& text) {
  vector<int> result;
  // Implement this function yourself

  vector<int> pf = prefix_function(pattern);

  int i=0,j=0, len=text.length();

  while(i<len)
  {
    if(text[i]==pattern[j])
    {
      i++,j++;
    }
    else if(j)
    {
      j=pf[j-1];
    }
    else
    {
      i++;
    }
    if(j==pattern.length())
    {
      result.push_back(i-j);
      j=pf[j-1];
    }
  }
  return result;
}

int main() {
  string pattern, text;
  cin >> pattern;
  cin >> text;
  vector<int> result = find_pattern(pattern, text);
  for (int i = 0; i < result.size(); ++i) {
    printf("%d ", result[i]);
  }
  printf("\n");
  return 0;
}
