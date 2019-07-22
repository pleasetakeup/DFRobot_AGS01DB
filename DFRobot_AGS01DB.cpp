/*!
 * @file DFRobot_AGS01DB.h
 * @brief 定义DFRobot_AGS01DB 类的基础结构
 * @copyright	Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @licence     The MIT License (MIT)
 * @author [fengli](1074485750@qq.com)
 * @version  V1.0
 * @date  2019-07-13
 * @https://github.com/DFRobot/DFRobot_AGS01DB
 */
#include"DFRobot_AGS01DB.h"

DFRobot_AGS01DB::DFRobot_AGS01DB(TwoWire * pWire)
    :_pWire(pWire){

 // _pWire->begin();
}

int DFRobot_AGS01DB::begin() {
  _pWire->begin();
  //检验iic是否可以正常通信
  if (_pWire->requestFrom(AGS01DB_IIC_ADDR, 1) != 1) {
    return -1;
  }
  return 0;
}

float DFRobot_AGS01DB::readVocPPM() {
  uint8_t readCMD[2];
  uint8_t data[3] = {0};
  uint16_t voc;
  readCMD[0] = CMD_DATA_COLLECTION_HIGH;
  readCMD[1] = CMD_DATA_COLLECTION_LOW;
  writeCommand(readCMD, 2);
  delay(100);
  readData(data, 3);
  //从传感器读回的数据，经过校验函数校验得到的voc是否正确。
  //校验为正确，则返回voc浓度
  if (checkCRC8(data, 2) == 1) {
    voc = data[0];
    voc <<= 8;
    voc |= data[1];
    //Serial.print("VOC浓度:");
    //Serial.print(float(VOC)/10); //显示VOC值
    //Serial.println(" PPM");
    //因为传感器的分辨率是0.1PPM，因此数据还需除以10才是正确的浓度值
    return float(voc)/10;
  }
  else {
    DBG("VocConcentration's Crc8 incorrect");
    return -1;
  }
  // return float(VOC)/10;
}

uint8_t DFRobot_AGS01DB::readSensorVersion() {
  uint8_t readCMD[2];
  //uint8_t read[2];
  uint8_t data[2] = {0,0};
  uint8_t version;
  readCMD[0] = CMD_GET_VERSION_HIGH;
  readCMD[1] = CMD_GET_VERSION_LOW;
  writeCommand(readCMD, 2);
  delay(100);
  readData(data, 2);
  //从传感器读回的数据，经过校验函数校验得到的版本号是否正确。
  if (checkCRC8(data, 1) == 1) {
    version = data[0];
    // Serial.print("AGS01DB版本号:");
    // Serial.println(Version,HEX); //显示Version值
    return version;
  }
  else {
    DBG("version's Crc8 incorrect");
  }
  return -1;
}

bool DFRobot_AGS01DB::checkCRC8(uint8_t *data, uint8_t Num) {
  uint8_t bit, byte, crc = 0xFF;
  // 数据位的数据经过转换应该与校验位的数据相同
  for (byte = 0; byte < Num; byte++)
  {
    crc ^= (data[byte]);
    for (bit = 8; bit > 0; --bit)
    {
      if (crc & 0x80) crc = (crc << 1) ^ 0x31;
      else crc = (crc << 1);
    }
  }
  //Serial.print("crc:");
  // Serial.println(crc,HEX);
  if (crc == data[Num])  //让计算的到的crc与读到的crc作比较，来判断读到的数据是否zhengque
    return true;
  else
    return false;
}

void DFRobot_AGS01DB::writeCommand(const void *pBuf, size_t size) {
  //Wire.begin();
  if (pBuf == NULL) {
    DBG("pBuf ERROR!! : null pointer");
  }
  uint8_t * _pBuf = (uint8_t *)pBuf;
  _pWire->beginTransmission(AGS01DB_IIC_ADDR);
  // 将命令通过iic发给芯片
  for (uint16_t i = 0; i < size; i++) {
    _pWire->write(_pBuf[i]);
  }
  _pWire->endTransmission();
}

uint8_t DFRobot_AGS01DB::readData(void *pBuf, size_t size) {
  if (pBuf == NULL) {
    DBG("pBuf ERROR!! : null pointer");
  }
  uint8_t * _pBuf = (uint8_t *)pBuf;
  //读取芯片返回的数据
  _pWire->requestFrom(AGS01DB_IIC_ADDR, size + 1);
  delay(100);
  uint8_t i = 0;

  for (uint8_t i = 0 ; i < size + 1 ; i++) {
    _pBuf[i] = _pWire->read();

  }
  return 1;
}