#include "header/StructureofData.hpp"
#include "header/student.hpp"
#include <cctype>
#include <unistd.h>
using namespace std;
int main()
{
    vector<int> nums = {5, 8, 9, 12, 6, 7, 5, 9, 8};
    int l = 0, r = nums.size() - 1;
    while (l < r)
    {
        while (nums[l] % 2 == 1)
            l++;
        swap(nums[l], nums[r]);
        while (nums[r] % 2 == 0)
            --r;
    }
    for (const int &a : nums)
        cout << a << " ";
    return 0;
}