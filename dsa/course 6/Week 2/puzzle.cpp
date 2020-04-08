#include <bits/stdc++.h>
using namespace std;

struct Square
{
    string up, left, down, right;
    Square() {};
    Square(string &up, string &left, string &down, string &right): up(up), left(left), down(down), right(right) {}
    Square(const Square &A)
    {
        this->up=A.up;
        this->down=A.down;
        this->left=A.left;
        this->right=A.right;
    }

    void print()
    {
        cout << '(' << up << ',' << left << ',' << down << ',' << right << ')';
    }

    void reinitialize(const Square &A)
    {
        this->up=A.up;
        this->down=A.down;
        this->left=A.left;
        this->right=A.right;
    }

    int corner_sqaure()
    {
        if(this->up=="black"&&this->left=="black")
        return 1;
        else if(this->left=="black"&&this->down=="black")
        return 3;
        else if(this->down=="black"&&this->right=="black")
        return 4;
        else if(this->right=="black"&&this->up=="black")
        return 2;
        return 0;
    }
    
    int square_place()
    {
        if(this->up=="black")
        return 1;
        else if(this->left=="black")
        return 2;
        else if(this->down=="black")
        return 3;
        else if(this->right=="black")
        return 4;
        return 5;
    }
};

typedef vector< vector<Square> >  Square_puzzle;

bool check_up(const vector<int> &up, const vector<Square> &v)
{
    for(int i=1;i<up.size();i++)
    {
        Square left(v[up[i-1]]), right(v[up[i]]);
        if(left.right!=right.left)
            return false;
    }
    return true;
}

bool check_left(const vector<int> &left, const vector<Square> &v)
{
    for(int i=1;i<left.size();i++)
    {
        Square up(v[left[i-1]]), down(v[left[i]]);
        if(up.down!=down.up)
            return false;
    }
    return true;
}

bool check_down(const vector<int> &down, const vector<Square> &v)
{
    for(int i=1;i<down.size();i++)
    {
        Square left(v[down[i-1]]), right(v[down[i]]);
        if(left.right!=right.left)
            return false;
    }
    return true;
}

bool check_right(const vector<int> &right, const vector<Square> &v)
{
    for(int i=1;i<right.size();i++)
    {
        Square up(v[right[i-1]]), down(v[right[i]]);
        if(up.down!=down.up)
            return false;
    }
    return true;
}

bool check_middle(const vector<int> &middle, const vector<int> up, const vector<int> left, const vector<Square> &v)
{
    int size = v.size();
    int r_size = sqrt(size);
    
    for(int i=0;i<middle.size();i++)
    {
        Square L, U, C(v[middle[i]]);
        if(i<r_size-2)
        {
            U.reinitialize(v[up[i+1]]);
        }
        else 
        U.reinitialize(v[middle[i-(r_size-2)]]);
        if(i%(r_size-2)==0)
        L.reinitialize(v[left[i/(r_size-2)+1]]);
        else
        L.reinitialize(v[middle[i-1]]);
        if(L.right!=C.left||U.down!=C.up)
        return false;
    }
    return true;
}

vector<int> solve_puzzle(vector<Square> &v)
{
    int size = v.size();
    int r_size = sqrt(size);
    vector<int> solved_position(size, -1);
    vector<int> up(r_size),left(r_size),down(r_size),right(r_size),middle;

    int u=1,d=1,l=1,r=1;

    for(int i=0;i<size;i++)
    {
        int p = v[i].corner_sqaure();
        int q = v[i].square_place();
        if(p==1)
        {
            solved_position[0]=i;
            up[0]=i;
            left[0]=i;
        }
        else if(p==2)
        {
            solved_position[r_size-1]=i;
            right[0]=i;
            up[r_size-1]=i;
        }
        else if(p==3)
        {
            solved_position[size-r_size]=i;
            left[r_size-1]=i;
            down[0]=i;
        }
        else if(p==4)
        {
            solved_position[size-1]=i;
            right[r_size-1]=i;
            down[r_size-1]=i;
        }
        else if(q==1)
        up[u++]=i;
        else if(q==2)
        left[l++]=i;
        else if(q==3)
        down[d++]=i;
        else if(q==4)
        right[r++]=i;
        else
        middle.push_back(i);        
    }

    while(!check_up(up, v))
    {
        next_permutation(up.begin()+1,up.end()-1);
    }
    while(!check_left(left, v))
    {
        next_permutation(left.begin()+1,left.end()-1);
    }
    while(!check_right(right, v))
    {
        next_permutation(right.begin()+1,right.end()-1);
    }
    while(!check_down(down, v))
    {
        next_permutation(down.begin()+1,down.end()-1);
    }

    for(int i=1, j=r_size, k=(r_size-1)*r_size+1, m=2*r_size-1;i<r_size-1;i++,k++, j+=r_size, m+=r_size)
    {
        solved_position[i]=up[i];
        solved_position[j]=left[i];
        solved_position[k]=down[i];
        solved_position[m]=right[i];
    }

    while(!check_middle(middle, up, left, v))
    {
        next_permutation(middle.begin(), middle.end());
    }

    for(int i=r_size, j=0;i<size-r_size;i++)
    {
        if( i%r_size ==0 || i%r_size == (r_size-1))
        continue;
        else
        {
            solved_position[i]=middle[j++];
        }
    }
    return solved_position;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    vector<Square> v;
    string up, left, down, right, tmp;
    while(getline(cin, up, ','))
    {
        up = up.substr(1);
        getline(cin, left, ',');
        getline(cin, down, ',');
        getline(cin, right, ')');
        getline(cin, tmp, '\n');
        v.push_back(Square(up, left, down, right));
    }
    
    int size = v.size();
    int r_size = sqrt(size);

    vector<int> solved_position = solve_puzzle(v);

    for(int i=0;i<size;i++)
    {
        v[solved_position[i]].print();
        if(i%r_size==(r_size-1))
        cout << '\n';
        else 
        cout << ';';
    }
    return 0;
}