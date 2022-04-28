#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
struct mice
{
    int weight, rank, index, sequence;
};
int main()
{
    int Np, Ng;
    cin >> Np >> Ng;
    vector<mice> m(Np);
    queue<mice> remain;
    for (int i = 0; i < Np; ++i)
    {
        cin >> m[i].weight;
        m[i].sequence = i;
    }
    for (int i = 0; i < Np; ++i)
    {
        int j;
        cin >> j;
        m[j].index = i;
    }
    sort(m.begin(), m.end(), [](mice x, mice y)
         { return x.index < y.index; });
    for (mice &x : m)
        remain.push(x);
    sort(m.begin(), m.end(), [](mice x, mice y)
         { return x.sequence < y.sequence; });
    while (!remain.empty())
    {
        mice temp;
        int size = remain.size(), maxw = 0, cnt = 0;
        int group = size / Ng;
        if (size % Ng)
            ++group;
        if (size == 1)
        {
            m[remain.front().sequence].rank = 1;
            remain.pop();
            break;
        }
        for (int i = 0; i < size; ++i)
        {
            if (remain.front().weight > maxw)
            {
                maxw = remain.front().weight;
                temp = remain.front();
            }
            m[remain.front().sequence].rank = group + 1;
            remain.pop();
            ++cnt;
            if (cnt == Ng || i == size - 1)
            {
                maxw = 0;
                cnt = 0;
                remain.push(temp);
            }
        }
    }
    sort(m.begin(), m.end(), [](mice x, mice y)
         { return x.sequence < y.sequence; });
    for (int i = 0; i < Np; ++i)
    {
        if (i != 0)
            cout << " ";
        cout << m[i].rank;
    }

    return 0;
}