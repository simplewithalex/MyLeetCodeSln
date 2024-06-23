#include "header.h"

/*

331. ��֤��������ǰ�����л�

���л���������һ�ַ�����ʹ�� ǰ�����
����������һ���ǿսڵ�ʱ�����ǿ��Լ�¼������ڵ��ֵ
�������һ���սڵ㣬���ǿ���ʹ��һ�����ֵ��¼������ #

���磬����Ķ��������Ա����л�Ϊ�ַ��� "9,3,4,#,#,1,#,#,2,#,6,#,#"������ # ����һ���սڵ�

����һ���Զ��ŷָ������У���֤���Ƿ�����ȷ�Ķ�������ǰ�����л�
��дһ���ڲ��ع����������µĿ����㷨

��֤ÿ���Զ��ŷָ����ַ���Ϊһ��������Ϊһ����ʾ null ָ��� '#'
�������Ϊ�����ʽ������Ч�ģ���������Զ����������������Ķ��ţ����� "1,,3"

ע�⣺�������ؽ�����

ʾ�� 1:
����: preorder = "9,3,4,#,#,1,#,#,2,#,6,#,#"
���: true

ʾ�� 2:
����: preorder = "1,#"
���: false

ʾ�� 3:
����: preorder = "9,#,#,1"
���: false

��ʾ:
1 <= preorder.length <= 10^4
preorder ���Զ��� ������ �ָ��� [0,100] ��Χ�ڵ������� ��#�� ���

*/

class Solution1 {
public:
	bool isValidSerialization(string preorder) {
		istringstream in(preorder);
		vector<char> s;
		string str;
		while (getline(in, str, ',')) {
			str == "#" ? s.push_back('#') : s.push_back(stoi(str));
			int len = s.size();
			while (len >= 3 && s[len - 1] == '#' && s[len - 2] == '#' &&
				s[len - 3] != '#') {
				s.pop_back(), s.pop_back(), s.pop_back();
				s.push_back('#');
				len = s.size();
			}
		}
		return s.size() == 1 && s.back() == '#';
	}
};



class Solution2 {
public:
	bool isValidSerialization(string preorder) {
		istringstream in(preorder);
		// diff = ��� - ����
		int diff = -1;
		string str;
		while (getline(in, str, ',')) {
			diff += 1;
			if (diff > 0) return false;
			if (str != "#") diff -= 2;
		}
		return diff == 0;
	}
};
// https://leetcode.cn/problems/verify-preorder-serialization-of-a-binary-tree/solutions/651132/pai-an-jiao-jue-de-liang-chong-jie-fa-zh-66nt/
// @author https://leetcode.cn/u/fuxuemingzhu/

