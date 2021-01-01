/*********************************************************************                                                                   **
**  Device:     AX5043
**  File:  Radio.c
**  Author:  Strong
**  Target:  R8C/1B
**  Tools:  ICE
**  Version:    V00
**  Date:     2014-01-20
**  Update :    2014/01/20
**  Description:
**        This file is a sample code for your reference.
**  Copyright (C) 2014 Karv Technology Co.,Ltd
*********************************************************************/
#include <rtthread.h>
#include <rtdevice.h>
#include "drv_spi.h"
#include <string.h>
#include "AX5043.h"
#include "Radio_Config.h"
#include "Radio.h"
#include "pin_config.h"
#include "Radio_Decoder.h"
#include "Radio_Encoder.h"

#define DBG_TAG "radio"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>


#define RADIO_NSS_PORT GPIOC
#define RADIO_NSS_PIN GPIO_PIN_8
#define RADIO_Device_Name "ax5043"

struct rt_spi_device *ax5043_device;//spi设备

unsigned char AxRadioPHYChanPllRng_TX[1];   //频率补偿
unsigned char AxRadioPHYChanPllRng_RX[1];

unsigned char ChannelPtr ;
unsigned char ubRFState ;

unsigned char TXBuff[500];
unsigned int TxLen;
unsigned char RXBuff[64+1];
unsigned char RxLen;

uint8_t wor_flag=0;

#define axradio_phy_preamble_wor_len  400
#define axradio_phy_preamble_wor_longlen 1600
#define axradio_phy_preamble_len  32
#define axradio_framing_synclen   32

#define axradio_phy_preamble_flags 0x38
#define axradio_phy_preamble_byte 0x55

uint32_t axradio_txbuffer_cnt = 0;

unsigned char ubReceiveFlag;

const unsigned int RegisterVaule[][2]=
{
    { REG_AX5043_MODULATION,          0x08},
    { REG_AX5043_ENCODING,            0x00},
    { REG_AX5043_FRAMING,             0x26},
    { REG_AX5043_PINFUNCSYSCLK,       0x01},
    { REG_AX5043_PINFUNCDCLK,         0x01},
    { REG_AX5043_PINFUNCDATA,         0x01},
    { REG_AX5043_PINFUNCANTSEL,       0x04},
    { REG_AX5043_PINFUNCPWRAMP,       0x00},
    { REG_AX5043_WAKEUPXOEARLY,       0x01},
    { REG_AX5043_IFFREQ1,             0x01},
    { REG_AX5043_IFFREQ0,             0xE4},
    { REG_AX5043_DECIMATION,          0x16},
    { REG_AX5043_RXDATARATE2,         0x00},
    { REG_AX5043_RXDATARATE1,         0x3D},
    { REG_AX5043_RXDATARATE0,         0x8D},
    { REG_AX5043_MAXDROFFSET2,        0x00},
    { REG_AX5043_MAXDROFFSET1,        0x00},
    { REG_AX5043_MAXDROFFSET0,        0x00},
    { REG_AX5043_MAXRFOFFSET2,        0x80},
    { REG_AX5043_MAXRFOFFSET1,        0x02},
    { REG_AX5043_MAXRFOFFSET0,        0x31},
    { REG_AX5043_FSKDMAX1,            0x00},
    { REG_AX5043_FSKDMAX0,            0xA6},
    { REG_AX5043_FSKDMIN1,            0xFF},
    { REG_AX5043_FSKDMIN0,            0x5A},
    { REG_AX5043_AMPLFILTER,          0x00},
    { REG_AX5043_RXPARAMSETS,         0xF4},
    { REG_AX5043_AGCGAIN0,            0xC5},
    { REG_AX5043_AGCTARGET0,          0x84},
    { REG_AX5043_TIMEGAIN0,           0xF8},
    { REG_AX5043_DRGAIN0,             0xF2},
    { REG_AX5043_PHASEGAIN0,          0xC3},
    { REG_AX5043_FREQUENCYGAINA0,     0x0F},
    { REG_AX5043_FREQUENCYGAINB0,     0x1F},
    { REG_AX5043_FREQUENCYGAINC0,     0x08},
    { REG_AX5043_FREQUENCYGAIND0,     0x08},
    { REG_AX5043_AMPLITUDEGAIN0,      0x06},
    { REG_AX5043_FREQDEV10,           0x00},
    { REG_AX5043_FREQDEV00,           0x00},
    { REG_AX5043_BBOFFSRES0,          0x00},
    { REG_AX5043_AGCGAIN1,            0xC5},
    { REG_AX5043_AGCTARGET1,          0x84},
    { REG_AX5043_AGCAHYST1,           0x00},
    { REG_AX5043_AGCMINMAX1,          0x00},
    { REG_AX5043_TIMEGAIN1,           0xF6},
    { REG_AX5043_DRGAIN1,             0xF1},
    { REG_AX5043_PHASEGAIN1,          0xC3},
    { REG_AX5043_FREQUENCYGAINA1,     0x0F},
    { REG_AX5043_FREQUENCYGAINB1,     0x1F},
    { REG_AX5043_FREQUENCYGAINC1,     0x08},
    { REG_AX5043_FREQUENCYGAIND1,     0x08},
    { REG_AX5043_AMPLITUDEGAIN1,      0x06},
    { REG_AX5043_FREQDEV11,           0x00},
    { REG_AX5043_FREQDEV01,           0x3E},
    { REG_AX5043_FOURFSK1,            0x16},
    { REG_AX5043_BBOFFSRES1,          0x00},
    { REG_AX5043_AGCGAIN3,            0xFF},
    { REG_AX5043_AGCTARGET3,          0x84},
    { REG_AX5043_AGCAHYST3,           0x00},
    { REG_AX5043_AGCMINMAX3,          0x00},
    { REG_AX5043_TIMEGAIN3,           0xF5},
    { REG_AX5043_DRGAIN3,             0xF0},
    { REG_AX5043_PHASEGAIN3,          0xC3},
    { REG_AX5043_FREQUENCYGAINA3,     0x0F},
    { REG_AX5043_FREQUENCYGAINB3,     0x1F},
    { REG_AX5043_FREQUENCYGAINC3,     0x0C},
    { REG_AX5043_FREQUENCYGAIND3,     0x0C},
    { REG_AX5043_AMPLITUDEGAIN3,      0x06},
    { REG_AX5043_FREQDEV13,           0x00},
    { REG_AX5043_FREQDEV03,           0x3E},
    { REG_AX5043_FOURFSK3,            0x16},
    { REG_AX5043_BBOFFSRES3,          0x00},
    { REG_AX5043_MODCFGF,             0x00},
    { REG_AX5043_FSKDEV2,             0x00},
    { REG_AX5043_FSKDEV1,             0x04},
    { REG_AX5043_FSKDEV0,             0x2F},
    { REG_AX5043_MODCFGA,             0x05},
    { REG_AX5043_TXRATE2,             0x00},
    { REG_AX5043_TXRATE1,             0x0C},
    { REG_AX5043_TXRATE0,             0x19},
    { REG_AX5043_TXPWRCOEFFB1,        0x07},
    { REG_AX5043_TXPWRCOEFFB0,        0x00},
    { REG_AX5043_PLLVCOI,             0x99},
    { REG_AX5043_PLLRNGCLK,           0x04},
    { REG_AX5043_BBTUNE,              0x0F},
    { REG_AX5043_BBOFFSCAP,           0x77},
    { REG_AX5043_PKTADDRCFG,          0x00},
    { REG_AX5043_PKTLENCFG,           0x00},
    { REG_AX5043_PKTLENOFFSET,        0x21},
    { REG_AX5043_PKTMAXLEN,           0xC8},
    { REG_AX5043_MATCH0PAT3,          0xAA},
    { REG_AX5043_MATCH0PAT2,          0xCC},
    { REG_AX5043_MATCH0PAT1,          0xAA},
    { REG_AX5043_MATCH0PAT0,          0xCC},
    { REG_AX5043_MATCH0LEN,           0x9F},
    { REG_AX5043_MATCH0MAX,           0x1F},
    { REG_AX5043_MATCH1PAT1,          0x55},
    { REG_AX5043_MATCH1PAT0,          0x55},
    { REG_AX5043_MATCH1LEN,           0x8A},
    { REG_AX5043_MATCH1MAX,           0x0A},
    { REG_AX5043_TMGTXBOOST,          0x3E},
    { REG_AX5043_TMGTXSETTLE,         0x31},
    { REG_AX5043_TMGRXBOOST,          0x3E},
    { REG_AX5043_TMGRXSETTLE,         0x31},
    { REG_AX5043_TMGRXOFFSACQ,        0x00},
    { REG_AX5043_TMGRXCOARSEAGC,      0x7F},
    { REG_AX5043_TMGRXRSSI,           0x03},
    { REG_AX5043_TMGRXPREAMBLE2,      0x35},
    { REG_AX5043_RSSIABSTHR,          0xE0},
    { REG_AX5043_BGNDRSSITHR,         0x00},
    { REG_AX5043_PKTCHUNKSIZE,        0x0D},
    { REG_AX5043_PKTACCEPTFLAGS,      0x20},
    { REG_AX5043_DACVALUE1,           0x00},
    { REG_AX5043_DACVALUE0,           0x00},
    { REG_AX5043_DACCONFIG,           0x00},
    { REG_AX5043_REF,                 0x03},
    { REG_AX5043_0xF1C,               0x07},
    { REG_AX5043_0xF21,               0x68},
    { REG_AX5043_0xF22,               0xFF},
    { REG_AX5043_0xF23,               0x84},
    { REG_AX5043_0xF26,               0x98},
    { REG_AX5043_0xF34,               0x28},
    { REG_AX5043_0xF35,               0x11},
    { REG_AX5043_0xF44,               0x25},
    {AX5043_Addr_END    , AX5043_Vule_END}
};

