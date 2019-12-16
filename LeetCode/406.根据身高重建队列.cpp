#include "header.h"

/*

�����д���˳���һȺ��վ��һ�����С� 

ÿ������һ��������(h, k)��ʾ������h������˵���ߣ�k�����������ǰ������ߴ��ڻ����h�������� 

��дһ���㷨���ؽ�������С�

ע�⣺
����������1100�ˡ�

ʾ��

����:
[[7,0], [4,4], [7,1], [5,0], [6,1], [5,2]]

���:
[[5,0], [7,0], [5,2], [6,1], [4,4], [7,1]]

*/

class Solution {
public:
	vector<vector<int>> reconstructQueue(vector<vector<int>> &people)
	{
		if (people.empty()) return{};
		sort(people.begin(), people.end(), [](const vector<int> &v1, const vector<int> &v2)->bool
		{
			if (v1[0] > v2[0]) return true;
			else if (v1[0] == v2[0] && v1[1] < v2[1]) return true;
			else return false;
		});
		vector<vector<int>> res;
		for (auto &v : people)
		{
			res.insert(res.begin() + v[1], v);
		}
		return res;
	}
};