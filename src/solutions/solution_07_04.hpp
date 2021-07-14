//
// Created by sword on 2021/7/4.
//

#ifndef LEETCODE_SOLUTION_07_04_HPP
#define LEETCODE_SOLUTION_07_04_HPP

#include <array>
#include <vector>
#include <stack>
#include <bitset>

template<typename V, V val>
requires requires(V v) {
    v = v;
}
struct Value {
    static constexpr V value = val;
};

template<int n>
struct tib {
    inline static int val = tib<n - 1>::val + tib<n - 2>::val + tib<n - 3>::val;
};

template<>
struct tib<0> {
    inline static int val = 0;
};

template<>
struct tib<1> {
    inline static int val = 1;
};

template<>
struct tib<2> {
    inline static int val = 1;
};

class Solution_509 {
public:
    int fib(int n) {
        int ridx = 2, lidx = 0, midx = 1;
        std::array<int, 3> space = {0, 1, 1};
        if (n <= 2) {
            return space[n];
        }
        for (int i = 0; i < n - 2; i++) {
            ridx = (ridx + 1) % 3;
            lidx = (lidx + 1) % 3;
            midx = (midx + 1) % 3;
            space[ridx] = space[midx] + space[lidx];
        }
        return space[ridx];
    }
};

namespace Solution_offer_09 {
    class CQueue {
        std::stack<int> m_stackA = {}, m_stackB = {};
    public:
        CQueue() = default;
        // 入队
        void appendTail(int value) {
            m_stackA.push(value);
        }
        // 出队
        int deleteHead() {
            if (m_stackA.empty()) {
                return -1;
            }

            while (m_stackA.size() > 1) {
                m_stackB.push(m_stackA.top());
                m_stackA.pop();
            }
            auto head = m_stackA.top();
            m_stackA.pop();

            while (!m_stackB.empty()) {
                m_stackA.push(m_stackB.top());
                m_stackB.pop();
            }
            return head;
        }
    };
};

namespace Solution_offer_10 {
    class Solution {
    public:
        static int fib(int n) {
            int ridx = 2, lidx = 0, midx = 1;
            std::array<int, 3> space = {0, 1, 1};
            if (n <= 2) {
                return space[n];
            }
            for (int i = 0; i < n - 2; i++) {
                ridx = (ridx + 1) % 3;
                lidx = (lidx + 1) % 3;
                midx = (midx + 1) % 3;
                space[ridx] = (space[midx] + space[lidx]) % 1000000007;
            }
            return space[ridx];
        }
    };
};

namespace Solution_offer_03 {
class Solution {
    std::bitset<100000> m_appear = {};
    std::bitset<100000> m_duplicated = {};
public:
    int findRepeatNumber(const std::vector<int>& nums) {
        for (auto num: nums) {
            if (m_appear.test(num)) {
                m_duplicated.set(num);
            } else {
                m_appear.set(num);
            }
        }

        for (auto i = 0; i < nums.size(); i++) {
            if (m_duplicated.test(i)) {
                return i;
            }
        }
        return -1;
    }
};
};

#endif //LEETCODE_SOLUTION_07_04_HPP
