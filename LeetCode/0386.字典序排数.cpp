#include "header.h"

/*

386. 字典序排数

给你一个整数 n ，按字典序返回范围 [1, n] 内所有整数
你必须设计一个时间复杂度为 O(n) 且使用 O(1) 额外空间的算法

示例 1：
输入：n = 13
输出：[1,10,11,12,13,2,3,4,5,6,7,8,9]

示例 2：
输入：n = 2
输出：[1,2]

提示：
1 <= n <= 5 * 10^4

*/


class Solution1 {
private:
	vector<int> ans;

public:
	vector<int> lexicalOrder(int n) {
		for (int i = 1; i <= 9; ++i) {
			if (i <= n) dfs(i, n);
		}
		return ans;
	}

private:
	void dfs(int cur, int limit) {
		ans.push_back(cur);
		for (int i = 0; i <= 9; ++i) {
			if ((cur * 10 + i) > limit) break;
			dfs(cur * 10 + i, limit);
		}
	}
};


class Solution2 {
public:
	vector<int> lexicalOrder(int n) {
		vector<int> ans;
		for (int i = 0, j = 1; i < n; ++i) {
			ans.push_back(j);
			if (j * 10 <= n) {
				j *= 10;
			} else {
				while (j % 10 == 9 || j + 1 > n) j /= 10;
				++j;
			}
		}
		return ans;
	}
};

