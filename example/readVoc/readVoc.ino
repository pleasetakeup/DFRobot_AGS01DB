/*!
   @file readVoc.ino
   @brief 读取空气中VOC的浓度和芯片的版本号，单位是勒克斯PPM
   @n 实验现象：每3秒读取一次voc浓度，并打印到串口，用不同的浓度的测试气体，可以得到不同的采集结果
   @n 传感器的量程时0~100PPM 所以只能测量范围较窄。

   @copyright  [DFRobot](http://www.dfrobot.com), 2016
   @copyright GNU Lesser General Public License
   @author [Ouki](ouki.feng@dfrobot.com)
   @version  V1.0
   @date  2019-07-13
   @https://github.com/
*/
#include<DFRobot_AGS01DB.h>
DFRobot_AGS01DB  AGS01DB(&Wire);

uint8_t sensorVersion;
void setup() {
  Serial.begin(115200);

  while (AGS01DB.begin() != 0) {
    Serial.println("初始化芯片失败，请确认芯片连接是否正确");
    delay(1000);
  }
  /*
  return -1 表示数据错误，在校验时没有通过
  否则返回的是正确的版本号
  */
  sensorVersion = AGS01DB.readSensorVersion();
  if (sensorVersion != -1) {
    Serial.print("the version of AGS01DB:");
    Serial.print("0x0");
    Serial.println(sensorVersion, HEX); //显示Version值
    //Serial.println(" ");
  }
  else {
    Serial.print("版本号读取失败 ！");
  }

}
void loop() {
  /*
  return -1 表示数据错误，在校验时没有通过
  否则返回的是正确的voc浓度值.
  */
  float vocConcentration = AGS01DB.readVocPPM();
  if (vocConcentration != -1) {
    Serial.print("the concentration of Voc:");
    Serial.print(vocConcentration); //显示VOC值
    Serial.println(" PPM");
  }
  else {
    Serial.println("返回数据有误！");
  }

  delay(3000);
}