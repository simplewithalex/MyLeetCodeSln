#include "header.h"

/*

����һ���ַ�������������Ǽ�������ַ������ж��ٸ������Ӵ���
���в�ͬ��ʼλ�û����λ�õ��Ӵ�����ʹ������ͬ���ַ���ɣ�Ҳ�ᱻ��Ϊ�ǲ�ͬ���Ӵ���

ʾ�� 1:
����: "abc"
���: 3
����: ���������Ӵ�: "a", "b", "c".

ʾ�� 2:
����: "aaa"
���: 6
����: 6�������Ӵ�: "a", "a", "a", "aa", "aa", "aaa".

ע��:
������ַ������Ȳ��ᳬ��1000��

*/

//������չ��
class Solution1 {
public:
	int countSubstrings(string s)
	{
		int res = 0;
		int len = s.size();
		for (int i = 0; i < len; ++i)
		{
			res += extend(s, i, i + 1) + extend(s, i, i);
		}
		return res;

	}
	int extend(const string &s, int i, int j)
	{
		int count = 0;
		for (; i >= 0 && j < s.size(); --i, ++j)
		{
			if (s[i] != s[j])
				break;
			++count;
		}
		return count;
	}
};

//��̬�滮
class Solution2 {
public:
	int countSubstrings(string s)
	{
		if (s.empty()) return 0;
		int len = s.size();
		vector<vector<char>> isPal(len, vector<char>(len, false));
		int res = 0;
		for (int palLen = 1; palLen <= len; ++palLen)
		{
			for (int i = 0; i <= len - palLen; ++i)
			{
				int j = i + palLen - 1;
				isPal[i][j] = (s[i] == s[j]) && (palLen < 3 || isPal[i + 1][j - 1]);
				if (isPal[i][j]) ++res;
			}
		}
		return res;
	}
};

//Manacher�㷨
class Solution3 {
public:
	int countSubstrings(string s)
	{
		int len = s.size();
		if (len < 2) return len;
		string str = preProcess(s);
		len = str.size();
		//pal�Լ�¼ÿ���±�Ϊ���ĵĻ��Ĵ����೤��
		vector<int> pal(len);
		//˫ָ��ֱ��¼�����Ӵ����ĵ���Ҳ���Զ�±�
		int center = 0, maxRight = 0;
		//��¼���Ĵ�������
		int res = 0;
		for (int i = 0; i < len; ++i)
		{
			if (i < maxRight)
			{
				int mirror = 2 * center - i;
				pal[i] = min(maxRight - i, pal[mirror]);
			}
			//��һ����ɢ���������
			int left = i - (1 + pal[i]);
			int right = i + (1 + pal[i]);
			while (left >= 0 && right < len&&str[left] == str[right])
			{
				++pal[i];
				--left;
				++right;
			}
			if ((i + pal[i])>maxRight)
			{
				maxRight = i + pal[i];
				center = i;
			}
			res += (pal[i] + 1) / 2;
		}
		return res;
	}
	string preProcess(const string &s)
	{
		int len = s.size();
		string res;
		for (int i = 0; i < len; ++i) res.append({ '#', s[i] });
		res += "#";
		return res;
	}
};