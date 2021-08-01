//
// Created by sword on 2021/8/1.
//

#ifndef LEETCODE_SOLUTION_08_01_HPP
#define LEETCODE_SOLUTION_08_01_HPP

#include "stdc++.h"

class Solution_1337 {
public:
    vector<int> kWeakestRows(vector<vector<int>>& mat, int k) {
        auto size = static_cast<int> (mat.size());

        vector<int> result = {};

        static auto getSum = [](const vector<int>& vec) -> int {
            int count = 0;
            for (const auto& it: vec) {
                if (it == 0) {
                    break;
                } else {
                    count++;
                }
            }

            return count;
        };

        auto cmp = [&mat](int a, int b) -> bool {
            auto sumA = getSum(mat[a]);
            auto sumB = getSum(mat[b]);

            if (sumA == sumB) {
                return a > b;
            } else {
                return sumA > sumB;
            }
        };

        priority_queue<int, std::vector<int>, decltype(cmp)> heap(cmp);

        for (int i = 0; i < size; i++) {
            heap.push(i);
        }

        for (int i = 0; i < k; i++) {
            result.emplace_back(heap.top());
            heap.pop();
        }

        return result;
    }
};

#endif //LEETCODE_SOLUTION_08_01_HPP
