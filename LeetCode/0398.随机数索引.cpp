#include "header.h"

/*

398. ���������

����һ�����ܺ��� �ظ�Ԫ�� ���������� nums ������������������Ŀ������ target ������
����Լ������������һ��������������

ʵ�� Solution �ࣺ
Solution(int[] nums) ������ nums ��ʼ������
int pick(int target) �� nums ��ѡ��һ������ nums[i] == target ��������� i
������ڶ����Ч����������ÿ�������ķ��ظ���Ӧ�����

ʾ����
����
["Solution", "pick", "pick", "pick"]
[[[1, 2, 3, 3, 3]], [3], [1], [3]]
���
[null, 4, 0, 2]
����
Solution solution = new Solution([1, 2, 3, 3, 3]);
solution.pick(3); // ����������� 2, 3 ���� 4 ֮һ��ÿ�������ķ��ظ���Ӧ�����
solution.pick(1); // ���� 0 ����Ϊֻ�� nums[0] ���� 1
solution.pick(3); // ����������� 2, 3 ���� 4 ֮һ��ÿ�������ķ��ظ���Ӧ�����

��ʾ��
1 <= nums.length <= 2 * 10^4
-2^31 <= nums[i] <= 2^31 - 1
target �� nums �е�һ������
������ pick ���� 10^4 ��

*/


class Solution1 {
public:
	unordered_map<int, vector<int>> pos;
	Solution1(vector<int> &nums) {
		for (int i = 0; i < nums.size(); ++i) {
			pos[nums[i]].push_back(i);
		}
	}

	int pick(int target) {
		const auto &indices = pos[target];
		return indices[rand() % indices.size()];
	}
};

// ˮ��������TLE��
// ����������ļ���ʽ�洢�����߿ɼ��蹹�캯��������Ǹ��ļ�·���������ļ���СԶ���ڴ��С
// �������޷�ͨ�����ļ��ķ�ʽ���������±걣�����ڴ��еģ������Ҫ�ҵ�һ�ֿռ临�Ӷȸ��͵��㷨
class Solution2 {
public:
	vector<int> &nums;
	Solution2(vector<int> &nums) : nums(nums) {}

	int pick(int target) {
		int ans = 0;
		for (int i = 0, cnt = 0; i < nums.size(); ++i) {
			if (nums[i] == target) {
				++cnt;
				if (rand() % cnt == 0) ans = i;
			}
		}
		return ans;
	}
};

/**
* Your Solution object will be instantiated and called as such:
* Solution* obj = new Solution(nums);
* int param_1 = obj->pick(target);
*/


