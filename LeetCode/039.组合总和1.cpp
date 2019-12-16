#include "header.h"

/*

给定一个无重复元素的数组 candidates 和一个目标数 target ，找出 candidates 中所有可以使数字和为 target 的组合。
candidates 中的数字可以无限制重复被选取。

说明：
所有数字（包括 target）都是正整数。
解集不能包含重复的组合。 

示例 1:
输入: candidates = [2,3,6,7], target = 7,
所求解集为:
[
  [7],
  [2,2,3]
]

示例 2:
输入: candidates = [2,3,5], target = 8,
所求解集为:
[
  [2,2,2,2],
  [2,3,3],
  [3,5]
]

*/

class Solution {
public:
	vector<vector<int>> combinationSum(vector<int> &candidates, int target)
	{
		vector<vector<int>> res;
		vector<int> v;
		sort(candidates.begin(), candidates.end());
		recur(res, candidates, v, target, 0);
		return res;
	}
	void recur(vector<vector<int>> &res, vector<int> &candidates, vector<int> &v, int remain, int start)
	{
		if (remain == 0)
		{
			res.push_back(v);
		}
		else
		{
			for (int i = start; i < candidates.size(); ++i)
			{
				if (candidates[i]>remain) return;
				v.push_back(candidates[i]);
				recur(res, candidates, v, remain - candidates[i], i);
				v.pop_back();
			}
		}
	}
};