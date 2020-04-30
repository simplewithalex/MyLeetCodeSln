#include "header.h"

/*

给定一个数组 candidates 和一个目标数 target ，找出 candidates 中所有可以使数字和为 target 的组合。
candidates 中的每个数字在每个组合中只能使用一次。

说明：
所有数字（包括目标数）都是正整数。
解集不能包含重复的组合。 

示例 1:
输入: candidates = [10,1,2,7,6,1,5], target = 8,
所求解集为:
[
  [1, 7],
  [1, 2, 5],
  [2, 6],
  [1, 1, 6]
]

示例 2:
输入: candidates = [2,5,2,1,2], target = 5,
所求解集为:
[
  [1,2,2],
  [5]
]

*/

class Solution
{
public:
	vector<vector<int>> combinationSum2(vector<int> &candidates, int target)
	{
		vector<vector<int>> res;
		vector<int> v;
		sort(candidates.begin(), candidates.end());
		backtrack(candidates, res, v, target, 0);
		return res;
	}
	void backtrack(vector<int> &candidates, vector<vector<int>> &res, vector<int>  &vec, int target, int index)
	{
		if (target == 0)
		{
			res.push_back(vec);
		}
		else
		{
			for (int i = index; i < candidates.size(); ++i)
			{
				if (i>index&&candidates[i] == candidates[i - 1]) continue;
				if (candidates[i] > target) return;
				vec.push_back(candidates[i]);
				backtrack(candidates, res, vec, target - candidates[i], i + 1);
				vec.pop_back();
			}
		}
	}
};