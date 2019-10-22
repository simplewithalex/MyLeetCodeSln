#include "header.h"

/*

给出一个区间的集合，请合并所有重叠的区间。

示例 1:
输入: [[1,3],[2,6],[8,10],[15,18]]
输出: [[1,6],[8,10],[15,18]]
解释: 区间 [1,3] 和 [2,6] 重叠, 将它们合并为 [1,6].

示例 2:
输入: [[1,4],[4,5]]
输出: [[1,5]]
解释: 区间 [1,4] 和 [4,5] 可被视为重叠区间。

*/


struct Interval 
{
	int start;
    int end;
    Interval() : start(0), end(0) {}
    Interval(int s, int e) : start(s), end(e) {}
};

class Solution {
public:
	vector<Interval> merge(vector<Interval> &intervals)
	{
		if (intervals.empty()) return{};
		sort(intervals.begin(), intervals.end(), [](const Interval &a, const Interval &b){ return a.start < b.start; });
		vector<Interval> res;
		res.push_back(intervals[0]);
		for (auto interval : intervals)
		{
			if (interval.start <= res.back().end)
			{
				res.back().end = max(interval.end, res.back().end);
			}
			else
			{
				res.push_back(interval);
			}
		}
		return res;
	}
};