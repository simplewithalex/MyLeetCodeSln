#include "header.h"

/*

306. 累加数

累加数是一个字符串，组成它的数字可以形成累加序列
一个有效的累加序列必须至少包含 3 个数。除了最开始的两个数以外，序列中的每个后续数字必须是它之前两个数字之和
给你一个只包含数字 '0'-'9' 的字符串，编写一个算法来判断给定输入是否是 累加数 。如果是，返回 true；否则返回 false

说明：累加序列里的数，除数字 0 之外，不会以 0 开头，所以不会出现 1, 2, 03 或者 1, 02, 3 的情况

示例 1：
输入："112358"
输出：true
解释：累加序列为: 1, 1, 2, 3, 5, 8 -> 1 + 1 = 2, 1 + 2 = 3, 2 + 3 = 5, 3 + 5 = 8

示例 2：
输入："199100199"
输出：true
解释：累加序列为: 1, 99, 100, 199 -> 1 + 99 = 100, 99 + 100 = 199

提示：
1 <= num.length <= 35
num 仅由数字（0 - 9）组成

进阶：你计划如何处理由过大的整数输入导致的溢出?


*/

class Solution {
public:
	bool isAdditiveNumber(string num) {
		int len = num.size();
		// 存储可以组成累加序列的合法数字
		vector<vector<int>> nums;
		return dfs(0, num, len, nums);
	}

private:
	bool dfs(int idx, const string &num, const int &numStrLen,
		vector<vector<int>> &nums) {
		int curLen = nums.size();
		// 分割点到达序列末尾，如果合法序列数组中的数字不少于3个，返回true
		if (idx == numStrLen) return curLen >= 3;
		// 处理当前分割点的数字为0的情况
		int tail = num[idx] == '0' ? idx + 1 : numStrLen;
		// 记录当前数字
		vector<int> cur;
		for (int i = idx; i < tail; ++i) {
			// 逆序存储，低位数字先存
			cur.insert(cur.begin(), num[i] - '0');
			if (curLen < 2 || check(nums[curLen - 2], nums[curLen - 1], cur)) {
				nums.push_back(cur);
				// 当前数字的下一个数字作为分割点递归
				if (dfs(i + 1, num, numStrLen, nums)) return true;
				nums.pop_back();
			}
		}
		return false;
	}
	bool check(const vector<int> &num1, const vector<int> &num2,
		const vector<int> &num3) {
		vector<int> ans;
		int tmp = 0;
		for (int i = 0; i < num1.size() || i < num2.size(); ++i) {
			if (i < num1.size()) tmp += num1[i];
			if (i < num2.size()) tmp += num2[i];
			ans.push_back(tmp % 10);
			tmp /= 10;
		}
		// 如果最后还存在进位，则添加最高位的1
		if (tmp) ans.push_back(1);
		if (num3.size() != ans.size()) return false;
		// 逐位判断，从最低位开始
		for (int i = 0; i < ans.size(); ++i) {
			if (num3[i] != ans[i]) return false;
		}
		return true;
	}
};
// https://leetcode.cn/problems/additive-number/solutions/1201929/gong-shui-san-xie-hui-su-gao-jing-du-jia-6o6b/
// @author https://leetcode.cn/u/ac_oier/
