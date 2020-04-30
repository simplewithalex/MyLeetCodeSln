#include "header.h"

/*

����һ��ֻ�������ֵ��ַ�������ԭ�����������п��ܵ� IP ��ַ��ʽ��

ʾ��:
����: "25525511135"
���: ["255.255.11.135", "255.255.111.35"]

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