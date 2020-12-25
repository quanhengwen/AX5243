//// Copyright (c) 2007,2008,2009,2010,2011,2012,2013, 2014 AXSEM AG
//// All rights reserved.
////
//// Redistribution and use in source and binary forms, with or without
//// modification, are permitted provided that the following conditions are met:
////
////     1.Redistributions of source code must retain the above copyright
////       notice, this list of conditions and the following disclaimer.
////     2.Redistributions in binary form must reproduce the above copyright
////       notice, this list of conditions and the following disclaimer in the
////       documentation and/or other materials provided with the distribution.
////     3.Neither the name of AXSEM AG, Duebendorf nor the
////       names of its contributors may be used to endorse or promote products
////       derived from this software without specific prior written permission.
////     4.All advertising materials mentioning features or use of this software
////       must display the following acknowledgement:
////       This product includes software developed by AXSEM AG and its contributors.
////     5.The usage of this source code is only granted for operation with AX5043
////       and AX8052F143. Porting to other radio or communication devices is
////       strictly prohibited.
////
//// THIS SOFTWARE IS PROVIDED BY AXSEM AG AND CONTRIBUTORS ``AS IS'' AND ANY
//// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
//// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
//// DISCLAIMED. IN NO EVENT SHALL AXSEM AG AND CONTRIBUTORS BE LIABLE FOR ANY
//// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
//// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
//// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
//// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
//// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
//// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//#include "rtthread.h"
//
//#ifndef AXRADIO_H
//#define AXRADIO_H
//
//#define AXRADIO_MODE_UNINIT                     0x00
//#define AXRADIO_MODE_OFF                        0x01
//#define AXRADIO_MODE_DEEPSLEEP                  0x02
//#define AXRADIO_MODE_CW_TRANSMIT                0x03
//#define AXRADIO_MODE_ASYNC_TRANSMIT             0x10
//#define AXRADIO_MODE_WOR_TRANSMIT               0x11
//#define AXRADIO_MODE_ACK_TRANSMIT               0x12
//#define AXRADIO_MODE_WOR_ACK_TRANSMIT           0x13
//#define AXRADIO_MODE_STREAM_TRANSMIT_UNENC      0x18
//#define AXRADIO_MODE_STREAM_TRANSMIT_SCRAM      0x19
//#define AXRADIO_MODE_STREAM_TRANSMIT_UNENC_LSB  0x1A
//#define AXRADIO_MODE_STREAM_TRANSMIT_SCRAM_LSB  0x1B
//#define AXRADIO_MODE_STREAM_TRANSMIT            0x1C
//#define AXRADIO_MODE_ASYNC_RECEIVE              0x20
//#define AXRADIO_MODE_WOR_RECEIVE                0x21
//#define AXRADIO_MODE_ACK_RECEIVE                0x22
//#define AXRADIO_MODE_WOR_ACK_RECEIVE            0x23
//#define AXRADIO_MODE_STREAM_RECEIVE_UNENC       0x28
//#define AXRADIO_MODE_STREAM_RECEIVE_SCRAM       0x29
//#define AXRADIO_MODE_STREAM_RECEIVE_UNENC_LSB   0x2A
//#define AXRADIO_MODE_STREAM_RECEIVE_SCRAM_LSB   0x2B
//#define AXRADIO_MODE_STREAM_RECEIVE             0x2C
//#define AXRADIO_MODE_STREAM_RECEIVE_DATAPIN     0x2D
//#define AXRADIO_MODE_SYNC_MASTER                0x30
//#define AXRADIO_MODE_SYNC_ACK_MASTER            0x31
//#define AXRADIO_MODE_SYNC_SLAVE                 0x32
//#define AXRADIO_MODE_SYNC_ACK_SLAVE             0x33
//
//#define AXRADIO_MODE_IS_STREAM_TRANSMIT(x)      (((x) & 0xF8) == ((AXRADIO_MODE_STREAM_TRANSMIT) & 0xF8))
//#define AXRADIO_MODE_IS_STREAM_RECEIVE(x)       (((x) & 0xF8) == ((AXRADIO_MODE_STREAM_RECEIVE) & 0xF8))
//
//#define AXRADIO_ERR_NOERROR                     0x00
//#define AXRADIO_ERR_NOTSUPPORTED                0x01
//#define AXRADIO_ERR_BUSY                        0x02
//#define AXRADIO_ERR_TIMEOUT                     0x03
//#define AXRADIO_ERR_INVALID                     0x04
//#define AXRADIO_ERR_NOCHIP                      0x05
//#define AXRADIO_ERR_RANGING                     0x06
//#define AXRADIO_ERR_LOCKLOST                    0x07
//#define AXRADIO_ERR_RETRANSMISSION              0x08
//#define AXRADIO_ERR_RESYNC                      0x09
//#define AXRADIO_ERR_RESYNCTIMEOUT               0x0a
//#define AXRADIO_ERR_RECEIVESTART                0x0b
//
//#define AXRADIO_STAT_RECEIVE                    0x00
//#define AXRADIO_STAT_RECEIVESFD                 0x01
//#define AXRADIO_STAT_CHANNELSTATE               0x02
//#define AXRADIO_STAT_TRANSMITSTART              0x03
//#define AXRADIO_STAT_TRANSMITEND                0x04
//#define AXRADIO_STAT_TRANSMITDATA               0x05
//
//struct axradio_address {
//    uint8_t addr[4];
//};
//
//struct axradio_address_mask {
//    uint8_t addr[4];
//    uint8_t mask[4];
//};
//
//struct axradio_status {
//    uint8_t status; // one of the AXRADIO_STAT_* constants
//    uint8_t error;  // one of the AXRADIO_ERR_* constants
//    uint32_t time;  // timestamp of the event
//
//    union {
//        //status AXRADIO_STAT_RECEIVE
//        struct axradio_status_receive {
//            struct axradio_status_receive_phy {
//                int16_t rssi;       //RSSI,dBm
//                int32_t offset;     //frequency offset, internal units
//                int16_t timeoffset; // time offset, timer0 units (only sync)
//                int16_t period;     // period offset (only sync)
//            } phy;
//            struct axradio_status_receive_mac {
//                uint8_t remoteaddr[4];
//                uint8_t localaddr[4];
//                const uint8_t *raw;
//            } mac;
//            const uint8_t *pktdata;
//            uint16_t pktlen;
//        } rx;
//
//        //status AXRADIO_STAT_CHANNELSTATE
//        struct axradio_status_channelstate {
//            int16_t rssi; // RSSI, dBm
//            uint8_t busy; // 1: over the LBT threshold
//        } cs;
//    } u;
//};
//
//# define SBIT(name, addr, bit)  volatile bool           name ;
//# define SFR(name, addr)        volatile unsigned char  name ;
//# define SFRX(name, addr)       volatile unsigned char  name ;
//# define SFR16(name, addr)      volatile unsigned short name ;
//# define SFR16E(name, fulladdr) volatile unsigned short name ;
//# define SFR16LEX(name, addr)   volatile unsigned short name ;
//# define SFR32(name, fulladdr)  volatile unsigned long  name ;
//# define SFR32E(name, fulladdr) volatile unsigned long  name ;
//
//extern uint8_t axradio_init(void);
//extern uint8_t axradio_cansleep(void) ;
//extern uint8_t axradio_set_mode(uint8_t mode);
//extern uint8_t axradio_get_mode(void);
//extern uint8_t axradio_set_channel(uint8_t chnum);
//extern uint8_t axradio_get_channel(void);
//extern uint8_t axradio_get_pllrange(void);
//extern uint8_t axradio_get_pllvcoi(void);
//extern void axradio_set_local_address(const struct axradio_address_mask *addr);
//extern void axradio_get_local_address(struct axradio_address_mask *addr);
//extern void axradio_set_default_remote_address(const struct axradio_address *addr);
//extern void axradio_get_default_remote_address(struct axradio_address *addr);
//extern uint8_t axradio_set_freqoffset(int32_t offs);
//extern int32_t axradio_get_freqoffset(void);
//extern int32_t axradio_conv_freq_tohz(int32_t f) ;
//extern int32_t axradio_conv_freq_fromhz(int32_t f) ;
//extern int32_t axradio_conv_timeinterval_totimer0(int32_t dt) ;
//extern uint32_t axradio_conv_time_totimer0(uint32_t dt) ;
//extern uint8_t axradio_transmit(const struct axradio_address *addr, const uint8_t *pkt, uint16_t pktlen);
//extern void axradio_statuschange(struct axradio_status *st);
//extern uint8_t axradio_agc_freeze(void);
//extern uint8_t axradio_agc_thaw(void);
//
//extern const uint8_t axradio_framing_maclen;
//extern const uint8_t axradio_framing_addrlen;
//
//// funtions implemented in AX_Radio_output/config.c
//void axradio_setup_pincfg1(void) ;
//void axradio_setup_pincfg2(void) ;
//
//#if defined(SDCC)
//// this is needed to make SDCC include this ISR into the vector table
//#define INT_RADIO        4
//extern void axradio_isr(void) __interrupt INT_RADIO;
//#endif
//
//#endif /* AXRADIO_H */
//
//SFRX(AX5043_AFSKCTRL,              0x4114)   /* AFSK Control */
//SFRX(AX5043_AFSKMARK0,             0x4113)   /* AFSK Mark (1) Frequency 0 */
//SFRX(AX5043_AFSKMARK1,             0x4112)   /* AFSK Mark (1) Frequency 1 */
//SFRX(AX5043_AFSKSPACE0,            0x4111)   /* AFSK Space (0) Frequency 0 */
//SFRX(AX5043_AFSKSPACE1,            0x4110)   /* AFSK Space (0) Frequency 1 */
//SFRX(AX5043_AGCCOUNTER,            0x4043)   /* AGC Counter */
//SFRX(AX5043_AMPLFILTER,            0x4115)   /* Amplitude Filter */
//SFRX(AX5043_BBOFFSCAP,             0x4189)   /* Baseband Offset Compensation Capacitors */
//SFRX(AX5043_BBTUNE,                0x4188)   /* Baseband Tuning */
//SFRX(AX5043_BGNDRSSI,              0x4041)   /* Background RSSI */
//SFRX(AX5043_BGNDRSSIGAIN,          0x422E)   /* Background RSSI Averaging Time Constant */
//SFRX(AX5043_BGNDRSSITHR,           0x422F)   /* Background RSSI Relative Threshold */
//SFRX(AX5043_CRCINIT0,              0x4017)   /* CRC Initial Value 0 */
//SFRX(AX5043_CRCINIT1,              0x4016)   /* CRC Initial Value 1 */
//SFRX(AX5043_CRCINIT2,              0x4015)   /* CRC Initial Value 2 */
//SFRX(AX5043_CRCINIT3,              0x4014)   /* CRC Initial Value 3 */
//SFRX(AX5043_DACCONFIG,             0x4332)   /* DAC Configuration */
//SFRX(AX5043_DACVALUE0,             0x4331)   /* DAC Value 0 */
//SFRX(AX5043_DACVALUE1,             0x4330)   /* DAC Value 1 */
//SFRX(AX5043_DECIMATION,            0x4102)   /* Decimation Factor  */
//SFRX(AX5043_DIVERSITY,             0x4042)   /* Antenna Diversity Configuration */
//SFRX(AX5043_ENCODING,              0x4011)   /* Encoding */
//SFRX(AX5043_FEC,                   0x4018)   /* Forward Error Correction */
//SFRX(AX5043_FECSTATUS,             0x401A)   /* Forward Error Correction Status */
//SFRX(AX5043_FECSYNC,               0x4019)   /* Forward Error Correction Sync Threshold */
//SFRX(AX5043_FIFOCOUNT0,            0x402B)   /* Number of Words currently in FIFO 0 */
//SFRX(AX5043_FIFOCOUNT1,            0x402A)   /* Number of Words currently in FIFO 1 */
//SFRX(AX5043_FIFODATA,              0x4029)   /* FIFO Data */
//SFRX(AX5043_FIFOFREE0,             0x402D)   /* Number of Words that can be written to FIFO 0 */
//SFRX(AX5043_FIFOFREE1,             0x402C)   /* Number of Words that can be written to FIFO 1 */
//SFRX(AX5043_FIFOSTAT,              0x4028)   /* FIFO Control */
//SFRX(AX5043_FIFOTHRESH0,           0x402F)   /* FIFO Threshold 0 */
//SFRX(AX5043_FIFOTHRESH1,           0x402E)   /* FIFO Threshold 1 */
//SFRX(AX5043_FRAMING,               0x4012)   /* Framing Mode */
//SFRX(AX5043_FREQA0,                0x4037)   /* Frequency A 0 */
//SFRX(AX5043_FREQA1,                0x4036)   /* Frequency A 1 */
//SFRX(AX5043_FREQA2,                0x4035)   /* Frequency A 2 */
//SFRX(AX5043_FREQA3,                0x4034)   /* Frequency A 3 */
//SFRX(AX5043_FREQB0,                0x403F)   /* Frequency B 0 */
//SFRX(AX5043_FREQB1,                0x403E)   /* Frequency B 1 */
//SFRX(AX5043_FREQB2,                0x403D)   /* Frequency B 2 */
//SFRX(AX5043_FREQB3,                0x403C)   /* Frequency B 3 */
//SFRX(AX5043_FSKDEV0,               0x4163)   /* FSK Deviation 0 */
//SFRX(AX5043_FSKDEV1,               0x4162)   /* FSK Deviation 1 */
//SFRX(AX5043_FSKDEV2,               0x4161)   /* FSK Deviation 2 */
//SFRX(AX5043_FSKDMAX0,              0x410D)   /* Four FSK Rx Maximum Deviation 0 */
//SFRX(AX5043_FSKDMAX1,              0x410C)   /* Four FSK Rx Maximum Deviation 1 */
//SFRX(AX5043_FSKDMIN0,              0x410F)   /* Four FSK Rx Minimum Deviation 0 */
//SFRX(AX5043_FSKDMIN1,              0x410E)   /* Four FSK Rx Minimum Deviation 1 */
//SFRX(AX5043_GPADC13VALUE0,         0x4309)   /* GPADC13 Value 0 */
//SFRX(AX5043_GPADC13VALUE1,         0x4308)   /* GPADC13 Value 1 */
//SFRX(AX5043_GPADCCTRL,             0x4300)   /* General Purpose ADC Control */
//SFRX(AX5043_GPADCPERIOD,           0x4301)   /* GPADC Sampling Period */
//SFRX(AX5043_IFFREQ0,               0x4101)   /* 2nd LO / IF Frequency 0 */
//SFRX(AX5043_IFFREQ1,               0x4100)   /* 2nd LO / IF Frequency 1 */
//SFRX(AX5043_IRQINVERSION0,         0x400B)   /* IRQ Inversion 0 */
//SFRX(AX5043_IRQINVERSION1,         0x400A)   /* IRQ Inversion 1 */
//SFRX(AX5043_IRQMASK0,              0x4007)   /* IRQ Mask 0 */
//SFRX(AX5043_IRQMASK1,              0x4006)   /* IRQ Mask 1 */
//SFRX(AX5043_IRQREQUEST0,           0x400D)   /* IRQ Request 0 */
//SFRX(AX5043_IRQREQUEST1,           0x400C)   /* IRQ Request 1 */
//SFRX(AX5043_LPOSCCONFIG,           0x4310)   /* Low Power Oscillator Calibration Configuration */
//SFRX(AX5043_LPOSCFREQ0,            0x4317)   /* Low Power Oscillator Frequency Tuning Low Byte */
//SFRX(AX5043_LPOSCFREQ1,            0x4316)   /* Low Power Oscillator Frequency Tuning High Byte */
//SFRX(AX5043_LPOSCKFILT0,           0x4313)   /* Low Power Oscillator Calibration Filter Constant Low Byte */
//SFRX(AX5043_LPOSCKFILT1,           0x4312)   /* Low Power Oscillator Calibration Filter Constant High Byte */
//SFRX(AX5043_LPOSCPER0,             0x4319)   /* Low Power Oscillator Period Low Byte */
//SFRX(AX5043_LPOSCPER1,             0x4318)   /* Low Power Oscillator Period High Byte */
//SFRX(AX5043_LPOSCREF0,             0x4315)   /* Low Power Oscillator Reference Frequency Low Byte */
//SFRX(AX5043_LPOSCREF1,             0x4314)   /* Low Power Oscillator Reference Frequency High Byte */
//SFRX(AX5043_LPOSCSTATUS,           0x4311)   /* Low Power Oscillator Calibration Status */
//SFRX(AX5043_MATCH0LEN,             0x4214)   /* Pattern Match Unit 0, Pattern Length */
//SFRX(AX5043_MATCH0MAX,             0x4216)   /* Pattern Match Unit 0, Maximum Match */
//SFRX(AX5043_MATCH0MIN,             0x4215)   /* Pattern Match Unit 0, Minimum Match */
//SFRX(AX5043_MATCH0PAT0,            0x4213)   /* Pattern Match Unit 0, Pattern 0 */
//SFRX(AX5043_MATCH0PAT1,            0x4212)   /* Pattern Match Unit 0, Pattern 1 */
//SFRX(AX5043_MATCH0PAT2,            0x4211)   /* Pattern Match Unit 0, Pattern 2 */
//SFRX(AX5043_MATCH0PAT3,            0x4210)   /* Pattern Match Unit 0, Pattern 3 */
//SFRX(AX5043_MATCH1LEN,             0x421C)   /* Pattern Match Unit 1, Pattern Length */
//SFRX(AX5043_MATCH1MAX,             0x421E)   /* Pattern Match Unit 1, Maximum Match */
//SFRX(AX5043_MATCH1MIN,             0x421D)   /* Pattern Match Unit 1, Minimum Match */
//SFRX(AX5043_MATCH1PAT0,            0x4219)   /* Pattern Match Unit 1, Pattern 0 */
//SFRX(AX5043_MATCH1PAT1,            0x4218)   /* Pattern Match Unit 1, Pattern 1 */
//SFRX(AX5043_MAXDROFFSET0,          0x4108)   /* Maximum Receiver Datarate Offset 0 */
//SFRX(AX5043_MAXDROFFSET1,          0x4107)   /* Maximum Receiver Datarate Offset 1 */
//SFRX(AX5043_MAXDROFFSET2,          0x4106)   /* Maximum Receiver Datarate Offset 2 */
//SFRX(AX5043_MAXRFOFFSET0,          0x410B)   /* Maximum Receiver RF Offset 0 */
//SFRX(AX5043_MAXRFOFFSET1,          0x410A)   /* Maximum Receiver RF Offset 1 */
//SFRX(AX5043_MAXRFOFFSET2,          0x4109)   /* Maximum Receiver RF Offset 2 */
//SFRX(AX5043_MODCFGA,               0x4164)   /* Modulator Configuration A */
//SFRX(AX5043_MODCFGF,               0x4160)   /* Modulator Configuration F */
//SFRX(AX5043_MODCFGP,               0x4F5F)   /* Modulator Configuration P */
//SFRX(AX5043_MODULATION,            0x4010)   /* Modulation */
//SFRX(AX5043_PINFUNCANTSEL,         0x4025)   /* Pin Function ANTSEL */
//SFRX(AX5043_PINFUNCDATA,           0x4023)   /* Pin Function DATA */
//SFRX(AX5043_PINFUNCDCLK,           0x4022)   /* Pin Function DCLK */
//SFRX(AX5043_PINFUNCIRQ,            0x4024)   /* Pin Function IRQ */
//SFRX(AX5043_PINFUNCPWRAMP,         0x4026)   /* Pin Function PWRAMP */
//SFRX(AX5043_PINFUNCSYSCLK,         0x4021)   /* Pin Function SYSCLK */
//SFRX(AX5043_PINSTATE,              0x4020)   /* Pin State */
//SFRX(AX5043_PKTACCEPTFLAGS,        0x4233)   /* Packet Controller Accept Flags */
//SFRX(AX5043_PKTCHUNKSIZE,          0x4230)   /* Packet Chunk Size */
//SFRX(AX5043_PKTMISCFLAGS,          0x4231)   /* Packet Controller Miscellaneous Flags */
//SFRX(AX5043_PKTSTOREFLAGS,         0x4232)   /* Packet Controller Store Flags */
//SFRX(AX5043_PLLCPI,                0x4031)   /* PLL Charge Pump Current */
//SFRX(AX5043_PLLCPIBOOST,           0x4039)   /* PLL Charge Pump Current (Boosted) */
//SFRX(AX5043_PLLLOCKDET,            0x4182)   /* PLL Lock Detect Delay */
//SFRX(AX5043_PLLLOOP,               0x4030)   /* PLL Loop Filter Settings */
//SFRX(AX5043_PLLLOOPBOOST,          0x4038)   /* PLL Loop Filter Settings (Boosted) */
//SFRX(AX5043_PLLRANGINGA,           0x4033)   /* PLL Autoranging A */
//SFRX(AX5043_PLLRANGINGB,           0x403B)   /* PLL Autoranging B */
//SFRX(AX5043_PLLRNGCLK,             0x4183)   /* PLL Autoranging Clock */
//SFRX(AX5043_PLLVCODIV,             0x4032)   /* PLL Divider Settings */
//SFRX(AX5043_PLLVCOI,               0x4180)   /* PLL VCO Current */
//SFRX(AX5043_PLLVCOIR,              0x4181)   /* PLL VCO Current Readback */
//SFRX(AX5043_POWCTRL1,              0x4F08)   /* Power Control 1 */
//SFRX(AX5043_POWIRQMASK,            0x4005)   /* Power Management Interrupt Mask */
//SFRX(AX5043_POWSTAT,               0x4003)   /* Power Management Status */
//SFRX(AX5043_POWSTICKYSTAT,         0x4004)   /* Power Management Sticky Status */
//SFRX(AX5043_PWRAMP,                0x4027)   /* PWRAMP Control */
//SFRX(AX5043_PWRMODE,               0x4002)   /* Power Mode */
//SFRX(AX5043_RADIOEVENTMASK0,       0x4009)   /* Radio Event Mask 0 */
//SFRX(AX5043_RADIOEVENTMASK1,       0x4008)   /* Radio Event Mask 1 */
//SFRX(AX5043_RADIOEVENTREQ0,        0x400F)   /* Radio Event Request 0 */
//SFRX(AX5043_RADIOEVENTREQ1,        0x400E)   /* Radio Event Request 1 */
//SFRX(AX5043_RADIOSTATE,            0x401C)   /* Radio Controller State */
//SFRX(AX5043_REF,                   0x4F0D)   /* Reference */
//SFRX(AX5043_RSSI,                  0x4040)   /* Received Signal Strength Indicator */
//SFRX(AX5043_RSSIABSTHR,            0x422D)   /* RSSI Absolute Threshold */
//SFRX(AX5043_RSSIREFERENCE,         0x422C)   /* RSSI Offset */
//SFRX(AX5043_RXDATARATE0,           0x4105)   /* Receiver Datarate 0 */
//SFRX(AX5043_RXDATARATE1,           0x4104)   /* Receiver Datarate 1 */
//SFRX(AX5043_RXDATARATE2,           0x4103)   /* Receiver Datarate 2 */
//SFRX(AX5043_SCRATCH,               0x4001)   /* Scratch */
//SFRX(AX5043_SILICONREVISION,       0x4000)   /* Silicon Revision */
//SFRX(AX5043_TIMER0,                0x405B)   /* 1MHz Timer 0 */
//SFRX(AX5043_TIMER1,                0x405A)   /* 1MHz Timer 1 */
//SFRX(AX5043_TIMER2,                0x4059)   /* 1MHz Timer 2 */
//SFRX(AX5043_TMGRXAGC,              0x4227)   /* Receiver AGC Settling Time */
//SFRX(AX5043_TMGRXBOOST,            0x4223)   /* Receive PLL Boost Time */
//SFRX(AX5043_TMGRXCOARSEAGC,        0x4226)   /* Receive Coarse AGC Time */
//SFRX(AX5043_TMGRXOFFSACQ,          0x4225)   /* Receive Baseband DC Offset Acquisition Time */
//SFRX(AX5043_TMGRXPREAMBLE1,        0x4229)   /* Receiver Preamble 1 Timeout */
//SFRX(AX5043_TMGRXPREAMBLE2,        0x422A)   /* Receiver Preamble 2 Timeout */
//SFRX(AX5043_TMGRXPREAMBLE3,        0x422B)   /* Receiver Preamble 3 Timeout */
//SFRX(AX5043_TMGRXRSSI,             0x4228)   /* Receiver RSSI Settling Time */
//SFRX(AX5043_TMGRXSETTLE,           0x4224)   /* Receive PLL (post Boost) Settling Time */
//SFRX(AX5043_TMGTXBOOST,            0x4220)   /* Transmit PLL Boost Time */
//SFRX(AX5043_TMGTXSETTLE,           0x4221)   /* Transmit PLL (post Boost) Settling Time */
//SFRX(AX5043_TRKAFSKDEMOD0,         0x4055)   /* AFSK Demodulator Tracking 0 */
//SFRX(AX5043_TRKAFSKDEMOD1,         0x4054)   /* AFSK Demodulator Tracking 1 */
//SFRX(AX5043_TRKAMPLITUDE0,         0x4049)   /* Amplitude Tracking 0 */
//SFRX(AX5043_TRKAMPLITUDE1,         0x4048)   /* Amplitude Tracking 1 */
//SFRX(AX5043_TRKDATARATE0,          0x4047)   /* Datarate Tracking 0 */
//SFRX(AX5043_TRKDATARATE1,          0x4046)   /* Datarate Tracking 1 */
//SFRX(AX5043_TRKDATARATE2,          0x4045)   /* Datarate Tracking 2 */
//SFRX(AX5043_TRKFREQ0,              0x4051)   /* Frequency Tracking 0 */
//SFRX(AX5043_TRKFREQ1,              0x4050)   /* Frequency Tracking 1 */
//SFRX(AX5043_TRKFSKDEMOD0,          0x4053)   /* FSK Demodulator Tracking 0 */
//SFRX(AX5043_TRKFSKDEMOD1,          0x4052)   /* FSK Demodulator Tracking 1 */
//SFRX(AX5043_TRKPHASE0,             0x404B)   /* Phase Tracking 0 */
//SFRX(AX5043_TRKPHASE1,             0x404A)   /* Phase Tracking 1 */
//SFRX(AX5043_TRKRFFREQ0,            0x404F)   /* RF Frequency Tracking 0 */
//SFRX(AX5043_TRKRFFREQ1,            0x404E)   /* RF Frequency Tracking 1 */
//SFRX(AX5043_TRKRFFREQ2,            0x404D)   /* RF Frequency Tracking 2 */
//SFRX(AX5043_TXPWRCOEFFA0,          0x4169)   /* Transmitter Predistortion Coefficient A 0 */
//SFRX(AX5043_TXPWRCOEFFA1,          0x4168)   /* Transmitter Predistortion Coefficient A 1 */
//SFRX(AX5043_TXPWRCOEFFB0,          0x416B)   /* Transmitter Predistortion Coefficient B 0 */
//SFRX(AX5043_TXPWRCOEFFB1,          0x416A)   /* Transmitter Predistortion Coefficient B 1 */
//SFRX(AX5043_TXPWRCOEFFC0,          0x416D)   /* Transmitter Predistortion Coefficient C 0 */
//SFRX(AX5043_TXPWRCOEFFC1,          0x416C)   /* Transmitter Predistortion Coefficient C 1 */
//SFRX(AX5043_TXPWRCOEFFD0,          0x416F)   /* Transmitter Predistortion Coefficient D 0 */
//SFRX(AX5043_TXPWRCOEFFD1,          0x416E)   /* Transmitter Predistortion Coefficient D 1 */
//SFRX(AX5043_TXPWRCOEFFE0,          0x4171)   /* Transmitter Predistortion Coefficient E 0 */
//SFRX(AX5043_TXPWRCOEFFE1,          0x4170)   /* Transmitter Predistortion Coefficient E 1 */
//SFRX(AX5043_TXRATE0,               0x4167)   /* Transmitter Bitrate 0 */
//SFRX(AX5043_TXRATE1,               0x4166)   /* Transmitter Bitrate 1 */
//SFRX(AX5043_TXRATE2,               0x4165)   /* Transmitter Bitrate 2 */
//SFRX(AX5043_WAKEUP0,               0x406B)   /* Wakeup Time 0 */
//SFRX(AX5043_WAKEUP1,               0x406A)   /* Wakeup Time 1 */
//SFRX(AX5043_WAKEUPFREQ0,           0x406D)   /* Wakeup Frequency 0 */
//SFRX(AX5043_WAKEUPFREQ1,           0x406C)   /* Wakeup Frequency 1 */
//SFRX(AX5043_WAKEUPTIMER0,          0x4069)   /* Wakeup Timer 0 */
//SFRX(AX5043_WAKEUPTIMER1,          0x4068)   /* Wakeup Timer 1 */
//SFRX(AX5043_WAKEUPXOEARLY,         0x406E)   /* Wakeup Crystal Oscillator Early */
//SFRX(AX5043_XTALAMPL,              0x4F11)   /* Crystal Oscillator Amplitude Control */
//SFRX(AX5043_XTALCAP,               0x4184)   /* Crystal Oscillator Load Capacitance */
//SFRX(AX5043_XTALOSC,               0x4F10)   /* Crystal Oscillator Control */
//SFRX(AX5043_XTALSTATUS,            0x401D)   /* Crystal Oscillator Status */
//
//SFRX(AX5043_0xF00,                 0x4F00)
//SFRX(AX5043_0xF0C,                 0x4F0C)
//SFRX(AX5043_0xF18,                 0x4F18)
//SFRX(AX5043_0xF1C,                 0x4F1C)
//SFRX(AX5043_0xF21,                 0x4F21)
//SFRX(AX5043_0xF22,                 0x4F22)
//SFRX(AX5043_0xF23,                 0x4F23)
//SFRX(AX5043_0xF26,                 0x4F26)
//SFRX(AX5043_0xF30,                 0x4F30)
//SFRX(AX5043_0xF31,                 0x4F31)
//SFRX(AX5043_0xF32,                 0x4F32)
//SFRX(AX5043_0xF33,                 0x4F33)
//SFRX(AX5043_0xF34,                 0x4F34)
//SFRX(AX5043_0xF35,                 0x4F35)
//SFRX(AX5043_0xF44,                 0x4F44)
//
//#if defined AX5043V1
//SFRX(AX5043_AGCGAIN0_V1,           0x4120)   /* AGC Speed */
//SFRX(AX5043_AGCGAIN1_V1,           0x412E)   /* AGC Speed */
//SFRX(AX5043_AGCGAIN2_V1,           0x413C)   /* AGC Speed */
//SFRX(AX5043_AGCGAIN3_V1,           0x414A)   /* AGC Speed */
//SFRX(AX5043_AGCTARGET0_V1,         0x4121)   /* AGC Target */
//SFRX(AX5043_AGCTARGET1_V1,         0x412F)   /* AGC Target */
//SFRX(AX5043_AGCTARGET2_V1,         0x413D)   /* AGC Target */
//SFRX(AX5043_AGCTARGET3_V1,         0x414B)   /* AGC Target */
//SFRX(AX5043_AMPLITUDEGAIN0_V1,     0x4129)   /* Amplitude Estimator Bandwidth */
//SFRX(AX5043_AMPLITUDEGAIN1_V1,     0x4137)   /* Amplitude Estimator Bandwidth */
//SFRX(AX5043_AMPLITUDEGAIN2_V1,     0x4145)   /* Amplitude Estimator Bandwidth */
//SFRX(AX5043_AMPLITUDEGAIN3_V1,     0x4153)   /* Amplitude Estimator Bandwidth */
//SFRX(AX5043_BBOFFSRES0_V1,         0x412D)   /* Baseband Offset Compensation Resistors */
//SFRX(AX5043_BBOFFSRES1_V1,         0x413B)   /* Baseband Offset Compensation Resistors */
//SFRX(AX5043_BBOFFSRES2_V1,         0x4149)   /* Baseband Offset Compensation Resistors */
//SFRX(AX5043_BBOFFSRES3_V1,         0x4157)   /* Baseband Offset Compensation Resistors */
//SFRX(AX5043_DRGAIN0_V1,            0x4123)   /* Data Rate Estimator Bandwidth */
//SFRX(AX5043_DRGAIN1_V1,            0x4131)   /* Data Rate Estimator Bandwidth */
//SFRX(AX5043_DRGAIN2_V1,            0x413F)   /* Data Rate Estimator Bandwidth */
//SFRX(AX5043_DRGAIN3_V1,            0x414D)   /* Data Rate Estimator Bandwidth */
//SFRX(AX5043_FOURFSK0_V1,           0x412C)   /* Four FSK Control */
//SFRX(AX5043_FOURFSK1_V1,           0x413A)   /* Four FSK Control */
//SFRX(AX5043_FOURFSK2_V1,           0x4148)   /* Four FSK Control */
//SFRX(AX5043_FOURFSK3_V1,           0x4156)   /* Four FSK Control */
//SFRX(AX5043_FREQDEV00_V1,          0x412B)   /* Receiver Frequency Deviation 0 */
//SFRX(AX5043_FREQDEV01_V1,          0x4139)   /* Receiver Frequency Deviation 0 */
//SFRX(AX5043_FREQDEV02_V1,          0x4147)   /* Receiver Frequency Deviation 0 */
//SFRX(AX5043_FREQDEV03_V1,          0x4155)   /* Receiver Frequency Deviation 0 */
//SFRX(AX5043_FREQDEV10_V1,          0x412A)   /* Receiver Frequency Deviation 1 */
//SFRX(AX5043_FREQDEV11_V1,          0x4138)   /* Receiver Frequency Deviation 1 */
//SFRX(AX5043_FREQDEV12_V1,          0x4146)   /* Receiver Frequency Deviation 1 */
//SFRX(AX5043_FREQDEV13_V1,          0x4154)   /* Receiver Frequency Deviation 1 */
//SFRX(AX5043_FREQUENCYGAINA0_V1,    0x4125)   /* Frequency Estimator Bandwidth A */
//SFRX(AX5043_FREQUENCYGAINA1_V1,    0x4133)   /* Frequency Estimator Bandwidth A */
//SFRX(AX5043_FREQUENCYGAINA2_V1,    0x4141)   /* Frequency Estimator Bandwidth A */
//SFRX(AX5043_FREQUENCYGAINA3_V1,    0x414F)   /* Frequency Estimator Bandwidth A */
//SFRX(AX5043_FREQUENCYGAINB0_V1,    0x4126)   /* Frequency Estimator Bandwidth B */
//SFRX(AX5043_FREQUENCYGAINB1_V1,    0x4134)   /* Frequency Estimator Bandwidth B */
//SFRX(AX5043_FREQUENCYGAINB2_V1,    0x4142)   /* Frequency Estimator Bandwidth B */
//SFRX(AX5043_FREQUENCYGAINB3_V1,    0x4150)   /* Frequency Estimator Bandwidth B */
//SFRX(AX5043_FREQUENCYGAINC0_V1,    0x4127)   /* Frequency Estimator Bandwidth C */
//SFRX(AX5043_FREQUENCYGAINC1_V1,    0x4135)   /* Frequency Estimator Bandwidth C */
//SFRX(AX5043_FREQUENCYGAINC2_V1,    0x4143)   /* Frequency Estimator Bandwidth C */
//SFRX(AX5043_FREQUENCYGAINC3_V1,    0x4151)   /* Frequency Estimator Bandwidth C */
//SFRX(AX5043_FREQUENCYGAIND0_V1,    0x4128)   /* Frequency Estimator Bandwidth D */
//SFRX(AX5043_FREQUENCYGAIND1_V1,    0x4136)   /* Frequency Estimator Bandwidth D */
//SFRX(AX5043_FREQUENCYGAIND2_V1,    0x4144)   /* Frequency Estimator Bandwidth D */
//SFRX(AX5043_FREQUENCYGAIND3_V1,    0x4152)   /* Frequency Estimator Bandwidth D */
//SFRX(AX5043_PHASEGAIN0_V1,         0x4124)   /* Phase Estimator Bandwidth */
//SFRX(AX5043_PHASEGAIN1_V1,         0x4132)   /* Phase Estimator Bandwidth */
//SFRX(AX5043_PHASEGAIN2_V1,         0x4140)   /* Phase Estimator Bandwidth */
//SFRX(AX5043_PHASEGAIN3_V1,         0x414E)   /* Phase Estimator Bandwidth */
//SFRX(AX5043_PKTADDR0_V1,           0x4203)   /* Packet Address 0 */
//SFRX(AX5043_PKTADDR1_V1,           0x4202)   /* Packet Address 1 */
//SFRX(AX5043_PKTADDRCFG_V1,         0x4201)   /* Packet Address Config */
//SFRX(AX5043_PKTADDRMASK0_V1,       0x4205)   /* Packet Address Mask 0 */
//SFRX(AX5043_PKTADDRMASK1_V1,       0x4204)   /* Packet Address Mask 1 */
//SFRX(AX5043_PKTLENCFG_V1,          0x4206)   /* Packet Length Configuration */
//SFRX(AX5043_PKTLENOFFSET_V1,       0x4207)   /* Packet Length Offset */
//SFRX(AX5043_PKTMAXLEN_V1,          0x4208)   /* Packet Maximum Length */
//SFRX(AX5043_RXPARAMCURSET_V1,      0x4117)   /* Receiver Parameter Current Set */
//SFRX(AX5043_RXPARAMSETS_V1,        0x4116)   /* Receiver Parameter Set Indirection */
//SFRX(AX5043_TIMEGAIN0_V1,          0x4122)   /* Time Estimator Bandwidth */
//SFRX(AX5043_TIMEGAIN1_V1,          0x4130)   /* Time Estimator Bandwidth */
//SFRX(AX5043_TIMEGAIN2_V1,          0x413E)   /* Time Estimator Bandwidth */
//SFRX(AX5043_TIMEGAIN3_V1,          0x414C)   /* Time Estimator Bandwidth */
//
//#define AX5043_AGCGAIN0            AX5043_AGCGAIN0_V1
//#define AX5043_AGCGAIN1            AX5043_AGCGAIN1_V1
//#define AX5043_AGCGAIN2            AX5043_AGCGAIN2_V1
//#define AX5043_AGCGAIN3            AX5043_AGCGAIN3_V1
//#define AX5043_AGCTARGET0          AX5043_AGCTARGET0_V1
//#define AX5043_AGCTARGET1          AX5043_AGCTARGET1_V1
//#define AX5043_AGCTARGET2          AX5043_AGCTARGET2_V1
//#define AX5043_AGCTARGET3          AX5043_AGCTARGET3_V1
//#define AX5043_AMPLITUDEGAIN0      AX5043_AMPLITUDEGAIN0_V1
//#define AX5043_AMPLITUDEGAIN1      AX5043_AMPLITUDEGAIN1_V1
//#define AX5043_AMPLITUDEGAIN2      AX5043_AMPLITUDEGAIN2_V1
//#define AX5043_AMPLITUDEGAIN3      AX5043_AMPLITUDEGAIN3_V1
//#define AX5043_BBOFFSRES0          AX5043_BBOFFSRES0_V1
//#define AX5043_BBOFFSRES1          AX5043_BBOFFSRES1_V1
//#define AX5043_BBOFFSRES2          AX5043_BBOFFSRES2_V1
//#define AX5043_BBOFFSRES3          AX5043_BBOFFSRES3_V1
//#define AX5043_DRGAIN0             AX5043_DRGAIN0_V1
//#define AX5043_DRGAIN1             AX5043_DRGAIN1_V1
//#define AX5043_DRGAIN2             AX5043_DRGAIN2_V1
//#define AX5043_DRGAIN3             AX5043_DRGAIN3_V1
//#define AX5043_FOURFSK0            AX5043_FOURFSK0_V1
//#define AX5043_FOURFSK1            AX5043_FOURFSK1_V1
//#define AX5043_FOURFSK2            AX5043_FOURFSK2_V1
//#define AX5043_FOURFSK3            AX5043_FOURFSK3_V1
//#define AX5043_FREQDEV00           AX5043_FREQDEV00_V1
//#define AX5043_FREQDEV01           AX5043_FREQDEV01_V1
//#define AX5043_FREQDEV02           AX5043_FREQDEV02_V1
//#define AX5043_FREQDEV03           AX5043_FREQDEV03_V1
//#define AX5043_FREQDEV10           AX5043_FREQDEV10_V1
//#define AX5043_FREQDEV11           AX5043_FREQDEV11_V1
//#define AX5043_FREQDEV12           AX5043_FREQDEV12_V1
//#define AX5043_FREQDEV13           AX5043_FREQDEV13_V1
//#define AX5043_FREQUENCYGAINA0     AX5043_FREQUENCYGAINA0_V1
//#define AX5043_FREQUENCYGAINA1     AX5043_FREQUENCYGAINA1_V1
//#define AX5043_FREQUENCYGAINA2     AX5043_FREQUENCYGAINA2_V1
//#define AX5043_FREQUENCYGAINA3     AX5043_FREQUENCYGAINA3_V1
//#define AX5043_FREQUENCYGAINB0     AX5043_FREQUENCYGAINB0_V1
//#define AX5043_FREQUENCYGAINB1     AX5043_FREQUENCYGAINB1_V1
//#define AX5043_FREQUENCYGAINB2     AX5043_FREQUENCYGAINB2_V1
//#define AX5043_FREQUENCYGAINB3     AX5043_FREQUENCYGAINB3_V1
//#define AX5043_FREQUENCYGAINC0     AX5043_FREQUENCYGAINC0_V1
//#define AX5043_FREQUENCYGAINC1     AX5043_FREQUENCYGAINC1_V1
//#define AX5043_FREQUENCYGAINC2     AX5043_FREQUENCYGAINC2_V1
//#define AX5043_FREQUENCYGAINC3     AX5043_FREQUENCYGAINC3_V1
//#define AX5043_FREQUENCYGAIND0     AX5043_FREQUENCYGAIND0_V1
//#define AX5043_FREQUENCYGAIND1     AX5043_FREQUENCYGAIND1_V1
//#define AX5043_FREQUENCYGAIND2     AX5043_FREQUENCYGAIND2_V1
//#define AX5043_FREQUENCYGAIND3     AX5043_FREQUENCYGAIND3_V1
//#define AX5043_PHASEGAIN0          AX5043_PHASEGAIN0_V1
//#define AX5043_PHASEGAIN1          AX5043_PHASEGAIN1_V1
//#define AX5043_PHASEGAIN2          AX5043_PHASEGAIN2_V1
//#define AX5043_PHASEGAIN3          AX5043_PHASEGAIN3_V1
//#define AX5043_PKTADDR0            AX5043_PKTADDR0_V1
//#define AX5043_PKTADDR1            AX5043_PKTADDR1_V1
//#define AX5043_PKTADDRCFG          AX5043_PKTADDRCFG_V1
//#define AX5043_PKTADDRMASK0        AX5043_PKTADDRMASK0_V1
//#define AX5043_PKTADDRMASK1        AX5043_PKTADDRMASK1_V1
//#define AX5043_PKTLENCFG           AX5043_PKTLENCFG_V1
//#define AX5043_PKTLENOFFSET        AX5043_PKTLENOFFSET_V1
//#define AX5043_PKTMAXLEN           AX5043_PKTMAXLEN_V1
//#define AX5043_RXPARAMCURSET       AX5043_RXPARAMCURSET_V1
//#define AX5043_RXPARAMSETS         AX5043_RXPARAMSETS_V1
//#define AX5043_TIMEGAIN0           AX5043_TIMEGAIN0_V1
//#define AX5043_TIMEGAIN1           AX5043_TIMEGAIN1_V1
//#define AX5043_TIMEGAIN2           AX5043_TIMEGAIN2_V1
//#define AX5043_TIMEGAIN3           AX5043_TIMEGAIN3_V1
//#else
//SFRX(AX5043_AGCAHYST0,             0x4122)   /* AGC Analog Hysteresis */
//SFRX(AX5043_AGCAHYST1,             0x4132)   /* AGC Analog Hysteresis */
//SFRX(AX5043_AGCAHYST2,             0x4142)   /* AGC Analog Hysteresis */
//SFRX(AX5043_AGCAHYST3,             0x4152)   /* AGC Analog Hysteresis */
//SFRX(AX5043_AGCGAIN0,              0x4120)   /* AGC Speed */
//SFRX(AX5043_AGCGAIN1,              0x4130)   /* AGC Speed */
//SFRX(AX5043_AGCGAIN2,              0x4140)   /* AGC Speed */
//SFRX(AX5043_AGCGAIN3,              0x4150)   /* AGC Speed */
//SFRX(AX5043_AGCMINMAX0,            0x4123)   /* AGC Analog Update Behaviour */
//SFRX(AX5043_AGCMINMAX1,            0x4133)   /* AGC Analog Update Behaviour */
//SFRX(AX5043_AGCMINMAX2,            0x4143)   /* AGC Analog Update Behaviour */
//SFRX(AX5043_AGCMINMAX3,            0x4153)   /* AGC Analog Update Behaviour */
//SFRX(AX5043_AGCTARGET0,            0x4121)   /* AGC Target */
//SFRX(AX5043_AGCTARGET1,            0x4131)   /* AGC Target */
//SFRX(AX5043_AGCTARGET2,            0x4141)   /* AGC Target */
//SFRX(AX5043_AGCTARGET3,            0x4151)   /* AGC Target */
//SFRX(AX5043_AMPLITUDEGAIN0,        0x412B)   /* Amplitude Estimator Bandwidth */
//SFRX(AX5043_AMPLITUDEGAIN1,        0x413B)   /* Amplitude Estimator Bandwidth */
//SFRX(AX5043_AMPLITUDEGAIN2,        0x414B)   /* Amplitude Estimator Bandwidth */
//SFRX(AX5043_AMPLITUDEGAIN3,        0x415B)   /* Amplitude Estimator Bandwidth */
//SFRX(AX5043_BBOFFSRES0,            0x412F)   /* Baseband Offset Compensation Resistors */
//SFRX(AX5043_BBOFFSRES1,            0x413F)   /* Baseband Offset Compensation Resistors */
//SFRX(AX5043_BBOFFSRES2,            0x414F)   /* Baseband Offset Compensation Resistors */
//SFRX(AX5043_BBOFFSRES3,            0x415F)   /* Baseband Offset Compensation Resistors */
//SFRX(AX5043_DRGAIN0,               0x4125)   /* Data Rate Estimator Bandwidth */
//SFRX(AX5043_DRGAIN1,               0x4135)   /* Data Rate Estimator Bandwidth */
//SFRX(AX5043_DRGAIN2,               0x4145)   /* Data Rate Estimator Bandwidth */
//SFRX(AX5043_DRGAIN3,               0x4155)   /* Data Rate Estimator Bandwidth */
//SFRX(AX5043_FOURFSK0,              0x412E)   /* Four FSK Control */
//SFRX(AX5043_FOURFSK1,              0x413E)   /* Four FSK Control */
//SFRX(AX5043_FOURFSK2,              0x414E)   /* Four FSK Control */
//SFRX(AX5043_FOURFSK3,              0x415E)   /* Four FSK Control */
//SFRX(AX5043_FREQDEV00,             0x412D)   /* Receiver Frequency Deviation 0 */
//SFRX(AX5043_FREQDEV01,             0x413D)   /* Receiver Frequency Deviation 0 */
//SFRX(AX5043_FREQDEV02,             0x414D)   /* Receiver Frequency Deviation 0 */
//SFRX(AX5043_FREQDEV03,             0x415D)   /* Receiver Frequency Deviation 0 */
//SFRX(AX5043_FREQDEV10,             0x412C)   /* Receiver Frequency Deviation 1 */
//SFRX(AX5043_FREQDEV11,             0x413C)   /* Receiver Frequency Deviation 1 */
//SFRX(AX5043_FREQDEV12,             0x414C)   /* Receiver Frequency Deviation 1 */
//SFRX(AX5043_FREQDEV13,             0x415C)   /* Receiver Frequency Deviation 1 */
//SFRX(AX5043_FREQUENCYGAINA0,       0x4127)   /* Frequency Estimator Bandwidth A */
//SFRX(AX5043_FREQUENCYGAINA1,       0x4137)   /* Frequency Estimator Bandwidth A */
//SFRX(AX5043_FREQUENCYGAINA2,       0x4147)   /* Frequency Estimator Bandwidth A */
//SFRX(AX5043_FREQUENCYGAINA3,       0x4157)   /* Frequency Estimator Bandwidth A */
//SFRX(AX5043_FREQUENCYGAINB0,       0x4128)   /* Frequency Estimator Bandwidth B */
//SFRX(AX5043_FREQUENCYGAINB1,       0x4138)   /* Frequency Estimator Bandwidth B */
//SFRX(AX5043_FREQUENCYGAINB2,       0x4148)   /* Frequency Estimator Bandwidth B */
//SFRX(AX5043_FREQUENCYGAINB3,       0x4158)   /* Frequency Estimator Bandwidth B */
//SFRX(AX5043_FREQUENCYGAINC0,       0x4129)   /* Frequency Estimator Bandwidth C */
//SFRX(AX5043_FREQUENCYGAINC1,       0x4139)   /* Frequency Estimator Bandwidth C */
//SFRX(AX5043_FREQUENCYGAINC2,       0x4149)   /* Frequency Estimator Bandwidth C */
//SFRX(AX5043_FREQUENCYGAINC3,       0x4159)   /* Frequency Estimator Bandwidth C */
//SFRX(AX5043_FREQUENCYGAIND0,       0x412A)   /* Frequency Estimator Bandwidth D */
//SFRX(AX5043_FREQUENCYGAIND1,       0x413A)   /* Frequency Estimator Bandwidth D */
//SFRX(AX5043_FREQUENCYGAIND2,       0x414A)   /* Frequency Estimator Bandwidth D */
//SFRX(AX5043_FREQUENCYGAIND3,       0x415A)   /* Frequency Estimator Bandwidth D */
//SFRX(AX5043_FREQUENCYLEAK,         0x4116)   /* Baseband Frequency Recovery Loop Leakiness */
//SFRX(AX5043_PHASEGAIN0,            0x4126)   /* Phase Estimator Bandwidth */
//SFRX(AX5043_PHASEGAIN1,            0x4136)   /* Phase Estimator Bandwidth */
//SFRX(AX5043_PHASEGAIN2,            0x4146)   /* Phase Estimator Bandwidth */
//SFRX(AX5043_PHASEGAIN3,            0x4156)   /* Phase Estimator Bandwidth */
//SFRX(AX5043_PKTADDR0,              0x4207)   /* Packet Address 0 */
//SFRX(AX5043_PKTADDR1,              0x4206)   /* Packet Address 1 */
//SFRX(AX5043_PKTADDR2,              0x4205)   /* Packet Address 2 */
//SFRX(AX5043_PKTADDR3,              0x4204)   /* Packet Address 3 */
//SFRX(AX5043_PKTADDRCFG,            0x4200)   /* Packet Address Config */
//SFRX(AX5043_PKTADDRMASK0,          0x420B)   /* Packet Address Mask 0 */
//SFRX(AX5043_PKTADDRMASK1,          0x420A)   /* Packet Address Mask 1 */
//SFRX(AX5043_PKTADDRMASK2,          0x4209)   /* Packet Address Mask 2 */
//SFRX(AX5043_PKTADDRMASK3,          0x4208)   /* Packet Address Mask 3 */
//SFRX(AX5043_PKTLENCFG,             0x4201)   /* Packet Length Configuration */
//SFRX(AX5043_PKTLENOFFSET,          0x4202)   /* Packet Length Offset */
//SFRX(AX5043_PKTMAXLEN,             0x4203)   /* Packet Maximum Length */
//SFRX(AX5043_RXPARAMCURSET,         0x4118)   /* Receiver Parameter Current Set */
//SFRX(AX5043_RXPARAMSETS,           0x4117)   /* Receiver Parameter Set Indirection */
//SFRX(AX5043_TIMEGAIN0,             0x4124)   /* Time Estimator Bandwidth */
//SFRX(AX5043_TIMEGAIN1,             0x4134)   /* Time Estimator Bandwidth */
//SFRX(AX5043_TIMEGAIN2,             0x4144)   /* Time Estimator Bandwidth */
//SFRX(AX5043_TIMEGAIN3,             0x4154)   /* Time Estimator Bandwidth */
//#endif
//
///* Radio Registers, X Address Space, Non-Blocking Version */
//
//#if !defined AX5043_DISABLE_NONBLOCKING
//SFRX(AX5043_AFSKCTRLNB,            0x5114)   /* AFSK Control, Non-Blocking */
//SFRX(AX5043_AFSKMARK0NB,           0x5113)   /* AFSK Mark (1) Frequency 0, Non-Blocking */
//SFRX(AX5043_AFSKMARK1NB,           0x5112)   /* AFSK Mark (1) Frequency 1, Non-Blocking */
//SFRX(AX5043_AFSKSPACE0NB,          0x5111)   /* AFSK Space (0) Frequency 0, Non-Blocking */
//SFRX(AX5043_AFSKSPACE1NB,          0x5110)   /* AFSK Space (0) Frequency 1, Non-Blocking */
//SFRX(AX5043_AGCCOUNTERNB,          0x5043)   /* AGC Counter, Non-Blocking */
//SFRX(AX5043_AMPLFILTERNB,          0x5115)   /* Amplitude Filter, Non-Blocking */
//SFRX(AX5043_BBOFFSCAPNB,           0x5189)   /* Baseband Offset Compensation Capacitors, Non-Blocking */
//SFRX(AX5043_BBTUNENB,              0x5188)   /* Baseband Tuning, Non-Blocking */
//SFRX(AX5043_BGNDRSSINB,            0x5041)   /* Background RSSI, Non-Blocking */
//SFRX(AX5043_BGNDRSSIGAINNB,        0x522E)   /* Background RSSI Averaging Time Constant, Non-Blocking */
//SFRX(AX5043_BGNDRSSITHRNB,         0x522F)   /* Background RSSI Relative Threshold, Non-Blocking */
//SFRX(AX5043_CRCINIT0NB,            0x5017)   /* CRC Initial Value 0, Non-Blocking */
//SFRX(AX5043_CRCINIT1NB,            0x5016)   /* CRC Initial Value 1, Non-Blocking */
//SFRX(AX5043_CRCINIT2NB,            0x5015)   /* CRC Initial Value 2, Non-Blocking */
//SFRX(AX5043_CRCINIT3NB,            0x5014)   /* CRC Initial Value 3, Non-Blocking */
//SFRX(AX5043_DACCONFIGNB,           0x5332)   /* DAC Configuration, Non-Blocking */
//SFRX(AX5043_DACVALUE0NB,           0x5331)   /* DAC Value 0, Non-Blocking */
//SFRX(AX5043_DACVALUE1NB,           0x5330)   /* DAC Value 1, Non-Blocking */
//SFRX(AX5043_DECIMATIONNB,          0x5102)   /* Decimation Factor , Non-Blocking */
//SFRX(AX5043_DIVERSITYNB,           0x5042)   /* Antenna Diversity Configuration, Non-Blocking */
//SFRX(AX5043_ENCODINGNB,            0x5011)   /* Encoding, Non-Blocking */
//SFRX(AX5043_FECNB,                 0x5018)   /* Forward Error Correction, Non-Blocking */
//SFRX(AX5043_FECSTATUSNB,           0x501A)   /* Forward Error Correction Status, Non-Blocking */
//SFRX(AX5043_FECSYNCNB,             0x5019)   /* Forward Error Correction Sync Threshold, Non-Blocking */
//SFRX(AX5043_FIFOCOUNT0NB,          0x502B)   /* Number of Words currently in FIFO 0, Non-Blocking */
//SFRX(AX5043_FIFOCOUNT1NB,          0x502A)   /* Number of Words currently in FIFO 1, Non-Blocking */
//SFRX(AX5043_FIFODATANB,            0x5029)   /* FIFO Data, Non-Blocking */
//SFRX(AX5043_FIFOFREE0NB,           0x502D)   /* Number of Words that can be written to FIFO 0, Non-Blocking */
//SFRX(AX5043_FIFOFREE1NB,           0x502C)   /* Number of Words that can be written to FIFO 1, Non-Blocking */
//SFRX(AX5043_FIFOSTATNB,            0x5028)   /* FIFO Control, Non-Blocking */
//SFRX(AX5043_FIFOTHRESH0NB,         0x502F)   /* FIFO Threshold 0, Non-Blocking */
//SFRX(AX5043_FIFOTHRESH1NB,         0x502E)   /* FIFO Threshold 1, Non-Blocking */
//SFRX(AX5043_FRAMINGNB,             0x5012)   /* Framing Mode, Non-Blocking */
//SFRX(AX5043_FREQA0NB,              0x5037)   /* Frequency A 0, Non-Blocking */
//SFRX(AX5043_FREQA1NB,              0x5036)   /* Frequency A 1, Non-Blocking */
//SFRX(AX5043_FREQA2NB,              0x5035)   /* Frequency A 2, Non-Blocking */
//SFRX(AX5043_FREQA3NB,              0x5034)   /* Frequency A 3, Non-Blocking */
//SFRX(AX5043_FREQB0NB,              0x503F)   /* Frequency B 0, Non-Blocking */
//SFRX(AX5043_FREQB1NB,              0x503E)   /* Frequency B 1, Non-Blocking */
//SFRX(AX5043_FREQB2NB,              0x503D)   /* Frequency B 2, Non-Blocking */
//SFRX(AX5043_FREQB3NB,              0x503C)   /* Frequency B 3, Non-Blocking */
//SFRX(AX5043_FSKDEV0NB,             0x5163)   /* FSK Deviation 0, Non-Blocking */
//SFRX(AX5043_FSKDEV1NB,             0x5162)   /* FSK Deviation 1, Non-Blocking */
//SFRX(AX5043_FSKDEV2NB,             0x5161)   /* FSK Deviation 2, Non-Blocking */
//SFRX(AX5043_FSKDMAX0NB,            0x510D)   /* Four FSK Rx Maximum Deviation 0, Non-Blocking */
//SFRX(AX5043_FSKDMAX1NB,            0x510C)   /* Four FSK Rx Maximum Deviation 1, Non-Blocking */
//SFRX(AX5043_FSKDMIN0NB,            0x510F)   /* Four FSK Rx Minimum Deviation 0, Non-Blocking */
//SFRX(AX5043_FSKDMIN1NB,            0x510E)   /* Four FSK Rx Minimum Deviation 1, Non-Blocking */
//SFRX(AX5043_GPADC13VALUE0NB,       0x5309)   /* GPADC13 Value 0, Non-Blocking */
//SFRX(AX5043_GPADC13VALUE1NB,       0x5308)   /* GPADC13 Value 1, Non-Blocking */
//SFRX(AX5043_GPADCCTRLNB,           0x5300)   /* General Purpose ADC Control, Non-Blocking */
//SFRX(AX5043_GPADCPERIODNB,         0x5301)   /* GPADC Sampling Period, Non-Blocking */
//SFRX(AX5043_IFFREQ0NB,             0x5101)   /* 2nd LO / IF Frequency 0, Non-Blocking */
//SFRX(AX5043_IFFREQ1NB,             0x5100)   /* 2nd LO / IF Frequency 1, Non-Blocking */
//SFRX(AX5043_IRQINVERSION0NB,       0x500B)   /* IRQ Inversion 0, Non-Blocking */
//SFRX(AX5043_IRQINVERSION1NB,       0x500A)   /* IRQ Inversion 1, Non-Blocking */
//SFRX(AX5043_IRQMASK0NB,            0x5007)   /* IRQ Mask 0, Non-Blocking */
//SFRX(AX5043_IRQMASK1NB,            0x5006)   /* IRQ Mask 1, Non-Blocking */
//SFRX(AX5043_IRQREQUEST0NB,         0x500D)   /* IRQ Request 0, Non-Blocking */
//SFRX(AX5043_IRQREQUEST1NB,         0x500C)   /* IRQ Request 1, Non-Blocking */
//SFRX(AX5043_LPOSCCONFIGNB,         0x5310)   /* Low Power Oscillator Calibration Configuration, Non-Blocking */
//SFRX(AX5043_LPOSCFREQ0NB,          0x5317)   /* Low Power Oscillator Frequency Tuning Low Byte, Non-Blocking */
//SFRX(AX5043_LPOSCFREQ1NB,          0x5316)   /* Low Power Oscillator Frequency Tuning High Byte, Non-Blocking */
//SFRX(AX5043_LPOSCKFILT0NB,         0x5313)   /* Low Power Oscillator Calibration Filter Constant Low Byte, Non-Blocking */
//SFRX(AX5043_LPOSCKFILT1NB,         0x5312)   /* Low Power Oscillator Calibration Filter Constant High Byte, Non-Blocking */
//SFRX(AX5043_LPOSCPER0NB,           0x5319)   /* Low Power Oscillator Period Low Byte, Non-Blocking */
//SFRX(AX5043_LPOSCPER1NB,           0x5318)   /* Low Power Oscillator Period High Byte, Non-Blocking */
//SFRX(AX5043_LPOSCREF0NB,           0x5315)   /* Low Power Oscillator Reference Frequency Low Byte, Non-Blocking */
//SFRX(AX5043_LPOSCREF1NB,           0x5314)   /* Low Power Oscillator Reference Frequency High Byte, Non-Blocking */
//SFRX(AX5043_LPOSCSTATUSNB,         0x5311)   /* Low Power Oscillator Calibration Status, Non-Blocking */
//SFRX(AX5043_MATCH0LENNB,           0x5214)   /* Pattern Match Unit 0, Pattern Length, Non-Blocking */
//SFRX(AX5043_MATCH0MAXNB,           0x5216)   /* Pattern Match Unit 0, Maximum Match, Non-Blocking */
//SFRX(AX5043_MATCH0MINNB,           0x5215)   /* Pattern Match Unit 0, Minimum Match, Non-Blocking */
//SFRX(AX5043_MATCH0PAT0NB,          0x5213)   /* Pattern Match Unit 0, Pattern 0, Non-Blocking */
//SFRX(AX5043_MATCH0PAT1NB,          0x5212)   /* Pattern Match Unit 0, Pattern 1, Non-Blocking */
//SFRX(AX5043_MATCH0PAT2NB,          0x5211)   /* Pattern Match Unit 0, Pattern 2, Non-Blocking */
//SFRX(AX5043_MATCH0PAT3NB,          0x5210)   /* Pattern Match Unit 0, Pattern 3, Non-Blocking */
//SFRX(AX5043_MATCH1LENNB,           0x521C)   /* Pattern Match Unit 1, Pattern Length, Non-Blocking */
//SFRX(AX5043_MATCH1MAXNB,           0x521E)   /* Pattern Match Unit 1, Maximum Match, Non-Blocking */
//SFRX(AX5043_MATCH1MINNB,           0x521D)   /* Pattern Match Unit 1, Minimum Match, Non-Blocking */
//SFRX(AX5043_MATCH1PAT0NB,          0x5219)   /* Pattern Match Unit 1, Pattern 0, Non-Blocking */
//SFRX(AX5043_MATCH1PAT1NB,          0x5218)   /* Pattern Match Unit 1, Pattern 1, Non-Blocking */
//SFRX(AX5043_MAXDROFFSET0NB,        0x5108)   /* Maximum Receiver Datarate Offset 0, Non-Blocking */
//SFRX(AX5043_MAXDROFFSET1NB,        0x5107)   /* Maximum Receiver Datarate Offset 1, Non-Blocking */
//SFRX(AX5043_MAXDROFFSET2NB,        0x5106)   /* Maximum Receiver Datarate Offset 2, Non-Blocking */
//SFRX(AX5043_MAXRFOFFSET0NB,        0x510B)   /* Maximum Receiver RF Offset 0, Non-Blocking */
//SFRX(AX5043_MAXRFOFFSET1NB,        0x510A)   /* Maximum Receiver RF Offset 1, Non-Blocking */
//SFRX(AX5043_MAXRFOFFSET2NB,        0x5109)   /* Maximum Receiver RF Offset 2, Non-Blocking */
//SFRX(AX5043_MODCFGANB,             0x5164)   /* Modulator Configuration A, Non-Blocking */
//SFRX(AX5043_MODCFGFNB,             0x5160)   /* Modulator Configuration F, Non-Blocking */
//SFRX(AX5043_MODCFGPNB,             0x5F5F)   /* Modulator Configuration P, Non-Blocking */
//SFRX(AX5043_MODULATIONNB,          0x5010)   /* Modulation, Non-Blocking */
//SFRX(AX5043_PINFUNCANTSELNB,       0x5025)   /* Pin Function ANTSEL, Non-Blocking */
//SFRX(AX5043_PINFUNCDATANB,         0x5023)   /* Pin Function DATA, Non-Blocking */
//SFRX(AX5043_PINFUNCDCLKNB,         0x5022)   /* Pin Function DCLK, Non-Blocking */
//SFRX(AX5043_PINFUNCIRQNB,          0x5024)   /* Pin Function IRQ, Non-Blocking */
//SFRX(AX5043_PINFUNCPWRAMPNB,       0x5026)   /* Pin Function PWRAMP, Non-Blocking */
//SFRX(AX5043_PINFUNCSYSCLKNB,       0x5021)   /* Pin Function SYSCLK, Non-Blocking */
//SFRX(AX5043_PINSTATENB,            0x5020)   /* Pin State, Non-Blocking */
//SFRX(AX5043_PKTACCEPTFLAGSNB,      0x5233)   /* Packet Controller Accept Flags, Non-Blocking */
//SFRX(AX5043_PKTCHUNKSIZENB,        0x5230)   /* Packet Chunk Size, Non-Blocking */
//SFRX(AX5043_PKTMISCFLAGSNB,        0x5231)   /* Packet Controller Miscellaneous Flags, Non-Blocking */
//SFRX(AX5043_PKTSTOREFLAGSNB,       0x5232)   /* Packet Controller Store Flags, Non-Blocking */
//SFRX(AX5043_PLLCPINB,              0x5031)   /* PLL Charge Pump Current, Non-Blocking */
//SFRX(AX5043_PLLCPIBOOSTNB,         0x5039)   /* PLL Charge Pump Current (Boosted), Non-Blocking */
//SFRX(AX5043_PLLLOCKDETNB,          0x5182)   /* PLL Lock Detect Delay, Non-Blocking */
//SFRX(AX5043_PLLLOOPNB,             0x5030)   /* PLL Loop Filter Settings, Non-Blocking */
//SFRX(AX5043_PLLLOOPBOOSTNB,        0x5038)   /* PLL Loop Filter Settings (Boosted), Non-Blocking */
//SFRX(AX5043_PLLRANGINGANB,         0x5033)   /* PLL Autoranging A, Non-Blocking */
//SFRX(AX5043_PLLRANGINGBNB,         0x503B)   /* PLL Autoranging B, Non-Blocking */
//SFRX(AX5043_PLLRNGCLKNB,           0x5183)   /* PLL Autoranging Clock, Non-Blocking */
//SFRX(AX5043_PLLVCODIVNB,           0x5032)   /* PLL Divider Settings, Non-Blocking */
//SFRX(AX5043_PLLVCOINB,             0x5180)   /* PLL VCO Current, Non-Blocking */
//SFRX(AX5043_PLLVCOIRNB,            0x5181)   /* PLL VCO Current Readback, Non-Blocking */
//SFRX(AX5043_POWCTRL1NB,            0x5F08)   /* Power Control 1, Non-Blocking */
//SFRX(AX5043_POWIRQMASKNB,          0x5005)   /* Power Management Interrupt Mask, Non-Blocking */
//SFRX(AX5043_POWSTATNB,             0x5003)   /* Power Management Status, Non-Blocking */
//SFRX(AX5043_POWSTICKYSTATNB,       0x5004)   /* Power Management Sticky Status, Non-Blocking */
//SFRX(AX5043_PWRAMPNB,              0x5027)   /* PWRAMP Control, Non-Blocking */
//SFRX(AX5043_PWRMODENB,             0x5002)   /* Power Mode, Non-Blocking */
//SFRX(AX5043_RADIOEVENTMASK0NB,     0x5009)   /* Radio Event Mask 0, Non-Blocking */
//SFRX(AX5043_RADIOEVENTMASK1NB,     0x5008)   /* Radio Event Mask 1, Non-Blocking */
//SFRX(AX5043_RADIOEVENTREQ0NB,      0x500F)   /* Radio Event Request 0, Non-Blocking */
//SFRX(AX5043_RADIOEVENTREQ1NB,      0x500E)   /* Radio Event Request 1, Non-Blocking */
//SFRX(AX5043_RADIOSTATENB,          0x501C)   /* Radio Controller State, Non-Blocking */
//SFRX(AX5043_REFNB,                 0x5F0D)   /* Reference, Non-Blocking */
//SFRX(AX5043_RSSINB,                0x5040)   /* Received Signal Strength Indicator, Non-Blocking */
//SFRX(AX5043_RSSIABSTHRNB,          0x522D)   /* RSSI Absolute Threshold, Non-Blocking */
//SFRX(AX5043_RSSIREFERENCENB,       0x522C)   /* RSSI Offset, Non-Blocking */
//SFRX(AX5043_RXDATARATE0NB,         0x5105)   /* Receiver Datarate 0, Non-Blocking */
//SFRX(AX5043_RXDATARATE1NB,         0x5104)   /* Receiver Datarate 1, Non-Blocking */
//SFRX(AX5043_RXDATARATE2NB,         0x5103)   /* Receiver Datarate 2, Non-Blocking */
//SFRX(AX5043_SCRATCHNB,             0x5001)   /* Scratch, Non-Blocking */
//SFRX(AX5043_SILICONREVISIONNB,     0x5000)   /* Silicon Revision, Non-Blocking */
//SFRX(AX5043_TIMER0NB,              0x505B)   /* 1MHz Timer 0, Non-Blocking */
//SFRX(AX5043_TIMER1NB,              0x505A)   /* 1MHz Timer 1, Non-Blocking */
//SFRX(AX5043_TIMER2NB,              0x5059)   /* 1MHz Timer 2, Non-Blocking */
//SFRX(AX5043_TMGRXAGCNB,            0x5227)   /* Receiver AGC Settling Time, Non-Blocking */
//SFRX(AX5043_TMGRXBOOSTNB,          0x5223)   /* Receive PLL Boost Time, Non-Blocking */
//SFRX(AX5043_TMGRXCOARSEAGCNB,      0x5226)   /* Receive Coarse AGC Time, Non-Blocking */
//SFRX(AX5043_TMGRXOFFSACQNB,        0x5225)   /* Receive Baseband DC Offset Acquisition Time, Non-Blocking */
//SFRX(AX5043_TMGRXPREAMBLE1NB,      0x5229)   /* Receiver Preamble 1 Timeout, Non-Blocking */
//SFRX(AX5043_TMGRXPREAMBLE2NB,      0x522A)   /* Receiver Preamble 2 Timeout, Non-Blocking */
//SFRX(AX5043_TMGRXPREAMBLE3NB,      0x522B)   /* Receiver Preamble 3 Timeout, Non-Blocking */
//SFRX(AX5043_TMGRXRSSINB,           0x5228)   /* Receiver RSSI Settling Time, Non-Blocking */
//SFRX(AX5043_TMGRXSETTLENB,         0x5224)   /* Receive PLL (post Boost) Settling Time, Non-Blocking */
//SFRX(AX5043_TMGTXBOOSTNB,          0x5220)   /* Transmit PLL Boost Time, Non-Blocking */
//SFRX(AX5043_TMGTXSETTLENB,         0x5221)   /* Transmit PLL (post Boost) Settling Time, Non-Blocking */
//SFRX(AX5043_TRKAFSKDEMOD0NB,       0x5055)   /* AFSK Demodulator Tracking 0, Non-Blocking */
//SFRX(AX5043_TRKAFSKDEMOD1NB,       0x5054)   /* AFSK Demodulator Tracking 1, Non-Blocking */
//SFRX(AX5043_TRKAMPLITUDE0NB,       0x5049)   /* Amplitude Tracking 0, Non-Blocking */
//SFRX(AX5043_TRKAMPLITUDE1NB,       0x5048)   /* Amplitude Tracking 1, Non-Blocking */
//SFRX(AX5043_TRKDATARATE0NB,        0x5047)   /* Datarate Tracking 0, Non-Blocking */
//SFRX(AX5043_TRKDATARATE1NB,        0x5046)   /* Datarate Tracking 1, Non-Blocking */
//SFRX(AX5043_TRKDATARATE2NB,        0x5045)   /* Datarate Tracking 2, Non-Blocking */
//SFRX(AX5043_TRKFREQ0NB,            0x5051)   /* Frequency Tracking 0, Non-Blocking */
//SFRX(AX5043_TRKFREQ1NB,            0x5050)   /* Frequency Tracking 1, Non-Blocking */
//SFRX(AX5043_TRKFSKDEMOD0NB,        0x5053)   /* FSK Demodulator Tracking 0, Non-Blocking */
//SFRX(AX5043_TRKFSKDEMOD1NB,        0x5052)   /* FSK Demodulator Tracking 1, Non-Blocking */
//SFRX(AX5043_TRKPHASE0NB,           0x504B)   /* Phase Tracking 0, Non-Blocking */
//SFRX(AX5043_TRKPHASE1NB,           0x504A)   /* Phase Tracking 1, Non-Blocking */
//SFRX(AX5043_TRKRFFREQ0NB,          0x504F)   /* RF Frequency Tracking 0, Non-Blocking */
//SFRX(AX5043_TRKRFFREQ1NB,          0x504E)   /* RF Frequency Tracking 1, Non-Blocking */
//SFRX(AX5043_TRKRFFREQ2NB,          0x504D)   /* RF Frequency Tracking 2, Non-Blocking */
//SFRX(AX5043_TXPWRCOEFFA0NB,        0x5169)   /* Transmitter Predistortion Coefficient A 0, Non-Blocking */
//SFRX(AX5043_TXPWRCOEFFA1NB,        0x5168)   /* Transmitter Predistortion Coefficient A 1, Non-Blocking */
//SFRX(AX5043_TXPWRCOEFFB0NB,        0x516B)   /* Transmitter Predistortion Coefficient B 0, Non-Blocking */
//SFRX(AX5043_TXPWRCOEFFB1NB,        0x516A)   /* Transmitter Predistortion Coefficient B 1, Non-Blocking */
//SFRX(AX5043_TXPWRCOEFFC0NB,        0x516D)   /* Transmitter Predistortion Coefficient C 0, Non-Blocking */
//SFRX(AX5043_TXPWRCOEFFC1NB,        0x516C)   /* Transmitter Predistortion Coefficient C 1, Non-Blocking */
//SFRX(AX5043_TXPWRCOEFFD0NB,        0x516F)   /* Transmitter Predistortion Coefficient D 0, Non-Blocking */
//SFRX(AX5043_TXPWRCOEFFD1NB,        0x516E)   /* Transmitter Predistortion Coefficient D 1, Non-Blocking */
//SFRX(AX5043_TXPWRCOEFFE0NB,        0x5171)   /* Transmitter Predistortion Coefficient E 0, Non-Blocking */
//SFRX(AX5043_TXPWRCOEFFE1NB,        0x5170)   /* Transmitter Predistortion Coefficient E 1, Non-Blocking */
//SFRX(AX5043_TXRATE0NB,             0x5167)   /* Transmitter Bitrate 0, Non-Blocking */
//SFRX(AX5043_TXRATE1NB,             0x5166)   /* Transmitter Bitrate 1, Non-Blocking */
//SFRX(AX5043_TXRATE2NB,             0x5165)   /* Transmitter Bitrate 2, Non-Blocking */
//SFRX(AX5043_WAKEUP0NB,             0x506B)   /* Wakeup Time 0, Non-Blocking */
//SFRX(AX5043_WAKEUP1NB,             0x506A)   /* Wakeup Time 1, Non-Blocking */
//SFRX(AX5043_WAKEUPFREQ0NB,         0x506D)   /* Wakeup Frequency 0, Non-Blocking */
//SFRX(AX5043_WAKEUPFREQ1NB,         0x506C)   /* Wakeup Frequency 1, Non-Blocking */
//SFRX(AX5043_WAKEUPTIMER0NB,        0x5069)   /* Wakeup Timer 0, Non-Blocking */
//SFRX(AX5043_WAKEUPTIMER1NB,        0x5068)   /* Wakeup Timer 1, Non-Blocking */
//SFRX(AX5043_WAKEUPXOEARLYNB,       0x506E)   /* Wakeup Crystal Oscillator Early, Non-Blocking */
//SFRX(AX5043_XTALAMPLNB,            0x5F11)   /* Crystal Oscillator Amplitude Control, Non-Blocking */
//SFRX(AX5043_XTALCAPNB,             0x5184)   /* Crystal Oscillator Load Capacitance, Non-Blocking */
//SFRX(AX5043_XTALOSCNB,             0x5F10)   /* Crystal Oscillator Control, Non-Blocking */
//SFRX(AX5043_XTALSTATUSNB,          0x501D)   /* Crystal Oscillator Status, Non-Blocking */
//
//SFRX(AX5043_0xF00NB,               0x5F00)
//SFRX(AX5043_0xF0CNB,               0x5F0C)
//SFRX(AX5043_0xF18NB,               0x5F18)
//SFRX(AX5043_0xF1CNB,               0x5F1C)
//SFRX(AX5043_0xF21NB,               0x5F21)
//SFRX(AX5043_0xF22NB,               0x5F22)
//SFRX(AX5043_0xF23NB,               0x5F23)
//SFRX(AX5043_0xF26NB,               0x5F26)
//SFRX(AX5043_0xF30NB,               0x5F30)
//SFRX(AX5043_0xF31NB,               0x5F31)
//SFRX(AX5043_0xF32NB,               0x5F32)
//SFRX(AX5043_0xF33NB,               0x5F33)
//SFRX(AX5043_0xF34NB,               0x5F34)
//SFRX(AX5043_0xF35NB,               0x5F35)
//SFRX(AX5043_0xF44NB,               0x5F44)
//
//#if defined AX5043V1
//SFRX(AX5043_AGCGAIN0NB_V1,         0x5120)   /* AGC Speed, Non-Blocking */
//SFRX(AX5043_AGCGAIN1NB_V1,         0x512E)   /* AGC Speed, Non-Blocking */
//SFRX(AX5043_AGCGAIN2NB_V1,         0x513C)   /* AGC Speed, Non-Blocking */
//SFRX(AX5043_AGCGAIN3NB_V1,         0x514A)   /* AGC Speed, Non-Blocking */
//SFRX(AX5043_AGCTARGET0NB_V1,       0x5121)   /* AGC Target, Non-Blocking */
//SFRX(AX5043_AGCTARGET1NB_V1,       0x512F)   /* AGC Target, Non-Blocking */
//SFRX(AX5043_AGCTARGET2NB_V1,       0x513D)   /* AGC Target, Non-Blocking */
//SFRX(AX5043_AGCTARGET3NB_V1,       0x514B)   /* AGC Target, Non-Blocking */
//SFRX(AX5043_AMPLITUDEGAIN0NB_V1,   0x5129)   /* Amplitude Estimator Bandwidth, Non-Blocking */
//SFRX(AX5043_AMPLITUDEGAIN1NB_V1,   0x5137)   /* Amplitude Estimator Bandwidth, Non-Blocking */
//SFRX(AX5043_AMPLITUDEGAIN2NB_V1,   0x5145)   /* Amplitude Estimator Bandwidth, Non-Blocking */
//SFRX(AX5043_AMPLITUDEGAIN3NB_V1,   0x5153)   /* Amplitude Estimator Bandwidth, Non-Blocking */
//SFRX(AX5043_BBOFFSRES0NB_V1,       0x512D)   /* Baseband Offset Compensation Resistors, Non-Blocking */
//SFRX(AX5043_BBOFFSRES1NB_V1,       0x513B)   /* Baseband Offset Compensation Resistors, Non-Blocking */
//SFRX(AX5043_BBOFFSRES2NB_V1,       0x5149)   /* Baseband Offset Compensation Resistors, Non-Blocking */
//SFRX(AX5043_BBOFFSRES3NB_V1,       0x5157)   /* Baseband Offset Compensation Resistors, Non-Blocking */
//SFRX(AX5043_DRGAIN0NB_V1,          0x5123)   /* Data Rate Estimator Bandwidth, Non-Blocking */
//SFRX(AX5043_DRGAIN1NB_V1,          0x5131)   /* Data Rate Estimator Bandwidth, Non-Blocking */
//SFRX(AX5043_DRGAIN2NB_V1,          0x513F)   /* Data Rate Estimator Bandwidth, Non-Blocking */
//SFRX(AX5043_DRGAIN3NB_V1,          0x514D)   /* Data Rate Estimator Bandwidth, Non-Blocking */
//SFRX(AX5043_FOURFSK0NB_V1,         0x512C)   /* Four FSK Control, Non-Blocking */
//SFRX(AX5043_FOURFSK1NB_V1,         0x513A)   /* Four FSK Control, Non-Blocking */
//SFRX(AX5043_FOURFSK2NB_V1,         0x5148)   /* Four FSK Control, Non-Blocking */
//SFRX(AX5043_FOURFSK3NB_V1,         0x5156)   /* Four FSK Control, Non-Blocking */
//SFRX(AX5043_FREQDEV00NB_V1,        0x512B)   /* Receiver Frequency Deviation 0, Non-Blocking */
//SFRX(AX5043_FREQDEV01NB_V1,        0x5139)   /* Receiver Frequency Deviation 0, Non-Blocking */
//SFRX(AX5043_FREQDEV02NB_V1,        0x5147)   /* Receiver Frequency Deviation 0, Non-Blocking */
//SFRX(AX5043_FREQDEV03NB_V1,        0x5155)   /* Receiver Frequency Deviation 0, Non-Blocking */
//SFRX(AX5043_FREQDEV10NB_V1,        0x512A)   /* Receiver Frequency Deviation 1, Non-Blocking */
//SFRX(AX5043_FREQDEV11NB_V1,        0x5138)   /* Receiver Frequency Deviation 1, Non-Blocking */
//SFRX(AX5043_FREQDEV12NB_V1,        0x5146)   /* Receiver Frequency Deviation 1, Non-Blocking */
//SFRX(AX5043_FREQDEV13NB_V1,        0x5154)   /* Receiver Frequency Deviation 1, Non-Blocking */
//SFRX(AX5043_FREQUENCYGAINA0NB_V1,  0x5125)   /* Frequency Estimator Bandwidth A, Non-Blocking */
//SFRX(AX5043_FREQUENCYGAINA1NB_V1,  0x5133)   /* Frequency Estimator Bandwidth A, Non-Blocking */
//SFRX(AX5043_FREQUENCYGAINA2NB_V1,  0x5141)   /* Frequency Estimator Bandwidth A, Non-Blocking */
//SFRX(AX5043_FREQUENCYGAINA3NB_V1,  0x514F)   /* Frequency Estimator Bandwidth A, Non-Blocking */
//SFRX(AX5043_FREQUENCYGAINB0NB_V1,  0x5126)   /* Frequency Estimator Bandwidth B, Non-Blocking */
//SFRX(AX5043_FREQUENCYGAINB1NB_V1,  0x5134)   /* Frequency Estimator Bandwidth B, Non-Blocking */
//SFRX(AX5043_FREQUENCYGAINB2NB_V1,  0x5142)   /* Frequency Estimator Bandwidth B, Non-Blocking */
//SFRX(AX5043_FREQUENCYGAINB3NB_V1,  0x5150)   /* Frequency Estimator Bandwidth B, Non-Blocking */
//SFRX(AX5043_FREQUENCYGAINC0NB_V1,  0x5127)   /* Frequency Estimator Bandwidth C, Non-Blocking */
//SFRX(AX5043_FREQUENCYGAINC1NB_V1,  0x5135)   /* Frequency Estimator Bandwidth C, Non-Blocking */
//SFRX(AX5043_FREQUENCYGAINC2NB_V1,  0x5143)   /* Frequency Estimator Bandwidth C, Non-Blocking */
//SFRX(AX5043_FREQUENCYGAINC3NB_V1,  0x5151)   /* Frequency Estimator Bandwidth C, Non-Blocking */
//SFRX(AX5043_FREQUENCYGAIND0NB_V1,  0x5128)   /* Frequency Estimator Bandwidth D, Non-Blocking */
//SFRX(AX5043_FREQUENCYGAIND1NB_V1,  0x5136)   /* Frequency Estimator Bandwidth D, Non-Blocking */
//SFRX(AX5043_FREQUENCYGAIND2NB_V1,  0x5144)   /* Frequency Estimator Bandwidth D, Non-Blocking */
//SFRX(AX5043_FREQUENCYGAIND3NB_V1,  0x5152)   /* Frequency Estimator Bandwidth D, Non-Blocking */
//SFRX(AX5043_PHASEGAIN0NB_V1,       0x5124)   /* Phase Estimator Bandwidth, Non-Blocking */
//SFRX(AX5043_PHASEGAIN1NB_V1,       0x5132)   /* Phase Estimator Bandwidth, Non-Blocking */
//SFRX(AX5043_PHASEGAIN2NB_V1,       0x5140)   /* Phase Estimator Bandwidth, Non-Blocking */
//SFRX(AX5043_PHASEGAIN3NB_V1,       0x514E)   /* Phase Estimator Bandwidth, Non-Blocking */
//SFRX(AX5043_PKTADDR0NB_V1,         0x5203)   /* Packet Address 0, Non-Blocking */
//SFRX(AX5043_PKTADDR1NB_V1,         0x5202)   /* Packet Address 1, Non-Blocking */
//SFRX(AX5043_PKTADDRCFGNB_V1,       0x5201)   /* Packet Address Config, Non-Blocking */
//SFRX(AX5043_PKTADDRMASK0NB_V1,     0x5205)   /* Packet Address Mask 0, Non-Blocking */
//SFRX(AX5043_PKTADDRMASK1NB_V1,     0x5204)   /* Packet Address Mask 1, Non-Blocking */
//SFRX(AX5043_PKTLENCFGNB_V1,        0x5206)   /* Packet Length Configuration, Non-Blocking */
//SFRX(AX5043_PKTLENOFFSETNB_V1,     0x5207)   /* Packet Length Offset, Non-Blocking */
//SFRX(AX5043_PKTMAXLENNB_V1,        0x5208)   /* Packet Maximum Length, Non-Blocking */
//SFRX(AX5043_RXPARAMCURSETNB_V1,    0x5117)   /* Receiver Parameter Current Set, Non-Blocking */
//SFRX(AX5043_RXPARAMSETSNB_V1,      0x5116)   /* Receiver Parameter Set Indirection, Non-Blocking */
//SFRX(AX5043_TIMEGAIN0NB_V1,        0x5122)   /* Time Estimator Bandwidth, Non-Blocking */
//SFRX(AX5043_TIMEGAIN1NB_V1,        0x5130)   /* Time Estimator Bandwidth, Non-Blocking */
//SFRX(AX5043_TIMEGAIN2NB_V1,        0x513E)   /* Time Estimator Bandwidth, Non-Blocking */
//SFRX(AX5043_TIMEGAIN3NB_V1,        0x514C)   /* Time Estimator Bandwidth, Non-Blocking */
//
//#define AX5043_AGCGAIN0NB          AX5043_AGCGAIN0NB_V1
//#define AX5043_AGCGAIN1NB          AX5043_AGCGAIN1NB_V1
//#define AX5043_AGCGAIN2NB          AX5043_AGCGAIN2NB_V1
//#define AX5043_AGCGAIN3NB          AX5043_AGCGAIN3NB_V1
//#define AX5043_AGCTARGET0NB        AX5043_AGCTARGET0NB_V1
//#define AX5043_AGCTARGET1NB        AX5043_AGCTARGET1NB_V1
//#define AX5043_AGCTARGET2NB        AX5043_AGCTARGET2NB_V1
//#define AX5043_AGCTARGET3NB        AX5043_AGCTARGET3NB_V1
//#define AX5043_AMPLITUDEGAIN0NB    AX5043_AMPLITUDEGAIN0NB_V1
//#define AX5043_AMPLITUDEGAIN1NB    AX5043_AMPLITUDEGAIN1NB_V1
//#define AX5043_AMPLITUDEGAIN2NB    AX5043_AMPLITUDEGAIN2NB_V1
//#define AX5043_AMPLITUDEGAIN3NB    AX5043_AMPLITUDEGAIN3NB_V1
//#define AX5043_BBOFFSRES0NB        AX5043_BBOFFSRES0NB_V1
//#define AX5043_BBOFFSRES1NB        AX5043_BBOFFSRES1NB_V1
//#define AX5043_BBOFFSRES2NB        AX5043_BBOFFSRES2NB_V1
//#define AX5043_BBOFFSRES3NB        AX5043_BBOFFSRES3NB_V1
//#define AX5043_DRGAIN0NB           AX5043_DRGAIN0NB_V1
//#define AX5043_DRGAIN1NB           AX5043_DRGAIN1NB_V1
//#define AX5043_DRGAIN2NB           AX5043_DRGAIN2NB_V1
//#define AX5043_DRGAIN3NB           AX5043_DRGAIN3NB_V1
//#define AX5043_FOURFSK0NB          AX5043_FOURFSK0NB_V1
//#define AX5043_FOURFSK1NB          AX5043_FOURFSK1NB_V1
//#define AX5043_FOURFSK2NB          AX5043_FOURFSK2NB_V1
//#define AX5043_FOURFSK3NB          AX5043_FOURFSK3NB_V1
//#define AX5043_FREQDEV00NB         AX5043_FREQDEV00NB_V1
//#define AX5043_FREQDEV01NB         AX5043_FREQDEV01NB_V1
//#define AX5043_FREQDEV02NB         AX5043_FREQDEV02NB_V1
//#define AX5043_FREQDEV03NB         AX5043_FREQDEV03NB_V1
//#define AX5043_FREQDEV10NB         AX5043_FREQDEV10NB_V1
//#define AX5043_FREQDEV11NB         AX5043_FREQDEV11NB_V1
//#define AX5043_FREQDEV12NB         AX5043_FREQDEV12NB_V1
//#define AX5043_FREQDEV13NB         AX5043_FREQDEV13NB_V1
//#define AX5043_FREQUENCYGAINA0NB   AX5043_FREQUENCYGAINA0NB_V1
//#define AX5043_FREQUENCYGAINA1NB   AX5043_FREQUENCYGAINA1NB_V1
//#define AX5043_FREQUENCYGAINA2NB   AX5043_FREQUENCYGAINA2NB_V1
//#define AX5043_FREQUENCYGAINA3NB   AX5043_FREQUENCYGAINA3NB_V1
//#define AX5043_FREQUENCYGAINB0NB   AX5043_FREQUENCYGAINB0NB_V1
//#define AX5043_FREQUENCYGAINB1NB   AX5043_FREQUENCYGAINB1NB_V1
//#define AX5043_FREQUENCYGAINB2NB   AX5043_FREQUENCYGAINB2NB_V1
//#define AX5043_FREQUENCYGAINB3NB   AX5043_FREQUENCYGAINB3NB_V1
//#define AX5043_FREQUENCYGAINC0NB   AX5043_FREQUENCYGAINC0NB_V1
//#define AX5043_FREQUENCYGAINC1NB   AX5043_FREQUENCYGAINC1NB_V1
//#define AX5043_FREQUENCYGAINC2NB   AX5043_FREQUENCYGAINC2NB_V1
//#define AX5043_FREQUENCYGAINC3NB   AX5043_FREQUENCYGAINC3NB_V1
//#define AX5043_FREQUENCYGAIND0NB   AX5043_FREQUENCYGAIND0NB_V1
//#define AX5043_FREQUENCYGAIND1NB   AX5043_FREQUENCYGAIND1NB_V1
//#define AX5043_FREQUENCYGAIND2NB   AX5043_FREQUENCYGAIND2NB_V1
//#define AX5043_FREQUENCYGAIND3NB   AX5043_FREQUENCYGAIND3NB_V1
//#define AX5043_PHASEGAIN0NB        AX5043_PHASEGAIN0NB_V1
//#define AX5043_PHASEGAIN1NB        AX5043_PHASEGAIN1NB_V1
//#define AX5043_PHASEGAIN2NB        AX5043_PHASEGAIN2NB_V1
//#define AX5043_PHASEGAIN3NB        AX5043_PHASEGAIN3NB_V1
//#define AX5043_PKTADDR0NB          AX5043_PKTADDR0NB_V1
//#define AX5043_PKTADDR1NB          AX5043_PKTADDR1NB_V1
//#define AX5043_PKTADDRCFGNB        AX5043_PKTADDRCFGNB_V1
//#define AX5043_PKTADDRMASK0NB      AX5043_PKTADDRMASK0NB_V1
//#define AX5043_PKTADDRMASK1NB      AX5043_PKTADDRMASK1NB_V1
//#define AX5043_PKTLENCFGNB         AX5043_PKTLENCFGNB_V1
//#define AX5043_PKTLENOFFSETNB      AX5043_PKTLENOFFSETNB_V1
//#define AX5043_PKTMAXLENNB         AX5043_PKTMAXLENNB_V1
//#define AX5043_RXPARAMCURSETNB     AX5043_RXPARAMCURSETNB_V1
//#define AX5043_RXPARAMSETSNB       AX5043_RXPARAMSETSNB_V1
//#define AX5043_TIMEGAIN0NB         AX5043_TIMEGAIN0NB_V1
//#define AX5043_TIMEGAIN1NB         AX5043_TIMEGAIN1NB_V1
//#define AX5043_TIMEGAIN2NB         AX5043_TIMEGAIN2NB_V1
//#define AX5043_TIMEGAIN3NB         AX5043_TIMEGAIN3NB_V1
//#else
//SFRX(AX5043_AGCAHYST0NB,           0x5122)   /* AGC Analog Hysteresis, Non-Blocking */
//SFRX(AX5043_AGCAHYST1NB,           0x5132)   /* AGC Analog Hysteresis, Non-Blocking */
//SFRX(AX5043_AGCAHYST2NB,           0x5142)   /* AGC Analog Hysteresis, Non-Blocking */
//SFRX(AX5043_AGCAHYST3NB,           0x5152)   /* AGC Analog Hysteresis, Non-Blocking */
//SFRX(AX5043_AGCGAIN0NB,            0x5120)   /* AGC Speed, Non-Blocking */
//SFRX(AX5043_AGCGAIN1NB,            0x5130)   /* AGC Speed, Non-Blocking */
//SFRX(AX5043_AGCGAIN2NB,            0x5140)   /* AGC Speed, Non-Blocking */
//SFRX(AX5043_AGCGAIN3NB,            0x5150)   /* AGC Speed, Non-Blocking */
//SFRX(AX5043_AGCMINMAX0NB,          0x5123)   /* AGC Analog Update Behaviour, Non-Blocking */
//SFRX(AX5043_AGCMINMAX1NB,          0x5133)   /* AGC Analog Update Behaviour, Non-Blocking */
//SFRX(AX5043_AGCMINMAX2NB,          0x5143)   /* AGC Analog Update Behaviour, Non-Blocking */
//SFRX(AX5043_AGCMINMAX3NB,          0x5153)   /* AGC Analog Update Behaviour, Non-Blocking */
//SFRX(AX5043_AGCTARGET0NB,          0x5121)   /* AGC Target, Non-Blocking */
//SFRX(AX5043_AGCTARGET1NB,          0x5131)   /* AGC Target, Non-Blocking */
//SFRX(AX5043_AGCTARGET2NB,          0x5141)   /* AGC Target, Non-Blocking */
//SFRX(AX5043_AGCTARGET3NB,          0x5151)   /* AGC Target, Non-Blocking */
//SFRX(AX5043_AMPLITUDEGAIN0NB,      0x512B)   /* Amplitude Estimator Bandwidth, Non-Blocking */
//SFRX(AX5043_AMPLITUDEGAIN1NB,      0x513B)   /* Amplitude Estimator Bandwidth, Non-Blocking */
//SFRX(AX5043_AMPLITUDEGAIN2NB,      0x514B)   /* Amplitude Estimator Bandwidth, Non-Blocking */
//SFRX(AX5043_AMPLITUDEGAIN3NB,      0x515B)   /* Amplitude Estimator Bandwidth, Non-Blocking */
//SFRX(AX5043_BBOFFSRES0NB,          0x512F)   /* Baseband Offset Compensation Resistors, Non-Blocking */
//SFRX(AX5043_BBOFFSRES1NB,          0x513F)   /* Baseband Offset Compensation Resistors, Non-Blocking */
//SFRX(AX5043_BBOFFSRES2NB,          0x514F)   /* Baseband Offset Compensation Resistors, Non-Blocking */
//SFRX(AX5043_BBOFFSRES3NB,          0x515F)   /* Baseband Offset Compensation Resistors, Non-Blocking */
//SFRX(AX5043_DRGAIN0NB,             0x5125)   /* Data Rate Estimator Bandwidth, Non-Blocking */
//SFRX(AX5043_DRGAIN1NB,             0x5135)   /* Data Rate Estimator Bandwidth, Non-Blocking */
//SFRX(AX5043_DRGAIN2NB,             0x5145)   /* Data Rate Estimator Bandwidth, Non-Blocking */
//SFRX(AX5043_DRGAIN3NB,             0x5155)   /* Data Rate Estimator Bandwidth, Non-Blocking */
//SFRX(AX5043_FOURFSK0NB,            0x512E)   /* Four FSK Control, Non-Blocking */
//SFRX(AX5043_FOURFSK1NB,            0x513E)   /* Four FSK Control, Non-Blocking */
//SFRX(AX5043_FOURFSK2NB,            0x514E)   /* Four FSK Control, Non-Blocking */
//SFRX(AX5043_FOURFSK3NB,            0x515E)   /* Four FSK Control, Non-Blocking */
//SFRX(AX5043_FREQDEV00NB,           0x512D)   /* Receiver Frequency Deviation 0, Non-Blocking */
//SFRX(AX5043_FREQDEV01NB,           0x513D)   /* Receiver Frequency Deviation 0, Non-Blocking */
//SFRX(AX5043_FREQDEV02NB,           0x514D)   /* Receiver Frequency Deviation 0, Non-Blocking */
//SFRX(AX5043_FREQDEV03NB,           0x515D)   /* Receiver Frequency Deviation 0, Non-Blocking */
//SFRX(AX5043_FREQDEV10NB,           0x512C)   /* Receiver Frequency Deviation 1, Non-Blocking */
//SFRX(AX5043_FREQDEV11NB,           0x513C)   /* Receiver Frequency Deviation 1, Non-Blocking */
//SFRX(AX5043_FREQDEV12NB,           0x514C)   /* Receiver Frequency Deviation 1, Non-Blocking */
//SFRX(AX5043_FREQDEV13NB,           0x515C)   /* Receiver Frequency Deviation 1, Non-Blocking */
//SFRX(AX5043_FREQUENCYGAINA0NB,     0x5127)   /* Frequency Estimator Bandwidth A, Non-Blocking */
//SFRX(AX5043_FREQUENCYGAINA1NB,     0x5137)   /* Frequency Estimator Bandwidth A, Non-Blocking */
//SFRX(AX5043_FREQUENCYGAINA2NB,     0x5147)   /* Frequency Estimator Bandwidth A, Non-Blocking */
//SFRX(AX5043_FREQUENCYGAINA3NB,     0x5157)   /* Frequency Estimator Bandwidth A, Non-Blocking */
//SFRX(AX5043_FREQUENCYGAINB0NB,     0x5128)   /* Frequency Estimator Bandwidth B, Non-Blocking */
//SFRX(AX5043_FREQUENCYGAINB1NB,     0x5138)   /* Frequency Estimator Bandwidth B, Non-Blocking */
//SFRX(AX5043_FREQUENCYGAINB2NB,     0x5148)   /* Frequency Estimator Bandwidth B, Non-Blocking */
//SFRX(AX5043_FREQUENCYGAINB3NB,     0x5158)   /* Frequency Estimator Bandwidth B, Non-Blocking */
//SFRX(AX5043_FREQUENCYGAINC0NB,     0x5129)   /* Frequency Estimator Bandwidth C, Non-Blocking */
//SFRX(AX5043_FREQUENCYGAINC1NB,     0x5139)   /* Frequency Estimator Bandwidth C, Non-Blocking */
//SFRX(AX5043_FREQUENCYGAINC2NB,     0x5149)   /* Frequency Estimator Bandwidth C, Non-Blocking */
//SFRX(AX5043_FREQUENCYGAINC3NB,     0x5159)   /* Frequency Estimator Bandwidth C, Non-Blocking */
//SFRX(AX5043_FREQUENCYGAIND0NB,     0x512A)   /* Frequency Estimator Bandwidth D, Non-Blocking */
//SFRX(AX5043_FREQUENCYGAIND1NB,     0x513A)   /* Frequency Estimator Bandwidth D, Non-Blocking */
//SFRX(AX5043_FREQUENCYGAIND2NB,     0x514A)   /* Frequency Estimator Bandwidth D, Non-Blocking */
//SFRX(AX5043_FREQUENCYGAIND3NB,     0x515A)   /* Frequency Estimator Bandwidth D, Non-Blocking */
//SFRX(AX5043_FREQUENCYLEAKNB,       0x5116)   /* Baseband Frequency Recovery Loop Leakiness, Non-Blocking */
//SFRX(AX5043_PHASEGAIN0NB,          0x5126)   /* Phase Estimator Bandwidth, Non-Blocking */
//SFRX(AX5043_PHASEGAIN1NB,          0x5136)   /* Phase Estimator Bandwidth, Non-Blocking */
//SFRX(AX5043_PHASEGAIN2NB,          0x5146)   /* Phase Estimator Bandwidth, Non-Blocking */
//SFRX(AX5043_PHASEGAIN3NB,          0x5156)   /* Phase Estimator Bandwidth, Non-Blocking */
//SFRX(AX5043_PKTADDR0NB,            0x5207)   /* Packet Address 0, Non-Blocking */
//SFRX(AX5043_PKTADDR1NB,            0x5206)   /* Packet Address 1, Non-Blocking */
//SFRX(AX5043_PKTADDR2NB,            0x5205)   /* Packet Address 2, Non-Blocking */
//SFRX(AX5043_PKTADDR3NB,            0x5204)   /* Packet Address 3, Non-Blocking */
//SFRX(AX5043_PKTADDRCFGNB,          0x5200)   /* Packet Address Config, Non-Blocking */
//SFRX(AX5043_PKTADDRMASK0NB,        0x520B)   /* Packet Address Mask 0, Non-Blocking */
//SFRX(AX5043_PKTADDRMASK1NB,        0x520A)   /* Packet Address Mask 1, Non-Blocking */
//SFRX(AX5043_PKTADDRMASK2NB,        0x5209)   /* Packet Address Mask 2, Non-Blocking */
//SFRX(AX5043_PKTADDRMASK3NB,        0x5208)   /* Packet Address Mask 3, Non-Blocking */
//SFRX(AX5043_PKTLENCFGNB,           0x5201)   /* Packet Length Configuration, Non-Blocking */
//SFRX(AX5043_PKTLENOFFSETNB,        0x5202)   /* Packet Length Offset, Non-Blocking */
//SFRX(AX5043_PKTMAXLENNB,           0x5203)   /* Packet Maximum Length, Non-Blocking */
//SFRX(AX5043_RXPARAMCURSETNB,       0x5118)   /* Receiver Parameter Current Set, Non-Blocking */
//SFRX(AX5043_RXPARAMSETSNB,         0x5117)   /* Receiver Parameter Set Indirection, Non-Blocking */
//SFRX(AX5043_TIMEGAIN0NB,           0x5124)   /* Time Estimator Bandwidth, Non-Blocking */
//SFRX(AX5043_TIMEGAIN1NB,           0x5134)   /* Time Estimator Bandwidth, Non-Blocking */
//SFRX(AX5043_TIMEGAIN2NB,           0x5144)   /* Time Estimator Bandwidth, Non-Blocking */
//SFRX(AX5043_TIMEGAIN3NB,           0x5154)   /* Time Estimator Bandwidth, Non-Blocking */
//#endif
//#endif
//
//#define AX5043_REG_SILICONREVISION   0x0000 /* Silicon Revision */
//#define AX5043_REG_SCRATCH           0x0001 /* Scratch */
//#define AX5043_REG_PWRMODE           0x0002 /* Power Mode */
//#define AX5043_REG_POWSTAT           0x0003 /* Power Management Status */
//#define AX5043_REG_POWSTICKYSTAT     0x0004 /* Power Management Sticky Status */
//#define AX5043_REG_POWIRQMASK        0x0005 /* Power Management Interrupt Mask */
//#define AX5043_REG_IRQMASK1          0x0006 /* IRQ Mask 1 */
//#define AX5043_REG_IRQMASK0          0x0007 /* IRQ Mask 0 */
//#define AX5043_REG_RADIOEVENTMASK1   0x0008 /* Radio Event Mask 1 */
//#define AX5043_REG_RADIOEVENTMASK0   0x0009 /* Radio Event Mask 0 */
//#define AX5043_REG_IRQINVERSION1     0x000A /* IRQ Inversion 1 */
//#define AX5043_REG_IRQINVERSION0     0x000B /* IRQ Inversion 0 */
//#define AX5043_REG_IRQREQUEST1       0x000C /* IRQ Request 1 */
//#define AX5043_REG_IRQREQUEST0       0x000D /* IRQ Request 0 */
//#define AX5043_REG_RADIOEVENTREQ1    0x000E /* Radio Event Request 1 */
//#define AX5043_REG_RADIOEVENTREQ0    0x000F /* Radio Event Request 0 */
//#define AX5043_REG_MODULATION        0x0010 /* Modulation */
//#define AX5043_REG_ENCODING          0x0011 /* Encoding */
//#define AX5043_REG_FRAMING           0x0012 /* Framing Mode */
//#define AX5043_REG_CRCINIT3          0x0014 /* CRC Initial Value 3 */
//#define AX5043_REG_CRCINIT2          0x0015 /* CRC Initial Value 2 */
//#define AX5043_REG_CRCINIT1          0x0016 /* CRC Initial Value 1 */
//#define AX5043_REG_CRCINIT0          0x0017 /* CRC Initial Value 0 */
//#define AX5043_REG_FEC               0x0018 /* Forward Error Correction */
//#define AX5043_REG_FECSYNC           0x0019 /* Forward Error Correction Sync Threshold */
//#define AX5043_REG_FECSTATUS         0x001A /* Forward Error Correction Status */
//#define AX5043_REG_RADIOSTATE        0x001C /* Radio Controller State */
//#define AX5043_REG_XTALSTATUS        0x001D /* Crystal Oscillator Status */
//#define AX5043_REG_PINSTATE          0x0020 /* Pin State */
//#define AX5043_REG_PINFUNCSYSCLK     0x0021 /* Pin Function SYSCLK */
//#define AX5043_REG_PINFUNCDCLK       0x0022 /* Pin Function DCLK */
//#define AX5043_REG_PINFUNCDATA       0x0023 /* Pin Function DATA */
//#define AX5043_REG_PINFUNCIRQ        0x0024 /* Pin Function IRQ */
//#define AX5043_REG_PINFUNCANTSEL     0x0025 /* Pin Function ANTSEL */
//#define AX5043_REG_PINFUNCPWRAMP     0x0026 /* Pin Function PWRAMP */
//#define AX5043_REG_PWRAMP            0x0027 /* PWRAMP Control */
//#define AX5043_REG_FIFOSTAT          0x0028 /* FIFO Control */
//#define AX5043_REG_FIFODATA          0x0029 /* FIFO Data */
//#define AX5043_REG_FIFOCOUNT1        0x002A /* Number of Words currently in FIFO 1 */
//#define AX5043_REG_FIFOCOUNT0        0x002B /* Number of Words currently in FIFO 0 */
//#define AX5043_REG_FIFOFREE1         0x002C /* Number of Words that can be written to FIFO 1 */
//#define AX5043_REG_FIFOFREE0         0x002D /* Number of Words that can be written to FIFO 0 */
//#define AX5043_REG_FIFOTHRESH1       0x002E /* FIFO Threshold 1 */
//#define AX5043_REG_FIFOTHRESH0       0x002F /* FIFO Threshold 0 */
//#define AX5043_REG_PLLLOOP           0x0030 /* PLL Loop Filter Settings */
//#define AX5043_REG_PLLCPI            0x0031 /* PLL Charge Pump Current */
//#define AX5043_REG_PLLVCODIV         0x0032 /* PLL Divider Settings */
//#define AX5043_REG_PLLRANGINGA       0x0033 /* PLL Autoranging A */
//#define AX5043_REG_FREQA3            0x0034 /* Frequency A 3 */
//#define AX5043_REG_FREQA2            0x0035 /* Frequency A 2 */
//#define AX5043_REG_FREQA1            0x0036 /* Frequency A 1 */
//#define AX5043_REG_FREQA0            0x0037 /* Frequency A 0 */
//#define AX5043_REG_PLLLOOPBOOST      0x0038 /* PLL Loop Filter Settings (Boosted) */
//#define AX5043_REG_PLLCPIBOOST       0x0039 /* PLL Charge Pump Current (Boosted) */
//#define AX5043_REG_PLLRANGINGB       0x003B /* PLL Autoranging B */
//#define AX5043_REG_FREQB3            0x003C /* Frequency B 3 */
//#define AX5043_REG_FREQB2            0x003D /* Frequency B 2 */
//#define AX5043_REG_FREQB1            0x003E /* Frequency B 1 */
//#define AX5043_REG_FREQB0            0x003F /* Frequency B 0 */
//#define AX5043_REG_RSSI              0x0040 /* Received Signal Strength Indicator */
//#define AX5043_REG_BGNDRSSI          0x0041 /* Background RSSI */
//#define AX5043_REG_DIVERSITY         0x0042 /* Antenna Diversity Configuration */
//#define AX5043_REG_AGCCOUNTER        0x0043 /* AGC Counter */
//#define AX5043_REG_TRKDATARATE2      0x0045 /* Datarate Tracking 2 */
//#define AX5043_REG_TRKDATARATE1      0x0046 /* Datarate Tracking 1 */
//#define AX5043_REG_TRKDATARATE0      0x0047 /* Datarate Tracking 0 */
//#define AX5043_REG_TRKAMPLITUDE1     0x0048 /* Amplitude Tracking 1 */
//#define AX5043_REG_TRKAMPLITUDE0     0x0049 /* Amplitude Tracking 0 */
//#define AX5043_REG_TRKPHASE1         0x004A /* Phase Tracking 1 */
//#define AX5043_REG_TRKPHASE0         0x004B /* Phase Tracking 0 */
//#define AX5043_REG_TRKRFFREQ2        0x004D /* RF Frequency Tracking 2 */
//#define AX5043_REG_TRKRFFREQ1        0x004E /* RF Frequency Tracking 1 */
//#define AX5043_REG_TRKRFFREQ0        0x004F /* RF Frequency Tracking 0 */
//#define AX5043_REG_TRKFREQ1          0x0050 /* Frequency Tracking 1 */
//#define AX5043_REG_TRKFREQ0          0x0051 /* Frequency Tracking 0 */
//#define AX5043_REG_TRKFSKDEMOD1      0x0052 /* FSK Demodulator Tracking 1 */
//#define AX5043_REG_TRKFSKDEMOD0      0x0053 /* FSK Demodulator Tracking 0 */
//#define AX5043_REG_TRKAFSKDEMOD1     0x0054 /* AFSK Demodulator Tracking 1 */
//#define AX5043_REG_TRKAFSKDEMOD0     0x0055 /* AFSK Demodulator Tracking 0 */
//#define AX5043_REG_TIMER2            0x0059 /* 1MHz Timer 2 */
//#define AX5043_REG_TIMER1            0x005A /* 1MHz Timer 1 */
//#define AX5043_REG_TIMER0            0x005B /* 1MHz Timer 0 */
//#define AX5043_REG_WAKEUPTIMER1      0x0068 /* Wakeup Timer 1 */
//#define AX5043_REG_WAKEUPTIMER0      0x0069 /* Wakeup Timer 0 */
//#define AX5043_REG_WAKEUP1           0x006A /* Wakeup Time 1 */
//#define AX5043_REG_WAKEUP0           0x006B /* Wakeup Time 0 */
//#define AX5043_REG_WAKEUPFREQ1       0x006C /* Wakeup Frequency 1 */
//#define AX5043_REG_WAKEUPFREQ0       0x006D /* Wakeup Frequency 0 */
//#define AX5043_REG_WAKEUPXOEARLY     0x006E /* Wakeup Crystal Oscillator Early */
//#define AX5043_REG_IFFREQ1           0xF100 /* 2nd LO / IF Frequency 1 */
//#define AX5043_REG_IFFREQ0           0xF101 /* 2nd LO / IF Frequency 0 */
//#define AX5043_REG_DECIMATION        0xF102 /* Decimation Factor */
//#define AX5043_REG_RXDATARATE2       0xF103 /* Receiver Datarate 2 */
//#define AX5043_REG_RXDATARATE1       0xF104 /* Receiver Datarate 1 */
//#define AX5043_REG_RXDATARATE0       0xF105 /* Receiver Datarate 0 */
//#define AX5043_REG_MAXDROFFSET2      0xF106 /* Maximum Receiver Datarate Offset 2 */
//#define AX5043_REG_MAXDROFFSET1      0xF107 /* Maximum Receiver Datarate Offset 1 */
//#define AX5043_REG_MAXDROFFSET0      0xF108 /* Maximum Receiver Datarate Offset 0 */
//#define AX5043_REG_MAXRFOFFSET2      0xF109 /* Maximum Receiver RF Offset 2 */
//#define AX5043_REG_MAXRFOFFSET1      0xF10A /* Maximum Receiver RF Offset 1 */
//#define AX5043_REG_MAXRFOFFSET0      0xF10B /* Maximum Receiver RF Offset 0 */
//#define AX5043_REG_FSKDMAX1          0xF10C /* Four FSK Rx Maximum Deviation 1 */
//#define AX5043_REG_FSKDMAX0          0xF10D /* Four FSK Rx Maximum Deviation 0 */
//#define AX5043_REG_FSKDMIN1          0xF10E /* Four FSK Rx Minimum Deviation 1 */
//#define AX5043_REG_FSKDMIN0          0xF10F /* Four FSK Rx Minimum Deviation 0 */
//#define AX5043_REG_AFSKSPACE1        0xF110 /* AFSK Space (0) Frequency 1 */
//#define AX5043_REG_AFSKSPACE0        0xF111 /* AFSK Space (0) Frequency 0 */
//#define AX5043_REG_AFSKMARK1         0xF112 /* AFSK Mark (1) Frequency 1 */
//#define AX5043_REG_AFSKMARK0         0xF113 /* AFSK Mark (1) Frequency 0 */
//#define AX5043_REG_AFSKCTRL          0xF114 /* AFSK Control */
//#define AX5043_REG_AMPLFILTER        0xF115 /* Amplitude Filter */
//#define AX5043_REG_FREQUENCYLEAK     0xF116 /* Baseband Frequency Recovery Loop Leakiness */
//#define AX5043_REG_RXPARAMSETS       0xF117 /* Receiver Parameter Set Indirection */
//#define AX5043_REG_RXPARAMCURSET     0xF118 /* Receiver Parameter Current Set */
//#define AX5043_REG_AGCGAIN0          0xF120 /* AGC Speed */
//#define AX5043_REG_AGCTARGET0        0xF121 /* AGC Target */
//#define AX5043_REG_AGCAHYST0         0xF122 /* AGC Analog Hysteresis */
//#define AX5043_REG_AGCMINMAX0        0xF123 /* AGC Analog Update Behaviour */
//#define AX5043_REG_TIMEGAIN0         0xF124 /* Time Estimator Bandwidth */
//#define AX5043_REG_DRGAIN0           0xF125 /* Data Rate Estimator Bandwidth */
//#define AX5043_REG_PHASEGAIN0        0xF126 /* Phase Estimator Bandwidth */
//#define AX5043_REG_FREQUENCYGAINA0   0xF127 /* Frequency Estimator Bandwidth A */
//#define AX5043_REG_FREQUENCYGAINB0   0xF128 /* Frequency Estimator Bandwidth B */
//#define AX5043_REG_FREQUENCYGAINC0   0xF129 /* Frequency Estimator Bandwidth C */
//#define AX5043_REG_FREQUENCYGAIND0   0xF12A /* Frequency Estimator Bandwidth D */
//#define AX5043_REG_AMPLITUDEGAIN0    0xF12B /* Amplitude Estimator Bandwidth */
//#define AX5043_REG_FREQDEV10         0xF12C /* Receiver Frequency Deviation 1 */
//#define AX5043_REG_FREQDEV00         0xF12D /* Receiver Frequency Deviation 0 */
//#define AX5043_REG_FOURFSK0          0xF12E /* Four FSK Control */
//#define AX5043_REG_BBOFFSRES0        0xF12F /* Baseband Offset Compensation Resistors */
//#define AX5043_REG_AGCGAIN1          0xF130 /* AGC Speed */
//#define AX5043_REG_AGCTARGET1        0xF131 /* AGC Target */
//#define AX5043_REG_AGCAHYST1         0xF132 /* AGC Analog Hysteresis */
//#define AX5043_REG_AGCMINMAX1        0xF133 /* AGC Analog Update Behaviour */
//#define AX5043_REG_TIMEGAIN1         0xF134 /* Time Estimator Bandwidth */
//#define AX5043_REG_DRGAIN1           0xF135 /* Data Rate Estimator Bandwidth */
//#define AX5043_REG_PHASEGAIN1        0xF136 /* Phase Estimator Bandwidth */
//#define AX5043_REG_FREQUENCYGAINA1   0xF137 /* Frequency Estimator Bandwidth A */
//#define AX5043_REG_FREQUENCYGAINB1   0xF138 /* Frequency Estimator Bandwidth B */
//#define AX5043_REG_FREQUENCYGAINC1   0xF139 /* Frequency Estimator Bandwidth C */
//#define AX5043_REG_FREQUENCYGAIND1   0xF13A /* Frequency Estimator Bandwidth D */
//#define AX5043_REG_AMPLITUDEGAIN1    0xF13B /* Amplitude Estimator Bandwidth */
//#define AX5043_REG_FREQDEV11         0xF13C /* Receiver Frequency Deviation 1 */
//#define AX5043_REG_FREQDEV01         0xF13D /* Receiver Frequency Deviation 0 */
//#define AX5043_REG_FOURFSK1          0xF13E /* Four FSK Control */
//#define AX5043_REG_BBOFFSRES1        0xF13F /* Baseband Offset Compensation Resistors */
//#define AX5043_REG_AGCGAIN2          0xF140 /* AGC Speed */
//#define AX5043_REG_AGCTARGET2        0xF141 /* AGC Target */
//#define AX5043_REG_AGCAHYST2         0xF142 /* AGC Analog Hysteresis */
//#define AX5043_REG_AGCMINMAX2        0xF143 /* AGC Analog Update Behaviour */
//#define AX5043_REG_TIMEGAIN2         0xF144 /* Time Estimator Bandwidth */
//#define AX5043_REG_DRGAIN2           0xF145 /* Data Rate Estimator Bandwidth */
//#define AX5043_REG_PHASEGAIN2        0xF146 /* Phase Estimator Bandwidth */
//#define AX5043_REG_FREQUENCYGAINA2   0xF147 /* Frequency Estimator Bandwidth A */
//#define AX5043_REG_FREQUENCYGAINB2   0xF148 /* Frequency Estimator Bandwidth B */
//#define AX5043_REG_FREQUENCYGAINC2   0xF149 /* Frequency Estimator Bandwidth C */
//#define AX5043_REG_FREQUENCYGAIND2   0xF14A /* Frequency Estimator Bandwidth D */
//#define AX5043_REG_AMPLITUDEGAIN2    0xF14B /* Amplitude Estimator Bandwidth */
//#define AX5043_REG_FREQDEV12         0xF14C /* Receiver Frequency Deviation 1 */
//#define AX5043_REG_FREQDEV02         0xF14D /* Receiver Frequency Deviation 0 */
//#define AX5043_REG_FOURFSK2          0xF14E /* Four FSK Control */
//#define AX5043_REG_BBOFFSRES2        0xF14F /* Baseband Offset Compensation Resistors */
//#define AX5043_REG_AGCGAIN3          0xF150 /* AGC Speed */
//#define AX5043_REG_AGCTARGET3        0xF151 /* AGC Target */
//#define AX5043_REG_AGCAHYST3         0xF152 /* AGC Analog Hysteresis */
//#define AX5043_REG_AGCMINMAX3        0xF153 /* AGC Analog Update Behaviour */
//#define AX5043_REG_TIMEGAIN3         0xF154 /* Time Estimator Bandwidth */
//#define AX5043_REG_DRGAIN3           0xF155 /* Data Rate Estimator Bandwidth */
//#define AX5043_REG_PHASEGAIN3        0xF156 /* Phase Estimator Bandwidth */
//#define AX5043_REG_FREQUENCYGAINA3   0xF157 /* Frequency Estimator Bandwidth A */
//#define AX5043_REG_FREQUENCYGAINB3   0xF158 /* Frequency Estimator Bandwidth B */
//#define AX5043_REG_FREQUENCYGAINC3   0xF159 /* Frequency Estimator Bandwidth C */
//#define AX5043_REG_FREQUENCYGAIND3   0xF15A /* Frequency Estimator Bandwidth D */
//#define AX5043_REG_AMPLITUDEGAIN3    0xF15B /* Amplitude Estimator Bandwidth */
//#define AX5043_REG_FREQDEV13         0xF15C /* Receiver Frequency Deviation 1 */
//#define AX5043_REG_FREQDEV03         0xF15D /* Receiver Frequency Deviation 0 */
//#define AX5043_REG_FOURFSK3          0xF15E /* Four FSK Control */
//#define AX5043_REG_BBOFFSRES3        0xF15F /* Baseband Offset Compensation Resistors */
//#define AX5043_REG_MODCFGF           0xF160 /* Modulator Configuration F */
//#define AX5043_REG_FSKDEV2           0xF161 /* FSK Deviation 2 */
//#define AX5043_REG_FSKDEV1           0xF162 /* FSK Deviation 1 */
//#define AX5043_REG_FSKDEV0           0xF163 /* FSK Deviation 0 */
//#define AX5043_REG_MODCFGA           0xF164 /* Modulator Configuration A */
//#define AX5043_REG_TXRATE2           0xF165 /* Transmitter Bitrate 2 */
//#define AX5043_REG_TXRATE1           0xF166 /* Transmitter Bitrate 1 */
//#define AX5043_REG_TXRATE0           0xF167 /* Transmitter Bitrate 0 */
//#define AX5043_REG_TXPWRCOEFFA1      0xF168 /* Transmitter Predistortion Coefficient A 1 */
//#define AX5043_REG_TXPWRCOEFFA0      0xF169 /* Transmitter Predistortion Coefficient A 0 */
//#define AX5043_REG_TXPWRCOEFFB1      0xF16A /* Transmitter Predistortion Coefficient B 1 */
//#define AX5043_REG_TXPWRCOEFFB0      0xF16B /* Transmitter Predistortion Coefficient B 0 */
//#define AX5043_REG_TXPWRCOEFFC1      0xF16C /* Transmitter Predistortion Coefficient C 1 */
//#define AX5043_REG_TXPWRCOEFFC0      0xF16D /* Transmitter Predistortion Coefficient C 0 */
//#define AX5043_REG_TXPWRCOEFFD1      0xF16E /* Transmitter Predistortion Coefficient D 1 */
//#define AX5043_REG_TXPWRCOEFFD0      0xF16F /* Transmitter Predistortion Coefficient D 0 */
//#define AX5043_REG_TXPWRCOEFFE1      0xF170 /* Transmitter Predistortion Coefficient E 1 */
//#define AX5043_REG_TXPWRCOEFFE0      0xF171 /* Transmitter Predistortion Coefficient E 0 */
//#define AX5043_REG_PLLVCOI           0xF180 /* PLL VCO Current */
//#define AX5043_REG_PLLVCOIR          0xF181 /* PLL VCO Current Readback */
//#define AX5043_REG_PLLLOCKDET        0xF182 /* PLL Lock Detect Delay */
//#define AX5043_REG_PLLRNGCLK         0xF183 /* PLL Autoranging Clock */
//#define AX5043_REG_XTALCAP           0xF184 /* Crystal Oscillator Load Capacitance */
//#define AX5043_REG_BBTUNE            0xF188 /* Baseband Tuning */
//#define AX5043_REG_BBOFFSCAP         0xF189 /* Baseband Offset Compensation Capacitors */
//#define AX5043_REG_PKTADDRCFG        0xF200 /* Packet Address Config */
//#define AX5043_REG_PKTLENCFG         0xF201 /* Packet Length Configuration */
//#define AX5043_REG_PKTLENOFFSET      0xF202 /* Packet Length Offset */
//#define AX5043_REG_PKTMAXLEN         0xF203 /* Packet Maximum Length */
//#define AX5043_REG_PKTADDR3          0xF204 /* Packet Address 3 */
//#define AX5043_REG_PKTADDR2          0xF205 /* Packet Address 2 */
//#define AX5043_REG_PKTADDR1          0xF206 /* Packet Address 1 */
//#define AX5043_REG_PKTADDR0          0xF207 /* Packet Address 0 */
//#define AX5043_REG_PKTADDRMASK3      0xF208 /* Packet Address Mask 3 */
//#define AX5043_REG_PKTADDRMASK2      0xF209 /* Packet Address Mask 2 */
//#define AX5043_REG_PKTADDRMASK1      0xF20A /* Packet Address Mask 1 */
//#define AX5043_REG_PKTADDRMASK0      0xF20B /* Packet Address Mask 0 */
//#define AX5043_REG_MATCH0PAT3        0xF210 /* Pattern Match Unit 0, Pattern 3 */
//#define AX5043_REG_MATCH0PAT2        0xF211 /* Pattern Match Unit 0, Pattern 2 */
//#define AX5043_REG_MATCH0PAT1        0xF212 /* Pattern Match Unit 0, Pattern 1 */
//#define AX5043_REG_MATCH0PAT0        0xF213 /* Pattern Match Unit 0, Pattern 0 */
//#define AX5043_REG_MATCH0LEN         0xF214 /* Pattern Match Unit 0, Pattern Length */
//#define AX5043_REG_MATCH0MIN         0xF215 /* Pattern Match Unit 0, Minimum Match */
//#define AX5043_REG_MATCH0MAX         0xF216 /* Pattern Match Unit 0, Maximum Match */
//#define AX5043_REG_MATCH1PAT1        0xF218 /* Pattern Match Unit 1, Pattern 1 */
//#define AX5043_REG_MATCH1PAT0        0xF219 /* Pattern Match Unit 1, Pattern 0 */
//#define AX5043_REG_MATCH1LEN         0xF21C /* Pattern Match Unit 1, Pattern Length */
//#define AX5043_REG_MATCH1MIN         0xF21D /* Pattern Match Unit 1, Minimum Match */
//#define AX5043_REG_MATCH1MAX         0xF21E /* Pattern Match Unit 1, Maximum Match */
//#define AX5043_REG_TMGTXBOOST        0xF220 /* Transmit PLL Boost Time */
//#define AX5043_REG_TMGTXSETTLE       0xF221 /* Transmit PLL (post Boost) Settling Time */
//#define AX5043_REG_TMGRXBOOST        0xF223 /* Receive PLL Boost Time */
//#define AX5043_REG_TMGRXSETTLE       0xF224 /* Receive PLL (post Boost) Settling Time */
//#define AX5043_REG_TMGRXOFFSACQ      0xF225 /* Receive Baseband DC Offset Acquisition Time */
//#define AX5043_REG_TMGRXCOARSEAGC    0xF226 /* Receive Coarse AGC Time */
//#define AX5043_REG_TMGRXAGC          0xF227 /* Receiver AGC Settling Time */
//#define AX5043_REG_TMGRXRSSI         0xF228 /* Receiver RSSI Settling Time */
//#define AX5043_REG_TMGRXPREAMBLE1    0xF229 /* Receiver Preamble 1 Timeout */
//#define AX5043_REG_TMGRXPREAMBLE2    0xF22A /* Receiver Preamble 2 Timeout */
//#define AX5043_REG_TMGRXPREAMBLE3    0xF22B /* Receiver Preamble 3 Timeout */
//#define AX5043_REG_RSSIREFERENCE     0xF22C /* RSSI Offset */
//#define AX5043_REG_RSSIABSTHR        0xF22D /* RSSI Absolute Threshold */
//#define AX5043_REG_BGNDRSSIGAIN      0xF22E /* Background RSSI Averaging Time Constant */
//#define AX5043_REG_BGNDRSSITHR       0xF22F /* Background RSSI Relative Threshold */
//#define AX5043_REG_PKTCHUNKSIZE      0xF230 /* Packet Chunk Size */
//#define AX5043_REG_PKTMISCFLAGS      0xF231 /* Packet Controller Miscellaneous Flags */
//#define AX5043_REG_PKTSTOREFLAGS     0xF232 /* Packet Controller Store Flags */
//#define AX5043_REG_PKTACCEPTFLAGS    0xF233 /* Packet Controller Accept Flags */
//#define AX5043_REG_GPADCCTRL         0xF300 /* General Purpose ADC Control */
//#define AX5043_REG_GPADCPERIOD       0xF301 /* GPADC Sampling Period */
//#define AX5043_REG_GPADC13VALUE1     0xF308 /* GPADC13 Value 1 */
//#define AX5043_REG_GPADC13VALUE0     0xF309 /* GPADC13 Value 0 */
//#define AX5043_REG_LPOSCCONFIG       0xF310 /* Low Power Oscillator Calibration Configuration */
//#define AX5043_REG_LPOSCSTATUS       0xF311 /* Low Power Oscillator Calibration Status */
//#define AX5043_REG_LPOSCKFILT1       0xF312 /* Low Power Oscillator Calibration Filter Constant High Byte */
//#define AX5043_REG_LPOSCKFILT0       0xF313 /* Low Power Oscillator Calibration Filter Constant Low Byte */
//#define AX5043_REG_LPOSCREF1         0xF314 /* Low Power Oscillator Reference Frequency High Byte */
//#define AX5043_REG_LPOSCREF0         0xF315 /* Low Power Oscillator Reference Frequency Low Byte */
//#define AX5043_REG_LPOSCFREQ1        0xF316 /* Low Power Oscillator Frequency Tuning High Byte */
//#define AX5043_REG_LPOSCFREQ0        0xF317 /* Low Power Oscillator Frequency Tuning Low Byte */
//#define AX5043_REG_LPOSCPER1         0xF318 /* Low Power Oscillator Period High Byte */
//#define AX5043_REG_LPOSCPER0         0xF319 /* Low Power Oscillator Period Low Byte */
//#define AX5043_REG_DACVALUE1         0xF330 /* DAC Value 1 */
//#define AX5043_REG_DACVALUE0         0xF331 /* DAC Value 0 */
//#define AX5043_REG_DACCONFIG         0xF332 /* DAC Configuration */
//#define AX5043_REG_0xF00             0xFF00
//#define AX5043_REG_POWCTRL1          0xFF08 /* Power Control 1 */
//#define AX5043_REG_0xF0C             0xFF0C
//#define AX5043_REG_REF               0xFF0D /* Reference */
//#define AX5043_REG_XTALOSC           0xFF10 /* Crystal Oscillator Control */
//#define AX5043_REG_XTALAMPL          0xFF11 /* Crystal Oscillator Amplitude Control */
//#define AX5043_REG_0xF18             0xFF18
//#define AX5043_REG_0xF1C             0xFF1C
//#define AX5043_REG_0xF21             0xFF21
//#define AX5043_REG_0xF22             0xFF22
//#define AX5043_REG_0xF23             0xFF23
//#define AX5043_REG_0xF26             0xFF26
//#define AX5043_REG_0xF30             0xFF30
//#define AX5043_REG_0xF31             0xFF31
//#define AX5043_REG_0xF32             0xFF32
//#define AX5043_REG_0xF33             0xFF33
//#define AX5043_REG_0xF34             0xFF34
//#define AX5043_REG_0xF35             0xFF35
//#define AX5043_REG_0xF44             0xFF44
//#define AX5043_REG_MODCFGP           0xFF5F /* Modulator Configuration P */
