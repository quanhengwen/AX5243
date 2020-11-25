#ifndef _RADIO_CONFIG_H_
#define _RADIO_CONFIG_H_

#include "rtthread.h"
void WirelessBitRateConfigure(uint8_t BitRate0);
uint32_t WirelessFreqConfigure(uint8_t Freq2, uint8_t Freq1, uint8_t Freq0, uint8_t Channel_Num);
void WirelessTxPowerConfigure(uint8_t TxPower);

#endif
