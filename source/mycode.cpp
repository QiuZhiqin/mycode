#include "StructureofData.hpp"
#include <string.h>
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

//给定一个节点数为 n 的二叉树和一个值 sum ，请找出所有的根节点到叶子节点的节点值之和等于的路径，如果没有则返回空。
class solution1
{
public:
    vector<vector<int>> ans;
    void dfs(TreeNode *root, int sum, vector<int> path)
    {
        path.push_back(root->val);
        if (root->left == nullptr && root->right == nullptr)
        {
            if (root->val == sum)
            {
                ans.push_back(path);
                return;
            }
        }
        else
        {
            if (root->left)
                dfs(root->left, sum - root->val, path);
            if (root->right)
                dfs(root->right, sum - root->val, path);
        }
    }
    vector<vector<int>> pathSum(TreeNode *root, int sum)
    {
        ans.clear();
        if (!root)
            return ans;
        vector<int> path;
        dfs(root, sum, path);
        return ans;
    }
};
/*
描述
一个 DNA 序列由 A/C/G/T 四个字母的排列组合组成。 G 和 C 的比例（定义为 GC-Ratio ）是序列中 G 和 C 两个字母的总的出现次数除以总的字母数目（也就是序列长度）。在基因工程中，这个比例非常重要。因为高的 GC-Ratio 可能是基因的起始点。

给定一个很长的 DNA 序列，以及限定的子串长度 N ，请帮助研究人员在给出的 DNA 序列中从左往右找出 GC-Ratio 最高且长度为 N 的第一个子串。
DNA序列为 ACGT 的子串有: ACG , CG , CGT 等等，但是没有 AGT ， CT 等等

输入的字符串只包含 A/C/G/T 字母

输入描述：
输入一个string型基因序列，和int型子串的长度

输出描述：
找出GC比例最高的子串,如果有多个则输出第一个的子串
*/
int func3()
{
    char str[1001] = {0};
    int N, n = 0, max_ratio = 0;
    scanf("%s\n", &str);
    scanf("%d", &N);
    char ans[N];
    int len = strlen(str);
    int count[len + 1];            //用于存储i之前有多少C或者G，不包括i
    for (int i = 0; i <= len; ++i) //初始化count
        count[i] = 0;
    for (int i = 0; i < len; ++i)
    {
        if (str[i] == 'G' || str[i] == 'C')
            n++;
        count[i + 1] = n;
    }
    for (int i = 0; i + N <= len; ++i)
    {
        int cur = count[i + N] - count[i]; // cur表示从i开始的子串有多少C或者G
        if (cur > max_ratio)
        {
            max_ratio = cur;
            strncpy(ans, str + i, N);
        }
    }
    for (int i = 0; i < N; ++i)
        printf("%c", ans[i]);
    return 0;
}

/*
正整数A和正整数B 的最小公倍数是指 能被A和B整除的最小的正整数值，设计一个算法，求输入A和B的最小公倍数。
*/
int gcd(int a, int b)
{
    if (b == 0)
        return a;
    else
        return gcd(b, a % b);
}
int func4()
{
    int a, b;
    scanf("%d%d", &a, &b);
    printf("%d", (a * b) / gcd(a, b)); //两数乘积除以他们的最大公约数结果就是最小公倍数
    return 0;
}

//给定 n 个字符串，请对 n 个字符串按照字典序排列。
int func5()
{
    int n;
    scanf("%d\n", &n);
    char strs[n][101]; //单个字符串不长于100
    for (int i = 0; i < n; ++i)
        scanf("%s", strs[i]);
    for (int i = 1; i < n; ++i)
    {
        char temp[100];
        strcpy(temp, strs[i]);
        int j;
        for (j = i; j > 0 && strcmp(strs[j - 1], temp) > 0; --j)
        {
            strcpy(strs[j], strs[j - 1]);
        }
        strcpy(strs[j], temp);
    }
    for (int i = 0; i < n; ++i)
        printf("%s\n", strs[i]);
    return 0;
}

