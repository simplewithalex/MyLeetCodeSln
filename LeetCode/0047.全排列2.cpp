#include "header.h"

/*

����һ���ɰ����ظ����ֵ����У��������в��ظ���ȫ���С�

ʾ��:
����: [1,1,2]
���:
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
		if (num.empty()) return{};
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
//������������ͬ�����Ĵ�����i>0 && num[i - 1] == num[i] && !used[i - 1]����һ����ζ�������ϸ�涨��ʹ��ǰ���������ʹ�ú���ģ�����ȵõ��˺�������֣�
//��ǰ��Ļ�û���õ�������Ϊ����һ���ظ�����������Ǵ���˳��
