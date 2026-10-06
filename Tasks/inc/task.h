#ifndef TASKS_TASK_H
#define TASKS_TASK_H

#include <stdint.h>

/*
 * 电控第一次作业 —— 业务代码接口
 *
 * tick : 全局毫秒计数器。定时器每 1ms 中断一次，在回调里 +1。
 *        必须是全局的 volatile uint32_t，名字必须是 tick，
 *        这样用 Ozone 调试时才能在变量窗口里看到它并画出曲线。
 */
extern volatile uint32_t tick;

/* 业务初始化：点亮板载灯 + 启动 1ms 定时中断 */
void Task_Init(void);

#endif /* TASKS_TASK_H */
