#include "header.h"

/*

382. ��������ڵ�

����һ�����������ѡ�������һ���ڵ㣬��������Ӧ�Ľڵ�ֵ

ÿ���ڵ� ��ѡ�еĸ���һ��

ʵ�� Solution �ࣺ
Solution(ListNode head) ʹ�����������ʼ������
int getRandom() �����������ѡ��һ���ڵ㲢���ظýڵ��ֵ�����������нڵ㱻ѡ�еĸ������

ʾ����
����
["Solution", "getRandom", "getRandom", "getRandom", "getRandom", "getRandom"]
[[[1, 2, 3]], [], [], [], [], []]
���
[null, 1, 3, 2, 2, 3]
����
Solution solution = new Solution([1, 2, 3]);
solution.getRandom(); // ���� 1
solution.getRandom(); // ���� 3
solution.getRandom(); // ���� 2
solution.getRandom(); // ���� 2
solution.getRandom(); // ���� 3
// getRandom() ����Ӧ������� 1��2��3�е�һ����ÿ��Ԫ�ر����صĸ�����ȡ�

��ʾ��
�����еĽڵ����ڷ�Χ [1, 10^4] ��
-10^4 <= Node.val <= 10^4
������� getRandom ���� 10^4 ��

���ף�
�������ǳ����ҳ���δ֪������ô����
���ܷ��ڲ�ʹ�ö���ռ������½�������⣿

*/


// ˮ�������㷨��O(1)�ռ�
class Solution {
private:
	ListNode *head;

public:
	Solution(ListNode *head) { this->head = head; }

	int getRandom() {
		int i = 1, ans = 0;
		for (ListNode *node = head; node; node = node->next) {
			if (rand() % i == 0) ans = node->val;
			++i;
		}
		return ans;
	}
};
// https://leetcode.cn/problems/linked-list-random-node/solutions/1210211/lian-biao-sui-ji-jie-dian-by-leetcode-so-x6it/
// @author LeetCode�ٷ����

/**
* Your Solution object will be instantiated and called as such:
* Solution* obj = new Solution(head);
* int param_1 = obj->getRandom();
*/