/*
开发一个坐标计算工具， A表示向左移动，D表示向右移动，W表示向上移动，S表示向下移动。从（0,0）点开始移动，从输入字符串里面读取一些坐标，并将最终输入结果输出到输出文件里面。

输入：

合法坐标为A(或者D或者W或者S) + 数字（两位以内）

坐标之间以;分隔。
*/
int charToint(char str[], int s, int e)
{
    int ans = 0;
    while (s + 1 < e)
    {
        ans = ans * 10;
        ans += (str[s + 1] - '0');
        s++;
    }
    return ans;
}
int isLegit(char str[], int s, int e) //判断输入是否合法
{
    if (e - s > 3) //长度超过3，返回0
        return 0;
    if (str[s] != 'W' && str[s] != 'A' && str[s] != 'S' && str[s] != 'D') //首位不合法，返回0
        return 0;
    for (int i = s + 1; i < e; ++i) //判断数字是否合法
        if (str[i] > '9' || str[i] < '0')
            return 0;
    return 1;
}
int func5()
{
    char str[10001];
    scanf("%s", str);
    int len = strlen(str);
    int s = 0, e = 0;
    int x = 0, y = 0;
    while (s < len && e < len)
    {
        while (e < len && str[e] != ';')
            e++;
        if (isLegit(str, s, e))
        {
            if (str[s] == 'A')
                x -= charToint(str, s, e);
            else if (str[s] == 'W')
                y += charToint(str, s, e);
            else if (str[s] == 'S')
                y -= charToint(str, s, e);
            else
                x += charToint(str, s, e);
        }
        s = e + 1;
        e = s;
    }
    printf("%d,%d", x, y);
    return 0;
}
/*
定义一个单词的“兄弟单词”为：交换该单词字母顺序（注：可以交换任意次），而不添加、删除、修改原有的字母就能生成的单词。
兄弟单词要求和原来的单词不同。例如： ab 和 ba 是兄弟单词。 ab 和 ab 则不是兄弟单词。
现在给定你 n 个单词，另外再给你一个单词 x ，让你寻找 x 的兄弟单词里，按字典序排列后的第 k 个单词是什么？
注意：字典中可能有重复单词。
*/
int isBrother(char *a, char *b) //判断是否是兄弟单词
{
    if (strcmp(a, b) == 0) //完全一致则不是兄弟
        return 0;
    int counts[26]; //利用数组统计字符出现次数，若两个字符串字符出现次数完全一致，则是兄弟
    int a_len = strlen(a), b_len = strlen(b);
    for (int i = 0; i < 26; ++i) // count初始化
        counts[i] = 0;
    for (int i = 0; i < a_len; ++i) //统计a字符串
        counts[a[i] - 'a']++;
    for (int i = 0; i < b_len; ++i) //统计b字符串
        counts[b[i] - 'a']--;
    for (int i = 0; i < 26; ++i)
        if (counts[i] != 0)
            return 0;
    return 1;
}
int func6()
{
    int n, k;
    char a[11];
    scanf("%d", &n);
    char strs[n][11];
    for (int i = 0; i < n; ++i)
    {
        scanf("%s", strs[i]);
    }
    scanf("%s", a);
    scanf("%d", &k);
    int a_len = strlen(a);
    int l = 0, r = n - 1;
    char temp[11];
    while (l <= r)
    {
        if (strlen(strs[l]) != a_len || !isBrother(a, strs[l])) //如果当前字符串不是兄弟，则将其与最后一个字符串交换，r前移
        {
            strcpy(temp, strs[r]);
            strcpy(strs[r], strs[l]);
            strcpy(strs[l], temp);
            r--;
        }
        else
            l++;
    }
    for (int i = 1; i <= r; ++i) //排序
    {
        strcpy(temp, strs[i]);
        int j;
        for (j = i; j > 0 && strcmp(strs[j - 1], temp) > 0; --j)
        {
            strcpy(strs[j], strs[j - 1]);
        }
        strcpy(strs[j], temp);
    }
    printf("%d\n", r + 1);
    if (k <= r) //判断k是否合法
        printf("%s", strs[k - 1]);
    return 0;
}

