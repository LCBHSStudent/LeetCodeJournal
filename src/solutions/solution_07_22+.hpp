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

class Solution_1713 {
public:
    int minOperations(vector<int>& target, vector<int>& arr) {
        auto size = static_cast<int>(target.size());
        unordered_map<int, int> hash;
        for (int i = 0; i < size; ++i) {
            hash[target[i]] = i;
        }

        // 查找最长递增子序列
        vector<int> inc;
        for (auto& val: arr) {
            if (hash.count(val)) {
                int idx = hash[val];
                auto it = lower_bound(inc.begin(), inc.end(), idx);
                if (it != inc.end()) {
                    *it = idx;
                } else {
                    inc.push_back(idx);
                }
            }
        }
        return size - (int)inc.size();
    }
};

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution_671 {
public:
public:
    int findSecondMinimumValue(TreeNode* root) {
        int result = INT_MAX;
        bool flag = false;

        queue<TreeNode*> q;
        q.push(root);

        while (!q.empty()) {
            auto node = q.front();
            q.pop();

            if (node->val != root->val && node->val <= result) {
                result = node->val;
                flag = true;
            }
            // 如果左右子结点的值大于ans，就不用比较了，否则压入队列继续比较
            if (node->left && node->left->val <= result) {
                q.push(node->left);
            }
            if (node->right && node->right->val <= result) {
                q.push(node->right);
            }
        }

        return flag? result: -1;
    }
};

class Solution_863 {
public:
    vector<int> distanceK(TreeNode* root, TreeNode* target, int k) {
        vector<int> result;

        if (root == nullptr) {
            return {};
        }
        if (k == 0) {
            return {target->val};
        }
        int distance = k;

        // find距离为k的子节点
        dfs(target, result, 0, distance);


        if (root != target){
            // 倒转二叉树
            {
                target->left = nullptr;
                target->right = nullptr;
                reverseTree(root, target);
            }

            // 再次find距离为k的子节点
            dfs(target, result, 0, distance);
        }
        return result;
    }

    // 回溯 放置父节点到子节点
    bool reverseTree(TreeNode* root, TreeNode* target){
        if (root == nullptr) {
            return false;
        }
        if (root == target) {
            return true;
        }

        if (reverseTree(root->left, target)){
            if(!root->left->left){
                root->left->left = root;
            }else if(!root->left->right){
                root->left->right = root;
            }
            root->left = nullptr;
            return true;
        }

        if (reverseTree(root->right, target)){
            if (!root->right->left) {
                root->right->left = root;
            } else if (!root->right->right) {
                root->right->right = root;
            }
            root->right = nullptr;
            return true;
        }
        return false;
    }

    void dfs(TreeNode* root, vector<int>& result, int step, int distance){
        if(!root) return;
        if(step == distance){
            result.push_back(root->val);
        }
        dfs(root->left, result, step+1, distance);
        dfs(root->right, result, step+1, distance);
    }

};

#endif //LEETCODE_SOLUTION_07_22_HPP
