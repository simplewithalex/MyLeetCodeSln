#include "header.h"

/*

����һ��רҵ��С͵���ƻ�͵���ؽֵķ��ݡ�

ÿ�䷿�ڶ�����һ�����ֽ�Ӱ����͵�Ե�Ψһ��Լ���ؾ������ڵķ���װ���໥��ͨ�ķ���ϵͳ������������ڵķ�����ͬһ���ϱ�С͵���룬ϵͳ���Զ�������

����һ������ÿ�����ݴ�Ž��ķǸ��������飬�������ڲ���������װ�õ�����£��ܹ�͵�Ե�����߽�

ʾ�� 1:

����: [1,2,3,1]
���: 4
����: ͵�� 1 �ŷ��� (��� = 1) ��Ȼ��͵�� 3 �ŷ��� (��� = 3)��͵�Ե�����߽�� = 1 + 3 = 4 

ʾ�� 2:

����: [2,7,9,3,1]
���: 12
����: ͵�� 1 �ŷ��� (��� = 2), ͵�� 3 �ŷ��� (��� = 9)������͵�� 5 �ŷ��� (��� = 1)��͵�Ե�����߽�� = 2 + 9 + 1 = 12 ��

*/

//����¼�㷨
class Solution1 {
public:
	int rob(vector<int> &nums)
	{
		int len = nums.size();
		vector<int> memo(len, -1);
		return dfs(nums, len - 1, memo);
	}
	int dfs(vector<int> &nums, int index, vector<int> &memo)
	{
		if (index < 0) return 0;
		if (memo[index] != -1) return memo[index];
		int res = max(dfs(nums, index - 2, memo) + nums[index], dfs(nums, index - 1, memo));
		memo[index] = res;
		return res;
	}
};

//�Ե׶��ϵĶ�̬�滮
class Solution2 {
public:
	int rob(vector<int> &nums)
	{
		if (nums.empty()) return 0;
		int len = nums.size();
		vector<int> dp(len + 1, 0);
		dp[0] = 0;
		dp[1] = nums[0];
		for (int i = 1; i < len; ++i)
			dp[i + 1] = max(dp[i], dp[i - 1] + nums[i]);
		return dp[len];
	}
};