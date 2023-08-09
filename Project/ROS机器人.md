# 基于ROS的室内移动机器人

## 这个项目中你主要负责什么？

主要负责项目软件环境搭建，keil + vscode,分析硬件电路图编写底层软件代码和移植FreeRTOS，如ADC采样电压、制定串口通信协议、模拟IIC读取传感器MPU6050的数据、DMA定长数据串口传输、PID调速等，ROS上层软件开发实现建图与导航等功能。

## 代码量多少？
C:
15个.c文件 15 * 200
15个.h文件 15 * 100
main.c    54

C++:
1个.cpp和1个.h 1000
一些python文件 launch文件 

总计 5000行以上


## 控制逻辑
-	定时器7每20ms中断一次：执行喂狗指令和电源指示灯显示->ADC采样
-	串口1中断接收数据，使用DMA传输数据
- 	FreeRtos任务1：实现增量式PID调速 10ms
-	FreeRtos任务2：将底层数据通过串口发送给上位机 10ms


## 通信协议如何制定?
使用`union`联合体和`#pragma pack(1)`预编译指令，使通信协议数据的`77字节`按`1字节`对齐。
优点：不需要注意移动、字节大小端和字节序等问题，便于解析
```c
#define PROTOCOL_HEADER		0XFEFEFEFE
#define PROTOCOL_END		  0XEE
 
#define PROTOCL_DATA_SIZE 77


#pragma pack(1)
typedef struct __Mpu6050_Str_
{
	short X_data;
	short Y_data;
	short Z_data;
}Mpu6050_Str;

typedef struct __Moto_Str_
{
	float Moto_CurrentSpeed;
	float Moto_TargetSpeed;
}Moto_Str;

typedef union _Upload_Data_   
{
	unsigned char buffer[PROTOCL_DATA_SIZE];
	struct _Sensor_Str_
	{
		unsigned int Header;	
		float X_speed;					
		float Y_speed;			
		float Z_speed;			
		float Battery_Voltage_;
		
		Mpu6050_Str Link_Accelerometer;		
		Mpu6050_Str Link_Gyroscope;			
		
		Moto_Str MotoStr[4];		
		float PID_Param[3];					
		
		unsigned char End_flag;			
	}Sensor_Str;
}Upload_Data;
#pragma pack(4)
```


## 相关知识点？

### IIC通信

> 硬件IIC与软件IIC的区别？

硬件IIC通信接口只有两个，不太灵活。\
软件模拟IIC，使用GPIO模拟IIC时序，比较灵活，易移植。

IIC通信：
-   半双工同步通信，通信可以双向，MCU向外设或者外设向MCU
-   两根线，SDA数据线，SCL时钟线

软件模拟IIC控制信号时序：
-   开始信号：SCL高电平，SDA由高电平向低电平跳变
-   发送控制指令：即IIC总线进行数据传送，SDA数据线上的数据必须在SCL的高电平期间保持稳定，数据线的电平状态只有在SCL为低电平改变。**不论主机还是从机，读取数据时SCL为高电平，发送数据时SCL为低电平。**
-   应答信号：低电平应答，高电平非应答。
-   结束信号：SCL为高电平时，SDA由低电平向高电平跳变。


### DMA+串口定长数据收发

自定义的串口通信协议为77个字节，波特率为115200，正常情况下发送时间过长，采用DMA+串口定长数据收发。

### 增量式PID

-  P:比例控制，作用是快速减小偏差，但是容易出现超调，导致系统的稳定性差
-  I:积分控制，消除稳态误差，使系统最终稳定在设定值附近。
-  D:微分控制：减小超调和抑制振荡，使系统更加稳定。

>一般情况下，如何进行PID整定？
-   手动整定法

### FreeRTOS任务相关内容

>FreeRTOS有哪几种调度方式？

-   合作式调度：很少使用
-   抢占式调度：每个任务都有不同的优先级，任务会一直运行直到被高优先级任务抢占或者遇到阻塞式API函数，如`vTaskDelay`。
-   时间片调度：每个任务有相同的优先级，任务会运行固定的时间片个数或者遇到阻塞的API函数，才会执行同优先级任务之间的任务切换。

>FreeRTOS任务创建?

`xTaskCreate`来指定任务函数、任务名称、任务栈大小、任务参数和任务优先级。创建任务后，它将开始在RTOS内核中调度执行。

>任务状态？

-   运行态
-   就绪态
-   阻塞态
-   挂起态

### MCU 基于STM32
[https://blog.csdn.net/qq_45290757/article/details/127166619?ops_request_misc=&request_id=&biz_id=102&utm_term=MCU%E9%9D%A2%E8%AF%95%E9%A2%98&utm_medium=distribute.pc_search_result.none-task-blog-2~all~sobaiduweb~default-5-127166619.nonecase&spm=1018.2226.3001.4187](MCU 基于STM32)



