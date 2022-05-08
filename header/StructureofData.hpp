#pragma once
#include <Ctime>
#include <algorithm>
#include <cctype>
#include <iostream>
#include <limits.h>
#include <math.h>
#include <numeric>
#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;
//***********************************************************************************************************************//

//链表
typedef struct ListNode
{
    int val;
    ListNode *next;
} * SqList;
SqList Creat_List(vector<int> v1)
{
    ListNode *L = new ListNode();
    L->next = NULL;
    ListNode *r = L;
    for (auto v : v1)
    {
        ListNode *temp = new ListNode();
        temp->val = v;
        temp->next = NULL;
        r->next = temp;
        r = r->next;
    }
    return L;
}
//***********************************************************************************************************************//
//二叉树
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
//***********************************************************************************************************************//
//排序
void InsertionSort(vector<int> &v)
{
    int N = v.size();
    int temp, j;
    if (N < 2)
        return;
    for (int i = 1; i < N; ++i)
    {
        temp = v[i];
        for (j = i; j > 0 && v[j - 1] > temp; --j)
            v[j] = v[j - 1];
        v[j] = temp;
    }
}
void BubbleSort(vector<int> &v)
{
    int N = v.size();
    bool flag;
    for (int i = 0; i < N; ++i)
    {
        flag = false;
        for (int j = N - 1; j > i; --j)
        {
            if (v[j] < v[j - 1])
            {
                swap(v[j], v[j - 1]);
                flag = true;
            }
        }
        if (flag == false)
            return;
    }
}
void SelectSort(vector<int> &v)
{
    int N = v.size();
    for (int i = 0; i < N; ++i)
    {
        int min = i;
        for (int j = i + 1; j < N; ++j)
            if (v[j] < v[min])
                min = j;
        if (min != i)
            swap(v[min], v[i]);
    }
}
void mergeSort(vector<int> &v, int l, int r)
{
    if (r - l < 1)
        return;
    int mid = l + ((r - l) >> 1);
    mergeSort(v, l, mid);        //递归排序左半边
    mergeSort(v, mid + 1, r);    //递归排序右半边
    vector<int> help(r - l + 1); //归并辅助数组
    int p1 = l, p2 = mid + 1, k = 0;
    while (p1 <= mid && p2 <= r)
        help[k++] = v[p1] <= v[p2] ? v[p1++] : v[p2++];
    while (p1 <= mid)
        help[k++] = v[p1++];
    while (p2 <= r)
        help[k++] = v[p2++];
    int n = help.size();
    for (int i = 0; i < n; ++i)
        v[l + i] = help[i];
}
int partition(vector<int> &nums, int l, int r)
{
    int pivot = nums[l];
    while (l < r)
    {
        while (nums[r] >= pivot && l < r)
            --r;
        nums[l] = nums[r];
        while (nums[l] <= pivot && l < r)
            ++l;
        nums[r] = nums[l];
    }
    nums[l] = pivot;
    return l;
}
void quickSort(vector<int> &nums, int l, int r)
{
    if (l < r)
    {
        int pivotpos = partition(nums, l, r);
        quickSort(nums, l, pivotpos - 1);
        quickSort(nums, pivotpos + 1, r);
    }
}
//***********************************************************************************************************************//
//查找
int search(const vector<int> &nums, int target) //二分找有序数组中下标最小的target（可能有重复数据）
{
    int l = 0, r = nums.size() - 1, mid;
    while (l <= r)
    {
        mid = l + ((r - l) >> 1);
        if (nums[mid] == target)
        {
            if (mid != 0 && nums[mid - 1] == target)
                r = mid - 1;
            else
                return mid;
        }
        else if (nums[mid] < target)
            l = mid + 1;
        else
            r = mid - 1;
    }
    return -1;
}