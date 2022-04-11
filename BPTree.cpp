// creating b+ tree

#include <bits/stdc++.h>
using namespace std;

class node
{
public:
    vector<int> key;
    vector<node *> ptr;
    node *par;
    bool is_leaf;
    node()
    {
        par = nullptr;
    }
};

class tree
{
public:
    node *root;
    int t;
    int d;
    int noi, nod;
    tree(int t1, int d1)
    {
        t = t1;
        d = d1;
        root = NULL;
        noi = 0;
        nod = 0;
    }
    void insert(int);
    void insert_index_node_while_data(node *, node *);
    void split_index_node(node *);
};

void tree::split_index_node(node *p)
{
    // cout << " af" << noi << endl;
    node *new_node = new node;
    noi++;
    new_node->is_leaf = false;
    // new_node->p = p->p;
    for (int i = 0; i < t + 1; i++)
    {
        new_node->key.push_back(p->key[i + t + 1]);
        new_node->ptr.push_back(p->ptr[i + t + 1]);
    }
    new_node->ptr.push_back(p->ptr[2 * t + 2]);
    int k = p->key[t];
    while (p->key.size() > t)
    {
        p->key.pop_back();
        p->ptr.pop_back();
    }
    if (p->par == nullptr)
    {
        node *new_root = new node;
        noi++;
        new_root->is_leaf = false;
        new_root->key.push_back(k);
        new_root->ptr.push_back(p);
        new_root->ptr.push_back(new_node);
        p->par = new_root;
        new_node->par = new_root;
        root = new_root;
    }
    else
    {
        node *par = p->par;
        int i = 0;
        while (par->key[i] < k)
        {
            i++;
        }
        par->key.insert(par->key.begin() + i, k);
        par->ptr.insert(par->ptr.begin() + i + 1, new_node);
        new_node->par = par;
        if (par->key.size() > 2 * t)
        {
            split_index_node(par);
        }
    }
}

void tree::insert_index_node_while_data(node *par, node *nn)
{
    // cout << "pranshu" << endl;
    int i = 0;
    while (i < par->key.size() && par->key[i] < nn->key[0])
    {
        i++;
    }
    par->key.insert(par->key.begin() + i, nn->key[0]);
    par->ptr.insert(par->ptr.begin() + i + 1, nn);
    nn->par = par;
    // nn->key.erase(nn->key.begin());
    // nn->ptr.erase(nn->ptr.begin());
    // cout << "pandya" << par->key.size() << endl;
    // for(auto u:par->key)
    // {
    //     // cout << u << " ";
    // }
    // cout << endl;
    if (par->key.size() > 2 * t + 1)
    {
        // cout << "Adsf" << endl;
        split_index_node(par);
    }
}
void tree::insert(int k)
{
    if (root == NULL)
    {
        root = new node;
        nod++;
        root->is_leaf = true;
        root->key.push_back(k);
        return;
    }
    node *cursor = root;
    while (cursor->is_leaf == false)
    {
        int i = 0;
        while (i < cursor->key.size() && cursor->key[i] < k)
            i++;
        cursor = cursor->ptr[i];
    }
    // cout << "asdf" << endl;
    cursor->key.push_back(k);
    sort(cursor->key.begin(), cursor->key.end());
    if (cursor->key.size() > 2 * d)
    {
        node *new_node = new node;
        nod++;
        new_node->is_leaf = true;
        for (int i = 0; i < d + 1; i++)
        {
            int tmp = cursor->key[cursor->key.size() - 1];
            new_node->key.push_back(tmp);
            cursor->key.pop_back();
        }
        sort(new_node->key.begin(), new_node->key.end());
        if (cursor->par == nullptr)
        {
            // cout<<k<<' '<<"chala"<<endl;
            node *new_index = new node;
            noi++;
            new_index->is_leaf = false;
            new_index->key.push_back(new_node->key[0]);
            new_index->ptr.push_back(cursor);
            new_index->ptr.push_back(new_node);
            cursor->par = new_index;
            new_node->par = new_index;
            root = new_index;
        }
        else
        {
            // cout << "fasdfkj" << endl;
            insert_index_node_while_data(cursor->par, new_node);
        }
    }
}

int main()
{
    int d, t;
    cin >> d >> t;
    tree bptree(t, d);

    while (true)
    {
        int n;
        cin >> n;
        if (n == 1)
        {
            int x;
            cin >> x;
            bptree.insert(x);
        }
        if (n == 2)
        {
            cout << bptree.noi << " " << bptree.nod << " ";
            for (auto u : bptree.root->key)
                cout << u << " ";
            cout << endl;
        }
        if (n == 3)
        {
            break;
        }
    }
}
