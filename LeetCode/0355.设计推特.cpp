#include "header.h"

/*

355. �������

���һ���򻯰������(Twitter)���������û�ʵ�ַ������ģ���ע/ȡ����ע�����û����ܹ�������ע�ˣ������Լ�������� 10 ������

ʵ�� Twitter �ࣺ
Twitter() ��ʼ�����װ����ض���
void postTweet(int userId, int tweetId) ���ݸ����� tweetId �� userId ����һ�������ġ�ÿ�ε��ô˺�������ʹ��һ����ͬ�� tweetId
List<Integer> getNewsFeed(int userId) ������ǰ�û��������������  10 �����ĵ� ID �����������е�ÿһ����������û���ע���˻������û��Լ����������ġ����ı��� ����ʱ��˳�����������Զ����
void follow(int followerId, int followeeId) ID Ϊ followerId ���û���ʼ��ע ID Ϊ followeeId ���û�
void unfollow(int followerId, int followeeId) ID Ϊ followerId ���û����ٹ�ע ID Ϊ followeeId ���û�

ʾ����
����
["Twitter", "postTweet", "getNewsFeed", "follow", "postTweet", "getNewsFeed", "unfollow", "getNewsFeed"]
[[], [1, 5], [1], [1, 2], [2, 6], [1], [1, 2], [1]]
���
[null, null, [5], null, null, [6, 5], null, [5]]
����
Twitter twitter = new Twitter();
twitter.postTweet(1, 5); // �û� 1 ������һ�������� (�û� id = 1, ���� id = 5)
twitter.getNewsFeed(1);  // �û� 1 �Ļ�ȡ����Ӧ������һ���б����а���һ�� id Ϊ 5 ������
twitter.follow(1, 2);    // �û� 1 ��ע���û� 2
twitter.postTweet(2, 6); // �û� 2 ������һ�������� (���� id = 6)
twitter.getNewsFeed(1);  // �û� 1 �Ļ�ȡ����Ӧ������һ���б����а����������ģ�id �ֱ�Ϊ -> [6, 5] ������ id 6 Ӧ�������� id 5 ֮ǰ����Ϊ������ 5 ֮���͵�
twitter.unfollow(1, 2);  // �û� 1 ȡ����ע���û� 2
twitter.getNewsFeed(1);  // �û� 1 ��ȡ����Ӧ������һ���б����а���һ�� id Ϊ 5 �����ġ���Ϊ�û� 1 �Ѿ����ٹ�ע�û� 2

��ʾ��
1 <= userId, followerId, followeeId <= 500
0 <= tweetId <= 10^4
�������ص� ID ��������ͬ
postTweet��getNewsFeed��follow �� unfollow ���������� 3 * 10^4 ��

*/

struct User {
	unordered_set<int> followee;
	list<int> tweet;
};

class Twitter {
private:
	int recentMax;
	int time;
	unordered_map<int, int> tweetTime;
	unordered_map<int, User> users;

public:
	Twitter() {
		time = 0;
		recentMax = 10;
	}

	void postTweet(int userId, int tweetId) {
		if (users[userId].tweet.size() == recentMax) {
			users[userId].tweet.pop_back();
		}
		users[userId].tweet.push_front(tweetId);
		tweetTime[tweetId] = ++time;
	}

	vector<int> getNewsFeed(int userId) {
		vector<int> res;
		for (int t : users[userId].tweet) {
			res.push_back(t);
		}
		for (int followeeId : users[userId].followee) {
			if (followeeId == userId) continue;
			vector<int> tmp;
			int i = 0;
			auto it = users[followeeId].tweet.begin();
			while (i < res.size() && it != users[followeeId].tweet.end()) {
				if (tweetTime[*it] > tweetTime[res[i]]) tmp.push_back(*it++);
				else tmp.push_back(res[i++]);
				if (tmp.size() == recentMax) break;
			}
			while (i < res.size() && tmp.size() < recentMax) {
				tmp.push_back(res[i++]);
			}
			while (it != users[followeeId].tweet.end() &&
				tmp.size() < recentMax) {
				tmp.push_back(*it++);
			}
			res.assign(tmp.begin(), tmp.end());
		}
		return res;
	}

	void follow(int followerId, int followeeId) {
		users[followerId].followee.insert(followeeId);
	}

	void unfollow(int followerId, int followeeId) {
		users[followerId].followee.erase(followeeId);
	}
};
