#ifndef __FLASHWORK_H__
#define __FLASHWORK_H__
#endif
#include "stdint.h"
uint32_t Flash_Get(uint32_t id);
uint8_t Flash_Get_Key_Valid(uint32_t key);
void Flash_Key_Change(uint32_t key,uint32_t value);
void Flash_Set(uint8_t id,uint32_t value);
void Flash_Factory(void);
uint8_t Add_Device(uint32_t Device_ID);
void Update_All_Time(void);
uint8_t Clear_Device_Time(uint32_t Device_ID);//更新时间戳为0
void Detect_All_Time(void);
void Boot_Times_Record(void);
void LoadDevice2Memory(void);
uint8_t Add_DoorDevice(uint32_t Device_ID);
uint32_t GetDoorID(void);
