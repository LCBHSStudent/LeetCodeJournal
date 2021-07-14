//
// Created by sword on 2021/7/12.
//

#ifndef LEETCODE_SOLUTION_07_12_HPP
#define LEETCODE_SOLUTION_07_12_HPP

#include "stdc++.h"

class TimeMap {
    unordered_map<string, vector<pair<string, int>>> m_data;
public:
    /** Initialize your data structure here. */
    TimeMap() = default;

    void set(const string& key, const string& value, int timestamp) {
        m_data[key].emplace_back(value, timestamp);
    }

    string get(const string& key, int timestamp) {
        auto& dataVec = m_data[key];
        auto size = static_cast<int>(dataVec.size());

        for (int i = size - 1; i >= 0; i--) {
            auto& value = dataVec[i];

            if (value.second <= timestamp) {
                return value.first;
            }
        }

        return "";
    }
};

class Solution_1833 {
public:
    int maxIceCream(vector<int>& costs, int coins) {
        std::sort(costs.begin(), costs.end(), std::less<>());
        auto size = static_cast<int>(costs.size());

        int sum = 0;

        for (int i = 0; i < size; i++) {
            sum += costs[i];
            if (sum > coins) {
                return i;
            } else if (sum == coins) {
                return i + 1;
            }
        }

        return 0;
    }
};

class Solution_1014 {
public:
    int maxScoreSightseeingPair(vector<int>& values) {
        auto size = static_cast<int>(values.size());

        int result = INT_MIN;
        int maxLVal = values[0];

        for (int i = 1; i < size; i++) {
            result = std::max(maxLVal - i + values[i] , result);
            maxLVal = std::max(maxLVal, values[i] + i);
        }

        return result;
    }
};

class Solution_121 {
public:
    int maxProfit(vector<int>& prices) {
        auto size = static_cast<int>(prices.size());

        int minLVal = prices[0];
        int result = INT_MIN;

        for (int i = 1; i < size; i++) {
            result = std::max(prices[i] - minLVal, result);
            minLVal = std::min(minLVal, prices[i]);
        }

        return result > 0? result: 0;
    }
};

class Solution_122 {
public:
    int maxProfit(vector<int>& prices) {
        int ans = 0;
        int n = prices.size();
        for (int i = 1; i < n; ++i) {
            ans += max(0, prices[i] - prices[i - 1]);
        }
        return ans;
    }
};

class Solution_518 {
public:
    int change(int amount, vector<int>& coins) {
        std::vector<int> dp(amount + 1, 0);
        dp[0] = 1;

        for (auto& coin: coins) {
            for (int i = coin; i <= amount; i++) {
                dp[i] += dp[i - coin];
            }
        }

        return dp[amount];
    }
};

#endif //LEETCODE_SOLUTION_07_12_HPP
