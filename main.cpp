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
int divide(int n, int k)
{
    if (k == 0 && n == 0)
        return 1;
    else if (k == 0)
        return 0;
    int ans = 0;
    for (int i = 1; i <= n; ++i)
    {
        ans += divide(n - i, k - 1);
    }
    return ans;
}
int main()
{
    int n, k;
    cin >> n >> k;
    int ans = divide(n, k);
    cout << ans;
    return 0;
}