/*
输入一个字符串，返回其最长的数字子串，以及其长度。若有多个最长的数字子串，则将它们全部输出（按原字符串的相对位置）
本题含有多组样例输入。
*/
int func7()
{
    char str[201];
    while (scanf("%s", str) != EOF)
    {
        int len = strlen(str), maxsize = 0;
        char nums[len] = {};
        int start = 0, end = 0;
        while (start < len && end < len)
        {
            if (str[start] <= '9' && str[start] >= '0')
            {
                end = start;
                while (str[end] <= '9' && str[end] >= '0' && end < len)
                    end++;
                if (end - start > maxsize)
                {
                    maxsize = end - start;
                    strncpy(nums, str + start, end - start);
                    nums[end - start] = '\0'; //手动填0，因为strncpy不会在字符串后加'\0'，故需要手动添加
                }
                else if (end - start == maxsize)
                {
                    strncat(nums, str + start, end - start);
                }
                start = end;
            }
            else
                start++;
        }
        printf("%s,", nums);
        printf("%d\n", maxsize);
    }
    return 0;
}

/*
在命令行输入如下命令：

xcopy /s c:\\ d:\\e，

各个参数如下：

参数1：命令字xcopy

参数2：字符串/s

参数3：字符串c:\\

参数4: 字符串d:\\e

请编写一个参数解析程序，实现将命令行各个参数解析出来。


解析规则：

1.参数分隔符为空格
2.对于用""包含起来的参数，如果中间有空格，不能解析为多个参数。比如在命令行输入xcopy /s "C:\\program files" "d:\"时，参数仍然是4个，第3个参数应该是字符串C:\\program files，而不是C:\\program，注意输出参数时，需要将""去掉，引号不存在嵌套情况。
3.参数不定长

4.输入由用例保证，不会出现不符合要求的输入
*/
int func8()
{
    char str[1001], temp[1001];
    temp[0] = '\0';
    fgets(str, 1001, stdin);
    int len = strlen(str), s = 0, e, count = 0;
    str[len - 1] = '\0';
    len--;
    while (s < len)
    {
        if (str[s] == '"')
        {
            s++; // s跳到指令头字母
            e = s;
            while (str[e] != '"' && e < len) // e跳到"处，则从s到e（不包括e）则是指令
                e++;
            count++;
            strncat(temp, str + s, e - s);
            strcat(temp, "\n"); //加上换行符，方便输出
            s = e + 2;          //两跳，从'"'到' '再到首字母
        }
        else
        {
            e = s;
            while (str[e] != ' ' && e < len)
                e++;
            count++;
            strncat(temp, str + s, e - s);
            strcat(temp, "\n");
            s = e + 1; //一跳，从' '到首字母
        }
    }
    printf("%d\n", count);
    printf("%s", temp);
    return 0;
}

/*
给出一个字符串，该字符串仅由小写字母组成，定义这个字符串的“漂亮度”是其所有字母“漂亮度”的总和。
每个字母都有一个“漂亮度”，范围在1到26之间。没有任何两个不同字母拥有相同的“漂亮度”。字母忽略大小写。

给出多个字符串，计算每个字符串最大可能的“漂亮度”。
*/
void BubbleSort(int nums[], int n) //从大到小的冒泡
{
    int flag;
    for (int i = 0; i < n; ++i)
    {
        flag = 0;
        for (int j = n - 1; j > i; --j)
        {
            if (nums[j] > nums[j - 1])
            {
                int temp = nums[j];
                nums[j] = nums[j - 1];
                nums[j - 1] = temp;
                flag = 1;
            }
        }
        if (flag == 0)
            break;
    }
}
int func8()
{
    int N, ans;
    scanf("%d\n", &N); // N表有多少个字符串
    for (int i = 0; i < N; ++i)
    {
        ans = 0;
        int hash[26] = {0};
        char str[10001];
        scanf("%s", str);
        int len = strlen(str);
        for (int i = 0; i < len; ++i)
        {
            str[i] = toupper(str[i]); //不分大小写，故全部转化为大写
            if (str[i] <= 'Z' && str[i] >= 'A')
                hash[str[i] - 'A']++;
        }
        BubbleSort(hash, 26); //把hash从大到小排序
        for (int i = 0; i < 26; ++i)
            ans += (26 - i) * hash[i]; //按出现次数分权值
        printf("%d\n", ans);
    }
    return 0;
}

/*
输出1到n之间与7有关的数有多少个
*/
int func9()
{
    int n, ans = 0;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        if (i % 7 == 0)
            ans++;
        else
        {
            int cur = i;
            while (cur)
            {
                if (cur % 10 == 7)
                {
                    ans++;
                    break;
                }
                cur /= 10;
            }
        }
    }
    printf("%d", ans);
    return 0;
}

