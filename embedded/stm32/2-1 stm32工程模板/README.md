# STM32F103C8 工程模板 · 第 2-1 课

来源：`E:\stm32_project\2-1 stm32工程模板`。工程使用 Keil uVision 和 STM32F10x 标准外设库（源码标注 V3.5.0），并保留原有 `User`、`start`、`Library` 目录结构。

`User/main.c` 开启 GPIOC 时钟，将 PC13 配置为 50 MHz 推挽输出并置高，然后进入空循环。工程配置 `project.uvprojx` 指向 STM32F103C8。

归档保留工程配置、用户源码、启动文件及库源码；Keil 用户界面/调试选项、调试器配置、`Objects`、`Listings` 和构建日志未纳入。库文件保留各自原有的版权与说明头。

本次只做文件归档与哈希核对，未编译、烧录或连接硬件验证。
