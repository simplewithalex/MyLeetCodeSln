#include "header.h"

/*

446. �Ȳ����л��� II - ������

����һ����������nums������nums�����еȲ������е���Ŀ
���һ�������� ����������Ԫ�أ�����������������Ԫ��֮����ͬ����Ƹ�����Ϊ�Ȳ�����

���磬[1, 3, 5, 7, 9]��[7, 7, 7, 7] �� [3, -1, -5, -9] ���ǵȲ�����
�����磬[1, 1, 2, 5, 7] ���ǵȲ�����

�����е��������Ǵ�������ɾ��һЩԪ�أ�Ҳ���ܲ�ɾ�����õ���һ������
���磬[2,5,10] �� [1,2,1,2,4,1,5,10] ��һ��������
��Ŀ���ݱ�֤����һ�� 32-bit ����

ʾ�� 1��
���룺nums = [2,4,6,8,10]
�����7
���ͣ����еĵȲ�������Ϊ��
[2,4,6]
[4,6,8]
[6,8,10]
[2,4,6,8]
[4,6,8,10]
[2,4,6,8,10]
[2,6,10]

ʾ�� 2��
���룺nums = [7,7,7,7,7]
�����16
���ͣ������е����������ж��ǵȲ�������

��ʾ��
1  <= nums.length <= 1000
-2^31 <= nums[i] <= 2^31 - 1

*/

// ����¼�㷨����ʱ
class Solution1 {
private:
	vector<unordered_map<long long, int>> memo;
	vector<unordered_map<long long, vector<int>>> dict;

public:
	int numberOfArithmeticSlices(vector<int>& nums) {
		int len = nums.size();
		int res = 0;
		dict.resize(len);
		memo.resize(len);

		for (int i = 0; i < len; ++i) {
			for (int j = i - 1; j >= 0; --j) {
				long long diff = (long long)nums[i] - nums[j];
				dict[i][diff].push_back(j);
			}
		}
		for (int i = 0; i < len; ++i) {
			for (auto p : dict[i]) res += helper(nums, i, p.first);
		}
		res -= len * (len - 1) / 2;
		return res;
	}

private:
	int helper(vector<int>& nums, int idx, long long d) {
		if (memo[idx].count(d)) return memo[idx][d];
		int cnt = 0;
		for (int j : dict[idx][d]) {
			cnt += helper(nums, j, d) + 1;
		}
		return memo[idx][d] = cnt;
	}
};


// �Ե׶��ϵĵĶ�̬�滮
class Solution2 {
public:
	int numberOfArithmeticSlices(vector<int> &nums) {
		int len = nums.size();
		vector<unordered_map<long long, int>> dp(len);
		for (int i = 0; i < len; ++i) {
			for (int j = i - 1; j >= 0; --j) {
				long long diff = (long long)nums[i] - nums[j];
				int cnt = 0;
				if (dp[j].count(diff)) cnt = dp[j][diff];
				dp[i][diff] += cnt + 1;
			}
		}
		int ans = 0;
		for (auto m : dp) {
			for (auto p : m) ans += p.second;
		}
		ans -= len * (len - 1) / 2;
		return ans;
	}
};