const unsigned int TXMODE_REG[][2]=
{
#if(XTAL_FREQ == 26000000)
    {
        REG_AX5043_PLLLOOP  , 0x0b
    },
    { REG_AX5043_PLLCPI   , 0x10    },
    { REG_AX5043_PLLVCODIV  , 0x24   },
    { REG_AX5043_PLLVCOI  , 0x99   },
    { REG_AX5043_XTALCAP  , 0x00   },
    { REG_AX5043_0xF00   , 0x0f    },
    { REG_AX5043_REF   , 0x03    },
    { REG_AX5043_0xF18   , 0x06    }
#endif
};

const unsigned int RXMODE_REG[][2]=
{
#if(XTAL_FREQ == 26000000)
    {
        REG_AX5043_PLLLOOP  , 0x0b
    },
    { REG_AX5043_PLLCPI   , 0x10  },
    { REG_AX5043_PLLVCODIV  , 0x24 },
    { REG_AX5043_PLLVCOI  , 0x99  },
    { REG_AX5043_XTALCAP  , 0x0c  },
    { REG_AX5043_0xF00   , 0x0f  },
    { REG_AX5043_REF   , 0x03   },
    { REG_AX5043_0xF18   , 0x02  }
#endif
};

struct rt_spi_device *ax5043_radio_spi_init(const char *bus_name,const char *device_name)
{
    rt_err_t res;
    struct rt_spi_device *radio_spi_device;

    RT_ASSERT(bus_name);

    {
        res = rt_hw_spi_device_attach( bus_name, device_name, RADIO_NSS_PORT, RADIO_NSS_PIN);

        if (res != RT_EOK)
        {
            LOG_D("rt_spi_bus_attach_device failed!\r\n");
            return RT_NULL;
        }

        radio_spi_device = (struct rt_spi_device *)rt_device_find(RADIO_Device_Name);
        if (!radio_spi_device)
        {
            LOG_D("spi sample run failed! cant't find %s device!\n", RADIO_Device_Name);
            return RT_NULL;
        }
    }

    LOG_D("find %s device!\n", RADIO_Device_Name);

    /* config spi */
    {
        struct rt_spi_configuration cfg;
        cfg.data_width = 8;
        cfg.mode = RT_SPI_MASTER | RT_SPI_MODE_0 | RT_SPI_MSB; /* SPI Compatible: Mode 0. */
        cfg.max_hz = 8 * 1000000;             /* max 10M */

        res = rt_spi_configure(radio_spi_device, &cfg);

        if (res != RT_EOK)
        {
            LOG_D("rt_spi_configure failed!\r\n");
        }
        res = rt_spi_take_bus(radio_spi_device);
        if (res != RT_EOK)
        {
            LOG_D("rt_spi_take_bus failed!\r\n");
        }

        res = rt_spi_release_bus(radio_spi_device);

        if(res != RT_EOK)
        {
            LOG_D("rt_spi_release_bus failed!\r\n");
        }
    }

    return radio_spi_device;
}

void IRQ_Bounding(void)
{
    rt_pin_mode(Radio_IRQ, PIN_MODE_INPUT_PULLUP);
    rt_pin_attach_irq(Radio_IRQ, PIN_IRQ_MODE_RISING, Receive_ISR, RT_NULL);
    rt_pin_irq_enable(Radio_IRQ, PIN_IRQ_ENABLE);
}
void Ax5043_Spi_Init(void)
{
    ax5043_device = ax5043_radio_spi_init("spi2",RADIO_Device_Name);
}

void AX5043_Reset(void)//复位
{
    unsigned char ubAddres;
    uint8_t msg[2] = {0};

    msg[0] = REG_AX5043_PWRMODE|0x80 ;
    msg[1] = 0x80 ;
    rt_spi_send(ax5043_device,msg,2);                                //write comm  bit7=1
    SpiWriteSingleAddressRegister(REG_AX5043_PWRMODE, 0x00);        //RADIO_PWRMODE = PWRMODE_PWRDOWN=0x00
    SpiWriteSingleAddressRegister(REG_AX5043_SCRATCH, 0x55);
    do
    {
        ubAddres = SpiReadSingleAddressRegister(REG_AX5043_SCRATCH);
    }
    while (ubAddres != 0x55);

    SpiWriteSingleAddressRegister(REG_AX5043_PINFUNCIRQ, 0x01);  // IRQ Line 1   001 IRQ Output ’1’
    SpiWriteSingleAddressRegister(REG_AX5043_PINFUNCIRQ, 0x00);  //IRQ Line 0  000 IRQ Output ’0’
    SpiWriteSingleAddressRegister(REG_AX5043_PINFUNCIRQ, 0x03);  //011 IRQ Output Interrupt Request
}
MSH_CMD_EXPORT(AX5043_Reset,AX5043_Reset);
/***********************************************************************
==单字节写==
***********************************************************************/
void SpiWriteByte(unsigned char ubByte)
{
    rt_spi_send(ax5043_device,&ubByte,1);
}

/***********************************************************************
==双字节写==
***********************************************************************/
void SpiWriteWord(unsigned int ubByte)
{
    uint8_t msg[2] = {0};
    msg[0] = ( ubByte & 0xFF00 ) >> 8;
    msg[1] = ubByte & 0x00FF;
    rt_spi_send(ax5043_device,msg,2);
}
/***********************************************************************
==单字节读==
***********************************************************************/
unsigned char SpiReadByte( void )
{
    uint8_t data;
    rt_spi_recv(ax5043_device,&data,1);
    return data;
}
/***********************************************************************
==写单字节地址==
***********************************************************************/
void SpiWriteSingleAddressRegister(unsigned char Addr, unsigned char Data)
{
    uint8_t ubAddr = Addr|0x80;
    rt_spi_send_then_send(ax5043_device,&ubAddr,1,&Data,1);
}
/***********************************************************************
==写双字节地址==
***********************************************************************/
void SpiWriteLongAddressRegister(unsigned int Addr, unsigned char Data)
{
    uint16_t ubAddr;
    ubAddr = Addr|0xF000;
    uint8_t msg[2] = {0};
    msg[0] = ( ubAddr & 0xFF00 ) >> 8;
    msg[1] = ubAddr & 0x00FF;

    rt_spi_send_then_send(ax5043_device,msg,2,&Data,1);
}
void SpiLongWriteLongAddressRegister(unsigned int Addr, unsigned int Data)
{
    uint16_t ubAddr;
    ubAddr = Addr|0xF000;
    uint8_t msg1[2] = {0};
    uint8_t msg2[2] = {0};
    msg1[0] = ( ubAddr & 0xFF00 ) >> 8;
    msg1[1] = ubAddr & 0x00FF;
    msg2[0] = ( Data & 0xFF00 ) >> 8;
    msg2[1] = Data & 0x00FF;
    rt_spi_send_then_send(ax5043_device,msg1,2,msg2,2);
}
/***********************************************************************
==写数据==
***********************************************************************/
void SpiWriteData(unsigned char *pBuf,unsigned char Length)
{
    unsigned char  data;
    data=REG_AX5043_FIFODATA| 0x80;
    rt_spi_send_then_send(ax5043_device,&data,1,pBuf,Length);
}
/***********************************************************************
==读取指定寄存器==
***********************************************************************/
unsigned char SpiReadSingleAddressRegister(unsigned char Addr)
{
    unsigned char ubAddr ;
    unsigned char RcvAddr ;
    ubAddr = Addr&0x7F ;//read common bit7=0
    rt_spi_send_then_recv(ax5043_device,&ubAddr,1,&RcvAddr,1);
    return RcvAddr ;
}

/***********************************************************************
==读取指定长寄存器==
***********************************************************************/
unsigned char SpiReadLongAddressRegister(unsigned int Addr)
{
    unsigned int ubAddr ;
    unsigned char RcvAddr ;
    ubAddr = Addr|0x7000 ;//read common bit7=0
    uint8_t msg[2] = {0};
    msg[0] = ( ubAddr & 0xFF00 ) >> 8;
    msg[1] = ubAddr & 0x00FF;
    rt_spi_send_then_recv(ax5043_device,msg,2,&RcvAddr,1);
    return RcvAddr ;
}

