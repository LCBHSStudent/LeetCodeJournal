//
// Created by sword on 2021/7/6.
//

#ifndef LEETCODE_SOLUTION_07_06_HPP
#define LEETCODE_SOLUTION_07_06_HPP

#include "stdc++.h"

class Solution_1418 {
public:
    vector<vector<string>> displayTable(vector<vector<string>>& orders) {
        vector<vector<string>> table = {{}};

        array<unordered_map<string, int>, 500> space = {};

        set<string, std::less<>> dishesSet;

        for (auto& order: orders) {
            dishesSet.insert(order[2]);

            auto& targetMap = space[atoi(order[1].c_str()) - 1];
            auto iter = targetMap.find(order[2]);
            if (iter != targetMap.end()) {
                iter->second++;
            } else {
                targetMap.insert(pair<string, int>(order[2], 1));
            }
        }
        table[0].emplace_back("Table");
        for (const auto& it: dishesSet) {
            table[0].emplace_back(it);
        }
        for (int i = 0; i < space.size(); i++) {
            auto& tableData = space[i];
            if (!tableData.empty()) {
                vector<string> row;

                row.emplace_back(to_string(i + 1));
                for (const auto& it: dishesSet) {
                    auto dishLog = tableData.find(it);
                    if (dishLog != tableData.end()) {
                        row.emplace_back(to_string(dishLog->second));
                    } else {
                        row.emplace_back("0");
                    }
                }

                table.emplace_back(row);
            }
        }

        return table;
    }
};

class Solution_198 {
public:
    int rob(vector<int>& nums) {
        auto size = nums.size();
        switch(size) {
        case 0:
            return 0;
        case 1:
            return nums[0];
        case 2:
            return std::max(nums[0], nums[1]);
        default:
            break;
        }


        vector<int> dp(size, 0);
        dp[0] = nums[0];
        dp[1] = std::max(nums[0], nums[1]);

        for (int i = 2; i < size; i++) {
            dp[i] =  std::max(dp[i - 1], dp[i - 2] + nums[i]);
        }

        return dp[size - 1];
    }
};

class Solution_213 {
    // 心得：当情况实在不好于一次遍历中区分时，试试分类讨论
public:
    int rob(vector<int>& nums) {
        auto size = nums.size();

        switch(size) {
        case 0:
            return 0;
        case 1:
            return nums[0];
        case 2:
            return std::max(nums[0], nums[1]);
        default:
            break;
        }


        int situation1 = 0;
        int situation2 = 0;

        vector<int> dp(size, 0);
        dp[0] = nums[0];
        dp[1] = std::max(nums[0], nums[1]);

        for (int i = 2; i < size; i++) {
            dp[i] =  std::max(dp[i - 1], dp[i - 2] + nums[i]);
        }
        situation1 = dp[size - 2];


        dp[1] = nums[1];
        dp[2] = std::max(nums[1], nums[2]);
        for (int i = 3; i < size; i++) {
            dp[i] =  std::max(dp[i - 1], dp[i - 2] + nums[i]);
        }
        situation2 = dp[size - 1];

        return std::max(situation1, situation2);
    }
};

class Solution_740 {
public:
    int deleteAndEarn(vector<int>& nums) {
        auto size = nums.size();

        map<int, int, std::less<>> numMap;
        for (int i = 0; i < size; i++) {
            if (numMap.find(nums[i]) == numMap.end()) {
                numMap.insert(pair<int, int>(nums[i], 1));
            } else {
                numMap[nums[i]]++;
            }
        }
        vector<int> newNums;

        int index = 0;
        int prevNum = 0;

        for (const auto& num: numMap) {
            if (index > 0) {
                if (num.first != prevNum + 1) {
                    newNums.push_back(0);
                }
            }
            newNums.push_back(num.second * num.first);

            index++;
            prevNum = num.first;
        }

        size = newNums.size();
        switch(size) {
        case 0:
            return 0;
        case 1:
            return newNums[0];
        default:
            break;
        }

        vector<int> dp(size, 0);
        dp[0] = newNums[0];
        dp[1] = std::max(newNums[1], newNums[0]);

        for (int i = 2; i < size; i++) {
            dp[i] = std::max(dp[i - 2] + newNums[i], dp[i - 1]);
        }

        return dp[dp.size() - 1];
    }
};

#endif //LEETCODE_SOLUTION_07_06_HPP
