#include "header.h"

/*

632. 最小区间

你有 k 个 非递减排列 的整数列表。找到一个 最小 区间，使得 k 个列表中的每个列表至少有一个数包含在其中

我们定义如果 b-a < d-c 或者在 b-a == d-c 时 a < c，则区间 [a,b] 比 [c,d] 小

示例 1：
输入：nums = [[4,10,15,24,26], [0,9,12,20], [5,18,22,30]]
输出：[20,24]
解释：
列表 1：[4, 10, 15, 24, 26]，24 在区间 [20,24] 中
列表 2：[0, 9, 12, 20]，20 在区间 [20,24] 中
列表 3：[5, 18, 22, 30]，22 在区间 [20,24] 中

示例 2：
输入：nums = [[1,2,3],[1,2,3],[1,2,3]]
输出：[1,1]

提示：
nums.length == k
1 <= k <= 3500
1 <= nums[i].length <= 50
-10^5 <= nums[i][j] <= 10^5
nums[i] 按非递减顺序排列


*/


// 双指针滑窗
class Solution1 {
public:
	vector<int> smallestRange(vector<vector<int>> &nums) {
		vector<pair<int, int>> v;
		for (int i = 0; i < nums.size(); ++i) {
			for (int n : nums[i]) v.push_back({ n, i });
		}
		sort(v.begin(), v.end());

		unordered_map<int, int> m;
		int len = v.size(), cnt = nums.size();
		int start = 0, end = 0;
		int lb = 0, rb = 0, range = INT_MAX;

		while (end < len) {
			int g = v[end].second;
			++m[g];
			++end;
			while (m.size() == cnt) {
				g = v[start].second;
				--m[g];
				if (m[g] == 0) {
					m.erase(g);
					int tmpLen = v[end - 1].first - v[start].first;
					if (tmpLen < range) {
						lb = v[start].first;
						rb = v[end - 1].first;
						range = tmpLen;
					}
				}
				++start;
			}
		}
		return{ lb, rb };
	}
};

// 优先级队列
class Solution2 {
public:
	vector<int> smallestRange(vector<vector<int>> &nums) {
		int len = nums.size();
		vector<int> pos(len);

		auto cmp = [&](const int &a, const int &b) {
			return nums[a][pos[a]] > nums[b][pos[b]];
		};
		priority_queue<int, vector<int>, decltype(cmp)> pq(cmp);

		int minval = 0, maxval = INT_MIN;
		for (int i = 0; i < len; ++i) {
			pq.push(i);
			maxval = max(maxval, nums[i][0]);
		}

		int minIdx = pq.top();
		minval = nums[minIdx][pos[minIdx]];
		int left = minval, right = maxval;
		while (pos[minIdx] != nums[minIdx].size() - 1) {
			pq.pop();
			++pos[minIdx];
			maxval = max(maxval, nums[minIdx][pos[minIdx]]);
			pq.push(minIdx);
			minIdx = pq.top();
			minval = nums[minIdx][pos[minIdx]];
			if (maxval - minval < right - left) {
				left = minval;
				right = maxval;
			}
		}
		return{ left, right };
	}
};


