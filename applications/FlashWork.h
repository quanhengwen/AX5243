#ifndef __FLASHWORK_H__
#define __FLASHWORK_H__
#endif
#include "stdint.h"

typedef struct
{
    uint8_t  LastFlag;
    uint32_t Num;
    uint32_t DoorID;
    uint32_t ID[210];
    uint32_t ID_Time[210];
    uint8_t  Bat[210];
    uint8_t  Rssi[210];
}Device_Info;

#define NormalOff   1
#define OtherOff    2
#define NormalOpen  3
#define OtherOpen   4

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
void DeleteAllDevice(void);//数据载入到内存中;
void Flash_Moto_Change(uint8_t value);
uint32_t Flash_Get_Moto_Flag(void);
uint8_t Update_Device_Bat(uint32_t Device_ID,uint8_t bat);
uint8_t Update_Device_Rssi(uint32_t Device_ID,uint8_t rssi);//更新Rssi;
void Detect_All_TimeInDecoder(uint8_t ID);
uint8_t Device_RssiGet(uint32_t Device_ID);
void Device_RssiChange(uint32_t Device_ID,uint8_t value);
uint8_t Device_BatGet(uint32_t Device_ID);
void Device_BatChange(uint32_t Device_ID,uint8_t value);