/*
查找两个字符串a,b中的最长公共子串。若有多个，输出在较短串中最先出现的那个。
注：子串的定义：将一个字符串删去前缀和后缀（也可以不删）形成的字符串。请和“子序列”的概念分开！
*/
int func10()
{
    char str1[1000], str2[1000], ans[1000];
    int i, j, n, max;
    while (scanf("%s %s", str1, str2) != EOF)
    {
        if (strlen(str1) > strlen(str2)) //选择较短子串为str1
        {
            char temp[1000];
            strcpy(temp, str1);
            strcpy(str1, str2);
            strcpy(str2, temp);
        }
        max = 0;
        for (i = 0; i < strlen(str1); i++)
        {
            for (j = 0; j < strlen(str2); j++)
            {
                n = 0;
                while (str1[i + n] == str2[j + n] && str1[i + n] != '\0')
                {
                    n++;
                }
                if (n > max)
                {
                    max = n;
                    strcpy(ans, str1 + i);
                    ans[max] = '\0';
                }
            }
        }
        printf("%s\n", ans);
    }
    return 0;
}

/*
光标在第一首歌曲上时，按Up键光标挪到最后一首歌曲；光标在最后一首歌曲时，按Down键光标挪到第一首歌曲。

2. 歌曲总数大于4的时候（以一共有10首歌为例）：
特殊翻页：屏幕显示的是第一页（即显示第1 – 4首）时，光标在第一首歌曲上，用户按Up键后，屏幕要显示最后一页（即显示第7-10首歌），
同时光标放到最后一首歌上。同样的，屏幕显示最后一页时，光标在最后一首歌曲上，用户按Down键，屏幕要显示第一页，光标挪到第一首歌上。

一般翻页：屏幕显示的不是第一页时，光标在当前屏幕显示的第一首歌曲时，用户按Up键后，屏幕从当前歌曲的上一首开始显示，光标也挪到上
一首歌曲。光标当前屏幕的最后一首歌时的Down键处理也类似。
*/
int func11()
{
    int n;
    char order[101];
    scanf("%d\n", &n);
    scanf("%s", order);
    int up = 1, low = n > 4 ? 4 : n, cur = 1, len = strlen(order);
    for (int i = 0; i < len; ++i)
    {
        if (order[i] == 'U')
        {
            if (cur != up)
                cur--;
            else
            {
                if (n <= 4)
                    cur = low;
                else if (up == 1)
                {
                    up = n - 3;
                    low = n;
                    cur = low;
                }
                else
                {
                    up--;
                    cur = up;
                    low--;
                }
            }
        }
        else if (order[i] == 'D')
        {
            if (cur != low)
                cur++;
            else
            {
                if (n <= 4)
                    cur = up;
                else if (low == n)
                {
                    up = 1;
                    cur = up;
                    low = 4;
                }
                else
                {
                    up++;
                    low++;
                    cur = low;
                }
            }
        }
    }
    for (int i = up; i <= low; ++i)
        printf("%d ", i);
    printf("\n%d", cur);
    return 0;
}

//求最大子数组和
int maxSubArray(vector<int> &nums)
{
    int sum = 0, max_sum = INT_MIN;
    for (const int &a : nums)
    {
        sum += a;
        max_sum = max(max_sum, sum);
        if (sum < 0) //如果当前和小于0，则抛弃前段，直接从0开始往后
            sum = 0;
    }
    return max_sum;
}
int maxSubArrayWithDP(vector<int> &nums)
{
    int len = nums.size(), max_num = INT_MIN;
    if (len == 1)
        return nums[0];
    int dp[len];
    for (int i = 0; i < len; ++i)
    {
        if (i == 0)
            dp[i] = nums[0];
        else
            dp[i] = max(nums[i], dp[i - 1] + nums[i]);
        max_num = max(dp[i], max_num);
    }
    return max_num;
}

//矩阵乘法
int func12()
{
    int x, y, z;
    scanf("%d\n%d\n%d\n", &x, &y, &z);
    int m1[x][y], m2[y][z], ans[x][z];
    for (int i = 0; i < x; ++i)
        for (int j = 0; j < y; ++j)
            scanf("%d ", &m1[i][j]);
    for (int i = 0; i < y; ++i)
        for (int j = 0; j < z; ++j)
            scanf("%d ", &m2[i][j]);
    for (int i = 0; i < x; ++i)
    {
        for (int j = 0; j < z; ++j)
        {
            int cur = 0;
            for (int k = 0; k < y; ++k)
                cur += m1[i][k] * m2[k][j];
            ans[i][j] = cur;
        }
    }
    for (int i = 0; i < x; ++i)
    {
        for (int j = 0; j < z; ++j)
            printf("%d ", ans[i][j]);
        printf("\n");
    }
    return 0;
}

