# C++ 综合练习

需要 C++17 编译器和 CMake：

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
ctest --test-dir build --output-on-failure
./build/thread_pool
```

- `lru_cache.cpp`：用链表和哈希表实现 LRU，练习迭代器、`splice`、异常回滚与 `optional`。示例包含淘汰、更新和零容量检查；缓存没有做线程同步。
- `dijkstra.cpp`：优先队列求非负权图的最短路径，保存前驱并还原路径。演示不可达节点和输入检查。
- `thread_pool.cpp`：固定数量的工作线程、任务队列和 `future`；析构时等待已提交任务完成。任务应避免在同一线程池中同步等待其他任务，以免线程全部被占满。

使用 Debug 构建可以保留示例中的 `assert` 检查。
