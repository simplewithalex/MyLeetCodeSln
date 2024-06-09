#include "header.h"

/*

472. ���Ӵ�

����һ�������ظ����ʵ��ַ������� words�������ҳ������� words �е��������Ӵ�

���Ӵʶ���Ϊ��һ����ȫ�ɸ��������е����������϶̵��ʣ���һ���ǲ�ͬ���������ʣ���ɵ��ַ���

ʾ�� 1��
���룺words = ["cat","cats","catsdogcats","dog","dogcatsdog","hippopotamuses","rat","ratcatdogcat"]
�����["catsdogcats","dogcatsdog","ratcatdogcat"]
���ͣ�"catsdogcats" �� "cats", "dog" �� "cats" ���;
"dogcatsdog" �� "dog", "cats" �� "dog" ���;
"ratcatdogcat" �� "rat", "cat", "dog" �� "cat" ���

ʾ�� 2��
���룺words = ["cat","dog","catdog"]
�����["catdog"]

��ʾ��
1 <= words.length <= 10^4
1 <= words[i].length <= 30
words[i] ����СдӢ����ĸ���
words �е������ַ������� Ψһ ��
1 <= sum(words[i].length) <= 10^5

*/

class Solution1 {
private:
	vector<char> memo;
	unordered_set<string> dict;

public:
	vector<string> findAllConcatenatedWordsInADict(vector<string> &words) {
		sort(words.begin(), words.end(), [](const string &a, const string &b) {
			return a.size() < b.size();
		});
		vector<string> ans;
		for (const string &word : words) {
			if (word.empty()) continue;
			int len = word.size();
			memo.resize(len + 1, -1);
			memo.clear();
			if (helper(word, len)) ans.push_back(word);
			dict.insert(word);
		}
		return ans;
	}

private:
	bool helper(const string &s, int i) {
		if (i == 0) return true;
		if (memo[i] != -1) return memo[i];
		for (int j = 0; j < i; ++j) {
			if (dict.count(s.substr(j, i - j)) && helper(s, j)) {
				return memo[i] = true;
			}
		}
		return memo[i] = false;
	}
};


// ǰ׺��
struct TrieNode {
	bool isWord;
	vector<TrieNode *> children;
	TrieNode() : isWord(false), children(26, nullptr) {}
};

class Solution2 {
private:
	TrieNode *root;

public:
	vector<string> findAllConcatenatedWordsInADict(vector<string> &words) {
		sort(words.begin(), words.end(), [](const string &a, const string &b) {
			return a.size() < b.size();
		});
		root = new TrieNode();
		vector<string> ans;
		for (const string &word : words) {
			if (!word.empty()) {
				if (helper(word, 0)) ans.push_back(word);
				else insert(word);
			}
		}
		return ans;
	}

private:
	bool helper(const string &word, int start) {
		if (start == word.size()) return true;
		TrieNode *cur = root;
		while (start < word.size()) {
			cur = cur->children[word[start] - 'a'];
			if (!cur) return false;
			if (cur->isWord && helper(word, start + 1)) return true;
			++start;
		}
		return false;
	}
	void insert(const string &word) {
		TrieNode *cur = root;
		for (const auto &c : word) {
			char i = c - 'a';
			if (!cur->children[i]) {
				cur->children[i] = new TrieNode();
			}
			cur = cur->children[i];
		}
		cur->isWord = true;
	}
};
