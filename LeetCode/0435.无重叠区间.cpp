#include "header.h"

/*

435. 无重叠区间

给定一个区间的集合 intervals ，其中 intervals[i] = [starti, endi] 。返回 需要移除区间的最小数量，使剩余区间互不重叠

注意 只在一点上接触的区间是 不重叠的。例如 [1, 2] 和 [2, 3] 是不重叠的

示例 1:
输入: intervals = [[1,2],[2,3],[3,4],[1,3]]
输出: 1
解释: 移除 [1,3] 后，剩下的区间没有重叠

示例 2:
输入: intervals = [ [1,2], [1,2], [1,2] ]
输出: 2
解释: 你需要移除两个 [1,2] 来使剩下的区间没有重叠

示例 3:
输入: intervals = [ [1,2], [2,3] ]
输出: 0
解释: 你不需要移除任何区间，因为它们已经是无重叠的了

提示:
1 <= intervals.length <= 10^5
intervals[i].length == 2
-5 * 10^4 <= starti < endi <= 5 * 10^4

*/


// 最长上升子序列方法 TLE
class Solution1 {
public:
	vector<int> memo;
	int eraseOverlapIntervals(vector<vector<int>> &intervals) {
		int len = intervals.size();
		memo.resize(len, 0);
		sort(intervals.begin(), intervals.end(),
			[](const vector<int> &a, const vector<int> &b) {
			return a[0] < b[0];
		});
		int res = 0;
		for (int i = 0; i < len; ++i) res = helper(intervals, i);
		return len - res;
	}
	int helper(vector<vector<int>> &intervals, int idx) {
		if (memo[idx]) return memo[idx];
		int res = 1;
		for (int j = 0; j < idx; ++j) {
			if (intervals[j][1] <= intervals[idx][0]) {
				res = max(res, helper(intervals, j) + 1);
			}
		}
		return memo[idx] = res;
	}
};

// 贪心
class Solution2 {
public:
	int eraseOverlapIntervals(vector<vector<int>> &intervals) {
		int len = intervals.size();
		sort(intervals.begin(), intervals.end(),
			[](const vector<int> &a, const vector<int> &b) {
			return a[1] < b[1];
		});
		int erase_cnt = 0;
		int base_idx = 0;
		for (int i = 1; i < len; ++i) {
			if (intervals[base_idx][1] > intervals[i][0]) ++erase_cnt;
			else base_idx = i;
		}
		return erase_cnt;
	}
};

// 这道题的数据规模是10^5，那我们的题解时间复杂度最多只能是O(N∗logN)
// 因为如果是O(N^2)的话，把10^5代入可得操作次数为10^10，超过10^7的阈值会超时
