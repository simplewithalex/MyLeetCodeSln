#include "header.h"

/*

354. ����˹�����ŷ�����

����һ����ά�������� envelopes������ envelopes[i] = [wi, hi] ����ʾ�� i ���ŷ�Ŀ�Ⱥ͸߶�

����һ���ŷ�Ŀ�Ⱥ͸߶ȶ�������ŷ���ʱ������ŷ�Ϳ��ԷŽ���һ���ŷ����ͬ����˹����һ��

�����������ж��ٸ��ŷ������һ�顰����˹���ޡ��ŷ⣨�����԰�һ���ŷ�ŵ���һ���ŷ����棩

ע�⣺��������ת�ŷ�

ʾ�� 1��
���룺envelopes = [[5,4],[6,4],[6,7],[2,3]]
�����3
���ͣ�����ŷ�ĸ���Ϊ 3, ���Ϊ: [2,3] => [5,4] => [6,7]��

ʾ�� 2��
���룺envelopes = [[1,1],[1,1],[1,1]]
�����1

��ʾ��
1 <= envelopes.length <= 10^5
envelopes[i].length == 2
1 <= wi, hi <= 10^5

*/



class Solution {
public:
	int maxEnvelopes(vector<vector<int>> &envelopes) {
		sort(envelopes.begin(), envelopes.end(),
			[](const vector<int> &a, const vector<int> &b) {
			return a[0] == b[0] ? a[1] > b[1] : a[0] < b[0];
		});

		// 0300��ģ��
		int len = envelopes.size();
		vector<int> dp(len, 0);
		int res = 0;
		for (const auto &v : envelopes) {
			int lo = 0, hi = res;
			lo = biSearch(dp, lo, hi, v[1]);
			if (lo == 0 || dp[lo - 1] < v[1]) {
				dp[lo] = v[1];
				if (res == lo) ++res;
			}
		}
		return res;
	}

private:
	// ���ֲ��ҵ�һ�����ڵ���target��λ��
	int biSearch(vector<int> &nums, int lo, int hi, int target) {
		while (lo < hi) {
			int mi = lo + ((hi - lo) >> 1);
			(target < nums[mi]) ? hi = mi : lo = mi + 1;
		}
		return lo;
	}
};
// https://leetcode.cn/problems/russian-doll-envelopes/solutions/19681/zui-chang-di-zeng-zi-xu-lie-kuo-zhan-dao-er-wei-er/
// @author https://leetcode.cn/u/labuladong/