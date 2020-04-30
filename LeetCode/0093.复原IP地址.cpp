#include "header.h"

/*

给定一个只包含数字的字符串，复原它并返回所有可能的 IP 地址格式。

示例:
输入: "25525511135"
输出: ["255.255.11.135", "255.255.111.35"]

*/

class Solution {
public:
	vector<string> restoreIpAddresses(string s)
	{
		vector<string> res;
		string str;
		restoreIp(res, str, s, 0);
		return res;
	}
	void restoreIp(vector<string> &res, string str, string s, int k)
	{
		if (s.empty() || k == 4)
		{
			if (s.empty() && k == 4) res.push_back(str.substr(1));
			return;
		}
		for (int i = 1; i <= (s[0] == '0' ? 1 : 3) && i <= s.size(); ++i)
		{
			string temp = s.substr(0, i);
			if (stoi(temp) < 256)
			{
				restoreIp(res, str + "." + temp, s.substr(i), k + 1);
			}
		}
	}
};