/***********************************************************************
==读取数据==
***********************************************************************/
void SpiReadData(unsigned char *pBuf,unsigned char Length)
{
    unsigned char SendAddr ;
    SendAddr=REG_AX5043_FIFODATA & 0x7F;
    rt_spi_send_then_recv(ax5043_device,&SendAddr,1,pBuf,Length);
}

/***********************************************************************
* Funcation ��
* Description��
* InPut    ��
* OutPut   ��
* Return   ��
* Notice   ��
***********************************************************************/
char SetChannel(unsigned char ubNum )
{
    unsigned char ubRang;
    unsigned char ubTemp;          //ubData;
    unsigned long RadioChannel;

    ubRang = AxRadioPHYChanPllRng_RX[ubNum];

    //RadioChannel  = ChannelTable[ubNum];
    RadioChannel  = WirelessFreqConfigure(0x06,0xA2,0x0c,ubNum);

    //RadioChannel += axradio_curfreqoffset;  //����Ƶ�ʲ���
    ubTemp = SpiReadSingleAddressRegister(REG_AX5043_PLLLOOP);  //��PLLLOOP
    if (ubTemp & 0x80)
    {
        SpiWriteSingleAddressRegister(REG_AX5043_PLLRANGINGA, ubRang&0x0F);
        SpiWriteSingleAddressRegister(REG_AX5043_FREQA0, RadioChannel&0xFF);       //AX5043_FREQA0 = f;
        SpiWriteSingleAddressRegister(REG_AX5043_FREQA1, (RadioChannel>>8)&0xFF);  //AX5043_FREQA1 = f >> 8;
        SpiWriteSingleAddressRegister(REG_AX5043_FREQA2, (RadioChannel>>16)&0xFF); //AX5043_FREQA2 = f >> 16;
        SpiWriteSingleAddressRegister(REG_AX5043_FREQA3, (RadioChannel>>24)&0xFF); //AX5043_FREQA3 = f >> 24;
    }
    else
    {
        SpiWriteSingleAddressRegister(REG_AX5043_PLLRANGINGB, ubRang&0x0F);     //AX5043_PLLRANGINGB = rng & 0x0F;
        SpiWriteSingleAddressRegister(REG_AX5043_FREQB0, RadioChannel&0xFF);       //AX5043_FREQB0 = f;
        SpiWriteSingleAddressRegister(REG_AX5043_FREQB1, (RadioChannel>>8)&0xFF);  //AX5043_FREQB1 = f >> 8;
        SpiWriteSingleAddressRegister(REG_AX5043_FREQB2, (RadioChannel>>16)&0xFF); //AX5043_FREQB2 = f >> 16;
        SpiWriteSingleAddressRegister(REG_AX5043_FREQB3, (RadioChannel>>24)&0xFF); //AX5043_FREQB3 = f >> 24;
    }
    ubTemp^=0x80 ;
    SpiWriteSingleAddressRegister(REG_AX5043_PLLLOOP, ubTemp);                        //AX5043_PLLLOOP ^= 0x80;

    return AXRADIO_ERR_NOERROR;
}

/***********************************************************************
* Funcation ��
* Description��
* InPut    ��
* OutPut   ��
* Return   ��
* Notice   ��
***********************************************************************/

/***********************************************************************
* Funcation ��void InitAx5043REG(void)
* Description��init all register and local pktaddr
* InPut    ��
* OutPut   ��
* Return   ��
* Notice   ��
***********************************************************************/
void InitAx5043REG(void)
{
    unsigned char ubi;

    for (ubi = 0; ((RegisterVaule[ubi][0] != 0xFF)&&(RegisterVaule[ubi][1] != 0xDD));ubi++)
    {
        SpiWriteLongAddressRegister(RegisterVaule[ubi][0] , RegisterVaule[ubi][1] );
    }

    WirelessBitRateConfigure(0x02);
    WirelessTxPowerConfigure(0x03);

    SpiWriteSingleAddressRegister(REG_AX5043_PINFUNCIRQ, 0x03);    // AX5043_PINFUNCIRQ = 0x03;  use as IRQ pin

}

/***********************************************************************
* Funcation ��void Ax5043SetRegisters_TX(void)
* Description��set Tx register
* InPut    ��
* OutPut   ��
* Return   ��
* Notice   ��
***********************************************************************/
void Ax5043SetRegisters_TX(void)
{
    unsigned char ubi;

    for (ubi = 0x00;ubi < 8;ubi++)
    {
        SpiWriteLongAddressRegister(TXMODE_REG[ubi][0] , TXMODE_REG[ubi][1] );
    }
#if (XTAL_FREQ == 26000000)
    switch (0x02)//configData[DATARATE_LOCAT]
    {
        case 0:
        case 1:
        case 2:
            SpiWriteLongAddressRegister(REG_AX5043_PLLLOOP,0x0b);
            SpiWriteLongAddressRegister(REG_AX5043_PLLCPI,0x10);
            break;
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
            SpiWriteLongAddressRegister(REG_AX5043_PLLLOOP,0x09);
            SpiWriteLongAddressRegister(REG_AX5043_PLLCPI,0x02);
            break;
    }
#endif

}

