#include "header.h"

/*

306. �ۼ���

�ۼ�����һ���ַ���������������ֿ����γ��ۼ�����
һ����Ч���ۼ����б������ٰ��� 3 �����������ʼ�����������⣬�����е�ÿ���������ֱ�������֮ǰ��������֮��
����һ��ֻ�������� '0'-'9' ���ַ�������дһ���㷨���жϸ��������Ƿ��� �ۼ��� ������ǣ����� true�����򷵻� false

˵�����ۼ������������������ 0 ֮�⣬������ 0 ��ͷ�����Բ������ 1, 2, 03 ���� 1, 02, 3 �����

ʾ�� 1��
���룺"112358"
�����true
���ͣ��ۼ�����Ϊ: 1, 1, 2, 3, 5, 8 -> 1 + 1 = 2, 1 + 2 = 3, 2 + 3 = 5, 3 + 5 = 8

ʾ�� 2��
���룺"199100199"
�����true
���ͣ��ۼ�����Ϊ: 1, 99, 100, 199 -> 1 + 99 = 100, 99 + 100 = 199

��ʾ��
1 <= num.length <= 35
num �������֣�0 - 9�����

���ף���ƻ���δ����ɹ�����������뵼�µ����?


*/

class Solution {
public:
	bool isAdditiveNumber(string num) {
		int len = num.size();
		// �洢��������ۼ����еĺϷ�����
		vector<vector<int>> nums;
		return dfs(0, num, len, nums);
	}

private:
	bool dfs(int idx, const string &num, const int &numStrLen,
		vector<vector<int>> &nums) {
		int curLen = nums.size();
		// �ָ�㵽������ĩβ������Ϸ����������е����ֲ�����3��������true
		if (idx == numStrLen) return curLen >= 3;
		// ����ǰ�ָ�������Ϊ0�����
		int tail = num[idx] == '0' ? idx + 1 : numStrLen;
		// ��¼��ǰ����
		vector<int> cur;
		for (int i = idx; i < tail; ++i) {
			// ����洢����λ�����ȴ�
			cur.insert(cur.begin(), num[i] - '0');
			if (curLen < 2 || check(nums[curLen - 2], nums[curLen - 1], cur)) {
				nums.push_back(cur);
				// ��ǰ���ֵ���һ��������Ϊ�ָ��ݹ�
				if (dfs(i + 1, num, numStrLen, nums)) return true;
				nums.pop_back();
			}
		}
		return false;
	}
	bool check(const vector<int> &num1, const vector<int> &num2,
		const vector<int> &num3) {
		vector<int> ans;
		int tmp = 0;
		for (int i = 0; i < num1.size() || i < num2.size(); ++i) {
			if (i < num1.size()) tmp += num1[i];
			if (i < num2.size()) tmp += num2[i];
			ans.push_back(tmp % 10);
			tmp /= 10;
		}
		// �����󻹴��ڽ�λ����������λ��1
		if (tmp) ans.push_back(1);
		if (num3.size() != ans.size()) return false;
		// ��λ�жϣ������λ��ʼ
		for (int i = 0; i < ans.size(); ++i) {
			if (num3[i] != ans[i]) return false;
		}
		return true;
	}
};
// https://leetcode.cn/problems/additive-number/solutions/1201929/gong-shui-san-xie-hui-su-gao-jing-du-jia-6o6b/
// @author https://leetcode.cn/u/ac_oier/
