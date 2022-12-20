#include "header.h"

/*

220. �����ظ�Ԫ�� III

����һ���������� nums ���������� k �� t �������ж��Ƿ���� ������ͬ�±� i �� j��ʹ�� abs(nums[i] - nums[j]) <= t ��ͬʱ������ abs(i - j) <= k ��
��������򷵻� true�������ڷ��� false��

ʾ�� 1��
���룺nums = [1,2,3,1], k = 3, t = 0
�����true

ʾ�� 2��
���룺nums = [1,0,1,1], k = 1, t = 2
�����true

ʾ�� 3��
���룺nums = [1,5,9,1,5,9], k = 2, t = 3
�����false

��ʾ��
0 <= nums.length <= 2 * 10^4
-2^31 <= nums[i] <= 2^31 - 1
0 <= k <= 10^4
0 <= t <= 2^31 - 1

*/

// �������� + ���򼯺�
class Solution1 {
public:
	bool containsNearbyAlmostDuplicate(vector<int> &nums, int k, int t) {
		int len = nums.size();
		set<int> s;
		for (int i = 0; i < len; ++i) {
			auto it = s.lower_bound(max(nums[i], INT_MIN + t) - t);
			if (it != s.end() && *it <= (min(nums[i], INT_MAX - t) + t)) return true;
			s.insert(nums[i]);
			if (s.size() == k + 1) s.erase(nums[i - k]);
		}
		return false;
	}
};
/*
 * ��Ŀ��ʵ�ʺ���Ϊ��������ͬԪ�ص��±���벻����k��Ԫ��ֵ��С֮�����t
 * ��Ŀת��Ϊ��������Ԫ���±� j Ϊ��ʶ�㣬���� j ֮ǰ����Ϊk֮�ڵ�Ԫ���±� i����С�Ƿ���[Vj - t, Vj + t]���� 
 * ʵ���ϣ������ǿ��� i �� j ֮���������ʱ����� Vi ��[Vj - t, Vj + t]���䣬��ô Vj Ҳ��[Vi - t, Vi + t]���䣬��ʱ���Ի��� i��j�� 
 * ���ֻ����һ�����򼴿ɣ�������ɺ�Ҳ�Ͱ�������������ˡ�
 */

// Ͱ����
class Solution2 {
public:
	bool containsNearbyAlmostDuplicate(vector<int> &nums, int k, int t) {
		unordered_map<int, int> mp;
		int len = nums.size();
		for (int i = 0; i < len; ++i) {
			long long n = nums[i];
			int id = getID(n, t + 1LL);
			if (mp.count(id)) return true;
			if (mp.count(id - 1) && abs(n - mp[id - 1]) <= t) return true;
			if (mp.count(id + 1) && abs(n - mp[id + 1]) <= t) return true;
			mp[id] = n;
			if (mp.size() == k + 1) mp.erase(getID(nums[i - k], t + 1LL));
		}
		return false;
	}

private:
	int getID(long long n, long long m) { return n < 0 ? ((n + 1) / m) - 1 : n / m; }
};
// 1. һ��Ͱ������ֻ����һ��Ԫ�أ�2. ע��Ԫ��ֵ�������ķ���
// https://leetcode-cn.com/problems/contains-duplicate-iii/solution/cun-zai-zhong-fu-yuan-su-iii-by-leetcode-bbkt/