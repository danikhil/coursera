#include <iostream>
#include <vector>
#include <string>
#include <cstring>
using namespace std;

int calculate_overlap(const string &A, const string &B, const int mer)
{
    for(int i=0;i+mer<A.size();i++)
    {
        if(strncmp(A.c_str()+i, B.c_str(), A.size()-i)==0)
        return A.size()-i;
    }
    return 0;
}

string assemble_genome(vector<string> &reads, const int mer)
{
    string genome=reads[0];
    string cur_read;
    int cur_index=0;

    while(reads.size()>1)
    {
        cur_read = reads[cur_index];
        reads.erase(reads.begin()+cur_index);

        int max_overlap = -1;

        for(int j=0;j<reads.size();j++)
        {
            int overlap = calculate_overlap(cur_read, reads[j], mer);
            if(overlap>max_overlap)
            max_overlap=overlap, cur_index=j;
        }

        genome += reads[cur_index].substr(max_overlap);
    }

    return genome.erase(0, calculate_overlap(reads[0], genome, mer));
}


int main()
{
    // ios_base::sync_with_stdio(false);
    // cin.tie(NULL);

    vector<string> reads;
    string s;
    while(cin >> s)
        reads.emplace_back(s);

    cout << assemble_genome(reads, 11);
    return 0;
}