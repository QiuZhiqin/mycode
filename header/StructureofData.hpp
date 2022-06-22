#pragma once
#include <Ctime>
#include <algorithm>
#include <cctype>
#include <iostream>
#include <limits.h>
#include <math.h>
#include <numeric>
#include <queue>
#include <set>
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
} * SqList, LNode;
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
ListNode *FindFirstCommonNode(ListNode *pHead1, ListNode *pHead2) //无环链表
{
    int n = 0;
    ListNode *p = pHead1, *q;
    while (p != nullptr)
    {
        n++;
        p = p->next;
    }
    p = pHead2;
    while (p != nullptr)
    {
        n--;
        p = p->next;
    }
    p = n < 0 ? pHead2 : pHead1;
    q = n < 0 ? pHead1 : pHead2;
    n = abs(n);
    while (n > 0)
    {
        p = p->next;
        n--;
    }
    while (p != nullptr && q != nullptr)
    {
        if (p == q)
            return p;
        p = p->next;
        q = q->next;
    }
    return nullptr;
}
ListNode *GetLoopNode(ListNode *head)
{
    ListNode *slow = head, *fast = head;
    while (fast != nullptr)
    {
        slow = slow->next;
        if (fast->next == nullptr)
        {
            return nullptr;
        }
        fast = fast->next->next;
        if (fast == slow)
        {
            ListNode *ptr = head;
            while (ptr != slow)
            {
                ptr = ptr->next;
                slow = slow->next;
            }
            return ptr;
        }
    }
    return nullptr;
}
ListNode *insertionSortList(ListNode *head) //链表插排（不含头节点）
{
    if (head == nullptr || head->next == nullptr)
        return head;
    ListNode *new_head = new ListNode();
    new_head->next = new ListNode();
    new_head->next->val = head->val;
    ListNode *cur = head->next, *pre = new_head;
    head->next = nullptr; //原链表断链
    while (cur != nullptr)
    {
        pre = new_head;
        while (cur->val > pre->next->val && pre->next != nullptr)
            pre = pre->next;
        ListNode *temp = cur->next; //保护cur的next指向
        cur->next = pre->next;
        pre->next = cur;
        cur = temp;
    }
    return new_head->next;
}

