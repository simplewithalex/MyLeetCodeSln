#include "header.h"

/*

564. Ѱ������Ļ�����

����һ����ʾ�������ַ��� n��������������Ļ��������������������������ֹһ�������ؽ�С���Ǹ�

������ġ�����Ϊ����������ľ���ֵ��С

ʾ�� 1:
����: n = "123"
���: "121"

ʾ�� 2:
����: n = "1"
���: "0"
����: 0 �� 2 ������Ļ��ģ������Ƿ�����С�ģ�Ҳ���� 0

��ʾ:
1 <= n.length <= 18
n ֻ���������
n ����ǰ�� 0
n ������ [1, 10^18 - 1] ��Χ�ڵ�����

*/

class Solution {
public:
	string nearestPalindromic(string n) {
		unsigned long long num = stoll(n), ans = -1;
		const vector<unsigned long long> candidates = getCandidates(n);
		for (auto &candidate : candidates) {
			if (candidate != num) {
				if (ans == -1 || llabs(candidate - num) < llabs(ans - num) ||
					(llabs(candidate - num) == llabs(ans - num) &&
						candidate < ans)) {
					ans = candidate;
				}
			}
		}
		return to_string(ans);
	}
	vector<unsigned long long> getCandidates(const string &n) {
		int len = n.size();
		vector<unsigned long long> candidates = {
			(unsigned long long)pow(10, len - 1) - 1,
			(unsigned long long)pow(10, len) + 1 };
		unsigned long long prefix = stoull(n.substr(0, (len + 1) / 2));
		for (int num : {prefix - 1, prefix, prefix + 1}) {
			string p = to_string(num);
			string candidate = p + string(p.rbegin() + (len & 1), p.rend());
			candidates.push_back(stoll(candidate));
		}
		return candidates;
	}
};

