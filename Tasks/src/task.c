/*
 * 电控第一次作业 —— 业务代码
 *
 * 三道题都在这一个文件里：
 *   题目 1  GPIO  : PC13 输出低电平，点亮板载灯
 *   题目 2  定时器: TIM2 更新中断周期 1ms，回调里 tick++ 并喂狗
 *   题目 3  看门狗: 回调里去掉喂狗，芯片约 2s 复位，tick 涨到约 2000 归零
 *
 * 题目 2 和题目 3 只差一个宏：把 FEED_WATCHDOG 改成 0 重新编译下载，
 * 就是看门狗题（不喂狗）。
 */

#include "task.h"
#include "main.h"

/* 1 = 定时器题（回调里喂狗）；0 = 看门狗题（不喂狗） */
#define FEED_WATCHDOG 1

/* ---- 题目 2：全局毫秒计数器，供 Ozone 实时观察 ---- */
volatile uint32_t tick = 0;

/* CubeMX 在 main.c 里生成的外设句柄 */
extern TIM_HandleTypeDef  htim2;
extern IWDG_HandleTypeDef hiwdg;

/* ------------------------------------------------------------------ */
/* 业务初始化                                                          */
/* ------------------------------------------------------------------ */
void Task_Init(void)
{
    /* 题目 1：把 PC13 拉低 -> 板载灯点亮（低电平点亮） */
    HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);

    /* 题目 2/3：启动 TIM2 的更新中断，回调每 1ms 触发一次 */
    HAL_TIM_Base_Start_IT(&htim2);
}

/* ------------------------------------------------------------------ */
/* 定时器更新中断回调                                                  */
/* 整个工程只定义这一份（CubeMX 没有生成同名函数）。                  */
/* 用 C 写，不需要 extern "C"。                                        */
/* ------------------------------------------------------------------ */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM2)
    {
        tick++;                     /* 每 1ms 加 1，1 秒约 +1000 */

#if FEED_WATCHDOG
        HAL_IWDG_Refresh(&hiwdg);   /* 题目 2：喂狗 */
#endif
    }
}
