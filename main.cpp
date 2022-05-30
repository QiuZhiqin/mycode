#include "header/StructureofData.hpp"
#include "header/student.hpp"
#include <algorithm>
#include <cctype>
#include <queue>
#include <unistd.h>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;
struct business
{
    int cost;
    int profit;
};
bool cmp1(const business &a, const business &b)
{
    return a.profit < b.profit;
}
bool cmp2(const business &a, const business &b)
{
    return a.cost > b.cost;
}
int findMaximizedCapital(int k, int m, vector<int> &costs, vector<int> &profits)
{
    int size = costs.size();
    struct business businesses[size];
    for (int i = 0; i < size; ++i)
    {
        businesses[i].cost = costs[i];
        businesses[i].profit = profits[i];
    }
    priority_queue<struct business, vector<struct business>, decltype(*cmp2)> all(*cmp2);
    priority_queue<struct business, vector<struct business>, decltype(*cmp1)> affordable(*cmp1);
    for (int i = 0; i < size; ++i)
        all.push(businesses[i]);
    while (k)
    {
        if (affordable.empty() && all.top().cost > m)
            break;
        while (all.top().cost <= m && !all.empty())
        {
            affordable.push(all.top());
            all.pop();
        }
        if (affordable.empty())
            break;
        m += affordable.top().profit;
        affordable.pop();
        k--;
    }
    return m;
}
int main()
{
    char str[10001];
    fgets(str, 10001, stdin);
    int n = strlen(str), index = 0;
    char words[n / 2][21], temp[21];
    int s = 0, e;
    while (s < n && e < n)
    {
        memset(temp, '\0', 21);
        while (s < n && !isalpha(str[s]))
            s++;
        e = s;
        while (e < n && isalpha(str[e]))
            e++;
        strncpy(temp, str + s, e - s);
        strcpy(words[index++], temp);
        s = e;
        s++;
    }
    index--;
    while (index >= 0)
    {
        printf("%s ", words[index--]);
    }
    return 0;
}