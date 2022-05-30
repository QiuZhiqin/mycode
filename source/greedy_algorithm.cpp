#include "StructureofData.hpp"
//前缀树
struct TrieNode
{
    int path;
    int end;
    TrieNode *nexts[26];
};
class Trie
{
private:
    TrieNode *root;

public:
    Trie() { root = new TrieNode(); }
    ~Trie() { delete root; }
    void Insert(string word);
};
void Trie::Insert(string word)
{
    if (word.size() == 0)
        return;
    TrieNode *node = root;
    node->path++;
    int index = 0;
    for (auto &a : word)
    {
        index = a - 'a';
        if (node->nexts[index] == nullptr)
            node->nexts[index] = new TrieNode();
        node = node->nexts[index];
        node->path++;
    }
    node->end++;
}

/*给定一个长度为 n 的字符串数组 strs ，请找到一种拼接顺序，使得数组中所有的字
符串拼接起来组成的字符串是所有拼接方案中字典序最小的，并返回这个拼接后的字符串。*/
string minString(vector<string> &strs)
{
    sort(strs.begin(), strs.end(), [](const string &a, const string &b)
         { return a + b < b + a; }); //按str1+str2<str2+str1排序
    string ans = {};
    for (const auto &s : strs)
        ans += s;
    return ans;
}

/*一些项目要占用一个会议室宣讲，会议室不能同时容纳两个项目的宣讲。 给你每一个项目开始的时间和结束的时间
(给你一个数组，里面是一个个具体的项目)，你来安排宣讲的日程，要求会议室进行的宣讲的场次最多。 返回这个最多的宣讲场次。
*/
int greedy1()
{
    int n, ans = 0, cur = 0;
    cin >> n;
    vector<pair<int, int>> help(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> help[i].first >> help[i].second;
    }
    //按结束时间从早到晚排序，结束时间一样时按开始时间从早到晚排序
    sort(help.begin(), help.end(), [](const pair<int, int> &a, const pair<int, int> &b)
         {if(a.second!=b.second)return a.second<b.second;else return a.first<b.first; });
    for (const auto &a : help)
    {
        if (a.first >= cur)
        {
            ans++;
            cur = a.second;
        }
    }
    cout << ans;
    return 0;
}

/*
输入： 正数数组costs， 正数数组profits ，正数k ，正数m
含义： costs[i]表示i号项目的花费 ，profits[i]表示i号项目在扣除花费之后还能挣到的钱(利润)， k表示你只能串行的最多做k个项目 ，m表示你初始的资金
 说明： 你每做完一个项目，马上获得的收益，可以支持你去做下一个项目。 输出： 你最后获得的最大钱数。
*/
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
    //用于保存所有任务，cost最小的位于top
    priority_queue<struct business, vector<struct business>, decltype(*cmp2)> all(*cmp2);
    //用于保存当前能支付得起的任务，profit最大的位于top
    priority_queue<struct business, vector<struct business>, decltype(*cmp1)> affordable(*cmp1);
    for (int i = 0; i < size; ++i)
        all.push(businesses[i]);
    while (k)
    {
        while (all.top().cost <= m && !all.empty()) //付得起的入队
        {
            affordable.push(all.top());
            all.pop();
        }
        if (affordable.empty()) //没有付得起的，退出
            break;
        m += affordable.top().profit; //更新本金
        affordable.pop();
        k--;
    }
    return m;
}
