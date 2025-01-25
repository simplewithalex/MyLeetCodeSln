#include "header.h"

/*


591. ��ǩ��֤��

����һ����ʾ����Ƭ�ε��ַ���������Ҫʵ��һ����֤����������δ��룬���������Ƿ�Ϸ�

�Ϸ��Ĵ���Ƭ����Ҫ�������µ����й���

1. ������뱻�Ϸ��ıպϱ�ǩ��Χ�����򣬴�������Ч��

2. �պϱ�ǩ����һ���Ϸ���Ҫ�ϸ���ϸ�ʽ��<TAG_NAME>TAG_CONTENT</TAG_NAME>�����У�<TAG_NAME>����ʼ��ǩ��</TAG_NAME>�ǽ�����ǩ
��ʼ�ͽ�����ǩ�е� TAG_NAME Ӧ����ͬ�����ҽ��� TAG_NAME �� TAG_CONTENT ���ǺϷ��ģ��պϱ�ǩ���ǺϷ���

3. �Ϸ��� TAG_NAME �����д�д��ĸ�������ڷ�Χ [1,9] ֮�䡣���򣬸� TAG_NAME �ǲ��Ϸ���

4. �Ϸ��� TAG_CONTENT ���԰��������Ϸ��ıպϱ�ǩ��cdata ����ο�����7���������ַ���ע��ο�����1��
���˲�ƥ���<����ƥ�����ʼ�ͽ�����ǩ����ƥ��Ļ���в��Ϸ� TAG_NAME �ıպϱ�ǩ������TAG_CONTENT �ǲ��Ϸ���

5. һ����ʼ��ǩ�����û�о�����ͬ TAG_NAME �Ľ�����ǩ��֮ƥ�䣬�ǲ��Ϸ��ġ���֮��Ȼ����������Ҳ��Ҫ���Ǳ�ǩǶ�׵�����

6. һ��<��������Ҳ���һ��������>��֮ƥ�䣬�ǲ��Ϸ��ġ�
���ҵ����ҵ�һ��<��</ʱ������ֱ����һ��>��ǰ���ַ�����Ӧ��������Ϊ TAG_NAME����һ���Ϸ���

7. cdata �����¸�ʽ��<![CDATA[CDATA_CONTENT]]>��CDATA_CONTENT �ķ�Χ������� <![CDATA[ �ͺ����ĵ�һ�� ]]>֮����ַ�

8. CDATA_CONTENT ���԰��������ַ���cdata �Ĺ�������ֹ��֤������CDATA_CONTENT��
���Լ�ʹ������һЩ�ַ����Ա�����Ϊ��ǩ�����ۺϷ����ǲ��Ϸ�����ҲӦ�ý�������Ϊ�����ַ�

�Ϸ����������:

����: "<DIV>This is the first line <![CDATA[<div>]]></DIV>"
���: True
����:
���뱻�������˱պϵı�ǩ�ڣ� <DIV> �� </DIV>

TAG_NAME �ǺϷ��ģ�TAG_CONTENT ������һЩ�ַ��� cdata

��ʹ CDATA_CONTENT ���в�ƥ�����ʼ��ǩ�Ͳ��Ϸ��� TAG_NAME����Ӧ�ñ���Ϊ��ͨ���ı��������Ǳ�ǩ

���� TAG_CONTENT �ǺϷ��ģ���˴����ǺϷ��ġ����շ���True


����: "<DIV>>>  ![cdata[]] <![CDATA[<div>]>]]>]]>>]</DIV>"
���: True
����:
�������Ƚ�����ָ�Ϊ�� start_tag|tag_content|end_tag

start_tag -> "<DIV>"

end_tag -> "</DIV>"

tag_content Ҳ�ɱ��ָ�Ϊ�� text1|cdata|text2

text1 -> ">>  ![cdata[]] "

cdata -> "<![CDATA[<div>]>]]>" ������ CDATA_CONTENT Ϊ "<div>]>"

text2 -> "]]>>]"

start_tag ���� "<DIV>>>" ��ԭ����չ��� 6
cdata ���� "<![CDATA[<div>]>]]>]]>" ��ԭ����չ��� 7


���Ϸ����������:

����: "<A>  <B> </A>   </B>"
���: False
����: ���Ϸ������ "<A>" �Ǳպϵģ���ô "<B>" һ���ǲ�ƥ��ģ���֮��Ȼ

����: "<DIV>  div tag is not closed  <DIV>"
���: False

����: "<DIV>  unmatched <  </DIV>"
���: False

����: "<DIV> closed tags with invalid tag name  <b>123</b> </DIV>"
���: False

����: "<DIV> unmatched tags with invalid tag name  </1234567890> and <CDATA[[]]>  </DIV>"
���: False

����: "<DIV>  unmatched start tag <B>  and unmatched end tag </C>  </DIV>"
���: False

ע��:
Ϊ�������������Լ�������Ĵ��루�����ᵽ�������ַ���ֻ��������, ��ĸ, '<','>','/','!','[',']'��' '

*/






class Solution {
public:
	const string CDATA1 = "<![CDATA[";
	const string CDATA2 = "]]>";
	bool isValid(string code) {
		stack<string> s;
		int len = code.size(), i = 0;
		while (i < len) {
			if (i + 8 < len && code.substr(i, 9) == CDATA1) {
				if (i == 0) return false;
				int j = i + 9;
				while (j < len) {
					if (j + 2 < len && code.substr(j, 3) == CDATA2) {
						j += 3;
						break;
					}
					++j;
				}
				if (j == len) return false;
				i = j;
			} else if (code[i] == '<') {
				if (i == len - 1) return false;
				bool isEnd = code[i + 1] == '/';
				int p = isEnd ? i + 2 : i + 1, j = p;
				while (j < len && code[j] != '>') {
					if (!isupper(code[j])) return false;
					++j;
				}
				if (j == len) return false;
				int subLen = j - p;
				if (subLen < 1 || subLen > 9) return false;
				string tag = code.substr(p, subLen);
				i = j + 1;
				if (!isEnd) {
					s.push(tag);
				}
				else {
					if (s.empty() || !(s.top() == tag)) return false;
					s.pop();
					if (s.empty() && i < len) return false;
				}
			} else {
				if (i == 0) return false;
				++i;
			}
		}
		return s.empty();
	}
};
// https://leetcode.cn/problems/tag-validator/solutions/1463659/by-ac_oier-9l8z/
// @author https://leetcode.cn/u/ac_oier/