/***********************************************************************
* Funcation ��void Ax5043SetRegisters_RX(void)
* Description��set Rx register
* InPut    ��
* OutPut   ��
* Return   ��
* Notice   ��
***********************************************************************/
void Ax5043SetRegisters_RX(void)
{
    unsigned char ubi;

    for (ubi = 0x00;ubi < 8;ubi++)
    {
        SpiWriteLongAddressRegister(RXMODE_REG[ubi][0] , RXMODE_REG[ubi][1] );
    }
#if (XTAL_FREQ == 26000000)
    switch (0x02)//configData[DATARATE_LOCAT]
    {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
            SpiWriteLongAddressRegister(REG_AX5043_PLLLOOP,0x0b);
            SpiWriteLongAddressRegister(REG_AX5043_PLLCPI,0x10);
            break;
        case 5:
        case 6:
        case 7:
        case 8:
            SpiWriteLongAddressRegister(REG_AX5043_PLLLOOP,0x09);
            SpiWriteLongAddressRegister(REG_AX5043_PLLCPI,0x01);
            break;
    }
#endif

}
//static void wait_n_lposccycles(uint8_t n)
//{
//    uint8_t cnt = 0;
//    EA = 0; // isr is not handling lposc irq
//    AX5043_IRQMASK1 |= 0x04; // LPOSC irq
//    for(;;)
//    {
//        if( AX5043_IRQREQUEST1 & 0x04 )
//        {
//            cnt++;
//            AX5043_LPOSCSTATUS; // clear irq request
//        }
//
//        if(cnt > n)
//            break;
//        enter_standby();
//    }
//
//    AX5043_IRQMASK1 &= ~0x04; // disable LPOSC irq
//    EA = 1;
//}
void calibrate_lposc(void)
{
        uint16_t lposckfiltmax = 0x142a;
        //AX5043_LPOSCFREQ1 = 0x00;
        SpiWriteLongAddressRegister(AX5043_LPOSCFREQ1,0x00);
        //AX5043_LPOSCFREQ0 = 0x00;
        SpiWriteLongAddressRegister(AX5043_LPOSCFREQ0,0x00);

        //AX5043_LPOSCREF1 = ((XTAL_FREQ/640)>>8) & 0xFF;
        SpiWriteLongAddressRegister(AX5043_LPOSCREF1, ((XTAL_FREQ/640)>>8) & 0xFF);
        //AX5043_LPOSCREF0 = ((XTAL_FREQ/640)>>0) & 0xFF;
        SpiWriteLongAddressRegister(AX5043_LPOSCREF0,((XTAL_FREQ/640)>>0) & 0xFF);
        //AX5043_PWRMODE = AX5043_PWRSTATE_SYNTH_RX;
        SpiWriteSingleAddressRegister(REG_AX5043_PWRMODE, AX5043_PWRSTATE_SYNTH_TX);
        //AX5043_LPOSCKFILT1 = (lposckfiltmax >> (8 + 1)) & 0xFF; // kfiltmax >> 1
        SpiWriteLongAddressRegister(AX5043_LPOSCKFILT1,(lposckfiltmax >> (8 + 1)) & 0xFF);
        //AX5043_LPOSCKFILT0 = (lposckfiltmax >> 1) & 0xFF;
        SpiWriteLongAddressRegister(AX5043_LPOSCKFILT0,(lposckfiltmax >> 1) & 0xFF);
        //axradio_wait_for_xtal();

        //AX5043_LPOSCCONFIG =  0x25; // LPOSC ENA, slow mode; calibrate on rising edge, irq on rising edge
        SpiWriteLongAddressRegister(AX5043_LPOSCCONFIG,0x25);
        rt_thread_mdelay(6);

//        AX5043_LPOSCKFILT1 = (lposckfiltmax >> (8 + 2)) & 0xFF; // kfiltmax >> 2
//        AX5043_LPOSCKFILT0 = (lposckfiltmax >> 2) & 0xFF;
        SpiWriteLongAddressRegister(AX5043_LPOSCKFILT1,(lposckfiltmax >> (8 + 2)) & 0xFF);
        SpiWriteLongAddressRegister(AX5043_LPOSCKFILT0,(lposckfiltmax >> 2) & 0xFF);
        rt_thread_mdelay(5);

//        AX5043_LPOSCCONFIG = 0x00;
//        AX5043_PWRMODE = AX5043_PWRSTATE_POWERDOWN;
        //SpiWriteLongAddressRegister(AX5043_LPOSCCONFIG,0);
        //SpiWriteSingleAddressRegister(REG_AX5043_PWRMODE, AX5043_PWRSTATE_POWERDOWN);
        {
            uint8_t x = SpiReadLongAddressRegister(AX5043_LPOSCFREQ1);
            if( x == 0x7f || x == 0x80 )
            {
//                AX5043_LPOSCFREQ1 = 0;
//                AX5043_LPOSCFREQ0 = 0;
                SpiWriteLongAddressRegister(AX5043_LPOSCFREQ1,0);
                SpiWriteLongAddressRegister(AX5043_LPOSCFREQ0,0);
            }
        }
}
void ax5043_set_registers_rxwor(void)
{
    SpiWriteLongAddressRegister(AX5043_REG_TMGRXAGC,0x06);
    SpiWriteLongAddressRegister(AX5043_REG_TMGRXPREAMBLE1,0x19);
    SpiWriteLongAddressRegister(AX5043_REG_PKTMISCFLAGS,0x03);
}
MSH_CMD_EXPORT(ax5043_set_registers_rxwor,ax5043_set_registers_rxwor);
void reset_timer(void)
{
    uint16_t wp = 5000;
    SpiWriteSingleAddressRegister(REG_AX5043_WAKEUPFREQ1,(wp >> 8) & 0xFF);
    SpiWriteSingleAddressRegister(REG_AX5043_WAKEUPFREQ0,(wp >> 0) & 0xFF);
    wp += SpiReadLongAddressRegister(REG_AX5043_WAKEUPTIMER1);
    LOG_D("wp is %d\r\n",SpiReadLongAddressRegister(REG_AX5043_WAKEUPTIMER1));
    SpiWriteSingleAddressRegister(REG_AX5043_WAKEUP1,(wp >> 8) & 0xFF);
    SpiWriteSingleAddressRegister(REG_AX5043_WAKEUP0,(wp >> 0) & 0xFF);
    LOG_D("1 is %x\r\n",SpiReadLongAddressRegister(REG_AX5043_WAKEUP1));
    LOG_D("0 is %x\r\n",SpiReadLongAddressRegister(REG_AX5043_WAKEUP0));
}
void ax5043_receiver_on_wor(void)
{
    //unsigned char ubTemp;
    SpiWriteSingleAddressRegister(AX5043_BGNDRSSIGAIN,0x02);
    SpiWriteSingleAddressRegister(REG_AX5043_RADIOEVENTMASK0,0);
    SpiWriteSingleAddressRegister(REG_AX5043_FIFOSTAT,0x03);
    SpiWriteLongAddressRegister(AX5043_LPOSCCONFIG,1);
    SpiLongWriteLongAddressRegister(AX5043_RSSIREFERENCE,0xFA + 64);

    //SpiWriteLongAddressRegister(REG_AX5043_PKTSTOREFLAGS,0xBF);
//    ubTemp = SpiReadLongAddressRegister(REG_AX5043_PKTSTOREFLAGS);
//    ubTemp &= ~0x40;
//    SpiWriteLongAddressRegister(REG_AX5043_PKTSTOREFLAGS , ubTemp ); // AX5043_PKTSTOREFLAGS &= (uint8_t)~0x40;

    SpiWriteSingleAddressRegister(REG_AX5043_PWRMODE, AX5043_PWRSTATE_WOR_RX);//AX5043_PWRMODE = AX5043_PWRSTATE_POWERDOWN=0x00;
    ubRFState = trxstate_rxwor;
//    if(axradio_framing_enable_sfdcallback)
 //       AX5043_IRQMASK0 = 0x41; //  enable FIFO not empty / radio controller irq
//    else
//        AX5043_IRQMASK0 = 0x01; //  enable FIFO not empty
    SpiWriteSingleAddressRegister(REG_AX5043_IRQMASK0, 0x1);
    //SpiWriteSingleAddressRegister(REG_AX5043_IRQMASK0,SpiReadSingleAddressRegister(REG_AX5043_IRQMASK0)|0x80);
    SpiWriteSingleAddressRegister(REG_AX5043_POWIRQMASK,0X90);
    SpiWriteSingleAddressRegister(REG_AX5043_IRQMASK1, 0);

}
MSH_CMD_EXPORT(ax5043_receiver_on_wor,ax5043_receiver_on_wor);
void read(void)
{
    LOG_D("1 is %x\r\n",SpiReadLongAddressRegister(REG_AX5043_WAKEUP1));
    LOG_D("0 is %x\r\n",SpiReadLongAddressRegister(REG_AX5043_WAKEUP0));
    LOG_D("time is %d\r\n",SpiReadLongAddressRegister(REG_AX5043_WAKEUPTIMER1));
}
MSH_CMD_EXPORT(read,read);
void enable_wor(void)
{
    wor_flag=1;
    calibrate_lposc();
    ax5043_set_registers_rxwor();
    ax5043_receiver_on_wor();
    reset_timer();
}
MSH_CMD_EXPORT(enable_wor,enable_wor);
void restart_wor(void)
{
    LOG_D("Before");
    readirq();
    read();
    ax5043_set_registers_rxwor();
    ax5043_receiver_on_wor();
    LOG_D("After");
    readirq();
}
MSH_CMD_EXPORT(restart_wor,restart_wor);
/***********************************************************************
* Funcation ��void RdioXtalON(void)
* Description��
* InPut    ��
* OutPut   ��
* Return   ��
* Notice   ��
***********************************************************************/
void RdioXtalON(void)
{
    unsigned char ubTemp;

    rt_pin_mode(XTAL_PWR, PIN_MODE_OUTPUT);
    rt_pin_write(XTAL_PWR, 1);

    rt_thread_mdelay(2000);

    ubRFState = trxstate_wait_xtal;
    ubTemp = SpiReadSingleAddressRegister(REG_AX5043_IRQMASK1);
    SpiWriteSingleAddressRegister(REG_AX5043_IRQMASK1, ubTemp|0x01);            // enable xtal ready interrupt
    SpiWriteSingleAddressRegister(REG_AX5043_PWRMODE, AX5043_PWRSTATE_XTAL_ON); //AX5043_PWRSTATE_XTAL_ON=0x5
    do
    {
        asm("NOP");
        asm("NOP");
    }
    while (ubRFState == trxstate_wait_xtal);     //wait for ubRFState=trxstate_xtal_ready
}

