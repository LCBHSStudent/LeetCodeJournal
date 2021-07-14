//
// Created by sword on 2021/7/13.
//

#ifndef LEETCODE_SOLUTION_07_13_HPP
#define LEETCODE_SOLUTION_07_13_HPP

#include <utility>
#include "stdc++.h"

class Solution_218 {
public:
    vector<vector<int>> getSkyline(vector<vector<int>>& buildings) {
        vector<vector<int>> result = {};
        vector<array<int, 2>> bounds;
        using itemType = decltype(bounds)::value_type;

        for (const auto& building: buildings) {
            bounds.push_back({building[0], -building[2]});
            bounds.push_back({building[1], building[2]});
        }

        auto cmp = [](const itemType& a, const itemType& b) -> bool {
            if (a[0] == b[0]) {
                if (a[1] < 0 && b[1] >= 0) {
                    return true;
                } else if (a[1] >= 0 && b[1] < 0) {
                    return false;
                } else {
                    return a[1] < b[1];
                }
            }
            return a[0] < b[0];
        };
        std::sort(bounds.begin(), bounds.end(), cmp);

        multiset<int> heights;
        int prevHeight = -1;
        int prevPos = -1;

        for (const auto& bound: bounds) {
            if (bound[1] < 0) {
                heights.insert(-bound[1]);
            } else {
                heights.erase(heights.find(bound[1]));
            }

            int maxHeight = 0;
            if (!heights.empty()) {
                maxHeight = *heights.rbegin();
            }

            if (prevHeight != maxHeight) {
                prevHeight = maxHeight;
                result.push_back({bound[0], maxHeight});
            }
        }

        return result;
    }
};

class Solution_309 {
public:
    int maxProfit(vector<int>& prices) {
        auto size = static_cast<int>(prices.size());

        vector<array<int, 3>> dp(size, {0, 0, 0});
        dp[0][1] = -prices[0];

        for (int i = 1; i < size; i++) {
            dp[i][0] = std::max(dp[i - 1][2], dp[i - 1][0]);
            dp[i][1] = std::max(dp[i - 1][1], dp[i - 1][2] - prices[i]);
            dp[i][2] = dp[i - 1][1] + prices[i];
        }

        return std::max(dp[size - 1][0], dp[size - 1][2]);
    }
};

class Solution_714 {
public:
    int maxProfit(vector<int>& prices, int fee) {
        auto size = static_cast<int>(prices.size());
        vector<array<int, 2>> dp(size, {0, 0});

        dp[0][1] = -prices[0] - fee;

        for (int i = 1; i < size; i++) {
            dp[i][0] = std::max(dp[i - 1][0], dp[i - 1][1] + prices[i]);
            dp[i][1] = std::max(dp[i - 1][0] - prices[i] - fee, dp[i - 1][1]);
        }

        return dp[size - 1][0];
    }
};

class Solution_139 {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        auto size = static_cast<int>(s.size());

        set<string_view> dict = {};

        auto judge = [&dict, &s](int index, int length) -> bool {
            return dict.find(string_view(s.c_str() + index, length)) != dict.end();
        };

        vector<bool> dp(size + 1, false);

        int maxStrLength = -1;
        for (const auto& str: wordDict) {
            maxStrLength = std::max((int)str.size(), maxStrLength);
            dict.insert(string_view(str.c_str(), str.size()));
        }

        dp[0] = true;

        // 从长度1遍历到长度size
        for (int i = 1; i <= size; i++) {
            // 导回去，j还是下标，向前移动了maxStrLength个长度
            for (int j = std::max(i - maxStrLength, 0); j < i; j++) {
                if (dp[j] && judge(j, i - j)) {
                    dp[i] = true;
                    break;
                }
            }
        }

        return dp[size];
    }
};

#endif //LEETCODE_SOLUTION_07_13_HPP
