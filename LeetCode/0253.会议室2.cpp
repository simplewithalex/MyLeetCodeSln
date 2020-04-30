#include "header.h"

/*

Given an array of meeting time intervals consisting of start and end times [[s1,e1],[s2,e2],...] (si < ei), 
find the minimum number of conference rooms required.

Example 1:
Input: [[0, 30],[5, 10],[15, 20]]
Output: 2

Example 2:
Input: [[7,10],[2,4]]
Output: 1

*/

class Solution {
public:
	int minMeetingRooms(vector<vector<int>> &intervals)
	{
		sort(intervals.begin(), intervals.end(), [](const vector<int> &a, const vector<int> &b)
		{return a[0] < b[0]; });
		priority_queue<int, vector<int>, greater<int>> q;
		for (auto interval : intervals)
		{
			if (!q.empty() && q.top() < interval[0]) q.pop();
			q.push(interval[1]);
		}
		return q.size();
	}
};