unsigned char InitAX5043(void)
{
    unsigned char ubi,ubTemp;
    unsigned long uwFreq;
    uint8_t pllloop_save, pllcpi_save;

    Ax5043_Spi_Init();//Spi初始化

    IRQ_Bounding();

    AX5043_OFF();

    AX5043_Reset();
    InitAx5043REG();
    RdioXtalON();



    Ax5043SetRegisters_RX();
    pllloop_save = SpiReadSingleAddressRegister(REG_AX5043_PLLLOOP);
    pllcpi_save = SpiReadSingleAddressRegister(REG_AX5043_PLLCPI);

    SpiWriteSingleAddressRegister(REG_AX5043_PLLLOOP, 0x09);// AX5043_PLLLOOP = 0x09;default 100kHz loop BW for ranging
    SpiWriteSingleAddressRegister(REG_AX5043_PLLCPI, 0x08); //AX5043_PLLCPI = 0x08;

    for (ubi = 0x00; ubi < CHANNEL_NUM ;ubi++)
    {
        uwFreq = WirelessFreqConfigure(0x06,0xA2,0x0c,ubi);
        SpiWriteSingleAddressRegister(REG_AX5043_FREQA0, uwFreq&0xFF);
        SpiWriteSingleAddressRegister(REG_AX5043_FREQA1, (uwFreq>>8)&0xFF);
        SpiWriteSingleAddressRegister(REG_AX5043_FREQA2, (uwFreq>>16)&0xFF);
        SpiWriteSingleAddressRegister(REG_AX5043_FREQA3, (uwFreq>>24)&0xFF);
        if ( !(0x0a & 0xF0) )     // start values for ranging available
        {
            ubTemp = 0x0a | 0x10;
        }
        else
        {
            ubTemp = 0x18;
            if (ubi)
            {
                ubTemp = AxRadioPHYChanPllRng_RX[ubi - 1];
                if ( ubTemp & 0x20)
                    ubTemp = 0x08;
                ubTemp &= 0x0F;
                ubTemp |= 0x10;
            }
        }
        ubRFState = trxstate_pll_ranging;
        SpiWriteSingleAddressRegister(REG_AX5043_IRQMASK1, 0x10);     // enable pll autoranging done interrupt
        SpiWriteSingleAddressRegister(REG_AX5043_PLLRANGINGA, ubTemp); //init ranging process starting from "range"
        do
        {
            //delay(1);
            asm("NOP");
            asm("NOP");
        }
        while (ubRFState == trxstate_pll_ranging); //while(ubRFState != trxstate_pll_ranging_done); wait for trxstate_pll_ranging_done

        ubRFState = trxstate_off;
        SpiWriteSingleAddressRegister(REG_AX5043_IRQMASK0, 0x00);
        SpiWriteSingleAddressRegister(REG_AX5043_IRQMASK1, 0x00);     //AX5043_IRQMASK1 = 0x00;
        ubTemp = SpiReadSingleAddressRegister(REG_AX5043_PLLRANGINGA);
        AxRadioPHYChanPllRng_RX[ubi] = ubTemp;                        //AX5043_PLLRANGINGA;
    }

    //================================================================
    Ax5043SetRegisters_TX();
    SpiWriteSingleAddressRegister(REG_AX5043_PLLLOOP, 0x09); // AX5043_PLLLOOP = 0x09;default 100kHz loop BW for ranging
    SpiWriteSingleAddressRegister(REG_AX5043_PLLCPI, 0x08);  //AX5043_PLLCPI = 0x08;

    // for (ubi=0x00;ubi < 16 ;ubi++)
    for (ubi = 0x00;ubi < CHANNEL_NUM ;ubi++)
    {
        if ( !(0x0a & 0xF0) )   // start values for ranging available
        {
            ubTemp = 0x0a | 0x10;
        }
        else
        {
            ubTemp = AxRadioPHYChanPllRng_RX[ubi];
            if ( ubTemp & 0x20)
                ubTemp = 0x08;
            ubTemp &= 0x0F;
            ubTemp |= 0x10;
        }

        ubRFState = trxstate_pll_ranging;
        SpiWriteSingleAddressRegister(REG_AX5043_IRQMASK1, 0x10);      // enable pll autoranging done interrupt
        SpiWriteSingleAddressRegister(REG_AX5043_PLLRANGINGA, ubTemp); //  init ranging process starting from "range"

        do
        {
            asm("NOP");
            asm("NOP");//delay(1);
        }
        while (ubRFState == trxstate_pll_ranging);//while(ubRFState != trxstate_pll_ranging_done);

        ubRFState = trxstate_off;
        SpiWriteSingleAddressRegister(REG_AX5043_IRQMASK0, 0x00);     //disable low byte interrupt
        SpiWriteSingleAddressRegister(REG_AX5043_IRQMASK1, 0x00);     //disable high byte interrupt
        ubTemp=SpiReadSingleAddressRegister(REG_AX5043_PLLRANGINGA);
        AxRadioPHYChanPllRng_TX[ubi] = ubTemp;                        //AX5043_PLLRANGINGA;
    }

    SpiWriteSingleAddressRegister(REG_AX5043_PWRMODE, AX5043_PWRSTATE_POWERDOWN); // AX5043_PWRMODE = AX5043_PWRSTATE_POWERDOWN=0x00;
    ubTemp = AxRadioPHYChanPllRng_RX[0]&0x0F;                                     //AX5043_PLLRANGINGA = axradio_phy_chanpllrng_rx[0] & 0x0F;
    SpiWriteSingleAddressRegister(REG_AX5043_PLLRANGINGA,ubTemp );

    uwFreq = WirelessFreqConfigure(0x06,0xA2,0X0C,0);//
    //uwFreq = ChannelTable[0];

    SpiWriteSingleAddressRegister(REG_AX5043_FREQA0, uwFreq&0xFF);
    SpiWriteSingleAddressRegister(REG_AX5043_FREQA1, (uwFreq>>8)&0xFF);
    SpiWriteSingleAddressRegister(REG_AX5043_FREQA2, (uwFreq>>16)&0xFF);
    SpiWriteSingleAddressRegister(REG_AX5043_FREQA3, (uwFreq>>24)&0xFF);
    AxRadioPHYChanPllRng_TX[0] = AxRadioPHYChanPllRng_RX[0];

    //Whether all the channels in the range of Settings
    //for (ubi = 0x00;ubi < 16 ;ubi++)
    SpiWriteSingleAddressRegister(REG_AX5043_PLLLOOP, pllloop_save);
    SpiWriteSingleAddressRegister(REG_AX5043_PLLCPI,pllcpi_save);

	SpiWriteLongAddressRegister(REG_AX5043_POWCTRL1, 0x07);

    for (ubi = 0x00;ubi < CHANNEL_NUM ;ubi++)
    {
        if ((AxRadioPHYChanPllRng_TX[ubi] |AxRadioPHYChanPllRng_RX[ubi] ) & 0x20)
        {
            return AXRADIO_ERR_RANGING;
        }
    }
    return AXRADIO_ERR_NOERROR;
}

void sleep(void)
{
    // ax5043_off_xtal()
    //SpiWriteSingleAddressRegister(REG_AX5043_IRQMASK0, 0x00);      // IRQ off
   // SpiWriteSingleAddressRegister(REG_AX5043_IRQMASK1, 0x00);
    //SpiWriteSingleAddressRegister(REG_AX5043_PWRMODE, AX5043_PWRSTATE_XTAL_ON);    //AX5043_PWRMODE = AX5043_PWRSTATE_XTAL_ON=0x00;
    //SpiWriteLongAddressRegister(REG_AX5043_LPOSCCONFIG, 0x00);                    //AX5043_LPOSCCONFIG(0x310) = 0x00; // LPOSC off
    //ubRFState = trxstate_off;
    ax5043_set_registers_rxwor();
    SpiWriteSingleAddressRegister(REG_AX5043_PWRMODE, AX5043_PWRSTATE_WOR_RX);//AX5043_PWRMODE = AX5043_PWRSTATE_POWERDOWN=0x00;
//    rt_pin_mode(Radio_IRQ, 0);
//    rt_pin_write(Radio_IRQ,0);
    //rt_pin_mode(XTAL_PWR, 0);
    //rt_pin_write(XTAL_PWR,0);
//    rt_pin_mode(MISO, 0);
//    rt_pin_write(MISO,0);
//    rt_pin_mode(MOSI, 0);
//    rt_pin_write(MOSI,0);
//    rt_pin_mode(SYSCLK, 0);
//    rt_pin_write(SYSCLK,0);
//    rt_pin_mode(SCK, 0);
//    rt_pin_write(SCK,0);
//    rt_pin_mode(CS, 0);
//    rt_pin_write(CS,0);

}
MSH_CMD_EXPORT(sleep,sleep);
void wake(void)
{
    //���FIFO
    rt_pin_write(XTAL_PWR,1);
    SpiWriteSingleAddressRegister(REG_AX5043_FIFOSTAT,0x03);  // AX5043_FIFOSTAT(0x28) = 3;  bit[5:0]=0b00011 Clear FIFO Data and Flags  ���FIFO page 69
    SpiWriteSingleAddressRegister(REG_AX5043_PWRMODE,AX5043_PWRSTATE_FULL_RX); //AX5043_PWRSTATE_FULL_RX =0x09; bit[3:0]=1001 Receiver Running page55 ��������
    ubRFState = trxstate_rx;
    SpiWriteSingleAddressRegister(REG_AX5043_IRQMASK0,0x01);//AX5043_IRQMASK0��0x07�� = 0x01;  enable FIFO not empty
    SpiWriteSingleAddressRegister(REG_AX5043_IRQMASK1,0x00);
}
MSH_CMD_EXPORT(wake,wake);
/***********************************************************************
* Funcation ��void SetTransmitMode(void)
* Description��
* InPut    ��
* OutPut   ��
* Return   ��
* Notice   ��
***********************************************************************/
void SetTransmitMode(void)
{
    unsigned char Rng;
    unsigned char ubData;

    Ax5043SetRegisters_TX();
    Rng = AxRadioPHYChanPllRng_TX[0];//configData[CHANNEL_LOCAT]
    ubData=SpiReadSingleAddressRegister(REG_AX5043_PLLLOOP);
    if (ubData & 0x80)
    {
        SpiWriteSingleAddressRegister(REG_AX5043_PLLRANGINGB, Rng&0x0F);   //AX5043_PLLRANGINGB = rng & 0x0F;
    }
    else
    {
        SpiWriteSingleAddressRegister(REG_AX5043_PLLRANGINGA , Rng&0x0F);   //  AX5043_PLLRANGINGA = rng & 0x0F;
    }
}
/***********************************************************************
* Funcation ��
* Description��
* InPut    ��
* OutPut   ��
* Return   ��
* Notice   ��
***********************************************************************/
void AX5043ReceiverON(void)
{
    unsigned char ubTemp;
    SpiWriteLongAddressRegister(REG_AX5043_RSSIREFERENCE, 0x19);
    SpiWriteLongAddressRegister(REG_AX5043_TMGRXPREAMBLE1, 0x00); //   AX5043_TMGRXPREAMBLE1(0x229) = 0x00;
    ubTemp = SpiReadLongAddressRegister(REG_AX5043_PKTSTOREFLAGS);
    ubTemp &= ~0x40;
    SpiWriteLongAddressRegister(REG_AX5043_PKTSTOREFLAGS , ubTemp ); // AX5043_PKTSTOREFLAGS &= (uint8_t)~0x40;

    //���FIFO
    SpiWriteSingleAddressRegister(REG_AX5043_FIFOSTAT,0x03);  // AX5043_FIFOSTAT(0x28) = 3;  bit[5:0]=0b00011 Clear FIFO Data and Flags  ���FIFO page 69
    SpiWriteSingleAddressRegister(REG_AX5043_PWRMODE,AX5043_PWRSTATE_FULL_RX); //AX5043_PWRSTATE_FULL_RX =0x09; bit[3:0]=1001 Receiver Running page55 ��������
    ubRFState = trxstate_rx;
    SpiWriteSingleAddressRegister(REG_AX5043_IRQMASK0,0x01);//AX5043_IRQMASK0��0x07�� = 0x01;  enable FIFO not empty
    SpiWriteSingleAddressRegister(REG_AX5043_IRQMASK1,0x00);
}


