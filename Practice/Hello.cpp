#include "StructureofData.hpp"
using namespace std;
int main()
{
    int n, target;
    cin >> n >> target;
    vector<int> nums(n);
    for (int i = 0; i < n; ++i)
        cin >> nums[i];
    int l = -1, r = n, p = 0;
    while (p < r)
    {
        if (nums[p] < target)
            swap(nums[p++], nums[++l]);
        else if (nums[p] > target)
            swap(nums[p], nums[--r]);
        else
            ++p;
    }
    if (r - l == 1)
        cout << "-1 -1";
    else
        cout << l + 1 << " " << r - 1;
    return 0;
}