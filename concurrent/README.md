改造思路：

创建信号量。
```cpp
HANDLE s = CreateSemaphore(NULL, 1, 1, NULL);
```

对两个进程的临界区添加PV操作。
```cpp
WaitForSingleObject(s, INFINITE);
// ... 临界区
ReleaseSemaphore(s, 1, NULL);
```

从而使得两个进程是互斥访问count，输出结果为4，经测试，在添加Sleep()的情况下，依然能输出为4，验证其确实是互斥访问。