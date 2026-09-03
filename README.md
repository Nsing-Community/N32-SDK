**简体中文** | [English](#english)

# N32G45x-SDK

> [!NOTE]
> 固件库（`firmware/`）与中间件（`middlewares/`）均已直接纳入仓库，`git clone` 后即可使用，详见 [如何使用](#如何使用)。

## 概述

**N32G45x-SDK** 是 Nsing（国民技术）N32G45x 系列微控制器的固件开发套件（Software Development Kit），由 Nsing-Community 社区维护，为 N32G45x 系列 MCU 应用开发提供完整、统一的嵌入式软件平台，主要包括：

- **CMSIS 组件**（core + device）：适配 N32G45x 内置 ARM® Cortex®-M4F 内核，包含器件头文件、系统初始化、启动文件与链接脚本；
- **标准外设驱动库（Standard Peripheral Library）**：覆盖片上全部外设（ADC、USART、SPI、I2C、TIM、DMA、CAN、USB、ETH、DVP、QSPI、SDIO 等），API 风格统一、便于在系列内移植与复用；
- **安全算法库（预编译）**：AES / DES / HASH / RNG 等加密算法与 TSC 触摸按键算法；
- **USB 全速（FS）设备驱动**：USB 协议栈核心、枚举与传输处理；
- **中间件**：FreeRTOS、lwIP、RT-Thread 等开源组件；
- **完整示例工程**：面向 N32G45x_EVAL 评估板的外设驱动、应用与演示工程，分别提供 IAR EWARM / Keil MDK-ARM 工程，并附 GCC/Makefile 工程。

SDK 中每个示例工程都直接运行于 N32G45x 系列开发板上，可在 `projects/n32g45x_EVAL/examples/*外设*` 目录下找到对应的软件工程。

> [!IMPORTANT]
> ## 支持范围说明
>
> 本仓库面向 **N32G45x 系列**（N32G452 / N32G455 / N32G457 等型号，ARM Cortex-M4F 内核，最高主频 144 MHz）。

## 更新日志

固件库版本历史与更新内容见 [N32G45x Version History.txt](N32G45x%20Version%20History.txt)。

## 目录结构

```
N32G45x-SDK/
├── firmware/                         # 固件库
│   ├── CMSIS/                        # CMSIS core（ARM Cortex-M4F）
│   │   └── device/                   # 器件层：n32g45x.h、system 初始化、启动文件、链接脚本
│   ├── n32g45x_std_periph_driver/    # N32G45x 标准外设驱动库（inc/src）
│   ├── n32g45x_usbfs_driver/         # USB 全速设备驱动
│   └── n32g45x_algo_lib/             # 算法库（AES/DES/HASH/RNG 及 TSC 算法头文件 + 预编译 .lib）
├── middlewares/                      # 中间件（第三方开源，自带各自许可协议）
│   ├── FreeRTOSv202212.01/           # FreeRTOS 实时操作系统
│   ├── lwip-2.2.0/                   # lwIP 轻量级 TCP/IP 协议栈
│   └── rt-thread/                    # RT-Thread 实时操作系统
├── projects/
│   └── n32g45x_EVAL/                 # N32G45x_EVAL 评估板工程
│       ├── bsp/                      # 板级支持包（delay、log 等）
│       ├── applications/             # 应用层工程（GCC_demo，Makefile 构建）
│       └── examples/                 # 示例工程：
│                                     #   （每个示例均含 EWARM / MDK-ARM 工程与 readme.txt）
├── jlink/
│   └── flash.jlink                   # J-Link 烧录脚本（下载 build/output.hex）
├── .vscode/                          # VS Code 配置（任务/调试，配合 GCC 工具链）
└── N32G45x Version History.txt       # 版本历史与更新日志
```

## 如何使用

> 以下内容面向在本地使用本 SDK 的开发者。

1. **克隆仓库**（本仓库不含 submodule，直接克隆即可）

```bash
git clone https://github.com/Nsing-Community/N32-SDK.git
```

2. **获取最新更新**

```bash
git pull
```

3. **打开示例工程**（三种方式任选其一）

   - **Keil MDK-ARM**：直接打开示例目录下的 `MDK-ARM/*.uvprojx` 工程；
   - **IAR EWARM**：直接打开示例目录下的 `EWARM/*.eww` 工作空间；
   - **GCC + Makefile（命令行）**：进入 `projects/n32g45x_EVAL/applications/GCC_demo/GCC/`，使用 `arm-none-eabi-` 工具链执行 `make`（详见 VS Code 的 `.vscode/tasks.json` 任务配置）。

4. **烧录调试**：可使用 J-Link 运行 [jlink/flash.jlink](jlink/flash.jlink) 脚本将编译产物 `build/output.hex` 烧录至目标板，或直接在 IAR/Keil 中下载调试。

> [!TIP]
> 开始一个外设学习或移植时，建议先阅读目标示例的 `readme.txt`，其中说明了硬件连接、时钟/IO 配置与测试现象，再结合 `firmware/n32g45x_std_periph_driver/` 下的驱动源码使用。

## 许可证

本仓库固件代码遵循 BSD 风格开源许可（见各源文件头部版权声明）；`middlewares/` 目录下的第三方组件遵循其各自的开源许可证。

---
---

## <a name="english"></a>English

# N32G45x-SDK

> [!NOTE]
> The firmware (`firmware/`) and the middleware (`middlewares/`) are committed directly into this repository — a plain `git clone` is all you need. See [How to use](#how-to-use).

## Overview

**N32G45x-SDK** is the firmware software development kit (SDK) for the Nsing (Nations Technologies) N32G45x series microcontrollers, maintained by the Nsing-Community. It provides a complete and consistent embedded software platform for N32G45x series MCU application development, and mainly includes:

- **CMSIS components** (core & device): adapted to the ARM® Cortex®-M4F core embedded in the N32G45x, including the device header, system initialization, startup files and linker script;
- **Standard Peripheral Library**: covering all on-chip peripherals (ADC, USART, SPI, I2C, TIM, DMA, CAN, USB, ETH, DVP, QSPI, SDIO, etc.) with a uniform API style for easy porting and reuse across the series;
- **Algorithm library (prebuilt)**: AES / DES / HASH / RNG crypto algorithms and the TSC touch-key algorithm;
- **USB Full-Speed (FS) device driver**: USB protocol stack core, enumeration and transfer handling;
- **Middleware**: FreeRTOS, lwIP, RT-Thread and other open-source components;
- **Complete example projects**: peripheral, application and demonstration projects for the N32G45x_EVAL board, provided with IAR EWARM / Keil MDK-ARM projects plus a GCC/Makefile project.

Every example project in the SDK runs directly on the N32G45x series development boards. You can find the corresponding software projects under the `projects/n32g45x_EVAL/examples/*peripheral*` directories.

> [!IMPORTANT]
> ## Scope of this repository
>
> This repository targets the **N32G45x series** (N32G452 / N32G455 / N32G457 and other models, ARM Cortex-M4F core, up to 144 MHz).

## Changelog

The version history and release content of the firmware library can be found in [N32G45x Version History.txt](N32G45x%20Version%20History.txt).

## Repository structure

```
N32G45x-SDK/
├── firmware/                         # Firmware
│   ├── CMSIS/                        # CMSIS core (ARM Cortex-M4F)
│   │   └── device/                   # Device layer: n32g45x.h, system init, startup files, linker script
│   ├── n32g45x_std_periph_driver/    # N32G45x Standard Peripheral Library (inc/src)
│   ├── n32g45x_usbfs_driver/         # USB Full-Speed device driver
│   └── n32g45x_algo_lib/             # Algorithm library (AES/DES/HASH/RNG, TSC; headers + prebuilt .lib)
├── middlewares/                      # Middleware (third-party open-source, own licenses)
│   ├── FreeRTOSv202212.01/           # FreeRTOS real-time OS
│   ├── lwip-2.2.0/                   # lwIP lightweight TCP/IP stack
│   └── rt-thread/                    # RT-Thread real-time OS
├── projects/
│   └── n32g45x_EVAL/                 # Projects for the N32G45x_EVAL board
│       ├── bsp/                      # Board support package (delay, log, etc.)
│       ├── applications/             # Application projects (GCC_demo, built with Makefile)
│       └── examples/                 # Examples:
│                                     #   (each with EWARM / MDK-ARM project and readme.txt)
├── jlink/
│   └── flash.jlink                   # J-Link flash script (downloads build/output.hex)
├── .vscode/                          # VS Code configuration (tasks/debug for the GCC toolchain)
└── N32G45x Version History.txt       # Version history and changelog
```

## How to use

> The instructions below are for developers using this SDK locally.

1. **Clone the repository** (this repository contains no submodule, a plain clone is sufficient)

```bash
git clone https://github.com/Nsing-Community/N32-SDK.git
```

2. **Get the latest updates**

```bash
git pull
```

3. **Open an example project** (choose one of the three ways)

   - **Keil MDK-ARM**: directly open the `MDK-ARM/*.uvprojx` project in the example directory;
   - **IAR EWARM**: directly open the `EWARM/*.eww` workspace in the example directory;
   - **GCC + Makefile (command line)**: go to `projects/n32g45x_EVAL/applications/GCC_demo/GCC/` and run `make` with the `arm-none-eabi-` toolchain (see the task configuration in VS Code's `.vscode/tasks.json`).

4. **Flash & debug**: you may use a J-Link to run the [jlink/flash.jlink](jlink/flash.jlink) script to download the build output `build/output.hex` to the target board, or download/debug directly from IAR or Keil.

> [!TIP]
> When learning a peripheral or porting it to your design, it is recommended to first read the `readme.txt` of the related example — it describes the hardware connections, clock/IO configuration and the expected behavior — and then use it together with the driver sources under `firmware/n32g45x_std_periph_driver/`.

## License

The firmware code in this repository follows the BSD-style open-source license (see the copyright notices in the headers of the source files); third-party components under the `middlewares/` directory are governed by their own respective open-source licenses.
