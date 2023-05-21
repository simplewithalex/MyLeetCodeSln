#include "header.h"

/*

299. ��������Ϸ

���ں�����һ���� �����֣�Bulls and Cows����Ϸ������Ϸ�������£�

д��һ���������֣��������Ѳ���������Ƕ��١�����ÿ�²�һ�Σ���ͻ����һ������������Ϣ����ʾ��

�²��������ж���λ�������ֺ�ȷ��λ�ö��¶��ˣ���Ϊ "Bulls"����ţ����
�ж���λ�������ֲ¶��˵���λ�ò��ԣ���Ϊ "Cows"����ţ����Ҳ����˵����β²����ж���λ�ǹ�ţ���ֿ���ͨ����������ת���ɹ�ţ���֡�

����һ���������� secret �����Ѳ²������ guess �����㷵�ض�������β²����ʾ
��ʾ�ĸ�ʽΪ "xAyB" ��x �ǹ�ţ������ y ����ţ������A ��ʾ��ţ��B ��ʾ��ţ
��ע���������ֺ����Ѳ²�����ֶ����ܺ����ظ����֡�

ʾ�� 1��
���룺secret = "1807", guess = "7810"
�����"1A3B"
���ͣ����ֺ�λ�ö��ԣ���ţ���� '|' ���ӣ����ֲ¶�λ�ò��ԣ���ţ���Ĳ���б��Ӵֱ�ʶ��
"1807"
  |
"7810"

ʾ�� 2��
���룺secret = "1123", guess = "0111"
�����"1A1B"
���ͣ����ֺ�λ�ö��ԣ���ţ���� '|' ���ӣ����ֲ¶�λ�ò��ԣ���ţ���Ĳ���б��Ӵֱ�ʶ��
"1123"        "1123"
  |      or     |
"0111"        "0111"
ע�⣬������ƥ��� 1 �У�ֻ��һ����������ţ�����ֲ¶�λ�ò��ԣ���ͨ���������зǹ�ţ���֣����н���һ�� 1 ���Գ�Ϊ��ţ���֡�

��ʾ��
1 <= secret.length, guess.length <= 1000
secret.length == guess.length
secret �� guess �����������

*/

class Solution {
public:
	string getHint(string secret, string guess) {
		int len = secret.size();
		vector<int> bucket(10);
		int bull = 0, cow = 0;
		for (int i = 0; i < len; ++i) {
			if (secret[i] == guess[i]) {
				++bull;
			} else {
				++bucket[secret[i] - '0'];
				--bucket[guess[i] - '0'];
			}
		}
		for (int num : bucket) {
			if (num > 0) cow += num;
		}
		cow = len - cow - bull;
		return to_string(bull) + "A" + to_string(cow) + "B";
	}
};

// https://leetcode.cn/problems/bulls-and-cows/solutions/32429/javafang-fa-zhi-shi-yong-yi-lei-tong-jiu-gou-liao-/
// @author https://leetcode.cn/u/bug-19/