/***********************************************************************
* Funcation ��
* Description��
* InPut    ��
* OutPut   ��
* Return   ��
* Notice   ��
***********************************************************************/
void SetReceiveMode(void)
{
    unsigned char ubRng;
    unsigned char ubData;

    //ChannelPtr = 0x00;
    //SetChannel(configData[CHANNEL_LOCAT]);
    Ax5043SetRegisters_RX();

    ubRng = AxRadioPHYChanPllRng_RX[0]; //configData[CHANNEL_LOCAT]
    ubData=SpiReadSingleAddressRegister(REG_AX5043_PLLLOOP);
    if (ubData & 0x80)
    {
        SpiWriteSingleAddressRegister(REG_AX5043_PLLRANGINGB, ubRng&0x0F);   //AX5043_PLLRANGINGB = rng & 0x0F;
    }
    else
    {
        SpiWriteSingleAddressRegister(REG_AX5043_PLLRANGINGA , ubRng&0x0F);   //  AX5043_PLLRANGINGA = rng & 0x0F;
    }
}

/***********************************************************************
* Funcation ��
* Description��
* InPut    ��
* OutPut   ��
* Return   ��
* Notice   ��
***********************************************************************/
void ReceiveData(void)
{
    unsigned char ubDataLen,ubTepm;
    unsigned char ubTemCom;
    unsigned char ubDataFlag;
    unsigned char ubOffSet;
    signed char ubRssi;
    unsigned long uwFreqOffSet;    //RX Freq Offset
    int  uwRSSI;

    ubDataLen = SpiReadSingleAddressRegister(REG_AX5043_RADIOEVENTREQ0);  //RADIOEVENTREQ0(0x0F); bit0=1  FIFO not empty interrupt pending

    while (SpiReadSingleAddressRegister(REG_AX5043_IRQREQUEST0) & 0x01)   // bit0=1  FIFO not empty interrupt pending
    {
        ubTemCom = SpiReadSingleAddressRegister(REG_AX5043_FIFODATA);   // ��1���ֽ� read command
        ubDataLen = ubTemCom >>5 ;
        if (ubDataLen == 0x07)             //�����bit[7:5]=111  ��ʾ�ɱ�����ݳ���
        {
            ubDataLen = SpiReadSingleAddressRegister(REG_AX5043_FIFODATA); // ��2���ֽ� 7 means variable length, -> get length byte  ��� ���ݳ���
        }
        ubTemCom &=0x1F;
        switch (ubTemCom)
        {
            case AX5043_FIFOCMD_DATA: //0x0001 1111  ���bit[4:0]������  ubTemCom =0x01  ��ʾ����������,
                if (!ubDataLen)
                    break;
                ubDataFlag = SpiReadSingleAddressRegister(REG_AX5043_FIFODATA); //��3���ֽ�  ��־:0 /0/ UNENC/ RAW/ NOCRC/ RESIDUE /PKTEND /PKTSTART
                ubDataLen--;
                SpiReadData(RXBuff,ubDataLen);         //ax5043_readfifo(axradio_rxbuffer, len);  //��FIFO������
                RxLen = ubDataLen;
                rt_kprintf("Receive is");
                for( int i = 1; i < ubDataLen; i++ )
                {
                    rt_kprintf( " %02X", RXBuff[i] );
                }
                rt_kprintf("\r\n");
                ubTepm = SpiReadSingleAddressRegister(REG_AX5043_IRQMASK0);
                SpiWriteSingleAddressRegister(REG_AX5043_IRQMASK0, ubTepm&0xFE);   // disable FIFO not empty irq
                break;

            case AX5043_FIFOCMD_RFFREQOFFS:
                if (ubDataLen != 3)
                    goto dropchunk;
                ubOffSet = SpiReadSingleAddressRegister(REG_AX5043_FIFODATA);
                ubOffSet &= 0x0F;
                ubOffSet |= 1+(~(ubOffSet&0x08));
                uwFreqOffSet=((signed char)ubOffSet)>>8 ;
                uwFreqOffSet <<=8;
                uwFreqOffSet |= ubOffSet;
                uwFreqOffSet <<=8;
                ubOffSet = SpiReadSingleAddressRegister(REG_AX5043_FIFODATA);
                uwFreqOffSet |= ubOffSet;
                uwFreqOffSet <<=8;
                ubOffSet =SpiReadSingleAddressRegister(REG_AX5043_FIFODATA);
                uwFreqOffSet |= ubOffSet;
                break;

            case AX5043_FIFOCMD_RSSI:
                if (ubDataLen != 1)
                    goto dropchunk;
                ubRssi = SpiReadSingleAddressRegister(REG_AX5043_FIFODATA);
                uwRSSI = ubRssi - 32;
                break;

            case AX5043_FIFOCMD_TIMER:
                if (ubDataLen != 3)
                    goto dropchunk;
                SpiReadSingleAddressRegister(REG_AX5043_FIFODATA);
                SpiReadSingleAddressRegister(REG_AX5043_FIFODATA);
                SpiReadSingleAddressRegister(REG_AX5043_FIFODATA);
                break;

            default:
            dropchunk:
                if (!ubDataLen)
                    break;
                ubTepm = ubDataLen;
                do
                {
                    SpiReadSingleAddressRegister(REG_AX5043_FIFODATA);  // purge FIFO
                }
                while (--ubTepm);
                break;
        }
    }
    ubDataFlag = ubDataFlag;
    uwRSSI = uwRSSI;
}
MSH_CMD_EXPORT(ReceiveData,ReceiveData);
//=====================================================================
/***********************************************************************
* Funcation ��
* Description��
* InPut    ��
* OutPut   ��
* Return   ��
* Notice   ��
***********************************************************************/
void AX5043_OFF(void)
{
    // ax5043_off_xtal()
    SpiWriteSingleAddressRegister(REG_AX5043_IRQMASK0, 0x00);      // IRQ off
    SpiWriteSingleAddressRegister(REG_AX5043_IRQMASK1, 0x00);
    SpiWriteSingleAddressRegister(REG_AX5043_PWRMODE, AX5043_PWRSTATE_XTAL_ON);    //AX5043_PWRMODE = AX5043_PWRSTATE_XTAL_ON=0x00;
    SpiWriteLongAddressRegister(REG_AX5043_LPOSCCONFIG, 0x00);                    //AX5043_LPOSCCONFIG(0x310) = 0x00; // LPOSC off
    ubRFState = trxstate_off;
    SpiWriteSingleAddressRegister(REG_AX5043_PWRMODE, AX5043_PWRSTATE_POWERDOWN);//AX5043_PWRMODE = AX5043_PWRSTATE_POWERDOWN=0x00;
}

