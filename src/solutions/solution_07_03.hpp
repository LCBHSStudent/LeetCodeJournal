//
// Created by sword on 2021/7/3.
//

#ifndef LEETCODE_SOLUTION_07_03_HPP
#define LEETCODE_SOLUTION_07_03_HPP

#include <string>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <unordered_map>
#include <bitset>

using std::string;
using std::vector;

class Solution_451 {
public:
    static string frequencySort(const string& s) {
        struct Combo {
            char ch = '\0';
            int cnt = 0;
        };
        Combo combos[256] = {};

        for (auto& ch: s) {
            combos[ch].ch = ch;
            combos[ch].cnt++;
        }

        std::sort(combos, combos + 256, [](const Combo& lhs, const Combo& rhs) {
            return lhs.cnt > rhs.cnt;
        });

        string result;
        for (auto& combo : combos) {
            if (combo.cnt == 0) {
                break;
            }
            while (combo.cnt > 0) {
                result += combo.ch;
                combo.cnt--;
            }
        }


        return result;
    }
};


class Solution_001 {
public:
    static vector<int> twoSum(vector<int>& nums, int target) {
        std::unordered_map<int, int> pool;
        for(int i = 0; i < nums.size(); i++) {
            if (pool.find(nums[i]) != pool.end()) {
                return {i, pool[nums[i]]};
            } else {
                pool[target - nums[i]] = i;
            }
        }
        return {};
    }
};


class Solution_048 {
public:
    static void rotate(vector<vector<int>>& matrix) {
        const auto size = matrix.size();

        // 水平反转
        for (int i = 0; i < size / 2; ++i) {
            for (int j = 0; j < size; ++j) {
                std::swap(matrix[i][j], matrix[size - i - 1][j]);
            }
        }

        // 左上右下对角线反转
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < i; ++j) {
                std::swap(matrix[i][j], matrix[j][i]);
            }
        }
    }
};

class Solution_645 {
public:
    static vector<int> findErrorNums(const vector<int>& nums) {
        auto size = nums.size();
        
        std::unordered_map<int, int> hash;
        int duplicatedNum = 0;
        int lostNum = 0;
        
        for (auto num: nums) {
            hash[num] += 1;
        }
        for (int i = 1; i <= size; i++) {
            int count = hash[i];
            if (count == 2) {
                duplicatedNum = i;
            } else if (count == 0) {
                lostNum = i;
            }
        }
        return {duplicatedNum, lostNum};
    }
};

#endif //LEETCODE_SOLUTION_07_03_HPP
