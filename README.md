# 电控第一次作业（STM32F103C8T6 最小系统板）

三道题做在同一个 CubeMX 工程里：

1. **GPIO**：PC13 推挽输出、低电平，点亮板载灯。
2. **定时器**：TIM2 更新中断周期 1 ms，回调里 `tick++` 并喂狗（`HAL_IWDG_Refresh`）。
3. **看门狗**：去掉回调里的喂狗，芯片约 2 s 复位，`tick` 涨到约 2000 后归零。

## 目录结构

| 路径 | 说明 |
| --- | --- |
| `Core/` `Drivers/` `cmake/` `startup_*.s` `*.ld` | CubeMX 生成，一般不改动 |
| `Tasks/` | **业务代码只写在这里**（`Tasks/inc`、`Tasks/src`） |
| `CMakeLists.txt` | 老师发放的模板（`user_folders "Tasks"`） |
| `docs/说明文档.md` | 说明文档（含计算过程、附录） |
| `ec_hw1.ioc` | CubeMX 工程配置 |

## 编译

```shell
cmake --preset Debug
cmake --build --preset Debug
```

生成的固件：`build/ec_hw1.elf`（另有 `build/Debug/ec_hw1.hex` / `.bin`）。

## 题目 2 / 题目 3 的切换

`Tasks/src/task.c` 里的宏：

```c
#define FEED_WATCHDOG 1   // 1 = 定时器题（喂狗）；0 = 看门狗题（不喂狗）
```

改成 0 重新编译下载，即为看门狗题。

## 用 Ozone 调试

1. 用 Ozone 打开 `build/ec_hw1.elf`。
2. 在 `Watched Data` 窗口里加入全局变量 `tick`。
3. 右键 `tick` → `Graph`（或 `Data Sampling` + `Timeline`）看曲线。
4. 程序保持运行，不要停在断点上。
