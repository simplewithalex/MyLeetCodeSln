#include "header.h"

/*

����һ���ַ�������֤���Ƿ��ǻ��Ĵ���
ֻ������ĸ�������ַ������Ժ�����ĸ�Ĵ�Сд��
˵���������У����ǽ����ַ�������Ϊ��Ч�Ļ��Ĵ���

ʾ�� 1:
����: "A man, a plan, a canal: Panama"
���: true

ʾ�� 2:
����: "race a car"
���: false

*/

class Solution {
public:
	bool isPalindrome(string s)
	{
		int len = s.size();
		if (len == 0) return true;
		for (int i = 0, j = len - 1; i < j; ++i, --j)
		{
			while (i<j&&!isalnum(s[i]))
				++i;
			while (i<j&&!isalnum(s[j]))
				--j;
			if (toupper(s[i]) != toupper(s[j]))
				return false;
		}
		return true;
	}
};