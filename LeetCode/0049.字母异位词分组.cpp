#include "header.h"

/*

����һ���ַ������飬����ĸ��λ�������һ����ĸ��λ��ָ��ĸ��ͬ�������в�ͬ���ַ�����

ʾ��:
����: ["eat", "tea", "tan", "ate", "nat", "bat"],
���:
[
 ["ate","eat","tea"],
 ["nat","tan"],
 ["bat"]
]

˵����
���������ΪСд��ĸ��
�����Ǵ������˳��

*/

class Solution1 {
public:
	vector<vector<string>> groupAnagrams(vector<string> &strs)
	{
		unordered_map<string, vector<string>> m;
		for (auto s : strs)
		{
			string temp(s);
			sort(temp.begin(), temp.end());
			m[temp].push_back(s);
		}
		vector<vector<string>> res;
		for (auto p : m)
			res.push_back(p.second);
		return res;
	}
};

class Solution2 {
public:
	vector<vector<string>> groupAnagrams(vector<string> &strs) 
	{
		unordered_map<string, vector<string>> m;
		vector<vector<string>> res;
		for (int i = 0; i < strs.size(); ++i)
		{
			vector<int> ch(26, 0);
			for (int j = 0; j < strs[i].size(); ++j) ch[strs[i][j] - 'a'] += 1;
			string key;
			for (int j = 0; j < 26; ++j) key = key + to_string(ch[j]) + '#';
			m[key].push_back(strs[i]);
		}
		for (auto p : m) res.push_back(p.second);
		return res;
	}
};