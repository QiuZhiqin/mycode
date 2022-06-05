#include "StructureofData.hpp"

//打印n层汉诺塔从最左边移动到最右边的全部过程
void process(int n, string from, string to, string other)
{
    if (n == 1)
        cout << "Move 1 from " << from << " to " << to << endl; //只有一块
    else
    {
        process(n - 1, from, other, to);                                  //将n-1块移动到other，给第n块腾位置
        cout << "Move " << n << " from " << from << " to " << to << endl; //将第n块挪到to
        process(n - 1, other, to, from);                                  //再将n-1块移动到to，完成
    }
}
int hanoi()
{
    int n;
    cin >> n;
    process(n, "left", "right", "mid");
    return 0;
}

//打印一个字符串的全部子序列，包括空字符串，重复的也要
void getSub(const string &s, int index, string path, vector<string> &ans)
{
    if (index >= s.size())
    {
        ans.push_back(path);
        return;
    }
    getSub(s, index + 1, path, ans);            //不取当前字符
    getSub(s, index + 1, path + s[index], ans); //取当前字符
}
vector<string> getAllSubs(string s)
{
    vector<string> ans;
    string path = ""; // path用于暂存当前路径
    getSub(s, 0, path, ans);
    return ans;
}

//全排列
void permute(string cur, string path, vector<string> &ans)
{
    if (cur.size() == 0)
    {
        ans.push_back(path);
        return;
    }
    for (int i = 0; i < cur.size(); i++)
    {
        string next = cur;
        next.erase(i, 1);
        permute(next, path + cur[i], ans);
    }
}

/*
给定一个数字，我们按照如下规则把它转换为字符串：1转换成 “a” ，2 转换成 “b”，……，12 转换成 “l”，……，26转换成 “z”。
一个数字可能有多个转换。请编程实现一个函数，用来计算一个数字有多少种不同的转换方法。
*/
int process2(const string &number, int index)
{
    if (index == number.size())
        return 1;
    if (number[index] == '0')
        return 0;
    if (number[index] == '1')
    {
        int res = process2(number, index + 1);
        if (index + 1 < number.size())
            res += process2(number, index + 2);
        return res;
    }
    else if (number[index] == '2')
    {
        int res = process2(number, index + 1);
        if (index + 1 < number.size() && number[index + 1] >= '0' && number[index + 1] <= '6')
            res += process2(number, index + 2);
        return res;
    }
    else
        return process2(number, index + 1);
}
int translateNumber(string number)
{
    int ans = process2(number, 0);
    return ans;
}

// 0-1背包
struct goods
{
    int weight;
    int value;
};
int select(const struct goods help[], int index, int N, int res_capacity, int sum_value)
{
    if (index == N)
        return sum_value;
    int ans1, ans2 = -1;
    ans1 = select(help, index + 1, N, res_capacity, sum_value);
    if (res_capacity >= help[index].weight)
        ans2 = select(help, index + 1, N, res_capacity - help[index].weight, sum_value + help[index].value);
    return max(ans1, ans2);
}
int func2()
{
    int N, V;
    cin >> N >> V;
    struct goods help[N];
    for (int i = 0; i < N; ++i)
        cin >> help[i].value >> help[i].weight;
    int ans = select(help, 0, N, V, 0);
    cout << ans;
    return 0;
}

// N皇后的解法
class solution1
{
public:
    int firstpick(int cards[], int l, int r) //先手
    {
        if (l == r) //没得挑，返回该点值
            return cards[l];
        //拿左边或者右边的牌后进入后手选方式
        return max(cards[l] + secondpick(cards, l + 1, r), cards[r] + secondpick(cards, l, r - 1));
    }
    int secondpick(int cards[], int l, int r) //后手
    {
        if (l == r) //最后一张牌在对手手里，返回
            return 0;
        //这里不加边界值的原因是对手选牌，不需要加入自己的总值
        return min(firstpick(cards, l + 1, r), firstpick(cards, l, r - 1));
    }
    int main()
    {
        int n;
        cin >> n;
        int cards[n];
        for (int i = 0; i < n; ++i)
            cin >> cards[i];
        cout << max(firstpick(cards, 0, n - 1), secondpick(cards, 0, n - 1));
        return 0;
    }
};

class N_Queens
{
public:
    /*
    limit把控全局，表示可用的位置，n皇后则后n位为1
    colLim表示列重合，重合的位置置1，可用位置为0
    leftDiaLim表示左对角线重合
    rightDiaLim表示右对角线重合
    */
    int process(int limit, int colLim, int leftDiaLim, int rightDiaLim) //因为使用int，最多可解决32皇后
    {
        if (colLim == limit) //后n为都为1，表示已经放满
            return 1;
        int pos = limit & (~(colLim | leftDiaLim | rightDiaLim)); //通过按位与操作获取能用的位置，1表示可用
        int ans = 0, mostRightOne = 0;
        while (pos)
        {
            mostRightOne = pos & (~pos + 1); //此操作用于获取pos最右边的1
            pos = pos - mostRightOne;
            //对于下一行，左对角线重合位需要左移一位，右对角线重合位同理右移
            ans += process(limit, colLim | mostRightOne,
                           (leftDiaLim | mostRightOne) << 1,
                           (rightDiaLim | mostRightOne) >> 1);
        }
        return ans;
    }
    int main(int argc, char **argv)
    {
        int n;
        cin >> n;
        int ans = process(pow(2, n) - 1, 0, 0, 0);
        cout << ans << endl;
        return 0;
    }
};

/*
已知 n 个整数 x1,x2,…,xn，以及一个整数 k（k＜n）。从 n 个整数中任选 k 个整数相加，可分别得到一系列的和。
例如当 n=4，k＝3，4 个整数分别为 3，7，12，19 时，可得全部的组合与它们的和为：
3＋7＋12=22　　3＋7＋19＝29　　7＋12＋19＝38　　3＋12＋19＝34。
现在，要求你计算出和为素数共有多少种。
例如上例，只有一种的和为素数：3＋7＋19＝29）。
*/
class solution2
{
public:
    int isPrime(int x)
    {
        int size = sqrt(x);
        for (int i = 2; i <= size; ++i)
            if (x % i == 0)
                return 0;
        return 1;
    }
    int add(int nums[], int index, int k, int sum, int n)
    {
        if (k == 0 && isPrime(sum))
            return 1;
        if (index >= n)
            return 0;
        return add(nums, index + 1, k - 1, sum + nums[index], n) + add(nums, index + 1, k, sum, n);
    }
    int main()
    {
        int n, k;
        cin >> n >> k;
        int nums[n];
        for (int i = 0; i < n; ++i)
            cin >> nums[i];
        int ans = add(nums, 0, k, 0, n);
        cout << ans;
        return 0;
    }
};