void transmit_packet_task(uint8_t *Buf, uint8_t u8Len)
{
    SetChannel(0);
    SpiWriteSingleAddressRegister(REG_AX5043_PWRMODE, AX5043_PWRSTATE_XTAL_ON); //AX5043_PWRMODE = AX5043_PWRSTATE_XTAL_ON;    Crystal Oscillator enabled
    SpiWriteSingleAddressRegister(REG_AX5043_PWRMODE, AX5043_PWRSTATE_FIFO_ON); //AX5043_PWRMODE = AX5043_PWRSTATE_FIFO_ON;    FIFO enabled
    SetTransmitMode();//   ����TX�Ĵ�����������TX����Ƶ��
    TxLen = u8Len;
    TxLen++;
    TXBuff[0] = TxLen;
    memcpy(TXBuff+1, Buf, u8Len);
    SpiWriteSingleAddressRegister(REG_AX5043_FIFOTHRESH1, 0x00);  //AX5043_FIFOTHRESH1(0x2E) = 0;
    SpiWriteSingleAddressRegister(REG_AX5043_FIFOTHRESH0, 0x80);  //AX5043_FIFOTHRESH0(0x2F) = 0x80;
    ubRFState = trxstate_tx_xtalwait;
    SpiWriteSingleAddressRegister(REG_AX5043_IRQMASK0, 0x00);     //AX5043_IRQMASK0 = 0x00;
    SpiWriteSingleAddressRegister(REG_AX5043_IRQMASK1, 0x01);     //AX5043_IRQMASK1 = 0x01; // enable xtal ready interrupt
}
extern void radio_test(void);
void Normal_send(uint8_t *Buf, uint8_t u8Len)
{
    LOG_D("Normal Send\r\n");
    axradio_txbuffer_cnt = 0;
    transmit_packet_task(Buf,u8Len);
    //rt_thread_mdelay(50);
}
void Wor_send(uint8_t *Buf, uint8_t u8Len)
{
    LOG_D("Wor_send\r\n");
    axradio_txbuffer_cnt = 130;
    transmit_packet_task(Buf,u8Len);
}
void wor_test1(void)
{
    WorSend(28000001, 30, 4, 1);
}
MSH_CMD_EXPORT(wor_test1,wor_test1);
void wor_test2(void)
{
    WorSend(28000001, 30, 4, 0);
}
MSH_CMD_EXPORT(wor_test2,wor_test2);
void radio_send1(void)
{
    uint8_t buf[]={0xA,0xB,0xC,0xD,0xE,0xF};
    transmit_packet_task(buf,sizeof(buf));
}
MSH_CMD_EXPORT(radio_send1,radio_send1);
void radio_send2(void)
{
    uint8_t buf[]={0x7b,0x31,0x30,0x30,0x31,0x30,0x38,0x36,0x31,0x2c,0x32,0x30,0x30,0x32,0x32,0x36,0x33,0x36,0x2c,0x30,0x30,0x32,0x2c,0x30,0x35,0x2c,0x30,0x7d,0x46,0x35,0x0D,0x0A};
    transmit_packet_task(buf,sizeof(buf));
}
MSH_CMD_EXPORT(radio_send2,radio_send2);
void radio_send3(void)
{
    uint8_t buf[]={0x7b,0x31,0x30,0x30,0x31,0x30,0x38,0x36,0x31,0x2c,0x32,0x30,0x30,0x32,0x32,0x36,0x33,0x36,0x2c,0x30,0x30,0x32,0x2c,0x30,0x36,0x2c,0x30,0x7d,0x46,0x36,0x0D,0x0A};
    transmit_packet_task(buf,sizeof(buf));
}
MSH_CMD_EXPORT(radio_send3,radio_send3);
static void TransmitData(void)
{
    unsigned char ubFreeCnt;
    unsigned char ubi;
    //uint16_t axradio_txbuffer_cnt = 28832;
    for (;;)
    {
        ubFreeCnt = SpiReadSingleAddressRegister(REG_AX5043_FIFOFREE0); //uint8_t cnt = AX5043_FIFOFREE0;
        if (SpiReadSingleAddressRegister(REG_AX5043_FIFOFREE1))
            ubFreeCnt = 0xff;
        switch (ubRFState)
        {
            case trxstate_tx_longpreamble: //A
                if (!axradio_txbuffer_cnt)
                {
                    ubRFState = trxstate_tx_shortpreamble;
                    axradio_txbuffer_cnt = axradio_phy_preamble_len;
                    goto shortpreamble;
                }
                if (ubFreeCnt < 4)
                    goto fifocommit;
                ubFreeCnt = 7;
                if (axradio_txbuffer_cnt < 7)
                {
                    ubFreeCnt = axradio_txbuffer_cnt;
                }
                axradio_txbuffer_cnt -= ubFreeCnt;
                ubFreeCnt <<= 5;
                SpiWriteSingleAddressRegister(REG_AX5043_FIFODATA, 0x02 | (3 << 5));     //AX5043_FIFODATA = AX5043_FIFOCMD_REPEATDATA | (3 << 5); //0x62  bit[7:5]= 011 Three byte payload;#define AX5043_FIFOCMD_REPEATDATA 0x02
                SpiWriteSingleAddressRegister(REG_AX5043_FIFODATA, 0x38);     //AX5043_FIFODATA = axradio_phy_preamble_flags;  //axradio_phy_preamble_flags = 0x38; 0b0011 1000  bit5=UNENC bit4=RAW  bit3=NOCRC
                SpiWriteSingleAddressRegister(REG_AX5043_FIFODATA, ubFreeCnt);//AX5043_FIFODATA = cnt;  //�ط�����
                SpiWriteSingleAddressRegister(REG_AX5043_FIFODATA, 0x55);      //AX5043_FIFODATA = axradio_phy_preamble_byte; //axradio_phy_preamble_byte = 0x55;  �ط�������
                //LOG_D("A Send\r\n");
                break;

            case trxstate_tx_shortpreamble:   //B
            shortpreamble:
                if (!axradio_txbuffer_cnt)
                {
                    ubi = SpiReadSingleAddressRegister(REG_AX5043_FRAMING);
                    if ((ubi & 0x0E) == 0x06 && axradio_framing_synclen)                                  //axradio_framing_synclen=32
                    {
                        uint8_t len_byte = axradio_framing_synclen;
                        uint8_t i = (len_byte & 0x07) ? 0x04 : 0;
                        len_byte += 7;
                        len_byte >>= 3;
                        SpiWriteSingleAddressRegister(REG_AX5043_FIFODATA,0x01 | ((len_byte + 1) << 5));//AX5043_FIFODATA =   0xA1; //0x01 | ((len_byte + 1) << 5);  //0xA1
                        SpiWriteSingleAddressRegister(REG_AX5043_FIFODATA,0x18|i);//AX5043_FIFODATA = 0x18;//axradio_framing_syncflags | i;  //0x18   �������ʾʲô?
                        SpiWriteSingleAddressRegister(REG_AX5043_FIFODATA,0xCC);//AX5043_FIFODATA = 0xcc;
                        SpiWriteSingleAddressRegister(REG_AX5043_FIFODATA,0xAA);//AX5043_FIFODATA = 0xaa;
                        SpiWriteSingleAddressRegister(REG_AX5043_FIFODATA,0xCC);//AX5043_FIFODATA = 0xcc;
                        SpiWriteSingleAddressRegister(REG_AX5043_FIFODATA,0xAA);//AX5043_FIFODATA = 0xaa;

                        ubRFState = trxstate_tx_packet;
                        break;
                    }
                }

                ubFreeCnt = 255;
                if (axradio_txbuffer_cnt < (255*8))
                    ubFreeCnt = axradio_txbuffer_cnt >> 3;
                if (ubFreeCnt)
                {
                    axradio_txbuffer_cnt -= ((uint16_t)ubFreeCnt) << 3;
                    SpiWriteSingleAddressRegister(REG_AX5043_FIFODATA , AX5043_FIFOCMD_REPEATDATA | (3 << 5));
                    SpiWriteSingleAddressRegister(REG_AX5043_FIFODATA ,axradio_phy_preamble_flags);
                    SpiWriteSingleAddressRegister(REG_AX5043_FIFODATA , ubFreeCnt);
                    SpiWriteSingleAddressRegister(REG_AX5043_FIFODATA ,axradio_phy_preamble_byte);
                    break;
                }
                {
                    uint8_t byte = axradio_phy_preamble_byte;
                    ubFreeCnt = axradio_txbuffer_cnt;
                    axradio_txbuffer_cnt = 0;
                    SpiWriteSingleAddressRegister(REG_AX5043_FIFODATA ,AX5043_FIFOCMD_DATA | (2 << 5));
                    SpiWriteSingleAddressRegister(REG_AX5043_FIFODATA, 0x1C);
                    if (SpiReadLongAddressRegister(REG_AX5043_PKTADDRCFG) & 0x80)
                    {
                        // msb first -> stop bit below
                        byte &= 0xFF << (8-ubFreeCnt);
                        byte |= 0x80 >> ubFreeCnt;
                    }
                    else
                    {
                        // lsb first -> stop bit above
                        byte &= 0xFF >> (8-ubFreeCnt);
                        byte |= 0x01 << ubFreeCnt;
                    }
                    SpiWriteSingleAddressRegister(REG_AX5043_FIFODATA, byte);
                }
                // ubRFState = trxstate_tx_packet;
                LOG_D("B Send\r\n");
                break;
            case trxstate_tx_packet:  //C
                TxLen +=1 ;
                SpiWriteSingleAddressRegister(REG_AX5043_FIFODATA, AX5043_FIFOCMD_DATA | (7 << 5));//AX5043_FIFODATA = AX5043_FIFOCMD_DATA | (7 << 5);
                SpiWriteSingleAddressRegister(REG_AX5043_FIFODATA,TxLen);//write FIFO chunk length byte (data length+MAC_len + Flag byte=64+3+1)
                SpiWriteSingleAddressRegister(REG_AX5043_FIFODATA,0x03);//AX5043_FIFODATA = flags=0x03;
                TxLen--;
                SpiWriteData( TXBuff,TxLen);          //ax5043_writefifo(&axradio_txbuffer[axradio_txbuffer_cnt], cnt);
                ubRFState = trxstate_tx_waitdone;
                SpiWriteSingleAddressRegister(REG_AX5043_RADIOEVENTMASK0,0x01);//AX5043_RADIOEVENTMASK0 = 0x01; // enable REVRDONE event
                SpiWriteSingleAddressRegister(REG_AX5043_IRQMASK0,0x40);        //AX5043_IRQMASK0 = 0x40; // enable radio controller irq
                SpiWriteSingleAddressRegister(REG_AX5043_FIFOSTAT,0x04);        //AX5043_FIFOSTAT = 4; // commit
                LOG_D("C Send,Len is %d\r\n",TxLen);
                break;
            default:
                return;
        }
    }
    fifocommit:
        SpiWriteSingleAddressRegister(REG_AX5043_FIFOSTAT, 4); // commit
}
void send_t_callback(void *parameter)
{
    axradio_txbuffer_cnt = 112;
//    uint8_t buf[]={1,2,3,4,5,6,7,8,9,0};
//    transmit_packet_task(buf,sizeof(buf));
    RadioSend(10010861,0,5,0);

}
void send_start(void)
{
    rt_timer_t send_t = RT_NULL;
    send_t = rt_timer_create("send", send_t_callback,RT_NULL, 7400, RT_TIMER_FLAG_PERIODIC|RT_TIMER_FLAG_SOFT_TIMER);
    rt_timer_start(send_t);
}
MSH_CMD_EXPORT(send_start,send_start)
rt_sem_t Radio_IRQ_Sem=RT_NULL;
rt_thread_t Radio_Task=RT_NULL;
void Receive_ISR(void *parameter)
{
    rt_sem_release(Radio_IRQ_Sem);
    LOG_D("IRQ Inturrpet\r\n");
}
uint8_t reg_list[]={REG_AX5043_IRQINVERSION0,REG_AX5043_IRQINVERSION1,REG_AX5043_IRQMASK0,REG_AX5043_IRQMASK1,REG_AX5043_IRQREQUEST0,REG_AX5043_IRQREQUEST1};
void readirq(void)
{
    uint16_t temp;
    for(uint8_t i=0;i<sizeof(reg_list);i++)
    {
        temp = SpiReadSingleAddressRegister(reg_list[i]);
        LOG_D("The %d Value is %x",i,temp);
    }
}
MSH_CMD_EXPORT(readirq,readirq);