//计算一个浮点数的立方根，不使用库函数。保留一位小数。
int func12()
{
    double num;
    int is_neg = 0;
    scanf("%lf", &num);
    if (num < 0)
    {
        num = -num;
        is_neg = 1;
    }
    double l = 0, r = num < 1 ? 1 : num, mid, temp;
    while (l <= r)
    {
        mid = l + (r - l) / 2;
        temp = mid * mid * mid;
        double cmp = num > temp ? num - temp : temp - num;
        if (cmp <= 0.0001)
        {
            if (is_neg == 0)
                printf("%.1lf", mid);
            else
                printf("-%.1lf", mid);
            break;
        }
        else if (num < temp)
            r = mid;
        else
            l = mid;
    }
    return 0;
}

/*
请计算n*m的棋盘格子（n为横向的格子数，m为竖向的格子数）从棋盘左上角出发沿着边缘线从左上角走到右下角，总共有多少种走法，要求不能走回头路，即：只能往右和往下走，不能往左和往上走。

注：沿棋盘格之间的边缘线行走
*/
//递归写法
int help(int n, int m)
{
    int res;
    if (n == 0 || m == 0)
        res = 1;
    else
        res = help(n - 1, m) + help(n, m - 1);
    return res;
}
int func13()
{
    int n, m;
    scanf("%d %d", &n, &m);
    int ans = help(n, m);
    printf("%d", ans);
    return 0;
}
//非递归
int func14(int n, int m)
{
    int n, m;
    scanf("%d %d", &n, &m);
    int dp[n + 1][m + 1];
    for (int i = 0; i <= n; ++i)
    {
        for (int j = 0; j <= m; ++j)
        {
            if (i == 0 && j == 0)
                dp[i][j] = 1;
            else if (i == 0)
                dp[i][j] = dp[i][j - 1];
            else if (j == 0)
                dp[i][j] = dp[i - 1][j];
            else
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
        }
    }
    printf("%d", dp[n][m]);
    return 0;
}

/*
输入一个单向链表，输出该链表中倒数第k个结点，链表的倒数第1个结点为链表的尾指针。
正常返回倒数第k个结点指针，异常返回空指针.
要求：
(1)正序构建链表;
(2)构建后要忘记链表长度。
*/
int func13()
{
    int n, k;
    while (scanf("%d", &n) != EOF)
    {
        LNode *head = (LNode *)malloc(sizeof(LNode));
        LNode *p = head, *q;
        for (int i = 0; i < n; ++i)
        {
            LNode *temp = (LNode *)malloc(sizeof(LNode));
            scanf("%d", &temp->val);
            temp->next = NULL;
            p->next = temp;
            p = p->next;
        }
        scanf("%d", &k);
        p = head;
        q = head;
        for (int i = 0; i < k; ++i)
        {
            if (q == NULL)
                return 0;
            q = q->next;
        }
        while (q)
        {
            q = q->next;
            p = p->next;
        }
        printf("%d\n", p->val);
    }
    return 0;
}

/*
任意一个偶数（大于2）都可以由2个素数组成，组成偶数的2个素数有很多种情况，本题目要求输出组成指定偶数的两个素数差值最小的素数对。
*/
int isPrime(int x)
{
    int size = sqrt(x);
    for (int i = 2; i <= size; ++i)
        if (x % i == 0)
            return 0;
    return 1;
}
int func14()
{
    int n, ans;
    scanf("%d", &n);
    for (int i = 1; i <= n / 2; ++i)
    {
        if (isPrime(i) && isPrime(n - i))
            ans = i;
    }
    printf("%d\n%d", ans, n - ans);
    return 0;
}

