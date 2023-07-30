#include "header.h"

/*

42. 接雨水

给定 n 个非负整数表示每个宽度为 1 的柱子的高度图，计算按此排列的柱子，下雨之后能接多少雨水

示例 1：
输入：height = [0,1,0,2,1,0,1,3,2,1,2,1]
输出：6
解释：上面是由数组 [0,1,0,2,1,0,1,3,2,1,2,1] 表示的高度图，在这种情况下，可以接 6 个单位的雨水（蓝色部分表示雨水）。

示例 2：
输入：height = [4,2,0,3,2,5]
输出：9

提示：
n == height.length
1 <= n <= 2 * 10^4
0 <= height[i] <= 10^5

*/


// 备忘录
class Solution1 {
private:
	vector<int> memoLeft;
	vector<int> memoRight;

public:
	int trap(vector<int> &height) {
		int len = height.size();
		memoLeft.resize(len, -1);
		memoRight.resize(len, -1);
		int ans = 0;
		for (int i = 0; i < len; ++i) {
			ans += max(0, min(getLeftMax(height, i), getRightMax(height, i)) - height[i]);
		}
		return ans;
	}

private:
	int getLeftMax(vector<int> &height, int idx) {
		if (idx <= 0) return 0;
		if (memoLeft[idx] != -1) return memoLeft[idx];
		return memoLeft[idx] = max(getLeftMax(height, idx - 1), height[idx - 1]);
	}
	int getRightMax(vector<int> &height, int idx) {
		if (idx >= height.size() - 1) return 0;
		if (memoRight[idx] != -1) return memoRight[idx];
		return memoRight[idx] = max(getRightMax(height, idx + 1), height[idx + 1]);
	}
};
// https://leetcode.cn/problems/trapping-rain-water/solutions/2300748/bao-li-ji-yi-hua-sou-suo-qian-hou-zhui-f-njeq/
// @author https://leetcode.cn/u/xiaojian-zhong/


// 自底而上动态规划
class Solution2 {
public:
	int trap(vector<int> &height) {
		int len = height.size();
		vector<int> left_dp(len);
		vector<int> right_dp(len);
		for (int i = 1; i < len; ++i) {
			left_dp[i] = max(height[i - 1], left_dp[i - 1]);
		}
		for (int i = len - 2; i >= 0; --i) {
			right_dp[i] = max(height[i + 1], right_dp[i + 1]);
		}
		int ans = 0;
		for (int i = 0; i < len; ++i) {
			ans += max(0, min(left_dp[i], right_dp[i]) - height[i]);
		}
		return ans;
	}
};
// https://leetcode.cn/problems/trapping-rain-water/solutions/48255/bao-li-jie-fa-yi-kong-jian-huan-shi-jian-zhi-zhen-/
// @author https://leetcode.cn/u/liweiwei1419/



// 单调栈方法
class Solution3 {
public:
	int trap(int A[], int n)
	{
		stack<int> s;
		int res = 0;
		for (int i = 0; i < n;)
		{
			if (s.empty() || A[i] <= A[s.top()])
			{
				s.push(i++);
			}
			else
			{
				int pre = s.top();
				s.pop();
				if (!s.empty())
				{
					int minHeight = min(A[i], A[s.top()]);
					res += (minHeight - A[pre])*(i - s.top() - 1);
				}
			}
		}
		return res;
	}
};
// https://leetcode.com/problems/trapping-rain-water/discuss/17414/A-stack-based-solution-for-reference-inspired-by-Histogram


// 双指针
class Solution4 {
public:
	int trap(vector<int>& height)
	{
		int len = height.size();
		int res = 0;
		int left = 0, right = len - 1;
		int leftMax = 0, rightMax = 0;
		while (left < right)
		{
			if (height[left] < height[right])
			{
				height[left] >= leftMax ? leftMax = height[left] : res += leftMax - height[left];
				++left;
			}
			else
			{
				height[right] >= rightMax ? rightMax = height[right] : res += rightMax - height[right];
				--right;
			}
		}
		return res;
	}
};