void Radio_Task_Callback(void *parameter)
{
    while(1)
    {
        static rt_err_t result;
        result = rt_sem_take(Radio_IRQ_Sem, RT_WAITING_FOREVER);
        if (result == RT_EOK)
        {
            switch (ubRFState)
                    {
                        case trxstate_rx: //0x01
                            LOG_D("Got Data");
                            ReceiveData();
                            SpiWriteSingleAddressRegister(REG_AX5043_IRQMASK0,0x01);
                            AX5043ReceiverON();
                            if (RxLen != 0)
                            {
                                Rx_Done_Callback(RXBuff,RxLen);
                            }
                            if(wor_flag)
                            {
                                ax5043_receiver_on_wor();
                            }
                            break;

                        case trxstate_wait_xtal:     //3
                            SpiWriteSingleAddressRegister(REG_AX5043_IRQMASK0, 0x00);
                            SpiWriteSingleAddressRegister(REG_AX5043_IRQMASK1, 0x00);//AX5043_IRQMASK1 = 0x00 otherwise crystal ready will fire all over again
                            ubRFState = trxstate_xtal_ready;
                            break;

                        case trxstate_pll_ranging:     //5
                            SpiWriteSingleAddressRegister(REG_AX5043_IRQMASK0, 0x00);
                            SpiWriteSingleAddressRegister(REG_AX5043_IRQMASK1, 0x00);//AX5043_IRQMASK1 = 0x00 otherwise autoranging done will fire all over again
                            ubRFState = trxstate_pll_ranging_done;
                            break;

                        case trxstate_pll_settling:     //7
                            SpiWriteSingleAddressRegister(REG_AX5043_RADIOEVENTMASK0, 0x00);// AX5043_RADIOEVENTMASK0 = 0x00;
                            ubRFState = trxstate_pll_settled;
                            break;

                        case trxstate_tx_xtalwait:    //9
                            SpiReadSingleAddressRegister(REG_AX5043_RADIOEVENTREQ0); //make sure REVRDONE bit is cleared, so it is a reliable indicator that the packet is out
                            SpiWriteSingleAddressRegister(REG_AX5043_FIFOSTAT, 0x03);
                            SpiWriteSingleAddressRegister(REG_AX5043_IRQMASK1, 0x00);
                            SpiWriteSingleAddressRegister(REG_AX5043_IRQMASK0, 0x08);// enable fifo free threshold
                            ubRFState = trxstate_tx_longpreamble;
                            TransmitData();
                            SpiWriteSingleAddressRegister(REG_AX5043_PWRMODE, AX5043_PWRSTATE_FULL_TX); //AX5043_PWRMODE = AX5043_PWRSTATE_FULL_TX;
                            break;

                        case trxstate_tx_waitdone:                 //D
                            SpiReadSingleAddressRegister(REG_AX5043_RADIOEVENTREQ0);        //clear Interrupt flag
                            if (SpiReadSingleAddressRegister(REG_AX5043_RADIOSTATE) != 0)
                            {
                                break;
                            }
                            Tx_Done_Callback(TXBuff,TxLen);
                            SpiWriteSingleAddressRegister(REG_AX5043_RADIOEVENTMASK0, 0x00);
                            if(wor_flag)
                            {
                                restart_wor();
                            }
                            else
                            {
                                SetReceiveMode();           //接收模式
                                AX5043ReceiverON();         //接收开启
                            }

                            break;
                        case trxstate_rxwor:                 //D
                            LOG_D("Before");
                            readirq();
                            SpiReadLongAddressRegister(REG_AX5043_WAKEUPTIMER1);
                            if( SpiReadSingleAddressRegister(REG_AX5043_IRQREQUEST0) & 0x80 ) // power
                            {
                                SpiWriteSingleAddressRegister(REG_AX5043_IRQMASK1, 0x03);
                                SpiWriteSingleAddressRegister(REG_AX5043_IRQMASK0, 0xC1);
                                SpiWriteSingleAddressRegister(REG_AX5043_IRQMASK1, 0x03);
                                SpiWriteSingleAddressRegister(REG_AX5043_IRQMASK0, 0xC1);
                                SpiReadLongAddressRegister(REG_AX5043_WAKEUPTIMER1);
                                LOG_D("sleep\r\n");
                            }
                            if( SpiReadSingleAddressRegister(REG_AX5043_IRQREQUEST0) & 0x01 ) // fifo
                            {
                                ReceiveData();
                                ax5043_receiver_on_wor();
                                LOG_D("recv\r\n");
                            }
                            LOG_D("After");
                            readirq();
                            LOG_D("RX WOR\r\n");
                            break;
                        default:
                            SpiWriteSingleAddressRegister(REG_AX5043_IRQMASK1, 0x00);
                            SpiWriteSingleAddressRegister(REG_AX5043_IRQMASK0, 0x00);
                            break;
                    }
        }
    }
}
void xtal_off(void)
{
    rt_pin_write(XTAL_PWR,0);
}
MSH_CMD_EXPORT(xtal_off,xtal_off);
void Radio_Task_Init(void)
{
    Radio_IRQ_Sem = rt_sem_create("Radio_IRQ", 0, RT_IPC_FLAG_FIFO);
    Radio_Task = rt_thread_create("Radio_Task", Radio_Task_Callback, RT_NULL, 4096, 10, 10);\
    if(Radio_Task!=RT_NULL)rt_thread_startup(Radio_Task);
    if (InitAX5043() != AXRADIO_ERR_NOERROR)
    {
        LOG_D("Radio Init Fail\r\n");
        while(1);
    }
    LOG_D("Radio Init success\r\n");
    SetReceiveMode();           //接收模式
    AX5043ReceiverON();         //接收开启
    readirq();
    RadioDequeueTaskInit();
}
/********************************the end of file***********************/
