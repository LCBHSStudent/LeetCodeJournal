> 本飞舞做力扣还是习惯用本地IDE，对某些过长的输入数据在本地复现起来太麻烦了，所以写了个初步的小工具来支持一些类型的leetcode式输入串解析...

@[toc](目录)

## 目录结构

```bash
├───bin				   # 运行环境
├───include			    # 一些小工具，如输入解析器，头文件引用等
└───src				   # 源文件
    └───solutions		# xx月xx日的Solution
```

## 输入解析器

### 扔到.hpp中开盒即用，需要C++20
`对有无符号类型的处理、浮点类型的处理尚不全面，待补充`
```cpp
/**------------------------------------------------------------------------------
 * @brief LeetCode 输入解析器
 * @author DFW
 * @date 2021-07-06
 * @example auto input = InputParser<std::string>().getVecInVec("./1418_53.ipt");
 * -------------------------------------------------------------------------------
 */

#include <fstream>
#include <sstream>
#include <type_traits>

template<typename T>
concept IsInteger = std::is_integral_v<T>;

template<typename T>
class InputParser {
public:
    InputParser() = default;
    InputParser(char _lRegionSym, char _rRegionSym, char _splitter)
            : lRegionSym(_lRegionSym)
            , rRegionSym(_rRegionSym)
            , splitter(_splitter) {}

    template<typename DataType = T>
    DataType parseData(const std::string& file, int& index) {
        static_assert(false, "Unsupportable data type to extract.");
    }

    template<>
    T parseData<T>(const std::string& file, int& index) requires IsInteger<T> {
        char* pStart = const_cast<char*>(file.data()) + index;
        char* pEnd = pStart;

        static constexpr auto getVal = [](char* _p1, char** _p2) -> T {
            switch(sizeof(T)) {
            case 2:
                return static_cast<unsigned char> (strtol(_p1, _p2, 10));
            case 4:
                return strtol(_p1, _p2, 10);
            case 8:
                return strtoll(_p1, _p2, 10);
            default:
                return strtol(_p1, _p2, 10);
            }
        };

        auto val = getVal(pStart, &pEnd);
        index += static_cast<int>(pEnd - pStart) - 1;

        return val;
    }

    template<>
    std::string parseData<std::string>(const std::string& file, int& index) {
        while(file[index] == '\"') {
            index++;
        }
        int backupIdx = index;

        for (index; index < file.size(); index++) {
            if (file[index] == '\"') {
                break;
            }
        }

        return file.substr(backupIdx, index - backupIdx);
    }


    std::vector<T> getVec(const char* inputPath) {
        std::vector<T> data;
        auto&& file = readFile2Str(inputPath);

        int depth = 0;
        for (int i = 0; i < file.size(); i++) {
            if (file[i] == lRegionSym) {
                if (depth >= 1) {
                    break;
                } else {
                    depth = 1;
                }
                continue;
            } else if (file[i] == rRegionSym) {
                depth--;
                if (depth == 0) {
                    break;
                }
            } else if (file[i] == splitter) {
                continue;
            } else {
                auto val = parseData<T>(file, i);
                data.emplace_back(val);
            }
        }

        return data;
    }

    std::vector<std::vector<T>> getVecInVec(const char* inputPath) {
        std::vector<std::vector<T>> data;
        auto&& file = readFile2Str(inputPath);

        int depth = 0;

        std::vector<T> row = {};
        for (int i = 0; i < file.size(); i++) {
            if (file[i] == lRegionSym) {
                if (depth >= 1) {
                    depth++;
                    row.clear();
                } else {
                    depth = 1;
                }
                continue;
            } else if (file[i] == rRegionSym) {
                depth--;
                if (depth == 0) {
                    break;
                } else {
                    data.emplace_back(row);
                    continue;
                }
            } else if (file[i] == splitter) {
                continue;
            } else {
                auto val = parseData<T>(file, i);
                row.emplace_back(val);
            }
        }
        return data;
    }

protected:
    std::string readFile2Str(const char* inputPath) {
        std::ifstream fin(inputPath);
        if (!fin.is_open()) {
            throw std::runtime_error(
                    string("failed to open local file at: ") + inputPath
            );
        }

        std::ostringstream tmp;
        tmp << fin.rdbuf();

        // fin.close();

        return tmp.str();
    }

private:
    char lRegionSym = '[', rRegionSym = ']', splitter = ',';
};

```
###  示例
main.cpp
```cpp
#include "solutions/solution_07_06.hpp"
#include "utils.hpp"

#include <iostream>

using namespace std;
int main(int argc, char* argv[]) {
    auto input = InputParser<std::string>().getVecInVec("./1418_53.ipt");

    for (auto& row: Solution_1418().displayTable(input)) {
        cout << row << endl;
    }
    return 0;
}
```
## 实现ostream友元来直接输出支持数据类型的单层vector
```cpp
template <typename T>
std::ostream& operator<< (std::ostream& out, const std::vector<T>& v) {
    if (!v.empty()) {
        out << '[';
        std::copy(v.begin(), v.end(), std::ostream_iterator<T>(out, ", "));
        out << "\b\b]";
    }
    return out;
}
```