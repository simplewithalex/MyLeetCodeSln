#include "header.h"

/*

436. 寻找右区间

给你一个区间数组 intervals ，其中 intervals[i] = [starti, endi] ，且每个 starti 都 不同

区间 i 的 右侧区间 是满足 startj >= endi，且 startj 最小 的区间 j，注意 i 可能等于 j

返回一个由每个区间 i 对应的 右侧区间 下标组成的数组。如果某个区间 i 不存在对应的 右侧区间，则下标 i 处的值设为 -1

示例 1：
输入：intervals = [[1,2]]
输出：[-1]
解释：集合中只有一个区间，所以输出-1

示例 2：
输入：intervals = [[3,4],[2,3],[1,2]]
输出：[-1,0,1]
解释：对于 [3,4] ，没有满足条件的“右侧”区间
对于 [2,3] ，区间[3,4]具有最小的“右”起点;
对于 [1,2] ，区间[2,3]具有最小的“右”起点

示例 3：
输入：intervals = [[1,4],[2,3],[3,4]]
输出：[-1,2,-1]
解释：对于区间 [1,4] 和 [3,4] ，没有满足条件的“右侧”区间
对于 [2,3] ，区间 [3,4] 有最小的“右”起点

提示：
1 <= intervals.length <= 2 * 10^4
intervals[i].length == 2
-10^6 <= starti <= endi <= 10^6
每个间隔的起点都 不相同

*/

class Solution1 {
public:
	vector<int> findRightInterval(vector<vector<int>> &intervals) {
		int len = intervals.size();
		vector<pair<int, int>> startIntervals;
		for (int i = 0; i < len; ++i) startIntervals.push_back({ intervals[i][0], i });
		sort(startIntervals.begin(), startIntervals.end());
		vector<int> ans(len);
		for (int i = 0; i < len; ++i) {
			int target = intervals[i][1];
			int lo = 0, hi = len - 1;
			while (lo < hi) {
				int mi = lo + (hi - lo) / 2;
				startIntervals[mi].first < target ? lo = mi + 1 : hi = mi;
			}
			ans[i] = startIntervals[lo].first >= target
				? startIntervals[lo].second : -1;
		}
		return ans;
	}
};

class Solution2 {
public:
	vector<int> findRightInterval(vector<vector<int>> &intervals) {
		vector<pair<int, int>> startIntervals;
		vector<pair<int, int>> endIntervals;
		int len = intervals.size();
		for (int i = 0; i < len; ++i) {
			startIntervals.push_back({ intervals[i][0], i });
			endIntervals.push_back({ intervals[i][1], i });
		}
		sort(startIntervals.begin(), startIntervals.end());
		sort(endIntervals.begin(), endIntervals.end());
		vector<int> ans(len, -1);
		for (int i = 0, j = 0; i < len && j < len; ++i) {
			while (j < len && endIntervals[i].first > startIntervals[j].first) ++j;
			if (j < len) ans[endIntervals[i].second] = startIntervals[j].second;
		}
		return ans;
	}
};

