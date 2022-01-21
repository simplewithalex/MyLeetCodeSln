#include "header.h"

/*

给定一个 m x n 二维字符网格 board 和一个单词（字符串）列表 words，找出所有同时在二维网格和字典中出现的单词。

单词必须按照字母顺序，通过 相邻的单元格 内的字母构成，其中“相邻”单元格是那些水平相邻或垂直相邻的单元格。同一个单元格内的字母在一个单词中不允许被重复使用。

 

示例 1：
输入：board = [["o","a","a","n"],["e","t","a","e"],["i","h","k","r"],["i","f","l","v"]], words = ["oath","pea","eat","rain"]
输出：["eat","oath"]

示例 2：
输入：board = [["a","b"],["c","d"]], words = ["abcb"]
输出：[]
  
提示：
m == board.length
n == board[i].length
1 <= m, n <= 12
board[i][j] 是一个小写英文字母
1 <= words.length <= 3 * 10^4
1 <= words[i].length <= 10
words[i] 由小写英文字母组成
words 中的所有字符串互不相同

*/

// 暴力搜索
// 题意明确单词长度不超过10，可以作为剪枝条件
class Solution1 {
public:
	vector<string> findWords(vector<vector<char>> &board,
		vector<string> &words) {
		if (board.empty() || board[0].empty()) return {};
		int row = board.size(), col = board[0].size();
		vector<string> res;
		unordered_set<string> s;
		for (auto str : words) s.insert(str);
		string temp;
		for (int i = 0; i < row; ++i) {
			for (int j = 0; j < col; ++j) {
				backtrack(board, i, j, temp, s, res);
			}
		}
		return res;
	}

private:
	void backtrack(vector<vector<char>> &board, int i, int j, string &temp,
		unordered_set<string> &s, vector<string> &res) {
		int row = board.size(), col = board[0].size();
		if (i < 0 || i == row || j < 0 || j == col || board[i][j] == '*') return;
		if (temp.size() > 10) return;
		temp.push_back(board[i][j]);
		if (s.count(temp)) {
			res.push_back(temp);
			s.erase(temp);
		}
		board[i][j] = '*';
		backtrack(board, i - 1, j, temp, s, res);
		backtrack(board, i + 1, j, temp, s, res);
		backtrack(board, i, j - 1, temp, s, res);
		backtrack(board, i, j + 1, temp, s, res);
		board[i][j] = temp.back();
		temp.pop_back();
	}
};


class TrieNode {
private:
	int num = 26;
	string str;
	vector<TrieNode *> v;

public:
	TrieNode() : v(vector<TrieNode *>(num, nullptr)) {}
	bool containsKey(char ch) { return v[ch - 'a'] != nullptr; }
	TrieNode * get(char ch) { return v[ch - 'a']; }
	void put(char ch, TrieNode *node) { v[ch - 'a'] = node; }
	void setStr(const string &word) { str = word; }
	const string & getStr() { return str; }
	void clearStr() { str.clear(); }
};

// 使用Trie树优化
class Solution2 {
public:
	vector<string> findWords(vector<vector<char>> &board, vector<string> &words) {
		if (board.empty() || board[0].empty()) return {};
		int row = board.size(), col = board[0].size();
		vector<string> res;
		TrieNode *root = new TrieNode();
		for (auto str : words) insert(str, root);
		for (int i = 0; i < row; ++i) {
			for (int j = 0; j < col; ++j) {
				backtrack(board, i, j, root, res);
			}
		}
		return res;
	}

private:
	void backtrack(vector<vector<char>> &board, int i, int j, TrieNode *node, vector<string> &res) {
		if (!node->getStr().empty()) {
			res.push_back(node->getStr());
			node->clearStr();
		}
		int row = board.size(), col = board[0].size();
		// 注意board[i][j] == '*' 的判断应放在containsKey判断之前, 否则造成TrieNode中的数组成员越界访问
		if (i < 0 || i == row || j < 0 || j == col || board[i][j] == '*' || !node->containsKey(board[i][j])) return;
		char cur = board[i][j];
		board[i][j] = '*';
		backtrack(board, i - 1, j, node->get(cur), res);
		backtrack(board, i + 1, j, node->get(cur), res);
		backtrack(board, i, j - 1, node->get(cur), res);
		backtrack(board, i, j + 1, node->get(cur), res);
		board[i][j] = cur;
	}

	void insert(string word, TrieNode *root) {
		TrieNode *node = root;
		for (int i = 0; i < word.size(); ++i) {
			char cur = word[i];
			if (!node->containsKey(cur)) {
				node->put(cur, new TrieNode());
			}
			node = node->get(cur);
		}
		node->setStr(word);
	}
};

// https://leetcode-cn.com/problems/word-search-ii/solution/gong-shui-san-xie-yi-ti-shuang-jie-hui-s-am8f/
// https://leetcode-cn.com/problems/word-search-ii/solution/dan-ci-sou-suo-ii-by-leetcode-solution-7494/


