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
//
//#include "radiotest.h"
//#include <stdlib.h>
//#include <string.h>
//#include <rtthread.h>
//#include <rtdevice.h>
//#include "drv_spi.h"
//#include <string.h>
//#include "AX5043.h"
//#include "Radio_Config.h"
//#include "Radio.h"
//#include "pin_config.h"
//#include "Radio_Decoder.h"
//#include "Radio_Encoder.h"
//#include "configtest.h"
//
//typedef enum {
//    syncstate_off,
//    syncstate_lbt,
//    syncstate_asynctx,
//    syncstate_master_normal,
//    syncstate_master_xostartup,
//    syncstate_master_waitack,
//    syncstate_slave_synchunt,
//    syncstate_slave_syncpause,
//    syncstate_slave_rxidle,
//    syncstate_slave_rxxosc,
//    syncstate_slave_rxsfdwindow,
//    syncstate_slave_rxpacket,
//    syncstate_slave_rxack
//} axradio_syncstate_t;
//
//#define DBG_TAG "radio"
//#define DBG_LVL DBG_LOG
//#include <rtdbg.h>
//
//
//#define RADIO_NSS_PORT GPIOC
//#define RADIO_NSS_PIN GPIO_PIN_8
//#define RADIO_Device_Name "ax5043"
//
//struct rt_spi_device *ax5043_device;//spi设备
//
//volatile uint8_t axradio_mode = AXRADIO_MODE_UNINIT;
//volatile axradio_trxstate_t axradio_trxstate = trxstate_off;
//volatile axradio_syncstate_t axradio_syncstate;
//uint16_t axradio_txbuffer_len;
//uint16_t axradio_txbuffer_cnt;
//uint8_t axradio_curchannel;
//int32_t axradio_curfreqoffset;
//uint8_t axradio_ack_count;
//uint8_t axradio_ack_seqnr;
//#define axradio_sync_seqnr axradio_ack_seqnr
//uint32_t axradio_sync_time;
//int16_t axradio_sync_periodcorr;
//struct {
//    uint32_t timer0;
//    uint32_t radiotimer;
//} axradio_timeanchor;
//struct axradio_address_mask axradio_localaddr;
//struct axradio_address axradio_default_remoteaddr;
//
//#define SYNC_K0 2
//#define SYNC_K1 5
//
//uint8_t axradio_txbuffer[PKTDATA_BUFLEN];
//uint8_t axradio_rxbuffer[PKTDATA_BUFLEN];
//
//struct u32endian {
//    uint8_t b3;
//    uint8_t b2;
//    uint8_t b1;
//    uint8_t b0;
//};
//
//struct u16endian {
//    uint8_t b1;
//    uint8_t b0;
//};
//typedef void (*wtimer_callback_handler_t)(struct wtimer_callback *desc);
//typedef void (*wtimer_desc_handler_t)(struct wtimer_desc *desc);
//struct wtimer_callback {
//    // do not change the order
//    // must be compatible with wtimer_desc
//    struct wtimer_callback *next;
//    wtimer_callback_handler_t handler;
//};
//
//struct wtimer_desc {
//    // do not change the order
//    struct wtimer_desc *next;
//    wtimer_desc_handler_t handler;
//    uint32_t time;
//};
//struct axradio_callback_simple {
//    struct wtimer_callback cb;
//    struct {
//        uint8_t status;
//        uint8_t error;
//        union {
//            uint32_t t;
//            struct u32endian b;
//        } time;
//    } st;
//};
//
//struct axradio_callback_receive {
//    struct wtimer_callback cb;
//    struct {
//        uint8_t status;
//        uint8_t error;
//        union {
//            uint32_t t;
//            struct u32endian b;
//        } time;
//        struct {
//            struct {
//                int16_t rssi;
//                union {
//                    int32_t o;
//                    struct u32endian b;
//                } offset;
//                int16_t timeoffset;
//                int16_t period;
//            } phy;
//            struct axradio_status_receive_mac mac;
//            const uint8_t *pktdata;
//            uint16_t pktlen;
//        } rx;
//    } st;
//};
//
//struct axradio_callback_channelstate {
//    //struct wtimer_callback cb;
//    struct {
//        uint8_t status;
//        uint8_t error;
//        union {
//            uint32_t t;
//            struct u32endian b;
//        } time;
//        struct axradio_status_channelstate cs;
//    } st;
//};
//
//struct axradio_callback_receive axradio_cb_receive;
//struct axradio_callback_simple axradio_cb_receivesfd;
//struct axradio_callback_channelstate axradio_cb_channelstate;
//struct axradio_callback_simple axradio_cb_transmitstart;
//struct axradio_callback_simple axradio_cb_transmitend;
//struct axradio_callback_simple axradio_cb_transmitdata;
//struct wtimer_desc axradio_timer;
//
//volatile uint8_t f30_saved = 0x3f;
//volatile uint8_t f31_saved = 0xf0;
//volatile uint8_t f32_saved = 0x3f;
//volatile uint8_t f33_saved = 0xf0;
//
//#define memset_xdata memset
//#define memcpy_xdata memcpy
//#define memcpy_xdatageneric memcpy
//#define memcpy_genericxdata memcpy
//
//struct rt_spi_device *ax5043_radio_spi_init(const char *bus_name,const char *device_name)
//{
//    rt_err_t res;
//    struct rt_spi_device *radio_spi_device;
//
//    RT_ASSERT(bus_name);
//
//    {
//        res = rt_hw_spi_device_attach( bus_name, device_name, RADIO_NSS_PORT, RADIO_NSS_PIN);
//
//        if (res != RT_EOK)
//        {
//            LOG_D("rt_spi_bus_attach_device failed!\r\n");
//            return RT_NULL;
//        }
//
//        radio_spi_device = (struct rt_spi_device *)rt_device_find(RADIO_Device_Name);
//        if (!radio_spi_device)
//        {
//            LOG_D("spi sample run failed! cant't find %s device!\n", RADIO_Device_Name);
//            return RT_NULL;
//        }
//    }
//
//    LOG_D("find %s device!\n", RADIO_Device_Name);
//
//    /* config spi */
//    {
//        struct rt_spi_configuration cfg;
//        cfg.data_width = 8;
//        cfg.mode = RT_SPI_MASTER | RT_SPI_MODE_0 | RT_SPI_MSB; /* SPI Compatible: Mode 0. */
//        cfg.max_hz = 8 * 1000000;             /* max 10M */
//
//        res = rt_spi_configure(radio_spi_device, &cfg);
//
//        if (res != RT_EOK)
//        {
//            LOG_D("rt_spi_configure failed!\r\n");
//        }
//        res = rt_spi_take_bus(radio_spi_device);
//        if (res != RT_EOK)
//        {
//            LOG_D("rt_spi_take_bus failed!\r\n");
//        }
//
//        res = rt_spi_release_bus(radio_spi_device);
//
//        if(res != RT_EOK)
//        {
//            LOG_D("rt_spi_release_bus failed!\r\n");
//        }
//    }
//
//    return radio_spi_device;
//}
//
//void IRQ_Bounding(void)
//{
//    rt_pin_mode(Radio_IRQ, PIN_MODE_INPUT_PULLUP);
//    rt_pin_attach_irq(Radio_IRQ, PIN_IRQ_MODE_RISING, Receive_ISR, RT_NULL);
//    rt_pin_irq_enable(Radio_IRQ, PIN_IRQ_ENABLE);
//}
//void Ax5043_Spi_Init(void)
//{
//    ax5043_device = ax5043_radio_spi_init("spi2",RADIO_Device_Name);
//}
//void AX5043_Reset(void)//复位
//{
//    unsigned char ubAddres;
//    uint8_t msg[2] = {0};
//
//    msg[0] = REG_AX5043_PWRMODE|0x80 ;
//    msg[1] = 0x80 ;
//    rt_spi_send(ax5043_device,msg,2);                                //write comm  bit7=1
//    SpiWriteSingleAddressRegister(REG_AX5043_PWRMODE, 0x00);        //RADIO_PWRMODE = PWRMODE_PWRDOWN=0x00
//    SpiWriteSingleAddressRegister(REG_AX5043_SCRATCH, 0x55);
//    do
//    {
//        ubAddres = SpiReadSingleAddressRegister(REG_AX5043_SCRATCH);
//    }
//    while (ubAddres != 0x55);
//
//    SpiWriteSingleAddressRegister(REG_AX5043_PINFUNCIRQ, 0x01);  // IRQ Line 1   001 IRQ Output ’1’
//    SpiWriteSingleAddressRegister(REG_AX5043_PINFUNCIRQ, 0x00);  //IRQ Line 0  000 IRQ Output ’0’
//    SpiWriteSingleAddressRegister(REG_AX5043_PINFUNCIRQ, 0x03);  //011 IRQ Output Interrupt Request
//}
//MSH_CMD_EXPORT(AX5043_Reset,AX5043_Reset);
///***********************************************************************
//==单字节写==
//***********************************************************************/
//void SpiWriteByte(unsigned char ubByte)
//{
//    rt_spi_send(ax5043_device,&ubByte,1);
//}
//
///***********************************************************************
//==双字节写==
//***********************************************************************/
//void SpiWriteWord(unsigned int ubByte)
//{
//    uint8_t msg[2] = {0};
//    msg[0] = ( ubByte & 0xFF00 ) >> 8;
//    msg[1] = ubByte & 0x00FF;
//    rt_spi_send(ax5043_device,msg,2);
//}
///***********************************************************************
//==单字节读==
//***********************************************************************/
//unsigned char SpiReadByte( void )
//{
//    uint8_t data;
//    rt_spi_recv(ax5043_device,&data,1);
//    return data;
//}
///***********************************************************************
//==写单字节地址==
//***********************************************************************/
//void SpiWriteSingleAddressRegister(unsigned char Addr, unsigned char Data)
//{
//    uint8_t ubAddr = Addr|0x80;
//    rt_spi_send_then_send(ax5043_device,&ubAddr,1,&Data,1);
//}
///***********************************************************************
//==写双字节地址==
//***********************************************************************/
//void SpiWriteLongAddressRegister(unsigned int Addr, unsigned char Data)
//{
//    uint16_t ubAddr;
//    ubAddr = Addr|0xF000;
//    uint8_t msg[2] = {0};
//    msg[0] = ( ubAddr & 0xFF00 ) >> 8;
//    msg[1] = ubAddr & 0x00FF;
//
//    rt_spi_send_then_send(ax5043_device,msg,2,&Data,1);
//}
//
///***********************************************************************
//==写数据==
//***********************************************************************/
//void SpiWriteData(unsigned char *pBuf,unsigned char Length)
//{
//    unsigned char  data;
//    data=REG_AX5043_FIFODATA| 0x80;
//    rt_spi_send_then_send(ax5043_device,&data,1,pBuf,Length);
//}
///***********************************************************************
//==读取指定寄存器==
//***********************************************************************/
//unsigned char SpiReadSingleAddressRegister(unsigned char Addr)
//{
//    unsigned char ubAddr ;
//    unsigned char RcvAddr ;
//    ubAddr = Addr&0x7F ;//read common bit7=0
//    rt_spi_send_then_recv(ax5043_device,&ubAddr,1,&RcvAddr,1);
//    return RcvAddr ;
//}
//
///***********************************************************************
//==读取指定长寄存器==
//***********************************************************************/
//unsigned char SpiReadLongAddressRegister(unsigned int Addr)
//{
//    unsigned int ubAddr ;
//    unsigned char RcvAddr ;
//    ubAddr = Addr|0x7000 ;//read common bit7=0
//    uint8_t msg[2] = {0};
//    msg[0] = ( ubAddr & 0xFF00 ) >> 8;
//    msg[1] = ubAddr & 0x00FF;
//    rt_spi_send_then_recv(ax5043_device,msg,2,&RcvAddr,1);
//    return RcvAddr ;
//}
//
///***********************************************************************
//==读取数据==
//***********************************************************************/
//void SpiReadData(unsigned char *pBuf,unsigned char Length)
//{
//    unsigned char SendAddr ;
//    SendAddr=REG_AX5043_FIFODATA & 0x7F;
//    rt_spi_send_then_recv(ax5043_device,&SendAddr,1,pBuf,Length);
//}
//
//static void update_timeanchor(void)
//{
////    uint8_t iesave = IE & 0x80;
////    EA = 0;
////    axradio_timeanchor.timer0 = wtimer0_curtime();
////    axradio_timeanchor.radiotimer = radio_read24((uint16_t)&AX5043_TIMER2);
////    IE |= iesave;
//}
//
//uint32_t axradio_conv_time_totimer0(uint32_t dt)
//{
////    dt -= axradio_timeanchor.radiotimer;
////    dt = axradio_conv_timeinterval_totimer0(signextend24(dt));
////    dt += axradio_timeanchor.timer0;
////    return dt;
//}
//
//static uint8_t ax5043_init_registers_common(void)
//{
//    uint8_t rng = axradio_phy_chanpllrng[axradio_curchannel];
//    if (rng & 0x20)
//        return AXRADIO_ERR_RANGING;
//    if (AX5043_PLLLOOP & 0x80) {
//        AX5043_PLLRANGINGB = rng & 0x0F;
//    } else {
//        AX5043_PLLRANGINGA = rng & 0x0F;
//    }
//    rng = axradio_get_pllvcoi();
//    if (rng & 0x80)
//        AX5043_PLLVCOI = rng;
//    return AXRADIO_ERR_NOERROR;
//}
//
//uint8_t ax5043_init_registers_tx(void)
//{
//    ax5043_set_registers_tx();
//    return ax5043_init_registers_common();
//}
//
//uint8_t ax5043_init_registers_rx(void)
//{
//    ax5043_set_registers_rx();
//    return ax5043_init_registers_common();
//}
//
//static void receive_isr(void)
//{
//    uint8_t fifo_cmd, flags;
//    uint8_t i;
//    uint8_t len = AX5043_RADIOEVENTREQ0; // clear request so interrupt does not fire again. sync_rx enables interrupt on radio state changed in order to wake up on SDF detected
//
//    if ((len & 0x04) && AX5043_RADIOSTATE == 0x0F) {
//        // radio state has changed and is RX now: Radio has detected SFD -> save radio and LPXOSC time for time conversion
//        update_timeanchor();
//        if(axradio_framing_enable_sfdcallback)
//        {
//            //wtimer_remove_callback(&axradio_cb_receivesfd.cb);
//            axradio_cb_receivesfd.st.error = AXRADIO_ERR_NOERROR;
//            //axradio_cb_receivesfd.st.time.t = axradio_timeanchor.radiotimer;
//            //wtimer_add_callback(&axradio_cb_receivesfd.cb);
//        }
//    }
//
//#ifdef DBGPKT
//    if (len & 0x0C) {
//        len = AX5043_RADIOSTATE;
//        AX5043_PINFUNCDATA = len & 0x01;
//        AX5043_PINFUNCPWRAMP = (len >> 1) & 0x01;
//    }
//#endif
//
//    while (AX5043_IRQREQUEST0 & 0x01) {    // while fifo not empty
//        fifo_cmd = AX5043_FIFODATA; // read command
//        len = (fifo_cmd & 0xE0) >> 5; // top 3 bits encode payload len
//        if (len == 7)
//            len = AX5043_FIFODATA; // 7 means variable length, -> get length byte
//        fifo_cmd &= 0x1F;
//        switch (fifo_cmd) {
//        case AX5043_FIFOCMD_DATA:
//            if (!len)
//                break;
//
//            flags = AX5043_FIFODATA;
//            --len;
//            ax5043_readfifo(axradio_rxbuffer, len);
//            if(axradio_mode == AXRADIO_MODE_WOR_RECEIVE || axradio_mode == AXRADIO_MODE_WOR_ACK_RECEIVE)
//            {
//                f30_saved = AX5043_0xF30;
//                f31_saved = AX5043_0xF31;
//                f32_saved = AX5043_0xF32;
//                f33_saved = AX5043_0xF33;
//            }
//            if (axradio_mode == AXRADIO_MODE_WOR_RECEIVE ||
//                axradio_mode == AXRADIO_MODE_SYNC_SLAVE)
//                AX5043_PWRMODE = AX5043_PWRSTATE_POWERDOWN;
//            AX5043_IRQMASK0 &= (uint8_t)~0x01; // disable FIFO not empty irq
//            wtimer_remove_callback(&axradio_cb_receive.cb);
//            axradio_cb_receive.st.error = AXRADIO_ERR_NOERROR;
//            axradio_cb_receive.st.rx.mac.raw = axradio_rxbuffer;
//            if (AXRADIO_MODE_IS_STREAM_RECEIVE(axradio_mode)) {
//                axradio_cb_receive.st.rx.pktdata = axradio_rxbuffer;
//                axradio_cb_receive.st.rx.pktlen = len;
//                {
//                    int8_t r = AX5043_RSSI;
//                    axradio_cb_receive.st.rx.phy.rssi = r - (int16_t)axradio_phy_rssioffset;
//                }
//                if (axradio_phy_innerfreqloop)
//                    axradio_cb_receive.st.rx.phy.offset.o = axradio_conv_freq_fromreg(signextend16(radio_read16((uint16_t)&AX5043_TRKFREQ1)));
//                else
//                    axradio_cb_receive.st.rx.phy.offset.o = signextend20(radio_read24((uint16_t)&AX5043_TRKRFFREQ2));
//                wtimer_add_callback(&axradio_cb_receive.cb);
//                break;
//            }
//            axradio_cb_receive.st.rx.pktdata = &axradio_rxbuffer[axradio_framing_maclen];
//            if (len < axradio_framing_maclen) {
//                len = 0;
//                axradio_cb_receive.st.rx.pktlen = 0;
//            } else {
//                len -= axradio_framing_maclen;
//                axradio_cb_receive.st.rx.pktlen = len;
//                wtimer_add_callback(&axradio_cb_receive.cb);
//                if (axradio_mode == AXRADIO_MODE_SYNC_SLAVE ||
//                    axradio_mode == AXRADIO_MODE_SYNC_ACK_SLAVE)
//                    wtimer_remove(&axradio_timer);
//            }
//            break;
//
//        case AX5043_FIFOCMD_RFFREQOFFS:
//            if (axradio_phy_innerfreqloop || len != 3)
//                goto dropchunk;
//            i = AX5043_FIFODATA;
//            i &= 0x0F;
//            i |= 1 + (uint8_t)~(i & 0x08);
//            axradio_cb_receive.st.rx.phy.offset.b.b3 = ((int8_t)i) >> 8;
//            axradio_cb_receive.st.rx.phy.offset.b.b2 = i;
//            axradio_cb_receive.st.rx.phy.offset.b.b1 = AX5043_FIFODATA;
//            axradio_cb_receive.st.rx.phy.offset.b.b0 = AX5043_FIFODATA;
//            break;
//
//        case AX5043_FIFOCMD_FREQOFFS:
//            if (!axradio_phy_innerfreqloop || len != 2)
//                goto dropchunk;
//            axradio_cb_receive.st.rx.phy.offset.b.b1 = AX5043_FIFODATA;
//            axradio_cb_receive.st.rx.phy.offset.b.b0 = AX5043_FIFODATA;
//            axradio_cb_receive.st.rx.phy.offset.o = axradio_conv_freq_fromreg(signextend16(axradio_cb_receive.st.rx.phy.offset.o));
//            break;
//
//        case AX5043_FIFOCMD_RSSI:
//            if (len != 1)
//                goto dropchunk;
//            {
//                int8_t r = AX5043_FIFODATA;
//                axradio_cb_receive.st.rx.phy.rssi = r - (int16_t)axradio_phy_rssioffset;
//            }
//            break;
//
//        case AX5043_FIFOCMD_TIMER:
//            if (len != 3)
//                goto dropchunk;
//            // use the SFD time anchor
//            //update_timeanchor();
//            axradio_cb_receive.st.time.b.b3 = 0;
//            axradio_cb_receive.st.time.b.b2 = AX5043_FIFODATA;
//            axradio_cb_receive.st.time.b.b1 = AX5043_FIFODATA;
//            axradio_cb_receive.st.time.b.b0 = AX5043_FIFODATA;
//            break;
//
//        case AX5043_FIFOCMD_ANTRSSI:
//            if (!len)
//                break;
//            u//pdate_timeanchor();
//           // wtimer_remove_callback(&axradio_cb_channelstate.cb);
//            axradio_cb_channelstate.st.error = AXRADIO_ERR_NOERROR;
//            {
//                int8_t r = AX5043_FIFODATA;
//                axradio_cb_channelstate.st.cs.rssi = r - (int16_t)axradio_phy_rssioffset;
//                axradio_cb_channelstate.st.cs.busy = r >= axradio_phy_channelbusy;
//            }
//            //axradio_cb_channelstate.st.time.t = axradio_timeanchor.radiotimer;
//            //wtimer_add_callback(&axradio_cb_channelstate.cb);
//            --len;
//            goto dropchunk;
//
//        default:
//            // unhandled chunk type, just remove it from FIFO
//dropchunk:
//            if (!len)
//                break;
//            i = len;
//            do {
//                AX5043_FIFODATA;        // purge FIFO
//            }
//            while (--i);
//            break;
//        } // end switch(fifo_cmd)
//    } // end while( fifo not empty )
//}
//
//static void transmit_isr(void)
//{
//    for (;;) {
//        uint8_t cnt = AX5043_FIFOFREE0;
//        if (AX5043_FIFOFREE1)
//            cnt = 0xff;
//        switch (axradio_trxstate) {
//        case trxstate_tx_longpreamble:
//            if (!axradio_txbuffer_cnt) {
//                axradio_trxstate = trxstate_tx_shortpreamble;
//                if( axradio_mode == AXRADIO_MODE_WOR_TRANSMIT || axradio_mode == AXRADIO_MODE_WOR_ACK_TRANSMIT )
//                    axradio_txbuffer_cnt = axradio_phy_preamble_wor_len;
//                else
//                    axradio_txbuffer_cnt = axradio_phy_preamble_len;
//                goto shortpreamble;
//            }
//            if (cnt < 4)
//                goto fifocommit;
//            cnt = 7;
//            if (axradio_txbuffer_cnt < 7)
//                cnt = axradio_txbuffer_cnt;
//            axradio_txbuffer_cnt -= cnt;
//            cnt <<= 5;
//            AX5043_FIFODATA = AX5043_FIFOCMD_REPEATDATA | (3 << 5);
//            AX5043_FIFODATA = axradio_phy_preamble_flags;
//            AX5043_FIFODATA = cnt;
//            AX5043_FIFODATA = axradio_phy_preamble_byte;
//            break;
//
//        case trxstate_tx_shortpreamble:
//        shortpreamble:
//            if (!axradio_txbuffer_cnt) {
//                if (cnt < 15)
//                    goto fifocommit;
//                if (axradio_phy_preamble_appendbits) {
//                    uint8_t byte;
//                    AX5043_FIFODATA = AX5043_FIFOCMD_DATA | (2 << 5);
//                    AX5043_FIFODATA = 0x1C;
//                    byte = axradio_phy_preamble_appendpattern;
//                    if (AX5043_PKTADDRCFG & 0x80) {
//                        // msb first -> stop bit below
//                        byte &= 0xFF << (8-axradio_phy_preamble_appendbits);
//                        byte |= 0x80 >> axradio_phy_preamble_appendbits;
//                    } else {
//                         // lsb first -> stop bit above
//                        byte &= 0xFF >> (8-axradio_phy_preamble_appendbits);
//                        byte |= 0x01 << axradio_phy_preamble_appendbits;
//                    }
//                    AX5043_FIFODATA = byte;
//                }
//#ifdef DBGPKT
//                AX5043_FIFODATA = AX5043_FIFOCMD_TXCTRL | (1 << 5);
//                AX5043_FIFODATA = 0x02; // set PA, state 0
//#endif
//                if ((AX5043_FRAMING & 0x0E) == 0x06 && axradio_framing_synclen) {
//                    // write SYNC word if framing mode is raw_patternmatch, might use SYNCLEN > 0 as a criterion, but need to make sure SYNCLEN=0 for WMBUS (chip automatically sends SYNCWORD but matching in RX works via MATCH0PAT)
//                    uint8_t len_byte = axradio_framing_synclen;
//                    uint8_t i = (len_byte & 0x07) ? 0x04 : 0;
//                    // SYNCLEN in bytes, rather than bits. Ceiled to next integer e.g. fractional bits are counted as full bits;
//                    len_byte += 7;
//                    len_byte >>= 3;
//                    AX5043_FIFODATA = AX5043_FIFOCMD_DATA | ((len_byte + 1) << 5);
//                    AX5043_FIFODATA = axradio_framing_syncflags | i;
//                    for (i = 0; i < len_byte; ++i) {
//                        // better put a brace, it might prevent SDCC from optimizing away the assignement...
//                        AX5043_FIFODATA = axradio_framing_syncword[i];
//                    }
//                }
//#ifdef DBGPKT
//                AX5043_FIFODATA = AX5043_FIFOCMD_TXCTRL | (1 << 5);
//                AX5043_FIFODATA = 0x03; // set PA, state 1
//#endif
//                axradio_trxstate = trxstate_tx_packet;
//                break;
//            }
//            if (cnt < 4)
//                goto fifocommit;
//            cnt = 255;
//            if (axradio_txbuffer_cnt < 255*8)
//                cnt = axradio_txbuffer_cnt >> 3;
//            if (cnt) {
//                axradio_txbuffer_cnt -= ((uint16_t)cnt) << 3;
//                AX5043_FIFODATA = AX5043_FIFOCMD_REPEATDATA | (3 << 5);
//                AX5043_FIFODATA = axradio_phy_preamble_flags;
//                AX5043_FIFODATA = cnt;
//                AX5043_FIFODATA = axradio_phy_preamble_byte;
//                break;
//            }
//            {
//                uint8_t byte = axradio_phy_preamble_byte;
//                cnt = axradio_txbuffer_cnt;
//                axradio_txbuffer_cnt = 0;
//                AX5043_FIFODATA = AX5043_FIFOCMD_DATA | (2 << 5);
//                AX5043_FIFODATA = 0x1C;
//                if (AX5043_PKTADDRCFG & 0x80) {
//                    // msb first -> stop bit below
//                    byte &= 0xFF << (8-cnt);
//                    byte |= 0x80 >> cnt;
//                } else {
//                     // lsb first -> stop bit above
//                    byte &= 0xFF >> (8-cnt);
//                    byte |= 0x01 << cnt;
//                }
//                AX5043_FIFODATA = byte;
//            }
//            break;
//
//        case trxstate_tx_packet:
//            if (cnt < 11)
//                goto fifocommit;
//            {
//                uint8_t flags = 0;
//                if (!axradio_txbuffer_cnt)
//                    flags |= 0x01; // flag byte: pkt_start
//                {
//                    uint16_t len = axradio_txbuffer_len - axradio_txbuffer_cnt;
//                    cnt -= 3;
//                    if (cnt >= len) {
//                        cnt = len;
//                        flags |= 0x02; // flag byte: pkt_end
//                    }
//                }
//                if (!cnt)
//                    goto pktend;
//                AX5043_FIFODATA = AX5043_FIFOCMD_DATA | (7 << 5);
//                AX5043_FIFODATA = cnt + 1; // write FIFO chunk length byte (length includes the flag byte, thus the +1)
//                AX5043_FIFODATA = flags;
//                ax5043_writefifo(&axradio_txbuffer[axradio_txbuffer_cnt], cnt);
//                axradio_txbuffer_cnt += cnt;
//                if (flags & 0x02)
//                    goto pktend;
//            }
//            break;
//
//        default:
//            return;
//        }
//    }
//pktend:
//    axradio_trxstate = trxstate_tx_waitdone;
//    AX5043_RADIOEVENTMASK0 = 0x01; // enable REVRDONE event
//    AX5043_IRQMASK0 = 0x40; // enable radio controller irq
//fifocommit:
//    AX5043_FIFOSTAT = 4; // commit
//}
//
//#if defined SDCC
//void axradio_isr(void) __interrupt INT_RADIO
//#elif defined __CX51__ || defined __C51__
//void axradio_isr(void) interrupt INT_RADIO
//#elif defined __ICC8051__
//#pragma vector=0x23
//__interrupt void axradio_isr(void)
//#endif
//void rxisr(void)
//{
//    switch (axradio_trxstate) {
//    default:
//        AX5043_IRQMASK1 = 0x00;
//        AX5043_IRQMASK0 = 0x00;
//        break;
//
//    case trxstate_wait_xtal:
//        AX5043_IRQMASK1 = 0x00; // otherwise crystal ready will fire all over again
//        axradio_trxstate = trxstate_xtal_ready;
//        break;
//
//    case trxstate_pll_ranging:
//        AX5043_IRQMASK1 = 0x00; // otherwise autoranging done will fire all over again
//        axradio_trxstate = trxstate_pll_ranging_done;
//        break;
//
//    case trxstate_pll_settling:
//        AX5043_RADIOEVENTMASK0 = 0x00;
//        axradio_trxstate = trxstate_pll_settled;
//        break;
//
//    case trxstate_tx_xtalwait:
//        AX5043_RADIOEVENTREQ0; // make sure REVRDONE bit is cleared, so it is a reliable indicator that the packet is out
//        AX5043_FIFOSTAT = 3; // clear FIFO data & flags (prevent transmitting anything left over in the FIFO, this has no effect if the FIFO is not powerered, in this case it is reset any way)
//        AX5043_IRQMASK1 = 0x00;
//        AX5043_IRQMASK0 = 0x08; // enable fifo free threshold
//        axradio_trxstate = trxstate_tx_longpreamble;
//#if 1
//        if ((AX5043_MODULATION & 0x0F) == 9) { // 4-FSK
//            AX5043_FIFODATA = AX5043_FIFOCMD_DATA | (7 << 5);
//            AX5043_FIFODATA = 2;  // length (including flags)
//            AX5043_FIFODATA = 0x01;  // flag PKTSTART -> dibit sync
//            AX5043_FIFODATA = 0x11; // dummy byte for forcing dibit sync
//        }
//#endif
//#ifdef DBGPKT
//        AX5043_FIFODATA = AX5043_FIFOCMD_TXCTRL | (1 << 5);
//        AX5043_FIFODATA = 0x03; // set PA, state 1
//#endif
//        transmit_isr();
//        AX5043_PWRMODE = AX5043_PWRSTATE_FULL_TX;
//        update_timeanchor();
//        wtimer_remove_callback(&axradio_cb_transmitstart.cb);
//        switch (axradio_mode) {
//        case AXRADIO_MODE_ACK_TRANSMIT:
//        case AXRADIO_MODE_WOR_ACK_TRANSMIT:
//            if (axradio_ack_count != axradio_framing_ack_retransmissions) {
//                axradio_cb_transmitstart.st.error = AXRADIO_ERR_RETRANSMISSION;
//                break;
//            }
//            // fall through
//        default:
//            axradio_cb_transmitstart.st.error = AXRADIO_ERR_NOERROR;
//            break;
//        }
//        axradio_cb_transmitstart.st.time.t = axradio_timeanchor.radiotimer;
//        wtimer_add_callback(&axradio_cb_transmitstart.cb);
//        break;
//
//    case trxstate_tx_longpreamble:
//    case trxstate_tx_shortpreamble:
//    case trxstate_tx_packet:
//        transmit_isr();
//        break;
//
//    case trxstate_tx_waitdone:
//        AX5043_RADIOEVENTREQ0;
//        if (AX5043_RADIOSTATE != 0)
//            break;
//        AX5043_RADIOEVENTMASK0 = 0x00;
//        switch (axradio_mode) {
//        case AXRADIO_MODE_ASYNC_RECEIVE:
//            ax5043_init_registers_rx();
//            ax5043_receiver_on_continuous();
//            break;
//
//        case AXRADIO_MODE_ACK_RECEIVE:
//            if (axradio_cb_receive.st.error == AXRADIO_ERR_PACKETDONE) {
//                ax5043_init_registers_rx();
//                ax5043_receiver_on_continuous();
//                break;
//            }
//        offxtal:
//            ax5043_off_xtal();
//            break;
//
//        case AXRADIO_MODE_WOR_RECEIVE:
//            if (axradio_cb_receive.st.error == AXRADIO_ERR_PACKETDONE) {
//                ax5043_init_registers_rx();
//                ax5043_receiver_on_wor();
//                break;
//            }
//            goto offxtal;
//
//        case AXRADIO_MODE_WOR_ACK_RECEIVE:
//            ax5043_init_registers_rx();
//            ax5043_receiver_on_wor();
//            break;
//
//        case AXRADIO_MODE_SYNC_ACK_MASTER:
//            axradio_txbuffer_len = axradio_framing_minpayloadlen;
//            // fall through
//
//        case AXRADIO_MODE_ACK_TRANSMIT:
//        case AXRADIO_MODE_WOR_ACK_TRANSMIT:
//            ax5043_init_registers_rx();
//            ax5043_receiver_on_continuous();
//            //wtimer_remove(&axradio_timer);
//            //axradio_timer.time = axradio_framing_ack_timeout;
//            //wtimer0_addrelative(&axradio_timer);
//            break;
//
//        case AXRADIO_MODE_SYNC_MASTER:
//            axradio_txbuffer_len = axradio_framing_minpayloadlen;
//            // fall through
//
//        default:
//            ax5043_off();
//            break;
//        }
//        if (axradio_mode != AXRADIO_MODE_SYNC_MASTER &&
//            axradio_mode != AXRADIO_MODE_SYNC_ACK_MASTER &&
//            axradio_mode != AXRADIO_MODE_SYNC_SLAVE &&
//            axradio_mode != AXRADIO_MODE_SYNC_ACK_SLAVE)
//            axradio_syncstate = syncstate_off;
//        update_timeanchor();
//        wtimer_remove_callback(&axradio_cb_transmitend.cb);
//        axradio_cb_transmitend.st.error = AXRADIO_ERR_NOERROR;
//        if (axradio_mode == AXRADIO_MODE_ACK_TRANSMIT ||
//            axradio_mode == AXRADIO_MODE_WOR_ACK_TRANSMIT ||
//            axradio_mode == AXRADIO_MODE_SYNC_ACK_MASTER)
//            axradio_cb_transmitend.st.error = AXRADIO_ERR_BUSY;
//        axradio_cb_transmitend.st.time.t = axradio_timeanchor.radiotimer;
//        wtimer_add_callback(&axradio_cb_transmitend.cb);
//        break;
//
//
//    case trxstate_txcw_xtalwait:
//        AX5043_IRQMASK1 = 0x00;
//        AX5043_IRQMASK0 = 0x00;
//        AX5043_PWRMODE = AX5043_PWRSTATE_FULL_TX;
//        axradio_trxstate = trxstate_off;
//        update_timeanchor();
//        wtimer_remove_callback(&axradio_cb_transmitstart.cb);
//        axradio_cb_transmitstart.st.error = AXRADIO_ERR_NOERROR;
//        axradio_cb_transmitstart.st.time.t = axradio_timeanchor.radiotimer;
//        wtimer_add_callback(&axradio_cb_transmitstart.cb);
//        break;
//
//    case trxstate_txstream_xtalwait:
//        if (AX5043_IRQREQUEST1 & 0x01) {
//            AX5043_RADIOEVENTMASK0 = 0x03; // enable PLL settled and done event
//            AX5043_IRQMASK1 = 0x00;
//            AX5043_IRQMASK0 = 0x40; // enable radio controller irq
//            AX5043_PWRMODE = AX5043_PWRSTATE_FULL_TX;
//            axradio_trxstate = trxstate_txstream;
//        }
//        goto txstreamdatacb;
//
//    case trxstate_txstream:
//        {
//            uint8_t  evt = AX5043_RADIOEVENTREQ0;
//            if (evt & 0x03)
//                update_timeanchor();
//            if (evt & 0x01) {
//                wtimer_remove_callback(&axradio_cb_transmitend.cb);
//                axradio_cb_transmitend.st.error = AXRADIO_ERR_NOERROR;
//                axradio_cb_transmitend.st.time.t = axradio_timeanchor.radiotimer;
//                wtimer_add_callback(&axradio_cb_transmitend.cb);
//            }
//            if (evt & 0x02) {
//                wtimer_remove_callback(&axradio_cb_transmitstart.cb);
//                axradio_cb_transmitstart.st.error = AXRADIO_ERR_NOERROR;
//                axradio_cb_transmitstart.st.time.t = axradio_timeanchor.radiotimer;
//                wtimer_add_callback(&axradio_cb_transmitstart.cb);
//            }
//        }
//    txstreamdatacb:
//        if (AX5043_IRQREQUEST0 & AX5043_IRQMASK0 & 0x08) {
//            AX5043_IRQMASK0 &= (uint8_t)~0x08;
//            update_timeanchor();
//            wtimer_remove_callback(&axradio_cb_transmitdata.cb);
//            axradio_cb_transmitdata.st.error = AXRADIO_ERR_NOERROR;
//            axradio_cb_transmitdata.st.time.t = axradio_timeanchor.radiotimer;
//            wtimer_add_callback(&axradio_cb_transmitdata.cb);
//        }
//        break;
//
//    case trxstate_rxwor:
//        //F143_WOR_TCXO
//        //AX8052F143, WOR with TCXO: MCU needs to wake up upon TCXO enable / disable in order to get the TCXO_EN singal into the frozen GPIO
//        if( AX5043_IRQREQUEST0 & 0x80 ) // vdda ready (note irqinversion does not act upon AX5043_IRQREQUEST0)
//        {
//            AX5043_IRQINVERSION0 |= 0x80; // invert pwr irq, so it does not fire continuously
//        }
//        else
//        {
//            AX5043_IRQINVERSION0 &= (uint8_t)~0x80; // drop pwr irq inversion --> armed again
//        }
//
//
//        if( AX5043_IRQREQUEST1 & 0x01 ) // XTAL ready
//        {
//            AX5043_IRQINVERSION1 |= 0x01; // invert the xtal ready irq so it does not fire continuously
//        }
//        else // XTAL not running
//        {
//            AX5043_IRQINVERSION1 &= (uint8_t)~0x01; // drop xtal ready irq inversion --> armed again for next wake-up
//            AX5043_0xF30 = f30_saved;
//            AX5043_0xF31 = f31_saved;
//            AX5043_0xF32 = f32_saved;
//            AX5043_0xF33 = f33_saved;
//        }
//
//    // fall through
//    case trxstate_rx:
//        receive_isr();
//        break;
//
//    } // end switch(axradio_trxstate)
//} //end radio_isr
//
//
//void ax5043_receiver_on_continuous(void)
//{
//    uint8_t rschanged_int = (axradio_framing_enable_sfdcallback | (axradio_mode == AXRADIO_MODE_SYNC_ACK_SLAVE) | (axradio_mode == AXRADIO_MODE_SYNC_SLAVE) );
//    if(rschanged_int)
//        AX5043_RADIOEVENTMASK0 = 0x04;
//    AX5043_RSSIREFERENCE = axradio_phy_rssireference;
//    ax5043_set_registers_rxcont();
//
//#if 0
//    if (axradio_mode == AXRADIO_MODE_ASYNC_RECEIVE ||
//        axradio_mode == AXRADIO_MODE_ACK_RECEIVE ||
//        AXRADIO_MODE_IS_STREAM_RECEIVE(axradio_mode) {
//        AX5043_TMGRXPREAMBLE1 = axradio_phy_tmgrxpreamble1_cont;
//        AX5043_PKTSTOREFLAGS |= 0x40;
//    } else {
//        AX5043_TMGRXPREAMBLE1 = 0x00;
//        AX5043_PKTSTOREFLAGS &= (uint8_t)~0x40;
//    }
//#endif
//    AX5043_PKTSTOREFLAGS &= (uint8_t)~0x40;
//
//
//    AX5043_FIFOSTAT = 3; // clear FIFO data & flags
//    AX5043_PWRMODE = AX5043_PWRSTATE_FULL_RX;
//    axradio_trxstate = trxstate_rx;
//    if(rschanged_int)
//        AX5043_IRQMASK0 = 0x41; //  enable FIFO not empty / radio controller irq
//    else
//        AX5043_IRQMASK0 = 0x01; //  enable FIFO not empty
//    AX5043_IRQMASK1 = 0x00;
//}
//
//void ax5043_receiver_on_wor(void)
//{
//    AX5043_BGNDRSSIGAIN = 0x02;
//    if(axradio_framing_enable_sfdcallback)
//        AX5043_RADIOEVENTMASK0 = 0x04;
//    AX5043_FIFOSTAT = 3; // clear FIFO data & flags
//    AX5043_LPOSCCONFIG = 0x01; // start LPOSC, slow mode
//    AX5043_RSSIREFERENCE = axradio_phy_rssireference;
//    ax5043_set_registers_rxwor();
//    AX5043_PKTSTOREFLAGS &= (uint8_t)~0x40;
//
//    AX5043_PWRMODE = AX5043_PWRSTATE_WOR_RX;
//    axradio_trxstate = trxstate_rxwor;
//    if(axradio_framing_enable_sfdcallback)
//        AX5043_IRQMASK0 = 0x41; //  enable FIFO not empty / radio controller irq
//    else
//        AX5043_IRQMASK0 = 0x01; //  enable FIFO not empty
//
//    if( ( (PALTRADIO & 0x40) && ((AX5043_PINFUNCPWRAMP & 0x0F) == 0x07) ) || ( (PALTRADIO & 0x80) && ( (AX5043_PINFUNCANTSEL & 0x07 ) == 0x04 ) ) ) // pass through of TCXO_EN
//    {
//        // F143_WOR_TCXO
//        AX5043_IRQMASK0 |= 0x80; // power irq (AX8052F143 WOR with TCXO)
//        AX5043_POWIRQMASK = 0x90; // interrupt when vddana ready (AX8052F143 WOR with TCXO)
//    }
//
//    AX5043_IRQMASK1 = 0x01; // xtal ready
//    {
//        uint16_t wp = axradio_wor_period;
//        AX5043_WAKEUPFREQ1 = (wp >> 8) & 0xFF;
//        AX5043_WAKEUPFREQ0 = (wp >> 0) & 0xFF;  // actually wakeup period measured in LP OSC cycles
//        wp += radio_read16((uint16_t)&AX5043_WAKEUPTIMER1);
//        AX5043_WAKEUP1 = (wp >> 8) & 0xFF;
//        AX5043_WAKEUP0 = (wp >> 0) & 0xFF;
//    }
//}
//void ax5043_prepare_tx(void)
//{
//    AX5043_PWRMODE = AX5043_PWRSTATE_XTAL_ON;
//    AX5043_PWRMODE = AX5043_PWRSTATE_FIFO_ON;
//    ax5043_init_registers_tx();
//    AX5043_FIFOTHRESH1 = 0;
//    AX5043_FIFOTHRESH0 = 0x80;
//    axradio_trxstate = trxstate_tx_xtalwait;
//    AX5043_IRQMASK0 = 0x00;
//    AX5043_IRQMASK1 = 0x01; // enable xtal ready interrupt
//    AX5043_POWSTICKYSTAT; // clear pwr management sticky status --> brownout gate works
//}
//
//void ax5043_off(void)
//{
//    ax5043_off_xtal();
//    AX5043_PWRMODE = AX5043_PWRSTATE_POWERDOWN;
//}
//
//void ax5043_off_xtal(void)
//{
//    AX5043_IRQMASK0 = 0x00; // IRQ off
//    AX5043_IRQMASK1 = 0x00;
//    AX5043_PWRMODE = AX5043_PWRSTATE_XTAL_ON;
//    AX5043_LPOSCCONFIG = 0x00; // LPOSC off
//    axradio_trxstate = trxstate_off;
//}
//
//void axradio_wait_for_xtal(void)
//{
//    //uint8_t  iesave = IE & 0x80;
//    //EA = 0;
//    axradio_trxstate = trxstate_wait_xtal;
//    AX5043_IRQMASK1 |= 0x01; // enable xtal ready interrupt
//    for(;;) {
//       // EA = 0;
//        if (axradio_trxstate == trxstate_xtal_ready)
//            break;
//        //wtimer_idle(WTFLAG_CANSTANDBY);
//        //EA = 1;
//        //wtimer_runcallbacks();
//    }
//    IE |= iesave;
//}
//
//static void axradio_setaddrregs(void)
//{
//    AX5043_PKTADDR0 = axradio_localaddr.addr[0];
//    AX5043_PKTADDR1 = axradio_localaddr.addr[1];
//    AX5043_PKTADDR2 = axradio_localaddr.addr[2];
//    AX5043_PKTADDR3 = axradio_localaddr.addr[3];
//
//    AX5043_PKTADDRMASK0 = axradio_localaddr.mask[0];
//    AX5043_PKTADDRMASK1 = axradio_localaddr.mask[1];
//    AX5043_PKTADDRMASK2 = axradio_localaddr.mask[2];
//    AX5043_PKTADDRMASK3 = axradio_localaddr.mask[3];
//
//    if (axradio_phy_pn9 && axradio_framing_addrlen) {
//        uint16_t  pn = 0x1ff;
//        uint8_t  inv = -(AX5043_ENCODING & 0x01);
//        if (axradio_framing_destaddrpos != 0xff)
//            pn = pn9_advance_bits(pn, axradio_framing_destaddrpos << 3);
//        AX5043_PKTADDR0 ^= pn ^ inv;
//        pn = pn9_advance_byte(pn);
//        AX5043_PKTADDR1 ^= pn ^ inv;
//        pn = pn9_advance_byte(pn);
//        AX5043_PKTADDR2 ^= pn ^ inv;
//        pn = pn9_advance_byte(pn);
//        AX5043_PKTADDR3 ^= pn ^ inv;
//    }
//}
//
//static void ax5043_init_registers(void)
//{
//    ax5043_set_registers();
//
//#ifdef DBGPKT
//    AX5043_PINFUNCPWRAMP = 0x06; // output pwramp
//#endif
//    AX5043_PKTLENOFFSET += axradio_framing_swcrclen; // add len offs for software CRC16 (used for both, fixed and variable length packets
//    AX5043_PINFUNCIRQ = 0x03; // use as IRQ pin
//    AX5043_PKTSTOREFLAGS = axradio_phy_innerfreqloop ? 0x13 : 0x15; // store RF offset, RSSI and delimiter timing
//    axradio_setaddrregs();
//}
//
///*
// * Synchronous Mode Helper Routines
// */
//
//static void axradio_sync_addtime(uint32_t dt)
//{
//    axradio_sync_time += dt;
//}
//
//static void axradio_sync_subtime(uint32_t dt)
//{
//    axradio_sync_time -= dt;
//}
//
//static void axradio_sync_settimeradv(uint32_t dt)
//{
//    axradio_timer.time = axradio_sync_time;
//    axradio_timer.time -= dt;
//}
//
//static void axradio_sync_adjustperiodcorr(void)
//{
//    int32_t  dt = axradio_conv_time_totimer0(axradio_cb_receive.st.time.t) - axradio_sync_time;
//    axradio_cb_receive.st.rx.phy.timeoffset = dt;
//    if (!checksignedlimit16(axradio_sync_periodcorr, axradio_sync_slave_maxperiod)) {
//        axradio_sync_addtime(dt);
//        dt <<= SYNC_K1;
//        axradio_sync_periodcorr = dt;
//    } else {
//        axradio_sync_periodcorr += dt;
//        dt >>= SYNC_K0;
//        axradio_sync_addtime(dt);
//    }
//    axradio_sync_periodcorr = signedlimit16(axradio_sync_periodcorr, axradio_sync_slave_maxperiod);
//}
//
//static void axradio_sync_slave_nextperiod()
//{
//    axradio_sync_addtime(axradio_sync_period);
//    if (!checksignedlimit16(axradio_sync_periodcorr, axradio_sync_slave_maxperiod))
//        return;
//    {
//        int16_t  c = axradio_sync_periodcorr;
//        axradio_sync_addtime(c >> SYNC_K1);
//    }
//}
///*
// * Callbacks
// */
//static void axradio_timer_callback(struct wtimer_desc *desc)
//{
//    desc;
//    switch (axradio_mode) {
//    case AXRADIO_MODE_STREAM_RECEIVE:
//    case AXRADIO_MODE_STREAM_RECEIVE_UNENC:
//    case AXRADIO_MODE_STREAM_RECEIVE_SCRAM:
//    case AXRADIO_MODE_STREAM_RECEIVE_UNENC_LSB:
//    case AXRADIO_MODE_STREAM_RECEIVE_SCRAM_LSB:
//    case AXRADIO_MODE_ASYNC_RECEIVE:
//    case AXRADIO_MODE_WOR_RECEIVE:
//        if (axradio_syncstate == syncstate_asynctx)
//            goto transmitcs;
//        wtimer_remove(&axradio_timer);
//    rearmcstimer:
//        axradio_timer.time = axradio_phy_cs_period;
//        wtimer0_addrelative(&axradio_timer);
//    chanstatecb:
//        update_timeanchor();
//        wtimer_remove_callback(&axradio_cb_channelstate.cb);
//        axradio_cb_channelstate.st.error = AXRADIO_ERR_NOERROR;
//        {
//            int8_t  r = AX5043_RSSI;
//            axradio_cb_channelstate.st.cs.rssi = r - (int16_t)axradio_phy_rssioffset;
//            axradio_cb_channelstate.st.cs.busy = r >= axradio_phy_channelbusy;
//        }
//        axradio_cb_channelstate.st.time.t = axradio_timeanchor.radiotimer;
//        wtimer_add_callback(&axradio_cb_channelstate.cb);
//        break;
//
//    case AXRADIO_MODE_ASYNC_TRANSMIT:
//    case AXRADIO_MODE_WOR_TRANSMIT:
//    transmitcs:
//        if (axradio_ack_count)
//            --axradio_ack_count;
//        wtimer_remove(&axradio_timer);
//        if ((int8_t)AX5043_RSSI < axradio_phy_channelbusy ||
//            (!axradio_ack_count && axradio_phy_lbt_forcetx)) {
//            axradio_syncstate = syncstate_off;
//            axradio_txbuffer_cnt = axradio_phy_preamble_longlen;
//            ax5043_prepare_tx();
//            goto chanstatecb;
//        }
//        if (axradio_ack_count)
//            goto rearmcstimer;
//        update_timeanchor();
//        axradio_syncstate = syncstate_off;
//        ax5043_off();
//        wtimer_remove_callback(&axradio_cb_transmitstart.cb);
//        axradio_cb_transmitstart.st.error = AXRADIO_ERR_TIMEOUT;
//        axradio_cb_transmitstart.st.time.t = axradio_timeanchor.radiotimer;
//        wtimer_add_callback(&axradio_cb_transmitstart.cb);
//        break;
//
//    case AXRADIO_MODE_ACK_TRANSMIT:
//    case AXRADIO_MODE_WOR_ACK_TRANSMIT:
//        if (axradio_syncstate == syncstate_lbt)
//            goto transmitcs;
//        ax5043_off();
//        if (!axradio_ack_count) {
//            update_timeanchor();
//            wtimer_remove_callback(&axradio_cb_transmitend.cb);
//            axradio_cb_transmitend.st.error = AXRADIO_ERR_TIMEOUT;
//            axradio_cb_transmitend.st.time.t = axradio_timeanchor.radiotimer;
//            wtimer_add_callback(&axradio_cb_transmitend.cb);
//            break;
//        }
//        --axradio_ack_count;
//        axradio_txbuffer_cnt = axradio_phy_preamble_longlen;
//        ax5043_prepare_tx();
//        break;
//
//    case AXRADIO_MODE_ACK_RECEIVE:
//    case AXRADIO_MODE_WOR_ACK_RECEIVE:
//        if (axradio_syncstate == syncstate_lbt)
//            goto transmitcs;
//    transmitack:
//        AX5043_FIFOSTAT = 3;
//        AX5043_PWRMODE = AX5043_PWRSTATE_FULL_TX;
//        while (!(AX5043_POWSTAT & 0x08)); // wait for modem vdd so writing the FIFO is safe
//        ax5043_init_registers_tx();
//        AX5043_RADIOEVENTREQ0; // make sure REVRDONE bit is cleared, so it is a reliable indicator that the packet is out
//        AX5043_FIFOTHRESH1 = 0;
//        AX5043_FIFOTHRESH0 = 0x80;
//        axradio_trxstate = trxstate_tx_longpreamble;
//        axradio_txbuffer_cnt = axradio_phy_preamble_longlen;
//#if 1
//        if ((AX5043_MODULATION & 0x0F) == 9) { // 4-FSK
//            AX5043_FIFODATA = AX5043_FIFOCMD_DATA | (7 << 5);
//            AX5043_FIFODATA = 2;  // length (including flags)
//            AX5043_FIFODATA = 0x01;  // flag PKTSTART -> dibit sync
//            AX5043_FIFODATA = 0x11; // dummy byte for forcing dibit sync
//        }
//#endif
//#ifdef DBGPKT
//        AX5043_FIFODATA = AX5043_FIFOCMD_TXCTRL | (1 << 5);
//        AX5043_FIFODATA = 0x03; // set PA, state 1
//#endif
//        AX5043_IRQMASK0 = 0x08; // enable fifo free threshold
//        update_timeanchor();
//        wtimer_remove_callback(&axradio_cb_transmitstart.cb);
//        axradio_cb_transmitstart.st.error = AXRADIO_ERR_NOERROR;
//        axradio_cb_transmitstart.st.time.t = axradio_timeanchor.radiotimer;
//        wtimer_add_callback(&axradio_cb_transmitstart.cb);
//        break;
//
//    case AXRADIO_MODE_SYNC_MASTER:
//    case AXRADIO_MODE_SYNC_ACK_MASTER:
//        switch (axradio_syncstate) {
//        default:
//            AX5043_PWRMODE = AX5043_PWRSTATE_XTAL_ON;
//            ax5043_init_registers_tx();
//            axradio_syncstate = syncstate_master_xostartup;
//            wtimer_remove_callback(&axradio_cb_transmitdata.cb);
//            axradio_cb_transmitdata.st.error = AXRADIO_ERR_NOERROR;
//            axradio_cb_transmitdata.st.time.t = 0;
//            wtimer_add_callback(&axradio_cb_transmitdata.cb);
//            wtimer_remove(&axradio_timer);
//            axradio_timer.time = axradio_sync_time;
//            wtimer0_addabsolute(&axradio_timer);
//            break;
//
//        case syncstate_master_xostartup:
//            AX5043_FIFOSTAT = 3;
//            AX5043_PWRMODE = AX5043_PWRSTATE_FULL_TX;
//            while (!(AX5043_POWSTAT & 0x08)); // wait for modem vdd so writing the FIFO is safe
//            AX5043_RADIOEVENTREQ0; // make sure REVRDONE bit is cleared, so it is a reliable indicator that the packet is out
//            AX5043_FIFOTHRESH1 = 0;
//            AX5043_FIFOTHRESH0 = 0x80;
//            axradio_trxstate = trxstate_tx_longpreamble;
//            axradio_txbuffer_cnt = axradio_phy_preamble_longlen;
//#if 1
//            if ((AX5043_MODULATION & 0x0F) == 9) { // 4-FSK
//                AX5043_FIFODATA = AX5043_FIFOCMD_DATA | (7 << 5);
//                AX5043_FIFODATA = 2;  // length (including flags)
//                AX5043_FIFODATA = 0x01;  // flag PKTSTART -> dibit sync
//                AX5043_FIFODATA = 0x11; // dummy byte for forcing dibit sync
//            }
//#endif
//#ifdef DBGPKT
//            AX5043_FIFODATA = AX5043_FIFOCMD_TXCTRL | (1 << 5);
//            AX5043_FIFODATA = 0x03; // set PA, state 1
//#endif
//            wtimer_remove(&axradio_timer);
//            update_timeanchor();
//            AX5043_IRQMASK0 = 0x08; // enable fifo free threshold
//            axradio_sync_addtime(axradio_sync_period);
//            axradio_syncstate = syncstate_master_waitack;
//            if (axradio_mode != AXRADIO_MODE_SYNC_ACK_MASTER) {
//                axradio_syncstate = syncstate_master_normal;
//                axradio_sync_settimeradv(axradio_sync_xoscstartup);
//                wtimer0_addabsolute(&axradio_timer);
//            }
//            wtimer_remove_callback(&axradio_cb_transmitstart.cb);
//            axradio_cb_transmitstart.st.error = AXRADIO_ERR_NOERROR;
//            axradio_cb_transmitstart.st.time.t = axradio_timeanchor.radiotimer;
//            wtimer_add_callback(&axradio_cb_transmitstart.cb);
//            break;
//
//        case syncstate_master_waitack:
//            ax5043_off();
//            axradio_syncstate = syncstate_master_normal;
//            wtimer_remove(&axradio_timer);
//            axradio_sync_settimeradv(axradio_sync_xoscstartup);
//            wtimer0_addabsolute(&axradio_timer);
//            update_timeanchor();
//            wtimer_remove_callback(&axradio_cb_transmitend.cb);
//            axradio_cb_transmitend.st.error = AXRADIO_ERR_TIMEOUT;
//            axradio_cb_transmitend.st.time.t = axradio_timeanchor.radiotimer;
//            wtimer_add_callback(&axradio_cb_transmitend.cb);
//            break;
//        };
//        break;
//
//    case AXRADIO_MODE_SYNC_SLAVE:
//    case AXRADIO_MODE_SYNC_ACK_SLAVE:
//        switch (axradio_syncstate) {
//        default:
//        case syncstate_slave_synchunt:
//            ax5043_off();
//            axradio_syncstate = syncstate_slave_syncpause;
//            axradio_sync_addtime(axradio_sync_slave_syncpause);
//            wtimer_remove(&axradio_timer);
//            axradio_timer.time = axradio_sync_time;
//            wtimer0_addabsolute(&axradio_timer);
//            wtimer_remove_callback(&axradio_cb_receive.cb);
//            memset_xdata(&axradio_cb_receive.st, 0, sizeof(axradio_cb_receive.st));
//            axradio_cb_receive.st.time.t = axradio_timeanchor.radiotimer;
//            axradio_cb_receive.st.error = AXRADIO_ERR_RESYNCTIMEOUT;
//            wtimer_add_callback(&axradio_cb_receive.cb);
//            break;
//
//        case syncstate_slave_syncpause:
//            ax5043_receiver_on_continuous();
//            axradio_syncstate = syncstate_slave_synchunt;
//            axradio_sync_addtime(axradio_sync_slave_syncwindow);
//            wtimer_remove(&axradio_timer);
//            axradio_timer.time = axradio_sync_time;
//            wtimer0_addabsolute(&axradio_timer);
//            update_timeanchor();
//            wtimer_remove_callback(&axradio_cb_receive.cb);
//            memset_xdata(&axradio_cb_receive.st, 0, sizeof(axradio_cb_receive.st));
//            axradio_cb_receive.st.time.t = axradio_timeanchor.radiotimer;
//            axradio_cb_receive.st.error = AXRADIO_ERR_RESYNC;
//            wtimer_add_callback(&axradio_cb_receive.cb);
//            break;
//
//        case syncstate_slave_rxidle:
//            AX5043_PWRMODE = AX5043_PWRSTATE_XTAL_ON;
//            axradio_syncstate = syncstate_slave_rxxosc;
//            wtimer_remove(&axradio_timer);
//            axradio_timer.time += axradio_sync_xoscstartup;
//            wtimer0_addabsolute(&axradio_timer);
//            break;
//
//        case syncstate_slave_rxxosc:
//            ax5043_receiver_on_continuous();
//            axradio_syncstate = syncstate_slave_rxsfdwindow;
//            update_timeanchor();
//            wtimer_remove_callback(&axradio_cb_receive.cb);
//            memset_xdata(&axradio_cb_receive.st, 0, sizeof(axradio_cb_receive.st));
//            axradio_cb_receive.st.time.t = axradio_timeanchor.radiotimer;
//            axradio_cb_receive.st.error = AXRADIO_ERR_RECEIVESTART;
//            wtimer_add_callback(&axradio_cb_receive.cb);
//            wtimer_remove(&axradio_timer);
//            {
//                uint8_t  idx = axradio_sync_seqnr;
//                if (idx >= axradio_sync_slave_nrrx)
//                    idx = axradio_sync_slave_nrrx - 1;
//                axradio_timer.time += axradio_sync_slave_rxwindow[idx];
//            }
//            wtimer0_addabsolute(&axradio_timer);
//            break;
//
//        case syncstate_slave_rxsfdwindow:
//            {
//                uint8_t  rs = AX5043_RADIOSTATE;
//                if( !rs )
//                    break;
//
//                if (!(0x0F & (uint8_t)~rs)) {
//                    axradio_syncstate = syncstate_slave_rxpacket;
//                    wtimer_remove(&axradio_timer);
//                    axradio_timer.time += axradio_sync_slave_rxtimeout;
//                    wtimer0_addabsolute(&axradio_timer);
//                    break;
//                }
//                // fall through
//            }
//
//        case syncstate_slave_rxpacket:
//            ax5043_off();
//            if (!axradio_sync_seqnr)
//                axradio_sync_seqnr = 1;
//            ++axradio_sync_seqnr;
//            update_timeanchor();
//            wtimer_remove_callback(&axradio_cb_receive.cb);
//            memset_xdata(&axradio_cb_receive.st, 0, sizeof(axradio_cb_receive.st));
//            axradio_cb_receive.st.time.t = axradio_timeanchor.radiotimer;
//            axradio_cb_receive.st.error = AXRADIO_ERR_TIMEOUT;
//            if (axradio_sync_seqnr <= axradio_sync_slave_resyncloss) {
//                wtimer_add_callback(&axradio_cb_receive.cb);
//                axradio_sync_slave_nextperiod();
//                axradio_syncstate = syncstate_slave_rxidle;
//                wtimer_remove(&axradio_timer);
//                {
//                    uint8_t  idx = axradio_sync_seqnr;
//                    if (idx >= axradio_sync_slave_nrrx)
//                        idx = axradio_sync_slave_nrrx - 1;
//                    axradio_sync_settimeradv(axradio_sync_slave_rxadvance[idx]);
//                }
//                wtimer0_addabsolute(&axradio_timer);
//                break;
//            }
//            axradio_cb_receive.st.error = AXRADIO_ERR_RESYNC;
//            wtimer_add_callback(&axradio_cb_receive.cb);
//            ax5043_receiver_on_continuous();
//            axradio_syncstate = syncstate_slave_synchunt;
//            wtimer_remove(&axradio_timer);
//            axradio_timer.time = axradio_sync_slave_syncwindow;
//            wtimer0_addrelative(&axradio_timer);
//            axradio_sync_time = axradio_timer.time;
//            break;
//
//        case syncstate_slave_rxack:
//            axradio_syncstate = syncstate_slave_rxidle;
//            wtimer_remove(&axradio_timer);
//            axradio_sync_settimeradv(axradio_sync_slave_rxadvance[1]);
//            wtimer0_addabsolute(&axradio_timer);
//            goto transmitack;
//        };
//        break;
//
//    default:
//        break;
//    }
//}
//
//static void axradio_callback_fwd(struct wtimer_callback *desc)
//{
//    axradio_statuschange((struct axradio_status *)(desc + 1));
//}
//
//static void axradio_receive_callback_fwd(struct wtimer_callback *desc)
//{
//    //struct axradio_status *st = (struct axradio_status *)(desc + 1);
//    desc;
//    if (axradio_cb_receive.st.error != AXRADIO_ERR_NOERROR) {
//        axradio_statuschange((struct axradio_status *)&axradio_cb_receive.st);
//        return;
//    }
//    if (axradio_phy_pn9 && !AXRADIO_MODE_IS_STREAM_RECEIVE(axradio_mode)) {
//        uint16_t  len = axradio_cb_receive.st.rx.pktlen;
//        len += axradio_framing_maclen;
//        pn9_buffer((uint8_t *)axradio_cb_receive.st.rx.mac.raw, len, 0x1ff, -(AX5043_ENCODING & 0x01));
//    }
//    if (axradio_framing_swcrclen && !AXRADIO_MODE_IS_STREAM_RECEIVE(axradio_mode)) {
//        uint16_t  len = axradio_cb_receive.st.rx.pktlen;
//        len += axradio_framing_maclen;
//        len = axradio_framing_check_crc((uint8_t *)axradio_cb_receive.st.rx.mac.raw, len);
//        if (!len)
//            // receive error
//            goto endcb;
//        len -= axradio_framing_maclen;
//        len -= axradio_framing_swcrclen; // drop crc
//        axradio_cb_receive.st.rx.pktlen = len;
//    }
//
//
//    axradio_cb_receive.st.rx.phy.timeoffset = 0;
//    axradio_cb_receive.st.rx.phy.period = 0;
//    if (axradio_mode == AXRADIO_MODE_ACK_TRANSMIT ||
//        axradio_mode == AXRADIO_MODE_WOR_ACK_TRANSMIT ||
//        axradio_mode == AXRADIO_MODE_SYNC_ACK_MASTER) {
//        ax5043_off();
//        wtimer_remove(&axradio_timer);
//        if (axradio_mode == AXRADIO_MODE_SYNC_ACK_MASTER) {
//            axradio_syncstate = syncstate_master_normal;
//            axradio_sync_settimeradv(axradio_sync_xoscstartup);
//            wtimer0_addabsolute(&axradio_timer);
//        }
//        wtimer_remove_callback(&axradio_cb_transmitend.cb);
//        axradio_cb_transmitend.st.error = AXRADIO_ERR_NOERROR;
//        axradio_cb_transmitend.st.time.t = radio_read24((uint16_t)&AX5043_TIMER2);
//        wtimer_add_callback(&axradio_cb_transmitend.cb);
//    }
//    if (axradio_framing_destaddrpos != 0xff)
//        memcpy_xdata(&axradio_cb_receive.st.rx.mac.localaddr, &axradio_cb_receive.st.rx.mac.raw[axradio_framing_destaddrpos], axradio_framing_addrlen);
//    if (axradio_framing_sourceaddrpos != 0xff)
//        memcpy_xdata(&axradio_cb_receive.st.rx.mac.remoteaddr, &axradio_cb_receive.st.rx.mac.raw[axradio_framing_sourceaddrpos], axradio_framing_addrlen);
//    if (axradio_mode == AXRADIO_MODE_ACK_RECEIVE ||
//        axradio_mode == AXRADIO_MODE_WOR_ACK_RECEIVE ||
//        axradio_mode == AXRADIO_MODE_SYNC_ACK_SLAVE) {
//        axradio_ack_count = 0;
//        axradio_txbuffer_len = axradio_framing_maclen + axradio_framing_minpayloadlen;
//        memset_xdata(axradio_txbuffer, 0, axradio_framing_maclen);
//        if (axradio_framing_ack_seqnrpos != 0xff) {
//            uint8_t seqnr = axradio_cb_receive.st.rx.mac.raw[axradio_framing_ack_seqnrpos];
//            axradio_txbuffer[axradio_framing_ack_seqnrpos] = seqnr;
//            if (axradio_ack_seqnr != seqnr)
//                axradio_ack_seqnr = seqnr;
//            else
//                axradio_cb_receive.st.error = AXRADIO_ERR_RETRANSMISSION;
//        }
//        if (axradio_framing_destaddrpos != 0xff) {
//            if (axradio_framing_sourceaddrpos != 0xff)
//                memcpy_xdata(&axradio_txbuffer[axradio_framing_destaddrpos], &axradio_cb_receive.st.rx.mac.remoteaddr, axradio_framing_addrlen);
//            else
//                memcpy_xdata(&axradio_txbuffer[axradio_framing_destaddrpos], &axradio_default_remoteaddr, axradio_framing_addrlen);
//        }
//        if (axradio_framing_sourceaddrpos != 0xff)
//            memcpy_xdata(&axradio_txbuffer[axradio_framing_sourceaddrpos], &axradio_localaddr.addr, axradio_framing_addrlen);
//        if (axradio_framing_lenmask) {
//            uint8_t len_byte = (uint8_t)(axradio_txbuffer_len - axradio_framing_lenoffs) & axradio_framing_lenmask; // if you prefer not counting the len byte itself, set LENOFFS = 1
//            axradio_txbuffer[axradio_framing_lenpos] = (axradio_txbuffer[axradio_framing_lenpos] & (uint8_t)~axradio_framing_lenmask) | len_byte;
//        }
//        if (axradio_framing_swcrclen)
//            axradio_txbuffer_len = axradio_framing_append_crc(axradio_txbuffer, axradio_txbuffer_len);
//        if (axradio_phy_pn9) {
//            pn9_buffer(axradio_txbuffer, axradio_txbuffer_len, 0x1ff, -(AX5043_ENCODING & 0x01));
//        }
//        AX5043_IRQMASK1 = 0x00;
//        AX5043_IRQMASK0 = 0x00;
//        AX5043_PWRMODE = AX5043_PWRSTATE_XTAL_ON;
//        AX5043_FIFOSTAT = 3;
//        axradio_trxstate = trxstate_tx_longpreamble; // ensure that trxstate != off, otherwise we would prematurely enable the receiver, see below
//        while (AX5043_POWSTAT & 0x08);
//        wtimer_remove(&axradio_timer);
//        axradio_timer.time = axradio_framing_ack_delay;
//        wtimer1_addrelative(&axradio_timer);
//    }
//    if (axradio_mode == AXRADIO_MODE_SYNC_SLAVE ||
//        axradio_mode == AXRADIO_MODE_SYNC_ACK_SLAVE) {
//        if (axradio_mode != AXRADIO_MODE_SYNC_ACK_SLAVE)
//            ax5043_off();
//        switch (axradio_syncstate) {
//        default:
//        //case syncstate_slave_synchunt:
//        //case syncstate_slave_syncpause:
//            axradio_sync_time = axradio_conv_time_totimer0(axradio_cb_receive.st.time.t);
//            axradio_sync_periodcorr = -32768;
//            axradio_sync_seqnr = 0;
//            break;
//
//        case syncstate_slave_rxidle:
//        case syncstate_slave_rxsfdwindow:
//        case syncstate_slave_rxpacket:
//            axradio_sync_adjustperiodcorr();
//            axradio_cb_receive.st.rx.phy.period = axradio_sync_periodcorr >> SYNC_K1;
//            axradio_sync_seqnr = 1;
//            break;
//        };
//        axradio_sync_slave_nextperiod();
//        if (axradio_mode != AXRADIO_MODE_SYNC_ACK_SLAVE) {
//            axradio_syncstate = syncstate_slave_rxidle;
//            wtimer_remove(&axradio_timer);
//            axradio_sync_settimeradv(axradio_sync_slave_rxadvance[axradio_sync_seqnr]);
//            wtimer0_addabsolute(&axradio_timer);
//        } else {
//            axradio_syncstate = syncstate_slave_rxack;
//        }
//    }
//    axradio_statuschange((struct axradio_status *)&axradio_cb_receive.st);
//endcb:
//    if (axradio_mode == AXRADIO_MODE_WOR_RECEIVE) {
//        ax5043_receiver_on_wor();
//    } else if (axradio_mode == AXRADIO_MODE_ACK_RECEIVE ||
//               axradio_mode == AXRADIO_MODE_WOR_ACK_RECEIVE) {
//        uint8_t  trxst;
//        {
//            uint8_t  iesave = IE & 0x80;
//            EA = 0;
//            trxst = axradio_trxstate;
//            axradio_cb_receive.st.error = AXRADIO_ERR_PACKETDONE;
//            IE |= iesave;
//        }
//        if (trxst == trxstate_off) {
//                if (axradio_mode == AXRADIO_MODE_WOR_ACK_RECEIVE)
//                    ax5043_receiver_on_wor();
//                else
//                    ax5043_receiver_on_continuous();
//        }
//    } else {
//        switch (axradio_trxstate) {
//        case trxstate_rx:
//        case trxstate_rxwor:
//            AX5043_IRQMASK0 |= 0x01; // re-enable FIFO not empty irq
//            break;
//
//        default:
//            break;
//        }
//    }
//}
//
//static void axradio_killallcb(void)
//{
//    wtimer_remove_callback(&axradio_cb_receive.cb);
//    wtimer_remove_callback(&axradio_cb_receivesfd.cb);
//    wtimer_remove_callback(&axradio_cb_channelstate.cb);
//    wtimer_remove_callback(&axradio_cb_transmitstart.cb);
//    wtimer_remove_callback(&axradio_cb_transmitend.cb);
//    wtimer_remove_callback(&axradio_cb_transmitdata.cb);
//    wtimer_remove(&axradio_timer);
//}
//
//#if 0
//
//static uint16_t axradio_tunevoltage(void)
//{
//    uint16_t  r;
//    uint8_t  cnt = 2;
//    uint8_t  cnt2 = 0;
//    AX5043_GPADCCTRL = 0x84;
//    do {} while (AX5043_GPADCCTRL & 0x80);
//    r = (((uint16_t)(AX5043_GPADC13VALUE1 & 0x03)) << 8) | AX5043_GPADC13VALUE0;
//    r <<= 6;
//    do {
//        do {
//            AX5043_GPADCCTRL = 0x84;
//            r -= r >> 6;
//            do {} while (AX5043_GPADCCTRL & 0x80);
//            r += (((uint16_t)(AX5043_GPADC13VALUE1 & 0x03)) << 8) | AX5043_GPADC13VALUE0;
//        } while (--cnt2);
//    } while (--cnt);
//    return r;
//}
//
//#else
//
//static int16_t axradio_tunevoltage(void)
//{
//    int16_t  r = 0;
//    uint8_t  cnt = 64;
//    do {
//        AX5043_GPADCCTRL = 0x84;
//        do {} while (AX5043_GPADCCTRL & 0x80);
//    } while (--cnt);
//    cnt = 32;
//    do {
//        AX5043_GPADCCTRL = 0x84;
//        do {} while (AX5043_GPADCCTRL & 0x80);
//        {
//            int16_t x = AX5043_GPADC13VALUE1 & 0x03;
//            x <<= 8;
//            x |= AX5043_GPADC13VALUE0;
//            r += x;
//        }
//    } while (--cnt);
//    return r;
//}
//
//#endif
//
//static uint8_t axradio_adjustvcoi(uint8_t rng)
//{
//    uint8_t offs;
//    uint8_t bestrng;
//    uint16_t bestval = ~0;
//    rng &= 0x7F;
//    bestrng = rng;
//    for (offs = 0; offs != 16; ++offs) {
//        uint16_t val;
//        if (!((uint8_t)(rng + offs) & 0xC0)) {
//            AX5043_PLLVCOI = 0x80 | (rng + offs);
//            val = axradio_tunevoltage();
//            if (val < bestval) {
//                bestval = val;
//                bestrng = rng + offs;
//            }
//        }
//        if (!offs)
//            continue;
//        if (!((uint8_t)(rng - offs) & 0xC0)) {
//            AX5043_PLLVCOI = 0x80 | (rng - offs);
//            val = axradio_tunevoltage();
//            if (val < bestval) {
//                bestval = val;
//                bestrng = rng - offs;
//            }
//        }
//    }
//    // if we hit the lower rail, do not change anything
//    if (bestval <= 0x0010)
//        return rng | 0x80;
//    return bestrng | 0x80;
//}
//
//static uint8_t axradio_calvcoi(void)
//{
//    uint8_t i;
//    uint8_t r = 0;
//    uint16_t vmin = 0xffff;
//    uint16_t vmax = 0x0000;
//    for (i = 0x40; i != 0;) {
//        uint16_t curtune;
//        --i;
//        AX5043_PLLVCOI = 0x80 | i;
//        AX5043_PLLRANGINGA; // clear PLL lock loss
//        curtune = axradio_tunevoltage();
//        AX5043_PLLRANGINGA; // clear PLL lock loss
//        ((uint16_t *)axradio_rxbuffer)[i] = curtune;
//        if (curtune > vmax)
//            vmax = curtune;
//        if (curtune < vmin) {
//            vmin = curtune;
//            // check whether the PLL is locked
//            if (!(0xC0 & (uint8_t)~AX5043_PLLRANGINGA))
//                r = i | 0x80;
//        }
//    }
//    if (!(r & 0x80) || vmax >= 0xFF00 || vmin < 0x0100 || vmax - vmin < 0x6000)
//        return 0;
//    return r;
//}
//
///*
// * Public API
// */
//
//uint8_t axradio_init(void)
//{
//    uint8_t  i;
//    axradio_mode = AXRADIO_MODE_UNINIT;
//    axradio_killallcb();
//    axradio_cb_receive.cb.handler = axradio_receive_callback_fwd;
//    axradio_cb_receive.st.status = AXRADIO_STAT_RECEIVE;
//    memset_xdata(axradio_cb_receive.st.rx.mac.remoteaddr, 0, sizeof(axradio_cb_receive.st.rx.mac.remoteaddr));
//    memset_xdata(axradio_cb_receive.st.rx.mac.localaddr, 0, sizeof(axradio_cb_receive.st.rx.mac.localaddr));
//    axradio_cb_receivesfd.cb.handler = axradio_callback_fwd;
//    axradio_cb_receivesfd.st.status = AXRADIO_STAT_RECEIVESFD;
//    axradio_cb_channelstate.cb.handler = axradio_callback_fwd;
//    axradio_cb_channelstate.st.status = AXRADIO_STAT_CHANNELSTATE;
//    axradio_cb_transmitstart.cb.handler = axradio_callback_fwd;
//    axradio_cb_transmitstart.st.status = AXRADIO_STAT_TRANSMITSTART;
//    axradio_cb_transmitend.cb.handler = axradio_callback_fwd;
//    axradio_cb_transmitend.st.status = AXRADIO_STAT_TRANSMITEND;
//    axradio_cb_transmitdata.cb.handler = axradio_callback_fwd;
//    axradio_cb_transmitdata.st.status = AXRADIO_STAT_TRANSMITDATA;
//    axradio_timer.handler = axradio_timer_callback;
//    axradio_curchannel = 0;
//    axradio_curfreqoffset = 0;
//    IE_4 = 0;
//    axradio_trxstate = trxstate_off;
//    if (ax5043_reset())
//        return AXRADIO_ERR_NOCHIP;
//    ax5043_init_registers();
//    ax5043_set_registers_tx();
//    AX5043_PLLLOOP = 0x09; // default 100kHz loop BW for ranging
//    AX5043_PLLCPI = 0x08;
//
//    IE_4 = 1;
//    // range all channels
//    AX5043_PWRMODE = AX5043_PWRSTATE_XTAL_ON;
//    AX5043_MODULATION = 0x08;
//    AX5043_FSKDEV2 = 0x00;
//    AX5043_FSKDEV1 = 0x00;
//    AX5043_FSKDEV0 = 0x00;
//    axradio_wait_for_xtal();
//    for (i = 0; i < axradio_phy_nrchannels; ++i) {
//        uint8_t  iesave;
//        {
//            uint32_t  f = axradio_phy_chanfreq[i];
//            AX5043_FREQA0 = f;
//            AX5043_FREQA1 = f >> 8;
//            AX5043_FREQA2 = f >> 16;
//            AX5043_FREQA3 = f >> 24;
//        }
//        iesave = IE & 0x80;
//        EA = 0;
//        axradio_trxstate = trxstate_pll_ranging;
//        AX5043_IRQMASK1 = 0x10; // enable pll autoranging done interrupt
//        {
//            uint8_t  r;
//            if( !(axradio_phy_chanpllrnginit[0] & 0xF0) ) { // start values for ranging available
//                r = axradio_phy_chanpllrnginit[i] | 0x10;
//            }
//            else {
//                r = 0x18;
//                if (i) {
//                    r = axradio_phy_chanpllrng[i - 1];
//                    if (r & 0x20)
//                        r = 0x08;
//                    r &= 0x0F;
//                    r |= 0x10;
//                }
//            }
//            AX5043_PLLRANGINGA = r; // init ranging process starting from "range"
//        }
//        for (;;) {
//            EA = 0;
//            if (axradio_trxstate == trxstate_pll_ranging_done)
//                break;
//            wtimer_idle(WTFLAG_CANSTANDBY);
//            IE |= iesave;
//            wtimer_runcallbacks();
//        }
//        axradio_trxstate = trxstate_off;
//        AX5043_IRQMASK1 = 0x00;
//        axradio_phy_chanpllrng[i] = AX5043_PLLRANGINGA;
//        IE |= iesave;
//    }
//    // VCOI Calibration
//    if (axradio_phy_vcocalib) {
//        ax5043_set_registers_tx();
//        AX5043_MODULATION = 0x08;
//        AX5043_FSKDEV2 = 0x00;
//        AX5043_FSKDEV1 = 0x00;
//        AX5043_FSKDEV0 = 0x00;
//        AX5043_PLLLOOP |= 0x04;
//        {
//            uint8_t x = AX5043_0xF35;
//            x |= 0x80;
//            if (2 & (uint8_t)~x)
//                ++x;
//            AX5043_0xF35 = x;
//        }
//        AX5043_PWRMODE = AX5043_PWRSTATE_SYNTH_TX;
//        {
//            uint8_t  vcoisave = AX5043_PLLVCOI;
//            uint8_t j = 2;
//            for (i = 0; i < axradio_phy_nrchannels; ++i) {
//                axradio_phy_chanvcoi[i] = 0;
//                if (axradio_phy_chanpllrng[i] & 0x20)
//                    continue;
//                AX5043_PLLRANGINGA = axradio_phy_chanpllrng[i] & 0x0F;
//                {
//                    uint32_t  f = axradio_phy_chanfreq[i];
//                    AX5043_FREQA0 = f;
//                    AX5043_FREQA1 = f >> 8;
//                    AX5043_FREQA2 = f >> 16;
//                    AX5043_FREQA3 = f >> 24;
//                }
//                do {
//                    if (axradio_phy_chanvcoiinit[0]) {
//                        uint8_t x = axradio_phy_chanvcoiinit[i];
//                        if (!(axradio_phy_chanpllrnginit[0] & 0xF0))
//                            x += (axradio_phy_chanpllrng[i] & 0x0F) - (axradio_phy_chanpllrnginit[i] & 0x0F);
//                        axradio_phy_chanvcoi[i] = axradio_adjustvcoi(x);
//                    } else {
//                        axradio_phy_chanvcoi[i] = axradio_calvcoi();
//                    }
//                } while (--j);
//                j = 1;
//#if 0
//                dbglink_writestr("\nVCOI Calibration Channel ");
//                dbglink_writenum16(i, 0, 0);
//                dbglink_writestr(" result ");
//                dbglink_writehex16(axradio_phy_chanvcoi_tx[i], 2, WRNUM_PADZERO);
//                dbglink_tx('\n');
//                {
//                    uint8_t i;
//                    for (i = 0; i != 64; ++i) {
//                        dbglink_writenum16(i, 2, 0);
//                        dbglink_tx(' ');
//                        dbglink_writenum16(axradio_rxbuffer[2*i] | (((uint16_t)axradio_rxbuffer[2*i+1])<<8), 6, WRNUM_SIGNED);
//                        dbglink_tx(' ');
//                        dbglink_writehex16(axradio_rxbuffer[2*i] | (((uint16_t)axradio_rxbuffer[2*i+1])<<8), 6, WRNUM_PADZERO);
//                        dbglink_tx('\n');
//                    }
//                }
//#endif
//            }
//            AX5043_PLLVCOI = vcoisave;
//        }
//#if 1
//        if (DBGLNKSTAT & 0x10) {
//            for (i = 0; i < axradio_phy_nrchannels; ++i) {
//                uint8_t chg = ((axradio_phy_chanpllrnginit[0] & 0xF0) || axradio_phy_chanpllrnginit[i] != axradio_phy_chanpllrng[i])
//                    || (!axradio_phy_chanvcoiinit[0] || ((axradio_phy_chanvcoiinit[i] ^ axradio_phy_chanvcoi[i]) & 0x7F));
//                if (1 && !chg)
//                    continue;
//                dbglink_writestr("CH ");
//                dbglink_writenum16(i, 0, 0);
//                dbglink_writestr(" RNG ");
//                if (!(axradio_phy_chanpllrnginit[0] & 0xF0)) {
//                    dbglink_writenum16(axradio_phy_chanpllrnginit[i], 0, 0);
//                    dbglink_tx('/');
//                }
//                dbglink_writenum16(axradio_phy_chanpllrng[i], 0, 0);
//                dbglink_writestr(" VCOI ");
//                if (axradio_phy_chanvcoiinit[0]) {
//                    dbglink_writenum16(axradio_phy_chanvcoiinit[i] & 0x7F, 0, 0);
//                    dbglink_tx('/');
//                }
//                dbglink_writenum16(axradio_phy_chanvcoi[i] & 0x7F, 0, 0);
//                if (chg)
//                    dbglink_writestr(" *");
//                dbglink_tx('\n');
//            }
//        }
//#endif
//    }
//    AX5043_PWRMODE = AX5043_PWRSTATE_POWERDOWN;
//    ax5043_init_registers();
//    ax5043_set_registers_rx();
//    AX5043_PLLRANGINGA = axradio_phy_chanpllrng[0] & 0x0F;
//    {
//        uint32_t  f = axradio_phy_chanfreq[0];
//        AX5043_FREQA0 = f;
//        AX5043_FREQA1 = f >> 8;
//        AX5043_FREQA2 = f >> 16;
//        AX5043_FREQA3 = f >> 24;
//    }
//
//    axradio_mode = AXRADIO_MODE_OFF;
//    for (i = 0; i < axradio_phy_nrchannels; ++i)
//        if (axradio_phy_chanpllrng[i] & 0x20)
//            return AXRADIO_ERR_RANGING;
//    return AXRADIO_ERR_NOERROR;
//}
//
//uint8_t axradio_cansleep(void)
//{
//    if (axradio_trxstate == trxstate_off || axradio_trxstate == trxstate_rxwor)
//        return 1;
//    return 0;
//}
//
//#if defined(SDCC)
//static void wtimer_cansleep_dummy(void) __naked
//{
//        __asm
//        .area WTCANSLP0 (CODE)
//        .area WTCANSLP1 (CODE)
//        .area WTCANSLP2 (CODE)
//
//        .area WTCANSLP1 (CODE)
//        lcall   _axradio_cansleep
//        mov     a,dpl
//        jnz     00000$
//        ret
//00000$:
//        .area CSEG      (CODE)
//        __endasm;
//}
//#endif
//
//uint8_t axradio_set_mode(uint8_t mode)
//{
//    if (mode == axradio_mode)
//        return AXRADIO_ERR_NOERROR;
//    switch (axradio_mode) {
//    case AXRADIO_MODE_UNINIT:
//    {
//        uint8_t  r = axradio_init();
//        if (r != AXRADIO_ERR_NOERROR)
//            return r;
//        break;
//    }
//
//    case AXRADIO_MODE_DEEPSLEEP:
//    {
//        uint8_t  r = ax5043_wakeup_deepsleep();
//        if (r)
//            return AXRADIO_ERR_NOCHIP;
//        ax5043_init_registers();
//        r = axradio_set_channel(axradio_curchannel);
//        if (r != AXRADIO_ERR_NOERROR)
//            return r;
//        axradio_trxstate = trxstate_off;
//        axradio_mode = AXRADIO_MODE_OFF;
//        break;
//    }
//
//    case AXRADIO_MODE_STREAM_TRANSMIT:
//    case AXRADIO_MODE_STREAM_TRANSMIT_UNENC:
//    case AXRADIO_MODE_STREAM_TRANSMIT_SCRAM:
//    case AXRADIO_MODE_STREAM_TRANSMIT_UNENC_LSB:
//    case AXRADIO_MODE_STREAM_TRANSMIT_SCRAM_LSB:
//    case AXRADIO_MODE_CW_TRANSMIT:
//    {
//        uint8_t  iesave = IE & 0x80;
//        EA = 0;
//        if (axradio_trxstate == trxstate_off) {
//            update_timeanchor();
//            wtimer_remove_callback(&axradio_cb_transmitend.cb);
//            axradio_cb_transmitend.st.error = AXRADIO_ERR_NOERROR;
//            axradio_cb_transmitend.st.time.t = axradio_timeanchor.radiotimer;
//            wtimer_add_callback(&axradio_cb_transmitend.cb);
//        }
//        ax5043_off();
//        IE |= iesave;
//        // fully initialize chip, to restore modulation and framing registers
//        ax5043_init_registers();
//        axradio_mode = AXRADIO_MODE_OFF;
//        break;
//    }
//
//    case AXRADIO_MODE_STREAM_RECEIVE:
//    case AXRADIO_MODE_STREAM_RECEIVE_UNENC:
//    case AXRADIO_MODE_STREAM_RECEIVE_SCRAM:
//    case AXRADIO_MODE_STREAM_RECEIVE_UNENC_LSB:
//    case AXRADIO_MODE_STREAM_RECEIVE_SCRAM_LSB:
//    case AXRADIO_MODE_STREAM_RECEIVE_DATAPIN:
//        ax5043_off();
//        ax5043_init_registers();
//        axradio_mode = AXRADIO_MODE_OFF;
//
//    default:
//        ax5043_off();
//        axradio_mode = AXRADIO_MODE_OFF;
//        break;
//    }
//    axradio_killallcb();
//    if (mode == AXRADIO_MODE_UNINIT)
//        return AXRADIO_ERR_NOTSUPPORTED;
//    axradio_syncstate = syncstate_off;
//    switch (mode) {
//    case AXRADIO_MODE_OFF:
//        return AXRADIO_ERR_NOERROR;
//
//    case AXRADIO_MODE_DEEPSLEEP:
//        ax5043_enter_deepsleep();
//        axradio_mode = AXRADIO_MODE_DEEPSLEEP;
//        return AXRADIO_ERR_NOERROR;
//
//    case AXRADIO_MODE_ASYNC_TRANSMIT:
//    case AXRADIO_MODE_ACK_TRANSMIT:
//        axradio_mode = mode;
//        axradio_ack_seqnr = 0xff;
//        ax5043_init_registers_tx();
//        return AXRADIO_ERR_NOERROR;
//
//    case AXRADIO_MODE_WOR_TRANSMIT:
//    case AXRADIO_MODE_WOR_ACK_TRANSMIT:
//        axradio_mode = mode;
//        axradio_ack_seqnr = 0xff;
//        ax5043_init_registers_tx();
//        return AXRADIO_ERR_NOERROR;
//
//    case AXRADIO_MODE_ASYNC_RECEIVE:
//    case AXRADIO_MODE_ACK_RECEIVE:
//        axradio_mode = mode;
//        axradio_ack_seqnr = 0xff;
//        ax5043_init_registers_rx();
//        ax5043_receiver_on_continuous();
//    enablecs:
//        if (axradio_phy_cs_enabled) {
//            wtimer_remove(&axradio_timer);
//            axradio_timer.time = axradio_phy_cs_period;
//            wtimer0_addrelative(&axradio_timer);
//        }
//        return AXRADIO_ERR_NOERROR;
//
//    case AXRADIO_MODE_WOR_RECEIVE:
//    case AXRADIO_MODE_WOR_ACK_RECEIVE:
//        axradio_ack_seqnr = 0xff;
//        axradio_mode = mode;
//        ax5043_init_registers_rx();
//        ax5043_receiver_on_wor();
//        return AXRADIO_ERR_NOERROR;
//
//    case AXRADIO_MODE_STREAM_TRANSMIT:
//    case AXRADIO_MODE_STREAM_TRANSMIT_UNENC:
//    case AXRADIO_MODE_STREAM_TRANSMIT_SCRAM:
//    case AXRADIO_MODE_STREAM_TRANSMIT_UNENC_LSB:
//    case AXRADIO_MODE_STREAM_TRANSMIT_SCRAM_LSB:
//        axradio_mode = mode;
//        if (axradio_mode == AXRADIO_MODE_STREAM_TRANSMIT_UNENC ||
//            axradio_mode == AXRADIO_MODE_STREAM_TRANSMIT_UNENC_LSB)
//            AX5043_ENCODING = 0;
//        if (axradio_mode == AXRADIO_MODE_STREAM_TRANSMIT_SCRAM ||
//            axradio_mode == AXRADIO_MODE_STREAM_TRANSMIT_SCRAM_LSB)
//            AX5043_ENCODING = 4;
//        if (axradio_mode == AXRADIO_MODE_STREAM_TRANSMIT_UNENC_LSB ||
//            axradio_mode == AXRADIO_MODE_STREAM_TRANSMIT_SCRAM_LSB)
//            AX5043_PKTADDRCFG &= 0x7F;
//        ax5043_init_registers_tx();
//        AX5043_FRAMING = 0;
//        ax5043_prepare_tx();
//        axradio_trxstate = trxstate_txstream_xtalwait;
//        while (!(AX5043_POWSTAT & 0x08)) {}; // wait for modem vdd so writing the FIFO is safe
//        AX5043_FIFOSTAT = 3; // clear FIFO data & flags (prevent transmitting anything left over in the FIFO, this has no effect if the FIFO is not powerered, in this case it is reset any way)
//        AX5043_RADIOEVENTREQ0; // make sure REVRDONE bit is cleared, so it is a reliable indicator that the packet is out
//        update_timeanchor();
//        wtimer_remove_callback(&axradio_cb_transmitdata.cb);
//        axradio_cb_transmitdata.st.error = AXRADIO_ERR_NOERROR;
//        axradio_cb_transmitdata.st.time.t = axradio_timeanchor.radiotimer;
//        wtimer_add_callback(&axradio_cb_transmitdata.cb);
//        return AXRADIO_ERR_NOERROR;
//
//    case AXRADIO_MODE_STREAM_RECEIVE:
//    case AXRADIO_MODE_STREAM_RECEIVE_UNENC:
//    case AXRADIO_MODE_STREAM_RECEIVE_SCRAM:
//    case AXRADIO_MODE_STREAM_RECEIVE_UNENC_LSB:
//    case AXRADIO_MODE_STREAM_RECEIVE_SCRAM_LSB:
//    case AXRADIO_MODE_STREAM_RECEIVE_DATAPIN:
//        axradio_mode = mode;
//        ax5043_init_registers_rx();
//        if (axradio_mode == AXRADIO_MODE_STREAM_RECEIVE_UNENC ||
//            axradio_mode == AXRADIO_MODE_STREAM_RECEIVE_UNENC_LSB)
//            AX5043_ENCODING = 0;
//        if (axradio_mode == AXRADIO_MODE_STREAM_RECEIVE_SCRAM ||
//            axradio_mode == AXRADIO_MODE_STREAM_RECEIVE_SCRAM_LSB)
//            AX5043_ENCODING = 4;
//        if (axradio_mode == AXRADIO_MODE_STREAM_RECEIVE_UNENC_LSB ||
//            axradio_mode == AXRADIO_MODE_STREAM_RECEIVE_SCRAM_LSB)
//            AX5043_PKTADDRCFG &= 0x7F;
//        AX5043_FRAMING = 0;
//        AX5043_PKTCHUNKSIZE = 8; // 64 byte
//        AX5043_RXPARAMSETS = 0x00;
//        if( axradio_mode == AXRADIO_MODE_STREAM_RECEIVE_DATAPIN )
//        {
//            ax5043_set_registers_rxcont_singleparamset();
//            AX5043_PINFUNCDATA = 0x04;
//            AX5043_PINFUNCDCLK = 0x04;
//        }
//        ax5043_receiver_on_continuous();
//        goto enablecs;
//
//    case AXRADIO_MODE_CW_TRANSMIT:
//        axradio_mode = AXRADIO_MODE_CW_TRANSMIT;
//        ax5043_init_registers_tx();
//        AX5043_MODULATION = 8;   // Set an FSK mode
//        AX5043_FSKDEV2 = 0x00;
//        AX5043_FSKDEV1 = 0x00;
//        AX5043_FSKDEV0 = 0x00;
//        AX5043_TXRATE2 = 0x00;
//        AX5043_TXRATE1 = 0x00;
//        AX5043_TXRATE0 = 0x01;
//        AX5043_PINFUNCDATA = 0x04;
//        AX5043_PWRMODE = AX5043_PWRSTATE_FIFO_ON;
//        axradio_trxstate = trxstate_txcw_xtalwait;
//        AX5043_IRQMASK0 = 0x00;
//        AX5043_IRQMASK1 = 0x01; // enable xtal ready interrupt
//        return AXRADIO_ERR_NOERROR;
//
//    case AXRADIO_MODE_SYNC_MASTER:
//    case AXRADIO_MODE_SYNC_ACK_MASTER:
//        axradio_mode = mode;
//        axradio_syncstate = syncstate_master_normal;
//        // minimal startup delay
//        wtimer_remove(&axradio_timer);
//        axradio_timer.time = 2;
//        wtimer0_addrelative(&axradio_timer);
//        axradio_sync_time = axradio_timer.time;
//        axradio_sync_addtime(axradio_sync_xoscstartup);
//        return AXRADIO_ERR_NOERROR;
//
//    case AXRADIO_MODE_SYNC_SLAVE:
//    case AXRADIO_MODE_SYNC_ACK_SLAVE:
//        axradio_mode = mode;
//        ax5043_init_registers_rx();
//        ax5043_receiver_on_continuous();
//        axradio_syncstate = syncstate_slave_synchunt;
//        wtimer_remove(&axradio_timer);
//        axradio_timer.time = axradio_sync_slave_initialsyncwindow;
//        wtimer0_addrelative(&axradio_timer);
//        axradio_sync_time = axradio_timer.time;
//        wtimer_remove_callback(&axradio_cb_receive.cb);
//        memset_xdata(&axradio_cb_receive.st, 0, sizeof(axradio_cb_receive.st));
//        axradio_cb_receive.st.time.t = axradio_timeanchor.radiotimer;
//        axradio_cb_receive.st.error = AXRADIO_ERR_RESYNC;
//        wtimer_add_callback(&axradio_cb_receive.cb);
//        return AXRADIO_ERR_NOERROR;
//
//    default:
//        return AXRADIO_ERR_NOTSUPPORTED;
//    }
//}
//
//uint8_t axradio_get_mode(void)
//{
//    return axradio_mode;
//}
//
//uint8_t axradio_set_channel(uint8_t chnum)
//{
//    uint8_t  rng;
//    if (chnum >= axradio_phy_nrchannels)
//        return AXRADIO_ERR_INVALID;
//    axradio_curchannel = chnum;
//    rng = axradio_phy_chanpllrng[chnum];
//    if (rng & 0x20)
//        return AXRADIO_ERR_RANGING;
//    {
//        uint32_t  f = axradio_phy_chanfreq[chnum];
//        f += axradio_curfreqoffset;
//        if (AX5043_PLLLOOP & 0x80) {
//            AX5043_PLLRANGINGA = rng & 0x0F;
//            AX5043_FREQA0 = f;
//            AX5043_FREQA1 = f >> 8;
//            AX5043_FREQA2 = f >> 16;
//            AX5043_FREQA3 = f >> 24;
//        } else {
//            AX5043_PLLRANGINGB = rng & 0x0F;
//            AX5043_FREQB0 = f;
//            AX5043_FREQB1 = f >> 8;
//            AX5043_FREQB2 = f >> 16;
//            AX5043_FREQB3 = f >> 24;
//        }
//    }
//    AX5043_PLLLOOP ^= 0x80;
//    return AXRADIO_ERR_NOERROR;
//}
//
//uint8_t axradio_get_channel(void)
//{
//    return axradio_curchannel;
//}
//
//uint8_t axradio_get_pllrange(void)
//{
//    return axradio_phy_chanpllrng[axradio_curchannel] & 0x0F;
//}
//
//uint8_t axradio_get_pllvcoi(void)
//{
//    if (axradio_phy_vcocalib) {
//        uint8_t x = axradio_phy_chanvcoi[axradio_curchannel];
//        if (x & 0x80)
//            return x;
//    }
//    {
//        uint8_t x = axradio_phy_chanvcoiinit[axradio_curchannel];
//        if (x & 0x80) {
//            if (!(axradio_phy_chanpllrnginit[0] & 0xF0)) {
//                x += (axradio_phy_chanpllrng[axradio_curchannel] & 0x0F) - (axradio_phy_chanpllrnginit[axradio_curchannel] & 0x0F);
//                x &= 0x3f;
//                x |= 0x80;
//            }
//            return x;
//        }
//    }
//    return AX5043_PLLVCOI;
//}
//
//static uint8_t axradio_set_curfreqoffset(int32_t offs)
//{
//    axradio_curfreqoffset = offs;
//    if (checksignedlimit32(offs, axradio_phy_maxfreqoffset))
//        return AXRADIO_ERR_NOERROR;
//    if (axradio_curfreqoffset < 0)
//        axradio_curfreqoffset = -axradio_phy_maxfreqoffset;
//    else
//        axradio_curfreqoffset = axradio_phy_maxfreqoffset;
//    return AXRADIO_ERR_INVALID;
//}
//
//uint8_t axradio_set_freqoffset(int32_t offs)
//{
//    uint8_t  ret = axradio_set_curfreqoffset(offs);
//    {
//        uint8_t  ret2 = axradio_set_channel(axradio_curchannel);
//        if (ret == AXRADIO_ERR_NOERROR)
//            ret = ret2;
//    }
//    return ret;
//}
//
//int32_t axradio_get_freqoffset(void)
//{
//    return axradio_curfreqoffset;
//}
//
//void axradio_set_local_address(const struct axradio_address_mask  *addr)
//{
//    memcpy_xdatageneric(&axradio_localaddr, addr, sizeof(axradio_localaddr));
//    axradio_setaddrregs();
//}
//
//void axradio_get_local_address(struct axradio_address_mask  *addr)
//{
//    memcpy_genericxdata(addr, &axradio_localaddr, sizeof(axradio_localaddr));
//}
//
//void axradio_set_default_remote_address(const struct axradio_address  *addr)
//{
//    memcpy_xdatageneric(&axradio_default_remoteaddr, addr, sizeof(axradio_default_remoteaddr));
//}
//
//void axradio_get_default_remote_address(struct axradio_address  *addr)
//{
//    memcpy_genericxdata(addr, &axradio_default_remoteaddr, sizeof(axradio_default_remoteaddr));
//}
//
//uint8_t axradio_transmit(const struct axradio_address  *addr, const uint8_t  *pkt, uint16_t pktlen)
//{
//    switch (axradio_mode) {
//    case AXRADIO_MODE_STREAM_TRANSMIT:
//    case AXRADIO_MODE_STREAM_TRANSMIT_UNENC:
//    case AXRADIO_MODE_STREAM_TRANSMIT_SCRAM:
//    case AXRADIO_MODE_STREAM_TRANSMIT_UNENC_LSB:
//    case AXRADIO_MODE_STREAM_TRANSMIT_SCRAM_LSB:
//        {
//            uint16_t  fifofree = radio_read16((uint16_t)&AX5043_FIFOFREE1);
//            if (fifofree < pktlen + 3)
//                return AXRADIO_ERR_INVALID;
//        }
//        if (pktlen) {
//            uint8_t  i = pktlen;
//            AX5043_FIFODATA = AX5043_FIFOCMD_DATA | (7 << 5);
//            AX5043_FIFODATA = i + 1;
//            AX5043_FIFODATA = 0x08;
//            do {
//                AX5043_FIFODATA = *pkt++;
//            } while (--i);
//        }
//        AX5043_FIFOSTAT =  4; // FIFO commit
//        {
//            uint8_t  iesave = IE & 0x80;
//            EA = 0;
//            AX5043_IRQMASK0 |= 0x08;
//            IE |= iesave;
//        }
//        return AXRADIO_ERR_NOERROR;
//
//    case AXRADIO_MODE_SYNC_MASTER:
//    case AXRADIO_MODE_SYNC_ACK_MASTER:
//        goto dotx;
//
//    case AXRADIO_MODE_ASYNC_RECEIVE:
//    case AXRADIO_MODE_WOR_RECEIVE:
//        if (axradio_syncstate != syncstate_off)
//            return AXRADIO_ERR_BUSY;
//        AX5043_IRQMASK1 = 0x00;
//        AX5043_IRQMASK0 = 0x00;
//        AX5043_PWRMODE = AX5043_PWRSTATE_XTAL_ON;
//        AX5043_FIFOSTAT = 3;
//        while (AX5043_POWSTAT & 0x08);
//        ax5043_init_registers_tx();
//        goto dotx;
//
//    case AXRADIO_MODE_ASYNC_TRANSMIT:
//    case AXRADIO_MODE_WOR_TRANSMIT:
//    case AXRADIO_MODE_ACK_TRANSMIT:
//    case AXRADIO_MODE_WOR_ACK_TRANSMIT:
//        if (axradio_syncstate != syncstate_off)
//            return AXRADIO_ERR_BUSY;
//    dotx:
//        axradio_ack_count = axradio_framing_ack_retransmissions;
//        ++axradio_ack_seqnr;
//        axradio_txbuffer_len = pktlen + axradio_framing_maclen;
//        if (axradio_txbuffer_len > sizeof(axradio_txbuffer))
//            return AXRADIO_ERR_INVALID;
//        memset_xdata(axradio_txbuffer, 0, axradio_framing_maclen);
//        memcpy_xdatageneric(&axradio_txbuffer[axradio_framing_maclen], pkt, pktlen);
//        if (axradio_framing_ack_seqnrpos != 0xff)
//            axradio_txbuffer[axradio_framing_ack_seqnrpos] = axradio_ack_seqnr;
//        if (axradio_framing_destaddrpos != 0xff)
//            memcpy_xdatageneric(&axradio_txbuffer[axradio_framing_destaddrpos], &addr->addr, axradio_framing_addrlen);
//        if (axradio_framing_sourceaddrpos != 0xff)
//            memcpy_xdata(&axradio_txbuffer[axradio_framing_sourceaddrpos], &axradio_localaddr.addr, axradio_framing_addrlen);
//        if (axradio_framing_lenmask) {
//            uint8_t  len_byte = (uint8_t)(axradio_txbuffer_len - axradio_framing_lenoffs) & axradio_framing_lenmask; // if you prefer not counting the len byte itself, set LENOFFS = 1
//            axradio_txbuffer[axradio_framing_lenpos] = (axradio_txbuffer[axradio_framing_lenpos] & (uint8_t)~axradio_framing_lenmask) | len_byte;
//        }
//        if (axradio_framing_swcrclen)
//            axradio_txbuffer_len = axradio_framing_append_crc(axradio_txbuffer, axradio_txbuffer_len);
//        if (axradio_phy_pn9)
//            pn9_buffer(axradio_txbuffer, axradio_txbuffer_len, 0x1ff, -(AX5043_ENCODING & 0x01));
//        if (axradio_mode == AXRADIO_MODE_SYNC_MASTER ||
//            axradio_mode == AXRADIO_MODE_SYNC_ACK_MASTER)
//            return AXRADIO_ERR_NOERROR;
//        if (axradio_mode == AXRADIO_MODE_WOR_TRANSMIT ||
//            axradio_mode == AXRADIO_MODE_WOR_ACK_TRANSMIT)
//            axradio_txbuffer_cnt = axradio_phy_preamble_wor_longlen;
//        else
//            axradio_txbuffer_cnt = axradio_phy_preamble_longlen;
//        if (axradio_phy_lbt_retries) {
//            switch (axradio_mode) {
//            case AXRADIO_MODE_ASYNC_TRANSMIT:
//            case AXRADIO_MODE_WOR_TRANSMIT:
//            case AXRADIO_MODE_ACK_TRANSMIT:
//            case AXRADIO_MODE_WOR_ACK_TRANSMIT:
//            case AXRADIO_MODE_WOR_RECEIVE:
//            case AXRADIO_MODE_WOR_ACK_RECEIVE:
//            case AXRADIO_MODE_ASYNC_RECEIVE:
//            case AXRADIO_MODE_ACK_RECEIVE:
//                ax5043_off_xtal();
//                ax5043_init_registers_rx();
//                AX5043_RSSIREFERENCE = axradio_phy_rssireference;
//                AX5043_PWRMODE = AX5043_PWRSTATE_FULL_RX;
//                axradio_ack_count = axradio_phy_lbt_retries;
//                axradio_syncstate = syncstate_lbt;
//                wtimer_remove(&axradio_timer);
//                axradio_timer.time = axradio_phy_cs_period;
//                wtimer0_addrelative(&axradio_timer);
//                return AXRADIO_ERR_NOERROR;
//
//            default:
//                break;
//            }
//        }
//        axradio_syncstate = syncstate_asynctx;
//        ax5043_prepare_tx();
//        return AXRADIO_ERR_NOERROR;
//
//    default:
//        return AXRADIO_ERR_NOTSUPPORTED;
//    }
//}
//
//static uint8_t axradio_set_paramsets(uint8_t val)
//{
//    if (!AXRADIO_MODE_IS_STREAM_RECEIVE(axradio_mode))
//        return AXRADIO_ERR_NOTSUPPORTED;
//    AX5043_RXPARAMSETS = val;
//    return AXRADIO_ERR_NOERROR;
//}
//
//uint8_t axradio_agc_freeze(void)
//{
//    return axradio_set_paramsets(0xff);
//}
//
//uint8_t axradio_agc_thaw(void)
//{
//    return axradio_set_paramsets(0x00);
//}
