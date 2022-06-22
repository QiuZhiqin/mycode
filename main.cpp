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
struct Interval
{
    int start;
    int end;
    Interval() : start(0), end(0) {}
    Interval(int s, int e) : start(s), end(e) {}
};
int maxLength(vector<int> &arr)
{
    int size = arr.size(), maxlen = 0, l = 0, r = 0;
    unordered_set<int> visited;
    while (l < size)
    {
        while (visited.find(arr[r]) == visited.end() && r < size)
        {
            visited.insert(arr[r]);
            r++;
        }
        maxlen = max(maxlen, r - l);
        visited.erase(arr[l++]);
    }
    return maxlen;
}
int main()
{
    vector<int> v = {1, 2, 3, 1, 2, 3, 2, 2};
    int a = maxLength(v);
    return 0;
}