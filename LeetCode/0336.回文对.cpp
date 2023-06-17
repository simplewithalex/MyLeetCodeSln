#include "header.h"

/*

336. ���Ķ�

����һ�� ������ͬ �ĵ��ʣ� �ҳ����� ��ͬ �������� (i, j)��ʹ���б��е��������ʣ�words[i] + words[j]����ƴ�ӳɻ��Ĵ�

ʾ�� 1��
���룺words = ["abcd","dcba","lls","s","sssll"]
�����[[0,1],[1,0],[3,2],[2,4]]
���ͣ���ƴ�ӳɵĻ��Ĵ�Ϊ ["dcbaabcd","abcddcba","slls","llssssll"]

ʾ�� 2��
���룺words = ["bat","tab","cat"]
�����[[0,1],[1,0]]
���ͣ���ƴ�ӳɵĻ��Ĵ�Ϊ ["battab","tabbat"]

ʾ�� 3��
���룺words = ["a",""]
�����[[0,1],[1,0]]

��ʾ��
1 <= words.length <= 5000
0 <= words[i].length <= 300
words[i] ��СдӢ����ĸ���


*/

class Solution1 {
public:
	vector<vector<int>> palindromePairs(vector<string> &words) {
		// ��ϣ����ÿ���ַ�����ת
		// set���򱣴��ַ�������
		unordered_map<string, int> dict;
		set<int> s;
		for (int i = 0; i < words.size(); ++i) {
			string str = words[i];
			reverse(str.begin(), str.end());
			dict[str] = i;
			s.insert(str.size());
		};
		vector<vector<int>> res;
		for (int i = 0; i < words.size(); ++i) {
			const string &cur = words[i];
			int len = cur.size();
			if (dict.count(cur) && dict[cur] != i) res.push_back({ i, dict[cur] });
			auto end = s.find(len);
			for (auto it = s.begin(); it != end; ++it) {
				int subLen = *it;
				if (isPal(cur, subLen, len - 1) &&
					dict.count(cur.substr(0, subLen))) {
					res.push_back({ i, dict[cur.substr(0, subLen)] });
				}
				if (isPal(cur, 0, len - subLen - 1) &&
					dict.count(cur.substr(len - subLen))) {
					res.push_back({ dict[cur.substr(len - subLen)], i });
				}
			}
		}
		return res;
	}

private:
	bool isPal(const string &s, int i, int j) {
		while (i < j) {
			if (s[i++] != s[j--]) return false;
		}
		return true;
	}
};
// https://zhuanlan.zhihu.com/p/503767967

struct TrieNode {
	size_t num = 26;
	int index = -1;
	vector<TrieNode *> children{ num, nullptr };
	vector<int> suffixes;
};

class Solution2 {
public:
	vector<vector<int>> palindromePairs(vector<string> &words) {
		vector<vector<int>> res;
		TrieNode *root = new TrieNode();
		for (int i = 0; i < words.size(); ++i) add(root, words[i], i);
		for (int i = 0; i < words.size(); ++i) search(root, words, i, res);
		return res;
	}

private:
	void add(TrieNode *root, const string &word, int index) {
		for (int i = word.size() - 1; i >= 0; --i) {
			int j = word[i] - 'a';
			if (!root->children[j]) root->children[j] = new TrieNode();
			if (isPal(word, 0, i)) root->suffixes.push_back(index);
			root = root->children[j];
		}
		root->suffixes.push_back(index);
		root->index = index;
	}
	void search(TrieNode *root, vector<string> &words, int idx,
		vector<vector<int>> &res) {
		int len = words[idx].size();
		for (int j = 0; j < len; ++j) {
			if (isPal(words[idx], j, len - 1) && root->index != -1) {
				res.push_back({ idx, root->index });
			}
			root = root->children[words[idx][j] - 'a'];
			if (!root) return;
		}
		for (int k : root->suffixes) {
			if (k != idx) res.push_back({ idx, k });
		}
	}
	bool isPal(const string &s, int i, int j) {
		while (i < j) {
			if (s[i++] != s[j--]) return false;
		}
		return true;
	}
};
// https://leetcode.cn/problems/palindrome-pairs/solutions/187969/qian-zhui-shu-jie-fa-by-dufre/
// @author https://leetcode.cn/u/dufre/