/*
动态规划求最长回文子串，时间复杂度O(n²)，空间复杂度O(n²)
*/
int func15()
{
    char str[351];
    scanf("%s\n", str);
    int len = strlen(str);
    if (len < 2)
    {
        printf("%d", len);
        return 0;
    }
    int dp[len][len], ans = 1;
    for (int i = 0; i < len; ++i)
        dp[i][i] = 1;
    for (int j = 0; j < len; ++j)
    {
        for (int i = 0; i <= j; ++i)
        {
            if (str[i] != str[j])
                dp[i][j] = 0;
            else
            {
                if ((j - i < 3) || dp[i + 1][j - 1])
                {
                    dp[i][j] = j - i + 1;
                    ans = dp[i][j] > ans ? dp[i][j] : ans;
                }
                else
                    dp[i][j] = 0;
            }
        }
    }
    printf("%d", ans);
    return 0;
}

/*
dfs走迷宫
其中的1表示墙壁，0表示可以走的路，只能横着走或竖着走，不能斜着走，
要求编程序找出从左上角到右下角的路线。入口点为[0,0],既第一格是可以走的路。
*/
void dfs1(const vector<vector<int>> &nums, vector<vector<int>> path, int x, int y, vector<vector<int>> &ans, vector<vector<bool>> visited)
{
    if (x >= nums.size() || y >= nums[0].size() || nums[x][y] == 1 || visited[x][y])
        return;
    if (nums[x][y] == 0)
    {
        path.push_back({x, y});
        visited[x][y] = true;
    }
    if (x == nums.size() - 1 && y == nums[0].size() - 1)
    {
        ans = path;
        return;
    }
    dfs1(nums, path, x + 1, y, ans, visited);
    dfs1(nums, path, x, y + 1, ans, visited);
    dfs1(nums, path, x - 1, y, ans, visited);
    dfs1(nums, path, x, y - 1, ans, visited);
}
int func16()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>> nums(n, vector<int>(m));
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
            cin >> nums[i][j];
    }
    vector<vector<int>> path, ans;
    vector<vector<bool>> visited(n, vector<bool>(m));
    dfs1(nums, path, 0, 0, ans, visited);
    for (const auto &a : ans)
        cout << "(" << a[0] << "," << a[1] << ")" << endl;
    return 0;
}

/*
如何得到一个数据流中的中位数？如果从数据流中读出奇数个数值，那么中位数就是所有数值排序之后位于中间的数值。
如果从数据流中读出偶数个数值，那么中位数就是所有数值排序之后中间两个数的平均值。我们使用Insert()方法读取数据流，
使用GetMedian()方法获取当前读取数据的中位数。
*/
class Solution1
{
public:
    priority_queue<double, vector<double>, less<double>> maxInt;
    priority_queue<double, vector<double>, greater<double>> minInt;
    void adjust()
    {
        if (maxInt.size() >= minInt.size() + 2)
        {
            minInt.push(maxInt.top());
            maxInt.pop();
        }
        else if (minInt.size() >= maxInt.size() + 2)
        {
            maxInt.push(minInt.top());
            minInt.pop();
        }
    }
    void Insert(int num)
    {
        if (maxInt.empty() || num <= maxInt.top()) //大堆为空或者待插入数小于堆顶，插入大堆，否则插入小堆
            maxInt.push(num);
        else
            minInt.push(num);
        adjust(); //每次对大小堆进行调整，使得大小堆大小差距不超过1
    }

    double GetMedian()
    {
        if (maxInt.size() == minInt.size())
            return (maxInt.top() + minInt.top()) / 2;
        else if (maxInt.size() > minInt.size())
            return maxInt.top();
        else
            return minInt.top();
    }
};

/*
给定一个长度为n的数组arr，返回arr的最长无重复元素子数组的长度，无重复指的是所有数字都不相同。
子数组是连续的，比如[1,3,5,7,9]的子数组有[1,3]，[3,5,7]等等，但是[1,3,7]不是子数组
*/
int maxLength(vector<int> &arr)
{
    int size = arr.size(), maxlen = 0, l = 0, r = 0;
    unordered_set<int> visited; //存放子数组元素
    while (l < size)
    {
        while (visited.find(arr[r]) == visited.end() && r < size) //未重复则拓展数组
        {
            visited.insert(arr[r]);
            r++;
        }
        //跳出循环说明出现重复或者遍历完毕，先更新最大子数组长度，再“吐出”最左边元素，继续检查是否重复
        maxlen = max(maxlen, r - l);
        visited.erase(arr[l++]);
    }
    return maxlen;
}