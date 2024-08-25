#include "header.h"

/*

376. �ڶ�����

�����������֮��Ĳ��ϸ���������͸���֮�佻�棬���������г�Ϊ�ڶ�����
��һ���������ڵĻ�����������������
����һ��Ԫ�ػ��ߺ���������Ԫ�ص�����Ҳ�����ڶ�����

���磬 [1, 7, 4, 9, 2, 5] ��һ�� �ڶ����� ����Ϊ��ֵ (6, -3, 5, -7, 3) ������������ֵ�
�෴��[1, 4, 7, 2, 5] �� [1, 7, 4, 5, 5] ���ǰڶ����У���һ����������Ϊ����ǰ������ֵ�����������ڶ�����������Ϊ�������һ����ֵΪ��

������ ����ͨ����ԭʼ������ɾ��һЩ��Ҳ���Բ�ɾ����Ԫ������ã�ʣ�µ�Ԫ�ر�����ԭʼ˳��

����һ���������� nums ������ nums ����Ϊ �ڶ����� �� ������еĳ���

ʾ�� 1��
���룺nums = [1,7,4,9,2,5]
�����6
���ͣ��������о�Ϊ�ڶ����У���Ԫ��֮��Ĳ�ֵΪ (6, -3, 5, -7, 3)

ʾ�� 2��
���룺nums = [1,17,5,10,13,15,10,5,16,8]
�����7
���ͣ�������а�����������Ϊ 7 �ڶ�����
����һ���� [1, 17, 10, 13, 10, 16, 8] ����Ԫ��֮��Ĳ�ֵΪ (16, -7, 3, -3, 6, -8)

ʾ�� 3��
���룺nums = [1,2,3,4,5,6,7,8,9]
�����2

��ʾ��
1 <= nums.length <= 1000
0 <= nums[i] <= 1000

���ף����ܷ��� O(n) ʱ�临�Ӷ���ɴ���?

*/

// ���仯����
class Solution1 {
private:
	vector<int> memo_up;
	vector<int> memo_down;

public:
	int wiggleMaxLength(vector<int> &nums) {
		int len = nums.size();
		memo_up.resize(len);
		memo_down.resize(len);
		return max(helper(nums, len - 1, true), helper(nums, len - 1, false));
	}

private:
	int helper(vector<int> &nums, int idx, bool up) {
		if (idx == 0) return 1;
		if (up && memo_up[idx]) return memo_up[idx];
		if (!up && memo_down[idx]) return memo_down[idx];
		int cur = 0;
		if (nums[idx] > nums[idx - 1]) {
			cur = up ? helper(nums, idx - 1, false) + 1
				: helper(nums, idx - 1, false);
		} else if (nums[idx] < nums[idx - 1]) {
			cur = up ? helper(nums, idx - 1, true)
				: helper(nums, idx - 1, true) + 1;
		} else {
			cur = up ? helper(nums, idx - 1, true)
				: helper(nums, idx - 1, false);
		}
		return up ? memo_up[idx] = cur : memo_down[idx] = cur;
	}
};

// ��̬�滮
class Solution2 {
public:
	int wiggleMaxLength(vector<int> &nums) {
		int len = nums.size();
		vector<int> up(len);
		vector<int> down(len);
		up[0] = down[0] = 1;
		for (int i = 1; i < len; ++i) {
			if (nums[i] > nums[i - 1]) {
				up[i] = down[i - 1] + 1;
				down[i] = down[i - 1];
			} else if (nums[i] < nums[i - 1]) {
				up[i] = up[i - 1];
				down[i] = up[i - 1] + 1;
			} else {
				up[i] = up[i - 1];
				down[i] = down[i - 1];
			}
		}
		return max(up[len - 1], down[len - 1]);
	}
};

// �ռ��Ż�
class Solution3 {
public:
	int wiggleMaxLength(vector<int> &nums) {
		int len = nums.size();
		int up = 1, down = 1;
		for (int i = 1; i < len; ++i) {
			if (nums[i] > nums[i - 1]) up = down + 1;
			else if (nums[i] < nums[i - 1]) down = up + 1;
		}
		return max(up, down);
	}
};

