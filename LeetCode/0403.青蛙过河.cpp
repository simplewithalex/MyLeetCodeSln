#include "header.h"

/*

403. ���ܹ���

һֻ������Ҫ���ӣ��ٶ��������ȷ�Ϊ���ɸ���Ԫ�񣬲�����ÿһ����Ԫ���ڶ��п��ܷ���һ��ʯ�ӣ�Ҳ�п���û�У�

���ܿ�������ʯ�ӣ����ǲ���������ˮ��

����ʯ�ӵ�λ���б� stones���õ�Ԫ����� ���� ��ʾ�������ж������ܷ�ɹ����ӣ����ܷ������һ���������һ��ʯ���ϣ�

��ʼʱ������Ĭ����վ�ڵ�һ��ʯ���ϣ������Լٶ�����һ��ֻ����Ծ 1 ����λ����ֻ�ܴӵ�Ԫ�� 1 ������Ԫ�� 2��

���������һ����Ծ�� k ����λ����ô������������Ծ����ֻ��ѡ��Ϊ k - 1��k �� k + 1 ����λ������ע�⣬����ֻ����ǰ�����յ�ķ�����Ծ

ʾ�� 1��
���룺stones = [0,1,3,5,6,8,12,17]
�����true
���ͣ����ܿ��Գɹ����ӣ��������·�����Ծ���� 1 ����λ���� 2 ��ʯ��,
Ȼ���� 2 ����λ���� 3 ��ʯ��, ���� �� 2 ����λ���� 4 ��ʯ��,
Ȼ���� 3 ����λ���� 6 ��ʯ��, �� 4 ����λ���� 7 ��ʯ��,
����� 5 ����λ���� 8 ��ʯ�ӣ������һ��ʯ�ӣ�

ʾ�� 2��
���룺stones = [0,1,2,3,4,8,9,11]
�����false
���ͣ�������Ϊ�� 5 �͵� 6 ��ʯ��֮��ļ��̫��û�п�ѡ�ķ�����������Ծ��ȥ��

��ʾ��
2 <= stones.length <= 2000
0 <= stones[i] <= 2^31 - 1
stones[0] == 0
stones ���ϸ���������

*/



// ����¼ + ��������
class Solution1 {
private:
	vector<vector<int>> memo;
	unordered_map<int, int> stone_pos;

public:
	bool canCross(vector<int> &stones) {
		int len = stones.size();
		// dp[idx][dump] Ϊ��ǰ�� idx ��ǰ�� jump ����һ��λ��
		// ��Ծ�������Ϊ��Ծ����+1, ����������յ�,
		// ��Ծ�������Ϊ���鳤��
		memo.resize(len, vector<int>(len + 1, -1));
		for (int i = 0; i < stones.size(); ++i) stone_pos[stones[i]] = i;
		return helper(stones, 0, 1);
	}

private:
	bool helper(vector<int> &stones, int idx, int jump) {
		if (idx == stones.size() - 1) return true;
		if (memo[idx][jump] != -1) return memo[idx][jump];
		int next_stone = stones[idx] + jump;
		if (!stone_pos.count(next_stone)) return false;
		bool ans = false;
		for (int nextJump = jump - 1; nextJump <= jump + 1; ++nextJump) {
			if (nextJump > 0) {
				ans = ans || helper(stones, stone_pos[next_stone], nextJump);
			}
		}
		return memo[idx][jump] = ans;
	}
};
// https://leetcode.com/problems/frog-jump/editorial/
// https://leetcode.cn/problems/frog-jump/solutions/748878/c-ji-yi-hua-sou-suo-dong-tai-gui-hua-by-uq2pl/
// @author https://leetcode.cn/u/qian2/


// �Ե׶��ϵĶ�̬�滮
class Solution2 {
private:
	// dp[idx][dump] Ϊ��ǰ�� idx ��ǰ�� jump ����һ��λ��
	// ��Ծ�������Ϊ��Ծ����+1, ����������յ�,
	// ��Ծ�������Ϊ���鳤��
	int dp[2000][2001];

public:
	bool canCross(vector<int> &stones) {
		int len = stones.size();
		for (int i = 1; i < len; ++i) {
			if (stones[i] - stones[i - 1] > i) return false;
		}
		for (int jump = 0; jump <= len; ++jump) dp[len - 1][jump] = true;
		for (int i = len - 2; i >= 0; --i) {
			for (int j = i + 1; j < len; ++j) {
				int jump = stones[j] - stones[i];
				if (jump > i + 1) break;
				dp[i][jump] = dp[j][jump - 1] || dp[j][jump] || dp[j][jump + 1];
			}
		}
		return dp[0][1];
	}
};


// ����¼ + ���յ����
class Solution3 {
private:
	vector<vector<int>> memo;
	unordered_map<int, int> stone_pos;

public:
	bool canCross(vector<int> &stones) {
		int len = stones.size();
		// dp[idx][dump] Ϊ��һ������ jump ���� idx λ��
		// ��Ծ�������Ϊ��һ������+1, ����������յ�,
		// ��һ���������Ϊ���鳤��-1
		memo.resize(len, vector<int>(len, -1));
		for (int i = 0; i < stones.size(); ++i) stone_pos[stones[i]] = i;
		for (int j = len - 2; j >= 0; --j) {
			int preJump = stones[len - 1] - stones[j];
			if ((preJump <= j + 1) && helper(stones, len - 1, preJump)) {
				return true;
			}
		}
		return false;
	}

private:
	bool helper(vector<int> &stones, int idx, int preJump) {
		if (preJump <= 0 || preJump > idx) return false;
		if (memo[idx][preJump] != -1) return memo[idx][preJump];
		int last_stone = stones[idx] - preJump;
		if (!stone_pos.count(last_stone)) return false;
		if (idx == 1 && preJump == 1) return true;
		bool ans = false;
		for (int ppre_Jump = preJump - 1; ppre_Jump <= preJump + 1;
			++ppre_Jump) {
			ans = ans || helper(stones, stone_pos[last_stone], ppre_Jump);
		}
		return memo[idx][preJump] = ans;
	}
};
// https://leetcode.cn/problems/frog-jump/solutions/1034024/qing-wa-guo-he-xiang-xi-ti-jie-by-chaset-4ubi/
// @author https://leetcode.cn/u/chasetomorrow/

// �÷�����Ӧ���Ե׶��ϵĶ�̬�滮�������Կ��ٷ����


