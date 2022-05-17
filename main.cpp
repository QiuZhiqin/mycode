#include "header/StructureofData.hpp"
#include "header/student.hpp"
#include <cctype>
#include <unistd.h>
using namespace std;

struct Interval
{
    int start;
    int end;
    Interval(int s, int e) : start(start), end(e) {}
};

class Solution
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
            else if (ne < intervals[i].start)
                break;
            else
            {
                ns = min(ns, intervals[i].start);
                ne = max(ne, intervals[i].end);
            }
        }
        newInterval.start = ns;
        newInterval.end = ne;
        ans.push_back(newInterval);
        for (; i < n; ++i)
            ans.push_back(intervals[i]);
        return ans;
    }
};