//
// Created by sword on 2021/7/17.
//

#ifndef LEETCODE_SOLUTION_07_17_HPP
#define LEETCODE_SOLUTION_07_17_HPP

#include "stdc++.h"

namespace offer {

class Solution_42 {
public:
    int maxSubArray(vector<int>& nums) {
        int size = static_cast<int>(nums.size());
        if (size == 0) {
            return 0;
        }
        int dp = nums[0];
        int max = dp;

        for (int i = 1; i < size; i++) {
            dp = std::max(dp + nums[i], nums[i]);
            if (dp > max) {
                max = dp;
            }
        }

        return max;
    }
};

};

class Foo {
    mutex               mux {};         // 实现条件变量判断互斥所需要的锁
    condition_variable  phase2 {};      // 定义第二阶段结束条件
    condition_variable  phase3 {};      // 定义第三阶段结束条件

    bool                m_phase2Ok = false;
    bool                m_phase3Ok = false;

public:
    Foo() = default;

    void first(const function<void()>& printFirst) {
        printFirst();					// 输出first

        m_phase2Ok = true;              // 设置标记位
        phase2.notify_one();			// 标记条件阶段二运行 (输出second)
    }

    void second(const function<void()>& printSecond) {
        unique_lock<mutex> lock(mux);
        phase2.wait(lock, [this]() {return m_phase2Ok;});				// 等待阶段二开始运行

        printSecond();

        m_phase2Ok = false;
        m_phase3Ok = true;
        phase3.notify_one();			// 阶段二结束，标记条件阶段二运行	(输出third)
    }

    void third(const function<void()>& printThird) {
        unique_lock<mutex> lock(mux);
        phase3.wait(lock, [this]() {return m_phase3Ok;});				// 等待阶段三开始运行

        printThird();
        m_phase3Ok = false;
    }

    template<class F>
    static void TestFoo(F& foo) {
        thread t3(&F::third, std::addressof(foo), []{printf("third");});
        thread t2(&F::second, std::addressof(foo), []{printf("second");});
        thread t1(&F::first, std::addressof(foo), []{printf("first");});

        t2.detach();
        t1.detach();
        t3.join();
    }
};

#endif //LEETCODE_SOLUTION_07_17_HPP
