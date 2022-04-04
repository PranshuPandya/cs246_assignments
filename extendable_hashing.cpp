#include <bits/stdc++.h>
using namespace std;

class bucket
{
public:
    int capacity;
    vector<int> a;
    int local_depth;
    bool enable = false;
};

vector<bucket *> hash_table;
vector<int> order;
void double_hash_table(int ind, int global_depth)
{
    hash_table.resize(pow(2, global_depth));

    for (int i = pow(2, global_depth - 1); i < pow(2, global_depth); i++)
    {
        hash_table[i] = hash_table[i - pow(2, global_depth - 1)];
    }
    hash_table[ind + pow(2, global_depth - 1)] = new bucket;
    if (!hash_table[ind + pow(2, global_depth - 1)]->enable)
    {
        order.push_back(ind + pow(2, global_depth - 1));
        // cout << 'F' << ind + pow(2, global_depth - 1) << endl;
    }
    hash_table[ind + pow(2, global_depth - 1)]->enable = true;
    hash_table[ind + pow(2, global_depth - 1)]->local_depth = global_depth;
    hash_table[ind]->local_depth = global_depth;

    vector<int> tmp;
    tmp = hash_table[ind]->a;
    // tmp.push_back(x);
    hash_table[ind]->a.clear();
    for (int i = 0; i < tmp.size(); i++)
    {
        int ind = 0;
        int tm = tmp[i];
        for (int i = 0; i < global_depth; i++)
        {
            ind += pow(2, i) * (tm % 2);
            tm /= 2;
        }
        hash_table[ind]->a.push_back(tmp[i]);
        // if (hash_table[ind]->enable == false)
        // {
        //     hash_table[ind]->enable = true;
        //     // time++;
        //     order.push_back(ind);
        // }
    }
}
void increase_local_depth(int ind, int global_depth, int x)
{
    int tind = 0;
    int tmp = x;
    // cout << ind << " " << hash_table[ind]->local_depth << " ";
    bucket *tmpoint = hash_table[ind];
    for (int i = 0; i < tmpoint->local_depth - 1; i++)
    {
        tind += pow(2, i) * (tmp % 2);
        tmp /= 2;
    }
    tind += pow(2, tmpoint->local_depth - 1);
    // cout << tind;
    hash_table[tind] = new bucket;
    if (!hash_table[tind]->enable)
    {
        order.push_back(tind);
        // cout << " sf" << tind << " " << x << endl;
    }
    // order.push_back(tind);
    hash_table[tind]->enable = true;
    hash_table[tind]->local_depth = tmpoint->local_depth;
    // cout << tmpoint->local_depth << " ";
    vector<int> tmi;
    tmi = tmpoint->a;
    // tmi.push_back(x);
    tmpoint->a.clear();
    for (int i = 0; i < tmi.size(); i++)
    {
        int indi = 0;
        int tm = tmi[i];
        for (int i = 0; i < global_depth; i++)
        {
            indi += pow(2, i) * (tm % 2);
            tm /= 2;
        }
        hash_table[indi]->a.push_back(tmi[i]);

        // if (tmpoint->enable == false)
        // {
        //     tmpoint->enable = true;
        //     // time++;
        //     order.push_back(ind);
        // }
    }
    tind = 0;
    tmp = x;
    for (int i = 0; i < tmpoint->local_depth; i++)
    {
        tind += pow(2, i) * (tmp % 2);
        tmp /= 2;
    }
    for (int i = pow(2, hash_table[tind]->local_depth); i < pow(2, global_depth); i++)
    {
        if (i & tind == tind)
        {
            hash_table[i] = hash_table[tind];
            // cout<<"df"<<i<<" ";
        }
    }
    // cout<<endl;
}

int main()
{
    int global_depth, backet_cap;
    cin >> global_depth >> backet_cap;
    int option;
    int time = 0;

    // vector<bucket *> hash_table(pow(2, global_depth));
    hash_table.resize(pow(2, global_depth));
    for (int i = 0; i < pow(2, global_depth); i++)
    {
        hash_table[i] = new bucket;
        order.push_back(i);
        hash_table[i]->capacity = backet_cap;
        hash_table[i]->local_depth = global_depth;
    }

    while (true)
    {
        cin >> option;
        if (option == 6)
            break;
        if (option == 5)
        {
            // cout<<endl;
            cout << global_depth << endl;
            cout << order.size() << endl;
            for (auto u : order)
            {
                cout << hash_table[u]->a.size() << " " << hash_table[u]->local_depth << endl;
            }
            // for (int i = 0; i < order.size(); i++)
            // {
            //     cout << order[i] << " ";
            // }
            // cout << endl;
            // for (int i = 0; i < pow(2, global_depth); i++)
            // {
            //     cout << hash_table[i]->local_depth << " ";
            // }
            // cout << endl;
            // for (int i = 0; i < pow(2, global_depth); i++)
            // {
            //     cout << i << endl;
            //     for (int j = 0; j < hash_table[i]->a.size(); j++)
            //     {
            //         cout << hash_table[i]->a[j] << " ";
            //     }
            //     cout << endl;
            // }
        }
        if (option == 2)
        {
            int x;
            cin >> x;
            int ind = 0;
            while (global_depth <= 20)
            {
                int tm = x;
                ind = 0;
                for (int i = 0; i < global_depth; i++)
                {
                    ind += pow(2, i) * (tm % 2);
                    tm /= 2;
                }
                if (hash_table[ind]->a.size() < backet_cap)
                {
                    hash_table[ind]->a.push_back(x);
                    // if (hash_table[ind]->enable == false)
                    // {
                    //     hash_table[ind]->enable = true;
                    //     time++;
                    //     order.push_back(ind);
                    // }
                    break;
                }
                else if (hash_table[ind]->local_depth == global_depth)
                {
                    global_depth++;
                    double_hash_table(ind, global_depth);
                }
                else
                {
                    // cout << x << ind << hash_table[ind]->local_depth << global_depth << endl;
                    hash_table[ind]->local_depth++;
                    increase_local_depth(ind, global_depth, x);
                }
            }
        }
        if (option == 3)
        {
            int x;
            cin >> x;
        }
        if (option == 4)
        {
            int x;
            cin >> x;
            int ind = 0;
            int tm = x;
            for (int i = 0; i < global_depth; i++)
            {
                ind += pow(2, i) * (tm % 2);
                tm /= 2;
            }
            int r = 0;
            int i;
            for (i = 0; i < hash_table[ind]->a.size(); i++)
            {
                if (hash_table[ind]->a[i] == x)
                {
                    r = 1;
                    break;
                }
            }
            if (r == 1)
            {
                hash_table[ind]->a.erase(hash_table[ind]->a.begin() + i);
                // if(hash_table[ind]->a.size()==0)
                // {
                //     hash_table[ind]->enable=false;
                //     order.erase(order.begin()+ind);
                // }
            }
        }
    }
}
