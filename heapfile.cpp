#include <bits/stdc++.h>
using namespace std;

class Page
{

public:
    int page_id;
    int cur_page_size;
    vector<pair<int, int>> data; // key, sz
    Page *next;
    Page(int pg)
    {
        page_id = pg;
        cur_page_size = 16;
    };
    ~Page();
};

Page::~Page()
{
}

int main()
{
    int maxsz;
    cin >> maxsz;
    Page *root = nullptr;
    int nop = 0;
    while (true)
    {
        int n;
        cin >> n;
        if (n == 1)
        {
            int bt, pk;
            cin >> bt >> pk;
            Page *cur = root;
            int flag = 0;
            while (cur != nullptr)
            {
                if (cur->cur_page_size + bt + 4 <= maxsz)
                {
                    cur->data.push_back(make_pair(pk, bt));
                    cur->cur_page_size += bt + 4;
                    flag = 1;
                    break;
                }
                cur = cur->next;
            }
            if (flag == 0)
            {
                Page *new_page = new Page(nop);
                new_page->data.push_back(make_pair(pk, bt));
                new_page->cur_page_size += bt + 4;
                new_page->page_id = nop;
                new_page->next = nullptr;
                nop++;
                if (root == nullptr)
                {
                    root = new_page;
                }
                else
                {
                    cur=root;
                    while (cur->next != nullptr)
                    {
                        cur = cur->next;
                    }
                    cur->next = new_page;
                }
            }
        }
        if (n == 2)
        {
            cout << nop << " ";
            Page *cur = root;
            while (cur != nullptr)
            {
                cout << cur->data.size() << " ";
                cur = cur->next;
            }
            cout << endl;
        }
        if (n == 3)
        {
            int x;
            cin >> x;
            Page *cur = root;
            int flag = 0;
            while (cur != nullptr)
            {
                for (int i = 0; i < cur->data.size(); i++)
                {
                    if (cur->data[i].first == x)
                    {
                        cout << cur->page_id << " " << i << endl;
                        flag = 1;
                        break;
                    }
                }
                if (flag == 1)
                    break;
                cur = cur->next;
            }
            if (flag == 0)
            {
                cout << -1 << " " << -1 << endl;
            }
        }
        if (n == 4)
            break;
    }
}