ListNode *deleteDuplicates(ListNode *head) //删除所有重复节点（全部删除不留重复项，例如{1,1,3}删完得{3}）
{
    if (head == NULL)
        return NULL;
    ListNode *res = new ListNode;
    //在链表前加一个表头
    res->next = head;
    ListNode *cur = res;
    while (cur->next != NULL && cur->next->next != NULL)
    {
        //遇到相邻两个节点值相同
        if (cur->next->val == cur->next->next->val)
        {
            int temp = cur->next->val;
            //将所有相同的都跳过
            while (cur->next != NULL && cur->next->val == temp)
                cur->next = cur->next->next;
        }
        else
            cur = cur->next;
    }
    //返回时去掉表头
    return res->next;
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
//以下为三种遍历的非递归实现
vector<int> preOrder(TreeNode *root)
{
    vector<int> ans;
    if (root == nullptr)
        return ans;
    stack<TreeNode *> help;
    help.push(root);
    while (!help.empty())
    {
        TreeNode *temp = help.top();
        help.pop();
        ans.push_back(temp->val);
        if (temp->right != nullptr)
            help.push(temp->right);
        if (temp->left != nullptr)
            help.push(temp->left);
    }
    return ans;
}
vector<int> postOrder(TreeNode *root)
{
    vector<int> ans;
    if (root == nullptr)
        return ans;
    stack<TreeNode *> help1, help2; //使用两个栈，第一个栈出栈后加入第二个栈
    help1.push(root);
    while (!help1.empty())
    {
        TreeNode *temp = help1.top();
        help1.pop();
        help2.push(temp);
        if (temp->left != nullptr) //先入左子节点，保证出栈顺序为中右左，从而使得第二个栈出栈顺序为左右中
            help1.push(temp->left);
        if (temp->right != nullptr)
            help1.push(temp->right);
    }
    while (!help2.empty())
    {
        TreeNode *temp = help2.top();
        help2.pop();
        ans.push_back(temp->val);
    }
    return ans;
}
vector<int> inOrder(TreeNode *root)
{
    vector<int> ans;
    if (root == nullptr)
        return ans;
    stack<TreeNode *> help;
    TreeNode *cur = root;
    while (!help.empty() || cur != nullptr)
    {
        if (cur != nullptr)
        {
            help.push(cur);
            cur = cur->left;
        }
        else
        {
            cur = help.top();
            help.pop();
            ans.push_back(cur->val);
            cur = cur->right;
        }
    }
    return ans;
}

int getMaxWidth(TreeNode *head) //求最大宽度（在层序基础上修改而成）
{
    if (head == nullptr)
        return 0;
    queue<TreeNode *> help;
    unordered_map<TreeNode *, int> level_map;
    int CNode = 0, maxNode = 0, level = 1;
    level_map.insert({head, 1});
    help.push(head);
    while (!help.empty())
    {
        TreeNode *temp = help.front();
        help.pop();
        if (level_map[temp] != level)
        {
            level++;
            CNode = 0;
        }
        CNode++;
        maxNode = max(maxNode, CNode);
        if (temp->left != nullptr)
        {
            help.push(temp->left);
            level_map.insert({temp->left, level + 1});
        }
        if (temp->right != nullptr)
        {
            help.push(temp->right);
            level_map.insert({temp->right, level + 1});
        }
    }
    return maxNode;
}

bool isBST(TreeNode *root, int low, int high)
{
    if (root == nullptr)
        return true;
    if (root->val <= low || root->val >= high)
        return false;
    return isBST(root->left, low, root->val) && isBST(root->right, root->val, high);
}

bool isFBT(TreeNode *root)
{
    if (root == nullptr)
        return true;
    queue<TreeNode *> help;
    help.push(root);
    bool flag = false;
    while (!help.empty())
    {
        TreeNode *temp = help.front();
        help.pop();
        if ((!temp->left) && temp->right)
            return false;
        if (flag == true && (temp->left != nullptr || temp->right != nullptr))
            return false;
        if (temp->left)
            help.push(temp->left);
        if (temp->right)
            help.push(temp->right);
        else
            flag = true;
    }
    return true;
}

int getDepth(TreeNode *root)
{
    if (root == nullptr)
        return 0;
    return max(getDepth(root->left), getDepth(root->right)) + 1;
}

bool isBalanced(TreeNode *pRoot)
{
    if (pRoot == nullptr)
        return true;
    int help = abs(getDepth(pRoot->left) - getDepth(pRoot->right));
    if (help > 1)
        return false;
    return isBalanced(pRoot->left) && isBalanced(pRoot->right);
}

TreeNode *dfs(TreeNode *root, int o1, int o2)
{
    if (root == nullptr)
    {
        return nullptr;
    }
    if (root->val == o1 || root->val == o2)
        return root;
    TreeNode *t1 = dfs(root->left, o1, o2);
    TreeNode *t2 = dfs(root->right, o1, o2);
    if (t1 == nullptr)
        return t2;
    if (t2 == nullptr)
        return t1;
    return root;
}
int lowestCommonAncestor(TreeNode *root, int o1, int o2) //最近公共祖先
{
    return dfs(root, o1, o2)->val;
}

//***********************************************************************************************************************//
//排序
void insertionSort(vector<int> &v)
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

void CountSort(vector<int> &nums, int max_num)
{
    int n = nums.size(), index = 0;
    int count[max_num + 1];
    for (int i = 0; i <= max_num; ++i)
        count[i] = 0;
    for (int i = 0; i < n; ++i)
        count[nums[i]]++;
    for (int i = 0; i <= max_num; ++i)
    {
        for (int j = 0; j < count[i]; ++j)
            nums[index++] = i;
    }
}

int maxBit(vector<int> &v)
{
    int max = v[0];
    for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
    {
        if (*it > max)
        {
            max = *it;
        }
    }
    int bit = 0;
    while (max != 0)
    {
        bit++;
        max /= 10;
    }
    return bit;
}
//得到一个十进制数的第d位
int getdigit(int num, int d)
{
    return (int(num / pow(10, d))) % 10;
}

void radixSort(vector<int> &v, int digit)
{
    //先准备十个桶
    const int radix = 10;
    //准备一个辅助空间
    int *tempSpace = new int[v.size()];
    for (int d = 0; d < digit; d++)
    {
        int count[10] = {0};
        int j = 0; //记录每个数的次数
        for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
        {
            j = getdigit(*it, d);
            count[j]++;
        }
        //各个位置计数小于等于该位置数的次数
        for (int i = 1; i < radix; i++)
        {
            count[i] = count[i] + count[i - 1];
        }
        //从数组末端遍历
        for (vector<int>::reverse_iterator it = v.rbegin(); it != v.rend(); it++)
        {
            j = getdigit(*it, d);          //获取第d位的值
            tempSpace[count[j] - 1] = *it; //将此位置放在词频统计此范围的末端
            count[j]--;                    //安置好一个数，次数减一
        }
        //将辅助数组的值放回v里面
        for (int i = 0; i < v.size(); i++)
        {
            v[i] = tempSpace[i];
        }
    }
    delete[] tempSpace;
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

//***********************************************************************************************************************//
//图
struct node;
struct edge
{
    int weight;
    node *from;
    node *to;
    edge(int w, node *f, node *t) : weight(w), from(f), to(t) {}
    edge() {}
    ~edge() {}
    bool operator<(const edge &other) const { return weight > other.weight; }
};
struct node
{
    int val;
    int in;
    int out;
    set<node> nexts;
    vector<edge> edges;
    node(int x = 0) : val(x), in(0), out(0) {}
    ~node() {}
    bool operator<(node const &other) const { return val < other.val; }
};
struct graph
{
    vector<node> nodes;
    vector<edge> edges;
};
graph init(const vector<vector<int>> &g)
{
    graph G;
    unordered_map<int, node> created;
    node from, to;
    edge cur;
    for (auto &e : g)
    {
        edge cur = edge(e[2], &from, &to);
        if (created.find(e[0]) == created.end())
            from = node(e[0]);
        else
            from = created[e[0]];
        if (created.find(e[1]) == created.end())
            to = node(e[1]);
        else
            to = created[e[1]];
        from.out++;
        to.in++;
        from.nexts.insert(to);
        from.edges.push_back(cur);
        G.edges.push_back(cur);
        created.insert({e[1], to});
        created.insert({e[0], from});
    }
    for (auto &n : created)
    {
        G.nodes.push_back(n.second);
    }
    return G;
}
//并查集
int Find(vector<int> &father, int x)
{
    if (father[x] < 0)
        return x;
    else
    {
        father[x] = Find(father, father[x]);
        return father[x];
    }
}
void Union(vector<int> &father, int x, int y) //根的值为该集合高度，数组首位保存根个数
{
    x = Find(father, x);
    y = Find(father, y);
    if (x != y)
    {
        if (father[x] < father[y])
            father[y] = x;
        else if (father[x] > father[y])
            father[x] = y;
        else
        {
            father[y] = x;
            --father[x];
        }
        --father[0];
    }
}

//最小生成树
// Kruskal，利用并查集，返回值为最小耗费
int Kruskal(graph G) //无向图
{
    int ans = 0;
    sort(G.edges.begin(), G.edges.end(), [](const edge &x, const edge &y)
         { return x.weight < y.weight; });
    int n = G.nodes.size();
    vector<int> father(n + 1, -1);
    father[0] = n;
    for (const edge &a : G.edges)
    {
        if (Find(father, a.from->val) != Find(father, a.to->val))
        {
            Union(father, a.from->val, a.to->val);
            ans += a.weight;
        }
        if (father[0] == 1)
            break;
    }
    return 0;
}
// Prim，返回值为最小耗费
int Prim(graph G) //有向图
{
    int ans = 0;
    int count = G.nodes.size();
    priority_queue<edge> help;
    set<node> node_set;
    node_set.insert(G.nodes[0]);
    for (const auto &a : G.nodes[0].edges)
        help.push(a);
    while (node_set.size() != count)
    {
        while (!help.empty())
        {
            edge temp = help.top();
            help.pop();
            if (node_set.find(*temp.to) != node_set.end())
            {
                node_set.insert(*temp.to);
                for (const auto &e : (*temp.to).edges)
                    help.push(e);
                ans += temp.weight;
            }
        }
    }
    return ans;
}

//***********************************************************************************************************************//
//前缀树
struct TrieNode
{
    int pass;
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
    void insert(string word);
    int search(string word);
    int prefixNumber(string word);
    void deleteWord(string word);
};
void Trie::insert(string word)
{
    if (word.size() == 0)
        return;
    TrieNode *node = root;
    node->pass++;
    int index = 0;
    for (auto &a : word)
    {
        index = a - 'a';
        if (node->nexts[index] == nullptr)
            node->nexts[index] = new TrieNode();
        node = node->nexts[index];
        node->pass++;
    }
    node->end++;
}
int Trie::search(string word)
{
    if (word.empty())
        return 0;
    TrieNode *node = root;
    int index = 0;
    for (auto &a : word)
    {
        index = a - 'a';
        if (node->nexts[index] == nullptr)
            return 0;
        node = node->nexts[index];
    }
    return node->end;
}
int Trie::prefixNumber(string word)
{
    if (word.empty())
        return 0;
    TrieNode *node = root;
    int index = 0;
    for (auto &a : word)
    {
        index = a - 'a';
        if (node->nexts[index] == nullptr)
            return 0;
        node = node->nexts[index];
    }
    return node->pass;
}
void Trie::deleteWord(string word)
{
    if (search(word) == 0)
        return;
    TrieNode *node = root;
    node->pass--;

    TrieNode *delete_node = nullptr;
    int delete_index = -1;
    set<TrieNode *> deleteSet;
    for (auto &a : word)
    {
        int index = a - 'a';
        if (--node->nexts[index]->pass == 0)
        {
            delete_node = delete_node == nullptr ? node : delete_node;
            delete_index = delete_index == -1 ? index : delete_index;
            deleteSet.insert(node->nexts[index]);
        }
        node = node->nexts[index];
    }
    node->end--;
    delete_node->nexts[delete_index] = nullptr;
    for (auto &a : deleteSet)
    {
        delete a;
    }
}