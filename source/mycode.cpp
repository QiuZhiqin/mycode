#include "StructureofData.hpp"
using namespace std;
/*
编写一个程序，将输入字符串中的字符按如下规则排序。

规则 1 ：英文字母从 A 到 Z 排列，不区分大小写。

如，输入： Type 输出： epTy

规则 2 ：同一个英文字母的大小写同时存在时，按照输入顺序排列。

如，输入： BabA 输出： aABb

规则 3 ：非英文字母的其它字符保持原来的位置。
*/
void func1()
{
    string ans;
    getline(cin, ans);
    vector<pair<char, bool>> letters; //用于存储字母并排序，使用pair是为了保存大小写信息，将所有字母小写化方便排序
    bool isaletter[ans.size()];       //用于判断该位置是否为字母
    int index = 0, n = ans.size();
    for (const char &a : ans)
    {
        if (a >= 'a' && a <= 'z')
        {
            letters.push_back({a, false});
            isaletter[index++] = true;
        }
        else if (a >= 'A' && a <= 'Z')
        {
            letters.push_back({a + 32, true});
            isaletter[index++] = true;
        }
        else
        {
            isaletter[index++] = false;
        }
    }
    int j;
    for (int i = 1; i < letters.size(); i++) //插排稳定，故可保证同级字母相对位置不变
    {
        pair<char, bool> temp = letters[i];
        for (j = i; j > 0 && letters[j - 1].first > temp.first; --j)
            letters[j] = letters[j - 1];
        letters[j] = temp;
    }
    index = 0;
    for (int i = 0; i < n; ++i)
    {
        if (isaletter[i] == true) //如果该位置是字母，则修改为排序好的数组元素；若不是字母，保持原样
        {
            if (letters[index].second == true)
                ans[i] = letters[index++].first - 32;
            else
                ans[i] = letters[index++].first;
        }
    }
    cout << ans;
}
/*
月神拿到一个新的数据集，其中每个样本都是一个字符串，样本的的后六位是纯数字，月神需要将所有样本的后六位数字提出来，转换成数字，并排序输出。

注意：这里的排序并不是针对每个字符串的后六位，而是需要按数字大小顺序输出所有样本的后六位数字。

月神要实现这样一个很简单的功能确没有时间，作为好朋友的你，一定能解决月神的烦恼，对吧。
*/
int func2()
{
    int n;
    cin >> n;
    getchar();
    string data_set[n];
    for (int i = 0; i < n; ++i)
        getline(cin, data_set[i]);
    int nums[n];                //用于存储转换后的数字
    for (int i = 0; i < n; ++i) //以下部分用于转换每个字符串后六位为数字
    {
        int m = data_set[i].size(), res = 0;
        for (int j = m - 6; j < m; ++j)
            res = res * 10 + (data_set[i][j] - '0');
        nums[i] = res;
    }
    for (int i = 1; i < n; ++i) //插排
    {
        int temp = nums[i], j;
        for (j = i - 1; j >= 0 && nums[j] > temp; --j)
            nums[j + 1] = nums[j];
        nums[j + 1] = temp;
    }
    for (int i = 0; i < n; ++i)
        cout << nums[i] << endl;
    return 0;
}
/*
给定一组不重叠的时间区间，在时间区间中插入一个新的时间区间(如果有重叠的话就合并区间)。
这些时间区间初始是根据它们的开始时间排序的。
示例1:
给定时间区间[1,3]，[6,9]，在这两个时间区间中插入时间区间[2,5]，并将它与原有的时间区间合并，变成[1,5],[6,9].
示例2：
给定时间区间[]16],在这些时间区间中插入时间区间[4,9]，并将它与原有的时间区间合并，变成[1,2],[3,10],[12,16].
这是因为时间区间[4,9]覆盖了时间区间[3,5],[6,7],[8,10].
示例1
*/
struct Interval
{
    int start;
    int end;
    Interval(int s, int e) : start(start), end(e) {}
};

class Solution3
{
public:
    vector<Interval> insert(vector<Interval> &intervals, Interval newInterval)
    {
        int n = intervals.size(), i;
        int ns = newInterval.start, ne = newInterval.end;
        vector<Interval> ans;
        for (i = 0; i < n; ++i)
        {
            if (ns > intervals[i].end)
                ans.push_back(intervals[i]);
            else if (ne < intervals[i].start) //新区间与旧区间不相交，直接跳出
                break;
            else //以下是合并区间的过程，且可能合并多个
            {
                ns = min(ns, intervals[i].start);
                ne = max(ne, intervals[i].end);
            }
        }
        newInterval.start = ns; //更新区间信息
        newInterval.end = ne;
        ans.push_back(newInterval); //插入新区间
        for (; i < n; ++i)          //插入剩余不变的区间
            ans.push_back(intervals[i]);
        return ans;
    }
};
/*
P为给定的二维平面整数点集。定义P中某点x，如果x满足P中任意点都不在x的右上方区域内（横纵坐标都大于x），
则称其为“最大的”。求出所有“最大的”点的集合。（所有点的横坐标和纵坐标都不重复,坐标轴范围在[0, 1e9]内）
输出“最大的”点集合， 按照X轴从小到大的方式输出，每行两个数字分别代表点的X轴和Y轴。
*/
struct point
{
    int x;
    int y;
    point(int n = 0, int e = 0) : x(n), y(e) {}
};
int func3()
{
    int n;
    cin >> n;
    point points[n];
    for (int i = 0; i < n; ++i)
        cin >> points[i].x >> points[i].y;
    sort(points, points + n, [](point a, point b)
         { return a.y > b.y; }); //按y从大到小排序
    vector<point> ans;
    ans.push_back(points[0]); //放入排序后数组的首元素，一定是最大点
    for (int i = 1; i < n; ++i)
    {
        int cmp = (ans.end() - 1)->x; //在按x从小到大排序的数组ans中，只需与末尾元素的x比较即可，若比其大，
        if (cmp < points[i].x)        //则比其前面所有最大点的x都大
            ans.push_back(points[i]); //直接将点插入数组末尾即可保证有序
    }
    for (const point &a : ans)
        cout << a.x << " " << a.y << endl;
    return 0;
}

//判断回文链表
ListNode *ReverseList(ListNode *pHead) //翻转链表，返回反转后的头节点（不为空）
{
    if (pHead == nullptr)
        return pHead;
    ListNode *p = pHead->next, *q;
    pHead->next = nullptr;
    while (p != nullptr)
    {
        q = p;
        p = p->next;
        q->next = pHead;
        pHead = q;
    }
    return pHead;
}
bool isPail(ListNode *head)
{
    ListNode *f = head, *s = head;
    while (f->next != nullptr && f != nullptr) //快慢指针
    {
        f = f->next->next;
        s = s->next;
    }
    f = ReverseList(s); //从慢指针逆转
    s = head;
    while (s != nullptr && f != nullptr) //两头开始对比
    {
        if (s->val != f->val)
            return false;
    }
    return true;
}