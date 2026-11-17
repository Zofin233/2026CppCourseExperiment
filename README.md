# 2026CppCourseExperiment

ADAS Executor 课程实验，提交目录为 `2025080911014_刘昊坤/`。

## 实验目录

- `实验1-高质量编程基础/`：初始化、查询、M/L/R 与批量指令。
- `实验2-面向对象编程/`：命令继承体系与 F 加速状态。
- `实验3-1-面向对象编程/`：状态抽离、方向抽象与表驱动。
- `实验3-2-面向函数式编程/`：函数对象、B 倒车及 B+F 组合。
- `综合实验/`：原子动作编排、TR 掉头及 Normal/Sport/Bus 车辆类型。

各阶段均包含独立的 `include/`、`src/`、`tests/`、CMake 配置和 `代码说明.txt`。

## 构建与测试

需要 C++17、CMake 3.12 及以上版本，以及课程提供的 GoogleTest。将 GoogleTest 源码放在对应实验的 `tests/googletest/`，或通过 CMake GTest 包提供 `GTest::gtest_main`。

以综合实验为例：

```bash
cd "2025080911014_刘昊坤/综合实验"
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

其他实验使用相同命令，只需替换目录名。第三方测试框架和构建产物不纳入版本控制。
