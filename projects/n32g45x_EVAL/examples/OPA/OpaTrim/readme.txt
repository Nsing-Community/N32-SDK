1、功能说明
    1、OPAMP1的用户模式下的手动校准.
2、使用环境
    软件开发环境：  KEIL MDK-ARM V5.26.2.0
    硬件环境：        基于N32G4XV-STB V1.0 开发
3、使用说明
    系统配置；
        1、时钟源：
                HSE=8M,PLL=144M,AHB=144M,APB1=36M,APB2=72M,OPA CLK=36M
        3、端口配置：
                PA1选择为模拟功能OPA1 VP
        4、Log配置：
            PA9选择为LOG的TX引脚
        5、PGA配置：
            PA1输入，工作模式为校准模式
    使用方法：
        1、编译后下载，观察log打印的OPAMP1的校准值
4、注意事项
    无



1. Function description
    1. Manual calibration of the OPAMP1 in user mode.
2. Use environment
    Software development environment: KEIL MDK-ARM V5.26.2.0
    Hardware environment: Developed based on the development board N32G4XV-STB V1.0
3. Instructions for use
    System Configuration;
        1. Clock source:
                HSE=8M, PLL=144M, AHB=144M, APB1=36M, APB2=72M, OPA CLK=36M
        3. Port configuration:
                PA1 is selected as the analog function OPA1 VP
        4. Log Configuration:
            PA9 is the TX pin of LOG
        5, PGA1：
            PA1 is selected as input, user calibration mode
            
    Instructions:
        1. After compiling and download, Check the calibration value of OPAMP1 printed in the log.
4. Matters needing attention
    without