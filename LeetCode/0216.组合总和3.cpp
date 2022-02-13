#include "header.h"

/*

找出所有相加之和为 n 的 k 个数的组合。组合中只允许含有 1 - 9 的正整数，并且每种组合中不存在重复的数字。

说明：
所有数字都是正整数。
解集不能包含重复的组合。 

示例 1:
输入: k = 3, n = 7
输出: [[1,2,4]]

示例 2:
输入: k = 3, n = 9
输出: [[1,2,6], [1,3,5], [2,3,4]]

*/

class Solution1 {
public:
	vector<vector<int>> combinationSum3(int k, int n) {
		vector<vector<int>> res;
		vector<int> v;
		backtrack(res, v, k, n, 1);
		return res;
	}

private:
	void backtrack(vector<vector<int>> &res, vector<int> &v, int k, int remain,
		int start) {
		// [start, 9]区间中的数不足k个, 剪枝
		if (10 - start < k) return;
		if (k == 0) {
			if (remain == 0) res.push_back(v);
			else return;
		}

		/*
		 * 枚举起点值 [..., 7, 8, 9],  找 3 个数，起点最多到 7, 找 2 个数，起点最多到 8
		 * 规律是，起点上界 + k = 10，故起点上界 = 10 - k
		 */
		for (int i = start; i <= 10 - k; ++i) {
			if (i > remain) return;
			v.push_back(i);
			backtrack(res, v, k - 1, remain - i, i + 1);
			v.pop_back();
		}
	}
};

// 二进制枚举
class Solution {
public:
	vector<vector<int>> combinationSum3(int k, int n) {
		for (int mask = 0; mask<(1 << 9); ++mask) {
			if (check(mask, k, n)) res.push_back(temp);
		}
		return res;
	}
private:
	vector<int> temp;
	vector<vector<int>> res;
	bool check(int mask, int k, int n) {
		temp.clear();
		for (int i = 0; i<9; ++i) {
			if ((1 << i)&mask) temp.push_back(i + 1);
		}
		return temp.size() == k&&accumulate(temp.begin(), temp.end(), 0) == n;
	}
};
// https://leetcode-cn.com/problems/combination-sum-iii/solution/zu-he-zong-he-iii-by-leetcode-solution/