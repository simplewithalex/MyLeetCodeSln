#include "header.h"

/*

403. 青蛙过河

一只青蛙想要过河，假定河流被等分为若干个单元格，并且在每一个单元格内都有可能放有一块石子（也有可能没有）

青蛙可以跳上石子，但是不可以跳入水中

给你石子的位置列表 stones（用单元格序号 升序 表示），请判定青蛙能否成功过河（即能否在最后一步跳至最后一块石子上）

开始时，青蛙默认已站在第一块石子上，并可以假定它第一步只能跳跃 1 个单位（即只能从单元格 1 跳至单元格 2）

如果青蛙上一步跳跃了 k 个单位，那么它接下来的跳跃距离只能选择为 k - 1、k 或 k + 1 个单位。另请注意，青蛙只能向前方（终点的方向）跳跃

示例 1：
输入：stones = [0,1,3,5,6,8,12,17]
输出：true
解释：青蛙可以成功过河，按照如下方案跳跃：跳 1 个单位到第 2 块石子,
然后跳 2 个单位到第 3 块石子, 接着 跳 2 个单位到第 4 块石子,
然后跳 3 个单位到第 6 块石子, 跳 4 个单位到第 7 块石子,
最后，跳 5 个单位到第 8 个石子（即最后一块石子）

示例 2：
输入：stones = [0,1,2,3,4,8,9,11]
输出：false
解释：这是因为第 5 和第 6 个石子之间的间距太大，没有可选的方案供青蛙跳跃过去。

提示：
2 <= stones.length <= 2000
0 <= stones[i] <= 2^31 - 1
stones[0] == 0
stones 按严格升序排列

*/



// 备忘录 + 从起点递推
class Solution1 {
private:
	vector<vector<int>> memo;
	unordered_map<int, int> stone_pos;

public:
	bool canCross(vector<int> &stones) {
		int len = stones.size();
		// dp[idx][dump] 为当前从 idx 向前跳 jump 到下一个位置
		// 跳跃步长最大为跳跃次数+1, 如果能跳到终点,
		// 跳跃步长最大为数组长度
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


// 自底而上的动态规划
class Solution2 {
private:
	// dp[idx][dump] 为当前从 idx 向前跳 jump 到下一个位置
	// 跳跃步长最大为跳跃次数+1, 如果能跳到终点,
	// 跳跃步长最大为数组长度
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


// 备忘录 + 从终点递推
class Solution3 {
private:
	vector<vector<int>> memo;
	unordered_map<int, int> stone_pos;

public:
	bool canCross(vector<int> &stones) {
		int len = stones.size();
		// dp[idx][dump] 为上一次跳了 jump 到达 idx 位置
		// 跳跃步长最大为上一跳次数+1, 如果能跳到终点,
		// 上一跳步长最大为数组长度-1
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

// 该方法对应的自底而上的动态规划方法可以看官方题解


