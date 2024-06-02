#include "header.h"

/*

373. 查找和最小的 K 对数字

给定两个以非递减顺序排列的整数数组 nums1 和 nums2，以及一个整数 k

定义一对值 (u,v)，其中第一个元素来自 nums1，第二个元素来自 nums2

请找到和最小的 k 个数对 (u1,v1)，(u2,v2)  ...  (uk,vk)

示例 1:
输入: nums1 = [1,7,11], nums2 = [2,4,6], k = 3
输出: [1,2],[1,4],[1,6]
解释: 返回序列中的前 3 对数：
[1,2],[1,4],[1,6],[7,2],[7,4],[11,2],[7,6],[11,4],[11,6]

示例 2:
输入: nums1 = [1,1,2], nums2 = [1,2,3], k = 2
输出: [1,1],[1,1]
解释: 返回序列中的前 2 对数：
[1,1],[1,1],[1,2],[2,1],[1,2],[2,2],[1,3],[1,3],[2,3]

提示:
1 <= nums1.length, nums2.length <= 10^5
-10^9 <= nums1[i], nums2[i] <= 10^9
nums1 和 nums2 均为 升序排列
1 <= k <= 10^4
k <= nums1.length * nums2.length

*/

// 多路归并
class Solution1 {
private:
	static vector<int> nums1_cpy;
	static vector<int> nums2_cpy;

public:
	vector<vector<int>> kSmallestPairs(vector<int> &nums1, vector<int> &nums2,
		int k) {
		nums1_cpy = nums1;
		nums2_cpy = nums2;
		int flag = true;
		int len1 = nums1_cpy.size(), len2 = nums2_cpy.size();
		if (len1 > len2) {
			swap(len1, len2);
			swap(nums1_cpy, nums2_cpy);
			flag = false;
		}
		priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp) *> pq(cmp);
		vector<vector<int>> ans;
		for (int i = 0; i < min(len1, k); ++i) pq.push({ i, 0 });
		while (!pq.empty() && ans.size() < k) {
			const auto tmp = pq.top();
			pq.pop();
			flag ? ans.push_back({ nums1_cpy[tmp.first], nums2_cpy[tmp.second] })
				: ans.push_back({ nums2_cpy[tmp.second], nums1_cpy[tmp.first] });
			if (tmp.second + 1 < len2) pq.push({ tmp.first, tmp.second + 1 });
		}
		return ans;
	}

private:
	static bool cmp(const pair<int, int> &p1, const pair<int, int> &p2) {
		return nums1_cpy[p1.first] + nums2_cpy[p1.second] >
			nums1_cpy[p2.first] + nums2_cpy[p2.second];
	}
};

vector<int> Solution1::nums1_cpy;
vector<int> Solution1::nums2_cpy;

// 二分查找
class Solution2 {
public:
	vector<vector<int>> kSmallestPairs(vector<int> &nums1, vector<int> &nums2,
		int k) {
		vector<vector<int>> ans;
		int len1 = nums1.size(), len2 = nums2.size();
		int lo = nums1[0] + nums2[0], hi = nums1[len1 - 1] + nums2[len2 - 1];
		while (lo < hi) {
			int mi = lo + (hi - lo) / 2;
			if (check(mi, k, nums1, nums2)) hi = mi;
			else lo = mi + 1;
		}
		// 完成二分查找后，数对和 <= target 的数量可能大于等于 k 个
		// 但数对和 < target 的数据量小于 k 个
		int target = lo;
		for (int i = 0; i < len1; ++i) {
			for (int j = 0; j < len2; ++j)
				if (nums1[i] + nums2[j] < target) ans.push_back({ nums1[i], nums2[j] });
				else break;
		}
		// 从剩余的数中找到数对和 = target 的数，直到找全 k 个
		for (int i = 0; i < len1 && ans.size() < k; ++i) {
			int a = nums1[i], b = target - a;
			// 以下过程二分查找数组中的目标值，如果目标值有多个重复值，则找到最左侧和最右侧的数
			int lo = 0, hi = len2 - 1;
			while (lo < hi) {
				int mi = lo + (hi - lo) / 2;
				nums2[mi] >= b ? hi = mi : lo = mi + 1;
			}
			if (nums2[lo] != b) continue;
			int ic = lo;
			lo = 0, hi = len2 - 1;
			while (lo < hi) {
				int mi = lo + (hi - lo + 1) / 2;
				nums2[mi] <= b ? lo = mi : hi = mi - 1;
			}
			int id = lo;
			for (int j = ic; j <= id && ans.size() < k; ++j) ans.push_back({ a, b });
		}
		return ans;
	}

private:
	bool check(int target, int k, const vector<int> &nums1,
		const vector<int> &nums2) {
		int ans = 0;
		for (int i = 0; i < nums1.size() && ans < k; ++i) {
			for (int j = 0; j < nums2.size() && ans < k; ++j) {
				if (nums1[i] + nums2[j] <= target) ++ans;
				else break;
			}
		}
		return ans >= k;
	}
};
