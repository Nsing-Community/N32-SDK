1、功能说明

    1、QSPI Quad SPI 模式擦除、读、写 GT25Q40

2、使用环境

    /* 硬件环境：工程对应的开发硬件平台 */
    开发板：N32G457QE_EVB V1.0

3、使用说明
    
    /* 描述相关模块配置方法；例如:时钟，I/O等 */
    1、SystemClock：144MHz
    2、GPIO：QSPI(N32G455VGL7内部DATA Flash连接引脚)
            CS：PF0（QSPI_NSS）
            CLK：PF1（QSPI_CLK）
            DI：PF2（QSPI_IO0 )
            DO：PF3（QSPI_IO1）
            WP：PF4（QSPI_IO2）
            HD：PF5（QSPI_IO3）
  

    /* 描述Demo的测试步骤和现象 */
    1.编译后下载程序复位运行；
    2.QSPI 初始化完成后，先擦除 P25Q40HA 一个扇区，通过日志打印检查擦除正常，再往 P25Q40HA 写数据，
        写完后再读出来，比较读写数据，日志打印读写正常，再用日志打印读出来的数据；

4、注意事项
    




1. Function description

     1. QSPI Quad SPI mode erase, read, write GT25Q40

2. Use environment

     /* Hardware environment: the development hardware platform corresponding to the project */
     Development board: N32G457QE_EVB V1.0

3. Instructions for use
    
     /* Describe related module configuration methods; for example: clock, I/O, etc. */
     1. SystemClock: 144MHz
     2. GPIO: QSPI (Internal DATA Flash connection pins for N32G455VGL7)
            CS: PF0 (QSPI_NSS)
            CLK: PF1 (QSPI_CLK)
            DI: PF2 (QSPI_IO0)
            DO: PF3 (QSPI_IO1)
            WP: PF4 (QSPI_IO2)
            HD: PF5 (QSPI_IO3)

     /* Describe the test steps and phenomena of the Demo */
     1. After compiling, download the program to reset and run;
     2. After the QSPI initialization is completed, first erase one sector of P25Q40HA, check the erase is normal through log printing, and then write data to P25Q40HA,
         After writing, read it out, compare the read and write data, the log print and read and write are normal, and then use the log to print the read data;

4. Matters needing attention
     
