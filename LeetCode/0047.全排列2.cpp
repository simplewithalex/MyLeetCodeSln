#include "header.h"

/*

给定一个可包含重复数字的序列，返回所有不重复的全排列。

示例:
输入: [1,1,2]
输出:
[
 [1,1,2],
 [1,2,1],
 [2,1,1]
]

*/

class Solution {
public:
	vector<vector<int>> permuteUnique(vector<int> &num)
	{
		if (num.empty()) return {};
		vector<vector<int>> res;
		vector<bool> used(num.size(), false);
		vector<int> vec;
		sort(num.begin(), num.end());
		backTrack(res, num, used, vec);
		return res;
	}
	void backTrack(vector<vector<int>> &res, vector<int> &num, vector<bool> &used, vector<int> &vec)
	{
		int len1 = num.size();
		int len2 = vec.size();
		if (len1 == len2)
		{
			res.push_back(vec);
			return;
		}
		for (int i = 0; i < len1; ++i)
		{
			if (used[i]) continue;
			if (i>0 && num[i - 1] == num[i] && !used[i - 1]) continue;
			used[i] = true;
			vec.push_back(num[i]);
			backTrack(res, num, used, vec);
			used[i] = false;
			vec.pop_back();
		}
	}
};
//对于数组中相同的数的处理，（i>0 && num[i - 1] == num[i] && !used[i - 1]）这一句意味着我们严格规定先使用前面的数字再使用后面的，如果先得到了后面的数字，
//而前面的还没有用到，则认为这是一种重复情况，不考虑此种顺序。
