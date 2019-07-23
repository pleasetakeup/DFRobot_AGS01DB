# DFRobot_AGS01DB
    AGS01DB 是一款含有已校准数字信号输出的MEMS VOC 气体传感器。它应用专用的数字模块采集技术和气体
    感应传感技术，它的工作方式是IIC从机模式，我们可以使用IIC协议驱动此芯片，此款MEMS 气体传感器，
    有低功耗高灵敏度、快速响应、高可靠性和稳定性、成本低、驱动电路简单等特点。
 
![正反面svg效果图](https://github.com/ouki-wang/DFRobot_Sensor/raw/master/resources/images/SEN0245svg1.png)


## 产品链接（链接到英文商城）
    SKU：AGS01DB voc气体传感器
   
## Table of Contents

* [Summary](#summary)
* [Installation](#installation)
* [Methods](#methods)
* [Compatibility](#compatibility)
* [History](#history)
* [Credits](#credits)

## Summary

  使用此库可以驱动AGS01DB芯片读取空气中有害气体的浓度，如乙醇、氨气、硫化物、苯系蒸汽、烟雾和其它有害气体
,如果模块隔较长一段时间没有使用，则需要预热一段时间，最好是两分钟，读出的数据才会比较准确。

## Installation

To use this library, first download the library file, paste it into the \Arduino\libraries directory, then open the examples folder and run the demo in the folder.

## Methods

```C++
    
/**
 * @brief 初始化函数
 * @return 返回0表示初始化成功，返回其他值表示初始化失败，返回错误码
 */
int begin(void);
    
/**
 * @brief 读取空气中有害气体的浓度.
 * @return 返回读取到的VOC浓度值，单位是ppm.
 */
float readVocPPM();
    
/**
 * @brief 读取芯片的版本号.
 * @return 返回读取到的版本号，如0x0B.
 */
uint8_t readSensorVersion();
```

## Compatibility

MCU                | Work Well    | Work Wrong   | Untested    | Remarks
------------------ | :----------: | :----------: | :---------: | -----
Arduino uno        |      √       |              |             | 
Mega2560        |      √       |              |             | 
Leonardo        |      √       |              |             | 
ESP32        |      √       |              |             | 
micro:bit        |      √       |              |             | 


## History

- data 2019-7-23
- version V0.1


## Credits

Written by fengli(1074485750@qq.com), 2019.7.22 (Welcome to our [website](https://www.dfrobot.com/))





