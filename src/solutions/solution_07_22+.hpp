//
// Created by sword on 2021/7/22.
//

#ifndef LEETCODE_SOLUTION_07_22_HPP
#define LEETCODE_SOLUTION_07_22_HPP

#include "stdc++.h"

class Node {
public:
    int val;
    Node* next;
    Node* random;

    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};

class solution_138 {
public:
    Node* copyRandomList(Node* head) {
        if (!head) {
            return nullptr;
        }
        // 复制节点
        auto ptr = head;
        while (nullptr != ptr) {
            auto newNode = new Node(ptr->val);
            newNode->next = ptr->next;
            ptr->next = newNode;

            // 移动到下一个原节点
            ptr = newNode->next;
        }
        auto newHead = head->next;

        // 利用random指针的下一个节点就是新节点进行拷贝
        ptr = head;
        while (ptr) {
            auto newNode = ptr->next;
            if (ptr->random) {
                newNode->random = ptr->random->next;
            }
            ptr = newNode->next;
        }

        // 分离二链表
        ptr = head;
        while (nullptr != ptr->next) {
            auto nxt = ptr->next;
            ptr->next = nxt->next;
            ptr = nxt;
        }

        return newHead;
    }
};

class Solution_1893 {
    static constexpr int scope = 50;
public:
    bool isCovered(vector<vector<int>>& ranges, int left, int right) {
        bool result = true;

        array<bool, scope + 1> included = { false };

        for(auto& range: ranges) {
            std::fill(included.begin() + range[0], included.begin() + range[1] + 1, true);
        }

        for (int i = left; i <= right; i++) {
            if (!included[i]) {
                return false;
            }
        }

        return result;
    }
};

class Solution_1736 {
public:
    string maximumTime(string& time) {
        if (time[0] == '?') {
            if (time[1] >= '4' && time[1] <= '9') {
                time[0] = '1';
            } else {
                time[0] = '2';
            }
        }

        if (time[1] == '?') {
            if (time[0] == '2') {
                time[1] = '3';
            } else {
                time[1] = '9';
            }
        }

        if (time[3] == '?') {
            time[3] = '5';
        }

        if (time[4] == '?') {
            time[4] = '9';
        }

        return time;
    }
};

class Solution_1743 {
public:
    vector<int> restoreArray(vector<vector<int>>& adjacentPairs) {
        unordered_map<int, vector<int>> map;
        for (auto& pair: adjacentPairs) {
            map[pair[0]].push_back(pair[1]);
            map[pair[1]].push_back(pair[0]);
        }

        int size = static_cast<int>(adjacentPairs.size()) + 1;
        vector<int> res(size, 0);

        for (auto& iter: map) {
            if (iter.second.size() == 1) {
                res[0] = iter.first;
                break;
            }
        }

        res[1] = map[res[0]][0];
        for (int i = 2; i < size; i++) {
            vector<int> adj = map[res[i-1]];
            // 根据相邻判断是否重复
            res[i] = adj[0] == res[i-2] ? adj[1] : adj[0];
        }

        return res;
    }
};

class Solution_387 {
public:
    int firstUniqChar(string s) {
        vector<int> hash(26, 0);
        for(auto& c: s) {
            hash[c - 'a']++;
        }
        for(int i = 0; i < s.size(); i++) {
            if(hash[s[i] - 'a'] == 1)
                return i;
        }
        return -1;
    }
};

#endif //LEETCODE_SOLUTION_07_22_HPP
