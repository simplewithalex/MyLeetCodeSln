#include "header.h"

/*

根据每日气温列表，请重新生成一个列表，对应位置的输入是你需要再等待多久温度才会升高超过该日的天数。
如果之后都不会升高，请在该位置用 0 来代替。

例如，给定一个列表 temperatures = [73, 74, 75, 71, 69, 72, 76, 73]，
你的输出应该是 [1, 1, 4, 2, 1, 1, 0, 0]。

提示：气温列表长度的范围是 [1, 30000]。每个气温的值的均为华氏度，都是在 [30, 100] 范围内的整数。

*/

//栈解法
class Solution {
public:
	vector<int> dailyTemperatures(vector<int> &T) 
	{
		int len = T.size();
		if (len == 0) return {};
		stack<int> s;
		vector<int> res(len);
		for (int i = 0; i < len; ++i)
		{
			while (!s.empty() && T[i]>T[s.top()])
			{
				int j = s.top();
				s.pop();
				res[j] = i - j;
			}
			s.push(i);
		}
		return res;
	}
};