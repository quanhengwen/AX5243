#include "Radio.h"
#include "AX5043.h"
#include "Radio_Config.h"

#define DBG_TAG "radio"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>

void WirelessBitRateConfigure(uint8_t BitRate0)
{
    switch (BitRate0)
    {
        case 0://1200
            SpiWriteLongAddressRegister(REG_AX5043_IFFREQ1  , 0x00 );
            SpiWriteLongAddressRegister(REG_AX5043_IFFREQ0  , 0xFC  );
            SpiWriteLongAddressRegister(REG_AX5043_DECIMATION , 0x36  );
            SpiWriteLongAddressRegister(REG_AX5043_RXDATARATE2 , 0x00 );
            SpiWriteLongAddressRegister(REG_AX5043_RXDATARATE1 , 0x64 );
            SpiWriteLongAddressRegister(REG_AX5043_RXDATARATE0 , 0x4f  );
            SpiWriteLongAddressRegister( REG_AX5043_MAXRFOFFSET1 , 0x01);
            SpiWriteLongAddressRegister( REG_AX5043_MAXRFOFFSET0 , 0x17);
            SpiWriteLongAddressRegister(REG_AX5043_FSKDMAX1,0x01);
            SpiWriteLongAddressRegister(REG_AX5043_FSKDMAX0,0xC0);
            SpiWriteLongAddressRegister(REG_AX5043_FSKDMIN1,0xFe);
            SpiWriteLongAddressRegister(REG_AX5043_FSKDMIN0,0x40);

            SpiWriteLongAddressRegister(REG_AX5043_AGCGAIN0  , 0x97   );
            SpiWriteLongAddressRegister( REG_AX5043_AGCTARGET0 , 0x76  );
            SpiWriteLongAddressRegister( REG_AX5043_TIMEGAIN0  , 0xc9   );
            SpiWriteLongAddressRegister(REG_AX5043_DRGAIN0  , 0xc3  );
            SpiWriteLongAddressRegister( REG_AX5043_FREQUENCYGAINC0, 0x0a);
            SpiWriteLongAddressRegister( REG_AX5043_FREQUENCYGAIND0, 0x0a);
            SpiWriteLongAddressRegister( REG_AX5043_AGCGAIN1   , 0x97   );
            SpiWriteLongAddressRegister( REG_AX5043_TIMEGAIN1   , 0xc7   );
            SpiWriteLongAddressRegister( REG_AX5043_DRGAIN1   , 0xc2   );
            SpiWriteLongAddressRegister( REG_AX5043_FREQUENCYGAINC1, 0x0a);
            SpiWriteLongAddressRegister( REG_AX5043_FREQUENCYGAIND1, 0x0a);

            SpiWriteLongAddressRegister( REG_AX5043_TIMEGAIN3   , 0xc6   );
            SpiWriteLongAddressRegister( REG_AX5043_DRGAIN3,0xc1);
            SpiWriteLongAddressRegister(REG_AX5043_FREQUENCYGAINC3, 0x0d);
            SpiWriteLongAddressRegister(REG_AX5043_FREQUENCYGAIND3, 0x0d);
            SpiWriteLongAddressRegister( REG_AX5043_FSKDEV2   , 0x00  );
            SpiWriteLongAddressRegister(REG_AX5043_FSKDEV1   , 0x01  );
            SpiWriteLongAddressRegister(REG_AX5043_FSKDEV0   , 0x43  );
            SpiWriteLongAddressRegister( REG_AX5043_MODCFGA   , 0x05  );
            SpiWriteLongAddressRegister( REG_AX5043_TXRATE2   , 0x00  );
            SpiWriteLongAddressRegister(REG_AX5043_TXRATE1   , 0x03 );
            SpiWriteLongAddressRegister( REG_AX5043_TXRATE0   , 0x06 );
            SpiWriteLongAddressRegister(REG_AX5043_BBTUNE   , 0x0f  );
            break;
        case 1://2400
            SpiWriteLongAddressRegister(REG_AX5043_IFFREQ1  , 0x01   );
            SpiWriteLongAddressRegister( REG_AX5043_IFFREQ0  , 0xF8  );
            SpiWriteLongAddressRegister( REG_AX5043_DECIMATION , 0x22 );
            SpiWriteLongAddressRegister(REG_AX5043_RXDATARATE2 , 0x00  );
            SpiWriteLongAddressRegister( REG_AX5043_RXDATARATE1 , 0x4f );
            SpiWriteLongAddressRegister( REG_AX5043_RXDATARATE0 , 0xa8 );
            SpiWriteLongAddressRegister( REG_AX5043_MAXRFOFFSET1 , 0x01);
            SpiWriteLongAddressRegister( REG_AX5043_MAXRFOFFSET0 , 0x17);
            SpiWriteLongAddressRegister(REG_AX5043_FSKDMAX1,0x01);
            SpiWriteLongAddressRegister(REG_AX5043_FSKDMAX0,0x33);
            SpiWriteLongAddressRegister(REG_AX5043_FSKDMIN1,0xFe);
            SpiWriteLongAddressRegister(REG_AX5043_FSKDMIN0,0xcd);
            SpiWriteLongAddressRegister( REG_AX5043_AGCGAIN0  , 0x96   );
            SpiWriteLongAddressRegister( REG_AX5043_AGCTARGET0 , 0x76 );
            SpiWriteLongAddressRegister( REG_AX5043_TIMEGAIN0  , 0x99 );
            SpiWriteLongAddressRegister( REG_AX5043_DRGAIN0  , 0xa3  );
            SpiWriteLongAddressRegister(REG_AX5043_FREQUENCYGAINC0, 0x09);
            SpiWriteLongAddressRegister( REG_AX5043_FREQUENCYGAIND0, 0x09);
            SpiWriteLongAddressRegister( REG_AX5043_AGCGAIN1   , 0x96   );
            SpiWriteLongAddressRegister( REG_AX5043_TIMEGAIN1   , 0x97   );
            SpiWriteLongAddressRegister( REG_AX5043_DRGAIN1   , 0xa2  );
            SpiWriteLongAddressRegister( REG_AX5043_FREQUENCYGAINC1, 0x09);
            SpiWriteLongAddressRegister( REG_AX5043_FREQUENCYGAIND1, 0x09);
            SpiWriteLongAddressRegister( REG_AX5043_TIMEGAIN3   , 0x96   );
            SpiWriteLongAddressRegister( REG_AX5043_DRGAIN3   , 0xa1  );
            SpiWriteLongAddressRegister( REG_AX5043_FREQUENCYGAINC3, 0x0d);
            SpiWriteLongAddressRegister( REG_AX5043_FREQUENCYGAIND3, 0x0d);
            SpiWriteLongAddressRegister( REG_AX5043_FSKDEV2   , 0x00  );
            SpiWriteLongAddressRegister( REG_AX5043_FSKDEV1   , 0x02  );
            SpiWriteLongAddressRegister( REG_AX5043_FSKDEV0   , 0x04 );
            SpiWriteLongAddressRegister( REG_AX5043_MODCFGA   , 0x05  );
            SpiWriteLongAddressRegister( REG_AX5043_TXRATE2   , 0x00 );
            SpiWriteLongAddressRegister( REG_AX5043_TXRATE1   , 0x06  );
            SpiWriteLongAddressRegister( REG_AX5043_TXRATE0   , 0x0d );
            SpiWriteLongAddressRegister( REG_AX5043_BBTUNE   , 0x0f  );
            break;
        case 2://4800
            SpiWriteLongAddressRegister(REG_AX5043_IFFREQ1  , 0x01 );
            SpiWriteLongAddressRegister(REG_AX5043_IFFREQ0  , 0xE4  );
            SpiWriteLongAddressRegister(REG_AX5043_DECIMATION , 0x16  );
            SpiWriteLongAddressRegister(REG_AX5043_RXDATARATE2 , 0x00 );
            SpiWriteLongAddressRegister(REG_AX5043_RXDATARATE1 , 0x3D );
            SpiWriteLongAddressRegister(REG_AX5043_RXDATARATE0 , 0x8D  );
            SpiWriteLongAddressRegister( REG_AX5043_MAXRFOFFSET1 , 0x02);
            SpiWriteLongAddressRegister( REG_AX5043_MAXRFOFFSET0 , 0x31);
            SpiWriteLongAddressRegister(REG_AX5043_FSKDMAX1,0x00);
            SpiWriteLongAddressRegister(REG_AX5043_FSKDMAX0,0xA6);
            SpiWriteLongAddressRegister(REG_AX5043_FSKDMIN1,0xFF);
            SpiWriteLongAddressRegister(REG_AX5043_FSKDMIN0,0x5A);

            SpiWriteLongAddressRegister(REG_AX5043_AGCGAIN0  , 0xC5);
            SpiWriteLongAddressRegister( REG_AX5043_AGCTARGET0 , 0x84);
            SpiWriteLongAddressRegister( REG_AX5043_TIMEGAIN0  , 0xF8);
            SpiWriteLongAddressRegister(REG_AX5043_DRGAIN0  , 0xF2);
            SpiWriteLongAddressRegister(REG_AX5043_PHASEGAIN0  , 0xC3);
            SpiWriteLongAddressRegister( REG_AX5043_FREQUENCYGAINC0, 0x09);
            SpiWriteLongAddressRegister( REG_AX5043_FREQUENCYGAIND0, 0x09);
            SpiWriteLongAddressRegister( REG_AX5043_AGCGAIN1   , 0xC5);
            SpiWriteLongAddressRegister( REG_AX5043_TIMEGAIN1   , 0xF6);
            SpiWriteLongAddressRegister( REG_AX5043_DRGAIN1   , 0xF1 );
            SpiWriteLongAddressRegister(REG_AX5043_PHASEGAIN1  , 0xc3);
            SpiWriteLongAddressRegister( REG_AX5043_FREQUENCYGAINC1, 0x09);
            SpiWriteLongAddressRegister( REG_AX5043_FREQUENCYGAIND1, 0x09);

            SpiWriteLongAddressRegister( REG_AX5043_TIMEGAIN3   , 0xF5);
            SpiWriteLongAddressRegister( REG_AX5043_DRGAIN3,0xF0);
            SpiWriteLongAddressRegister(REG_AX5043_PHASEGAIN3  , 0xC3);

            SpiWriteLongAddressRegister(REG_AX5043_FREQUENCYGAINC3, 0x0C);
            SpiWriteLongAddressRegister(REG_AX5043_FREQUENCYGAIND3, 0x0C);
            SpiWriteLongAddressRegister( REG_AX5043_FSKDEV2   , 0x00  );
            SpiWriteLongAddressRegister(REG_AX5043_FSKDEV1   , 0x04  );
            SpiWriteLongAddressRegister(REG_AX5043_FSKDEV0   , 0x08  );
            SpiWriteLongAddressRegister( REG_AX5043_MODCFGA   , 0x05  );
            SpiWriteLongAddressRegister( REG_AX5043_TXRATE2   , 0x00  );
            SpiWriteLongAddressRegister(REG_AX5043_TXRATE1   , 0x0C );
            SpiWriteLongAddressRegister( REG_AX5043_TXRATE0   , 0x19 );
            SpiWriteLongAddressRegister(REG_AX5043_BBTUNE   , 0x0F  );
            SpiWriteLongAddressRegister(REG_AX5043_RSSIREFERENCE   , 0xFA);
            break;
        case 3://9600
            SpiWriteLongAddressRegister( REG_AX5043_IFFREQ1  , 0x07   );
            SpiWriteLongAddressRegister( REG_AX5043_IFFREQ0  , 0xe0   );
            SpiWriteLongAddressRegister( REG_AX5043_DECIMATION , 0x08  );
            SpiWriteLongAddressRegister( REG_AX5043_RXDATARATE2 , 0x00  );
            SpiWriteLongAddressRegister( REG_AX5043_RXDATARATE1 , 0x54  );
            SpiWriteLongAddressRegister( REG_AX5043_RXDATARATE0 , 0xa2  );
            SpiWriteLongAddressRegister(REG_AX5043_MAXRFOFFSET1 , 0x01 );
            SpiWriteLongAddressRegister(REG_AX5043_MAXRFOFFSET0 , 0x17 );
            SpiWriteLongAddressRegister(REG_AX5043_FSKDMAX1,0x01);
            SpiWriteLongAddressRegister(REG_AX5043_FSKDMAX0,0x33);
            SpiWriteLongAddressRegister(REG_AX5043_FSKDMIN1,0xFe);
            SpiWriteLongAddressRegister(REG_AX5043_FSKDMIN0,0xcd);
            SpiWriteLongAddressRegister( REG_AX5043_AGCGAIN0  , 0x94   );
            SpiWriteLongAddressRegister( REG_AX5043_AGCTARGET0 , 0x76   );
            SpiWriteLongAddressRegister(REG_AX5043_TIMEGAIN0  , 0xa9   );
            SpiWriteLongAddressRegister( REG_AX5043_DRGAIN0  , 0xa3   );
            SpiWriteLongAddressRegister( REG_AX5043_FREQUENCYGAINC0, 0x07);
            SpiWriteLongAddressRegister( REG_AX5043_FREQUENCYGAIND0, 0x07);
            SpiWriteLongAddressRegister( REG_AX5043_AGCGAIN1   , 0x94   );
            SpiWriteLongAddressRegister( REG_AX5043_TIMEGAIN1   , 0xa7   );
            SpiWriteLongAddressRegister( REG_AX5043_DRGAIN1   , 0xa2   );
            SpiWriteLongAddressRegister( REG_AX5043_FREQUENCYGAINC1, 0x07);
            SpiWriteLongAddressRegister(REG_AX5043_FREQUENCYGAIND1, 0x07);
            SpiWriteLongAddressRegister(REG_AX5043_TIMEGAIN3   , 0xa6   );
            SpiWriteLongAddressRegister( REG_AX5043_DRGAIN3   , 0xa1   );
            SpiWriteLongAddressRegister( REG_AX5043_FREQUENCYGAINC3, 0x0b);
            SpiWriteLongAddressRegister( REG_AX5043_FREQUENCYGAIND3, 0x0b);
            SpiWriteLongAddressRegister( REG_AX5043_FSKDEV2   , 0x00  );
            SpiWriteLongAddressRegister( REG_AX5043_FSKDEV1   , 0x08  );
            SpiWriteLongAddressRegister( REG_AX5043_FSKDEV0   , 0x11  );
            SpiWriteLongAddressRegister( REG_AX5043_MODCFGA   , 0x05  );
            SpiWriteLongAddressRegister(REG_AX5043_TXRATE2   , 0x00  );
            SpiWriteLongAddressRegister( REG_AX5043_TXRATE1   , 0x18 );
            SpiWriteLongAddressRegister( REG_AX5043_TXRATE0   , 0x33 );
            SpiWriteLongAddressRegister( REG_AX5043_BBTUNE   , 0x0f  );
            break;
        case 4://19200
            SpiWriteLongAddressRegister(REG_AX5043_IFFREQ1  , 0x0b  );
            SpiWriteLongAddressRegister( REG_AX5043_IFFREQ0  , 0xd1   );
            SpiWriteLongAddressRegister( REG_AX5043_DECIMATION , 0x04 );
            SpiWriteLongAddressRegister( REG_AX5043_RXDATARATE2 , 0x00  );
            SpiWriteLongAddressRegister( REG_AX5043_RXDATARATE1 , 0x54  );
            SpiWriteLongAddressRegister( REG_AX5043_RXDATARATE0 , 0xa2  );
            SpiWriteLongAddressRegister( REG_AX5043_MAXRFOFFSET1 , 0x00 );
            SpiWriteLongAddressRegister( REG_AX5043_MAXRFOFFSET0 , 0x00 );
            SpiWriteLongAddressRegister(REG_AX5043_FSKDMAX1,0x01);
            SpiWriteLongAddressRegister(REG_AX5043_FSKDMAX0,0x33);
            SpiWriteLongAddressRegister(REG_AX5043_FSKDMIN1,0xFe);
            SpiWriteLongAddressRegister(REG_AX5043_FSKDMIN0,0xcd);
            SpiWriteLongAddressRegister( REG_AX5043_AGCGAIN0  , 0x94   );
            SpiWriteLongAddressRegister( REG_AX5043_AGCTARGET0 , 0x76  );
            SpiWriteLongAddressRegister(REG_AX5043_TIMEGAIN0  , 0xa9  );
            SpiWriteLongAddressRegister( REG_AX5043_DRGAIN0  , 0xa3    );
            SpiWriteLongAddressRegister( REG_AX5043_FREQUENCYGAINC0, 0x06 );
            SpiWriteLongAddressRegister( REG_AX5043_FREQUENCYGAIND0, 0x06 );
            SpiWriteLongAddressRegister( REG_AX5043_AGCGAIN1   , 0x94    );
            SpiWriteLongAddressRegister( REG_AX5043_TIMEGAIN1   , 0xa7    );
            SpiWriteLongAddressRegister( REG_AX5043_DRGAIN1   , 0xa2    );
            SpiWriteLongAddressRegister( REG_AX5043_FREQUENCYGAINC1, 0x06 );
            SpiWriteLongAddressRegister( REG_AX5043_FREQUENCYGAIND1, 0x06 );
            SpiWriteLongAddressRegister(REG_AX5043_TIMEGAIN3   , 0xa6   );
            SpiWriteLongAddressRegister( REG_AX5043_DRGAIN3   , 0xa1    );
            SpiWriteLongAddressRegister( REG_AX5043_FREQUENCYGAINC3, 0x0a );
            SpiWriteLongAddressRegister( REG_AX5043_FREQUENCYGAIND3, 0x0a );
            SpiWriteLongAddressRegister( REG_AX5043_FSKDEV2   , 0x00  );
            SpiWriteLongAddressRegister( REG_AX5043_FSKDEV1   , 0x10   );
            SpiWriteLongAddressRegister( REG_AX5043_FSKDEV0   , 0x22   );
            SpiWriteLongAddressRegister( REG_AX5043_MODCFGA   , 0x05   );
            SpiWriteLongAddressRegister( REG_AX5043_TXRATE2   , 0x00   );
            SpiWriteLongAddressRegister( REG_AX5043_TXRATE1   , 0x30   );
            SpiWriteLongAddressRegister( REG_AX5043_TXRATE0   , 0x65  );
            SpiWriteLongAddressRegister(REG_AX5043_BBTUNE   , 0x0f  );
            break;
        case 5://38400
            SpiWriteLongAddressRegister( REG_AX5043_IFFREQ1  , 0x13   );
            SpiWriteLongAddressRegister( REG_AX5043_IFFREQ0  , 0xb1  );
            SpiWriteLongAddressRegister( REG_AX5043_DECIMATION , 0x02  );
            SpiWriteLongAddressRegister( REG_AX5043_RXDATARATE2 , 0x00 );
            SpiWriteLongAddressRegister( REG_AX5043_RXDATARATE1 , 0x54 );
            SpiWriteLongAddressRegister(REG_AX5043_RXDATARATE0 , 0xa2 );
            SpiWriteLongAddressRegister( REG_AX5043_MAXRFOFFSET1 , 0x00);
            SpiWriteLongAddressRegister( REG_AX5043_MAXRFOFFSET0 , 0x00);
            SpiWriteLongAddressRegister(REG_AX5043_FSKDMAX1,0x00);
            SpiWriteLongAddressRegister(REG_AX5043_FSKDMAX0,0xe1);
            SpiWriteLongAddressRegister(REG_AX5043_FSKDMIN1,0xFf);
            SpiWriteLongAddressRegister(REG_AX5043_FSKDMIN0,0x1f);
            SpiWriteLongAddressRegister(REG_AX5043_AGCGAIN0  , 0x94  );
            SpiWriteLongAddressRegister( REG_AX5043_AGCTARGET0 , 0x76  );
            SpiWriteLongAddressRegister(REG_AX5043_TIMEGAIN0  , 0xa9 );
            SpiWriteLongAddressRegister( REG_AX5043_DRGAIN0  , 0xa3  );
            SpiWriteLongAddressRegister( REG_AX5043_PHASEGAIN0  , 0x83  );
            SpiWriteLongAddressRegister( REG_AX5043_FREQUENCYGAINC0, 0x05);
            SpiWriteLongAddressRegister( REG_AX5043_FREQUENCYGAIND0, 0x05);
            SpiWriteLongAddressRegister( REG_AX5043_AGCGAIN1   , 0x94 );
            SpiWriteLongAddressRegister( REG_AX5043_TIMEGAIN1   , 0xa7);
            SpiWriteLongAddressRegister( REG_AX5043_DRGAIN1   , 0xa2);
            SpiWriteLongAddressRegister( REG_AX5043_PHASEGAIN1  , 0x83  );
            SpiWriteLongAddressRegister( REG_AX5043_FREQUENCYGAINC1, 0x05);
            SpiWriteLongAddressRegister( REG_AX5043_FREQUENCYGAIND1, 0x05);
            SpiWriteLongAddressRegister( REG_AX5043_TIMEGAIN3   , 0xa6  );
            SpiWriteLongAddressRegister( REG_AX5043_DRGAIN3   , 0xa1  );
            SpiWriteLongAddressRegister( REG_AX5043_PHASEGAIN3   , 0x83   );
            SpiWriteLongAddressRegister( REG_AX5043_FREQUENCYGAINC3, 0x09);
            SpiWriteLongAddressRegister( REG_AX5043_FREQUENCYGAIND3, 0x09);
            SpiWriteLongAddressRegister(REG_AX5043_FSKDEV2   , 0x00 );
            SpiWriteLongAddressRegister( REG_AX5043_FSKDEV1   , 0x20 );
            SpiWriteLongAddressRegister( REG_AX5043_FSKDEV0   , 0x44  );
            SpiWriteLongAddressRegister( REG_AX5043_MODCFGA   , 0x05);
            SpiWriteLongAddressRegister( REG_AX5043_TXRATE2   , 0x00 );
            SpiWriteLongAddressRegister( REG_AX5043_TXRATE1   , 0x60  );
            SpiWriteLongAddressRegister(REG_AX5043_TXRATE0   , 0xcb );
            SpiWriteLongAddressRegister( REG_AX5043_BBTUNE   , 0x0d  );
            break;
        case 6://50000
            SpiWriteLongAddressRegister( REG_AX5043_IFFREQ1  , 0x0f );
            SpiWriteLongAddressRegister(REG_AX5043_IFFREQ0  , 0x82  );
            SpiWriteLongAddressRegister( REG_AX5043_DECIMATION , 0x01 );
            SpiWriteLongAddressRegister( REG_AX5043_RXDATARATE2 , 0x00 );
            SpiWriteLongAddressRegister(REG_AX5043_RXDATARATE1 , 0x82 );
            SpiWriteLongAddressRegister(REG_AX5043_RXDATARATE0 , 0x00 );
            SpiWriteLongAddressRegister( REG_AX5043_MAXRFOFFSET1 , 0x00 );
            SpiWriteLongAddressRegister(REG_AX5043_MAXRFOFFSET0 , 0x00);
            SpiWriteLongAddressRegister(REG_AX5043_FSKDMAX1,0x01);
            SpiWriteLongAddressRegister(REG_AX5043_FSKDMAX0,0x33);
            SpiWriteLongAddressRegister(REG_AX5043_FSKDMIN1,0xFe);
            SpiWriteLongAddressRegister(REG_AX5043_FSKDMIN0,0xcd);
            SpiWriteLongAddressRegister( REG_AX5043_AGCGAIN0  , 0x94  );
            SpiWriteLongAddressRegister( REG_AX5043_AGCTARGET0 , 0x76 );
            SpiWriteLongAddressRegister( REG_AX5043_TIMEGAIN0  , 0x8a );
            SpiWriteLongAddressRegister( REG_AX5043_DRGAIN0  , 0x84  );
            SpiWriteLongAddressRegister( REG_AX5043_PHASEGAIN0  , 0x43  );
            SpiWriteLongAddressRegister( REG_AX5043_FREQUENCYGAINC0, 0x05 );
            SpiWriteLongAddressRegister( REG_AX5043_FREQUENCYGAIND0, 0x05 );
            SpiWriteLongAddressRegister( REG_AX5043_AGCGAIN1   , 0x94 );
            SpiWriteLongAddressRegister( REG_AX5043_TIMEGAIN1   , 0x88 );
            SpiWriteLongAddressRegister( REG_AX5043_DRGAIN1   , 0x83);
            SpiWriteLongAddressRegister( REG_AX5043_PHASEGAIN1  , 0x43  );
            SpiWriteLongAddressRegister(REG_AX5043_FREQUENCYGAINC1, 0x05 );
            SpiWriteLongAddressRegister( REG_AX5043_FREQUENCYGAIND1, 0x05 );
            SpiWriteLongAddressRegister( REG_AX5043_TIMEGAIN3   , 0x87 );
            SpiWriteLongAddressRegister( REG_AX5043_DRGAIN3   , 0x82);
            SpiWriteLongAddressRegister( REG_AX5043_PHASEGAIN3   , 0x43 );
            SpiWriteLongAddressRegister( REG_AX5043_FREQUENCYGAINC3, 0x09 );
            SpiWriteLongAddressRegister(REG_AX5043_FREQUENCYGAIND3, 0x09 );
            SpiWriteLongAddressRegister( REG_AX5043_FSKDEV2   , 0x00 );
            SpiWriteLongAddressRegister(REG_AX5043_FSKDEV1   , 0x2a );
            SpiWriteLongAddressRegister( REG_AX5043_FSKDEV0   , 0x03);
            SpiWriteLongAddressRegister(REG_AX5043_MODCFGA   , 0x05 );
            SpiWriteLongAddressRegister( REG_AX5043_TXRATE2   , 0x00);
            SpiWriteLongAddressRegister( REG_AX5043_TXRATE1   , 0x7e);
            SpiWriteLongAddressRegister( REG_AX5043_TXRATE0   , 0x08 );
            SpiWriteLongAddressRegister(REG_AX5043_BBTUNE   , 0x0c );
            break;
        case 7://70000
            SpiWriteLongAddressRegister(REG_AX5043_IFFREQ1  , 0x12);
            SpiWriteLongAddressRegister( REG_AX5043_IFFREQ0  , 0x4f   );
            SpiWriteLongAddressRegister(REG_AX5043_DECIMATION , 0x01 );
            SpiWriteLongAddressRegister(REG_AX5043_RXDATARATE2 , 0x00 );
            SpiWriteLongAddressRegister( REG_AX5043_RXDATARATE1 , 0x5c );
            SpiWriteLongAddressRegister( REG_AX5043_RXDATARATE0 , 0xdb );
            SpiWriteLongAddressRegister( REG_AX5043_MAXRFOFFSET1 , 0x00 );
            SpiWriteLongAddressRegister( REG_AX5043_MAXRFOFFSET0 , 0x00 );
            SpiWriteLongAddressRegister(REG_AX5043_FSKDMAX1,0x01);
            SpiWriteLongAddressRegister(REG_AX5043_FSKDMAX0,0x33);
            SpiWriteLongAddressRegister(REG_AX5043_FSKDMIN1,0xFe);
            SpiWriteLongAddressRegister(REG_AX5043_FSKDMIN0,0xcd);
            SpiWriteLongAddressRegister( REG_AX5043_AGCGAIN0  , 0x84   );
            SpiWriteLongAddressRegister( REG_AX5043_AGCTARGET0 , 0x76  );
            SpiWriteLongAddressRegister( REG_AX5043_TIMEGAIN0  , 0xb9 );
            SpiWriteLongAddressRegister( REG_AX5043_DRGAIN0  , 0xb3   );
            SpiWriteLongAddressRegister( REG_AX5043_PHASEGAIN0  , 0xc3  );
            SpiWriteLongAddressRegister( REG_AX5043_FREQUENCYGAINC0, 0x05);
            SpiWriteLongAddressRegister( REG_AX5043_FREQUENCYGAIND0, 0x05);
            SpiWriteLongAddressRegister( REG_AX5043_AGCGAIN1   , 0x84 );
            SpiWriteLongAddressRegister( REG_AX5043_TIMEGAIN1   , 0xb7  );
            SpiWriteLongAddressRegister( REG_AX5043_DRGAIN1   , 0xb2  );
            SpiWriteLongAddressRegister(REG_AX5043_PHASEGAIN1  , 0xc3);
            SpiWriteLongAddressRegister( REG_AX5043_FREQUENCYGAINC1, 0x05);
            SpiWriteLongAddressRegister( REG_AX5043_FREQUENCYGAIND1, 0x05);
            SpiWriteLongAddressRegister( REG_AX5043_TIMEGAIN3   , 0xb6 );
            SpiWriteLongAddressRegister(REG_AX5043_DRGAIN3   , 0xb1);
            SpiWriteLongAddressRegister( REG_AX5043_PHASEGAIN3   , 0xc3  );
            SpiWriteLongAddressRegister(REG_AX5043_FREQUENCYGAINC3, 0x09);
            SpiWriteLongAddressRegister( REG_AX5043_FREQUENCYGAIND3, 0x09);
            SpiWriteLongAddressRegister(REG_AX5043_FSKDEV2   , 0x00);
            SpiWriteLongAddressRegister( REG_AX5043_FSKDEV1   , 0x2c );
            SpiWriteLongAddressRegister(REG_AX5043_FSKDEV0   , 0x1c );
            SpiWriteLongAddressRegister(REG_AX5043_MODCFGA   , 0x05);
            SpiWriteLongAddressRegister(REG_AX5043_TXRATE2   , 0x00);
            SpiWriteLongAddressRegister(REG_AX5043_TXRATE1   , 0xb0 );
            SpiWriteLongAddressRegister( REG_AX5043_TXRATE0   , 0x71);
            SpiWriteLongAddressRegister( REG_AX5043_BBTUNE   , 0x0b);
            break;
        case 8://100000
            SpiWriteLongAddressRegister( REG_AX5043_IFFREQ1  , 0x16);
            SpiWriteLongAddressRegister(REG_AX5043_IFFREQ0  , 0x83);
            SpiWriteLongAddressRegister(REG_AX5043_DECIMATION , 0x01 );
            SpiWriteLongAddressRegister(REG_AX5043_RXDATARATE2 , 0x00  );
            SpiWriteLongAddressRegister(REG_AX5043_RXDATARATE1 , 0x41 );
            SpiWriteLongAddressRegister(REG_AX5043_RXDATARATE0 , 0x00 );
            SpiWriteLongAddressRegister(REG_AX5043_MAXRFOFFSET1 , 0x00 );
            SpiWriteLongAddressRegister(REG_AX5043_MAXRFOFFSET0 , 0x00);
            SpiWriteLongAddressRegister(REG_AX5043_FSKDMAX1,0x01);
            SpiWriteLongAddressRegister(REG_AX5043_FSKDMAX0,0x33);
            SpiWriteLongAddressRegister(REG_AX5043_FSKDMIN1,0xFe);
            SpiWriteLongAddressRegister(REG_AX5043_FSKDMIN0,0xcd);
            SpiWriteLongAddressRegister( REG_AX5043_AGCGAIN0  , 0x84  );
            SpiWriteLongAddressRegister( REG_AX5043_AGCTARGET0 , 0x76  );
            SpiWriteLongAddressRegister( REG_AX5043_TIMEGAIN0  , 0x89   );
            SpiWriteLongAddressRegister( REG_AX5043_DRGAIN0  , 0x83   );
            SpiWriteLongAddressRegister( REG_AX5043_PHASEGAIN0  , 0xc3 );
            SpiWriteLongAddressRegister( REG_AX5043_FREQUENCYGAINC0, 0x04);
            SpiWriteLongAddressRegister( REG_AX5043_FREQUENCYGAIND0, 0x04);
            SpiWriteLongAddressRegister( REG_AX5043_AGCGAIN1   , 0x84  );
            SpiWriteLongAddressRegister(REG_AX5043_TIMEGAIN1   , 0x87   );
            SpiWriteLongAddressRegister( REG_AX5043_DRGAIN1   , 0x82   );
            SpiWriteLongAddressRegister( REG_AX5043_PHASEGAIN1  , 0xc3);
            SpiWriteLongAddressRegister( REG_AX5043_FREQUENCYGAINC1, 0x04);
            SpiWriteLongAddressRegister( REG_AX5043_FREQUENCYGAIND1, 0x04);
            SpiWriteLongAddressRegister( REG_AX5043_TIMEGAIN3   , 0x86  );
            SpiWriteLongAddressRegister( REG_AX5043_DRGAIN3   , 0x81   );
            SpiWriteLongAddressRegister( REG_AX5043_PHASEGAIN3   , 0xc3  );
            SpiWriteLongAddressRegister( REG_AX5043_FREQUENCYGAINC3, 0x08);
            SpiWriteLongAddressRegister( REG_AX5043_FREQUENCYGAIND3, 0x08);
            SpiWriteLongAddressRegister(REG_AX5043_FSKDEV2   , 0x00);
            SpiWriteLongAddressRegister( REG_AX5043_FSKDEV1   , 0x3F );
            SpiWriteLongAddressRegister( REG_AX5043_FSKDEV0   , 0x04 );
            SpiWriteLongAddressRegister( REG_AX5043_MODCFGA   , 0x05 );
            SpiWriteLongAddressRegister( REG_AX5043_TXRATE2   , 0x00 );
            SpiWriteLongAddressRegister( REG_AX5043_TXRATE1   , 0xfc );
            SpiWriteLongAddressRegister( REG_AX5043_TXRATE0   , 0x10  );
            SpiWriteLongAddressRegister( REG_AX5043_BBTUNE   , 0x04 );
            SpiWriteLongAddressRegister( REG_AX5043_RSSIREFERENCE ,0x24);
            break;
        default:
            SpiWriteLongAddressRegister( REG_AX5043_IFFREQ1  , 0x07   );
            SpiWriteLongAddressRegister( REG_AX5043_IFFREQ0  , 0xe0   );
            SpiWriteLongAddressRegister( REG_AX5043_DECIMATION , 0x08  );
            SpiWriteLongAddressRegister( REG_AX5043_RXDATARATE2 , 0x00  );
            SpiWriteLongAddressRegister( REG_AX5043_RXDATARATE1 , 0x54  );
            SpiWriteLongAddressRegister( REG_AX5043_RXDATARATE0 , 0xa2  );
            SpiWriteLongAddressRegister(REG_AX5043_MAXRFOFFSET1 , 0x01 );
            SpiWriteLongAddressRegister(REG_AX5043_MAXRFOFFSET0 , 0x17 );
            SpiWriteLongAddressRegister(REG_AX5043_FSKDMAX1,0x01);
            SpiWriteLongAddressRegister(REG_AX5043_FSKDMAX0,0x33);
            SpiWriteLongAddressRegister(REG_AX5043_FSKDMIN1,0xFe);
            SpiWriteLongAddressRegister(REG_AX5043_FSKDMIN0,0xcd);
            SpiWriteLongAddressRegister( REG_AX5043_AGCGAIN0  , 0x94   );
            SpiWriteLongAddressRegister( REG_AX5043_AGCTARGET0 , 0x76   );
            SpiWriteLongAddressRegister(REG_AX5043_TIMEGAIN0  , 0xa9   );
            SpiWriteLongAddressRegister( REG_AX5043_DRGAIN0  , 0xa3   );
            SpiWriteLongAddressRegister( REG_AX5043_FREQUENCYGAINC0, 0x07);
            SpiWriteLongAddressRegister( REG_AX5043_FREQUENCYGAIND0, 0x07);
            SpiWriteLongAddressRegister( REG_AX5043_AGCGAIN1   , 0x94   );
            SpiWriteLongAddressRegister( REG_AX5043_TIMEGAIN1   , 0xa7   );
            SpiWriteLongAddressRegister( REG_AX5043_DRGAIN1   , 0xa2   );
            SpiWriteLongAddressRegister( REG_AX5043_FREQUENCYGAINC1, 0x07);
            SpiWriteLongAddressRegister(REG_AX5043_FREQUENCYGAIND1, 0x07);
            SpiWriteLongAddressRegister(REG_AX5043_TIMEGAIN3   , 0xa6   );
            SpiWriteLongAddressRegister( REG_AX5043_DRGAIN3   , 0xa1   );
            SpiWriteLongAddressRegister( REG_AX5043_FREQUENCYGAINC3, 0x0b);
            SpiWriteLongAddressRegister( REG_AX5043_FREQUENCYGAIND3, 0x0b);
            SpiWriteLongAddressRegister( REG_AX5043_FSKDEV2   , 0x00  );
            SpiWriteLongAddressRegister( REG_AX5043_FSKDEV1   , 0x08  );
            SpiWriteLongAddressRegister( REG_AX5043_FSKDEV0   , 0x11  );
            SpiWriteLongAddressRegister( REG_AX5043_MODCFGA   , 0x05  );
            SpiWriteLongAddressRegister(REG_AX5043_TXRATE2   , 0x00  );
            SpiWriteLongAddressRegister( REG_AX5043_TXRATE1   , 0x18 );
            SpiWriteLongAddressRegister( REG_AX5043_TXRATE0   , 0x33 );
            SpiWriteLongAddressRegister( REG_AX5043_BBTUNE   , 0x0f  );
            break;
    }
}

uint32_t WirelessFreqConfigure(uint8_t Freq2, uint8_t Freq1, uint8_t Freq0, uint8_t Channel_Num)
{
    uint32_t Freq_centr = 0;
    uint32_t FreqCentr_cal = 0;
    Freq_centr = Freq2;
    Freq_centr = Freq_centr << 8;
    Freq_centr += Freq1;
    Freq_centr = Freq_centr << 8;
    Freq_centr += Freq0;

    if (Freq_centr > 910000 || Freq_centr < 300000)
    {
        Freq_centr = 433000;
    }
    //Freq_centr = Freq_centr * 1000;
    Freq_centr += CHANNEL_BW * Channel_Num;
    FreqCentr_cal = (uint32_t)((double)(Freq_centr/(double)(XTAL_FREQ/1000))*1024*1024*16);
    //FreqCentr_cal = 0x0906eeef;
    return FreqCentr_cal;
}

void WirelessTxPowerConfigure(uint8_t TxPower)
{
    switch (TxPower)
    {
        case 0:
            SpiWriteLongAddressRegister(REG_AX5043_TXPWRCOEFFB1, 0x02);
            SpiWriteLongAddressRegister(REG_AX5043_TXPWRCOEFFB0, 0x07);
            break;
        case 1:
            SpiWriteLongAddressRegister(REG_AX5043_TXPWRCOEFFB1, 0x02);
            SpiWriteLongAddressRegister(REG_AX5043_TXPWRCOEFFB0, 0x44);
            break;
        case 2:
            SpiWriteLongAddressRegister(REG_AX5043_TXPWRCOEFFB1, 0x02);
            SpiWriteLongAddressRegister(REG_AX5043_TXPWRCOEFFB0, 0x90);
            break;
        case 3:
            SpiWriteLongAddressRegister(REG_AX5043_TXPWRCOEFFB1, 0x02);
            SpiWriteLongAddressRegister(REG_AX5043_TXPWRCOEFFB0, 0xEB);
            break;
        case 4:
            SpiWriteLongAddressRegister(REG_AX5043_TXPWRCOEFFB1, 0x03);
            SpiWriteLongAddressRegister(REG_AX5043_TXPWRCOEFFB0, 0x5E);
            break;
        case 5:
            SpiWriteLongAddressRegister(REG_AX5043_TXPWRCOEFFB1, 0x03);
            SpiWriteLongAddressRegister(REG_AX5043_TXPWRCOEFFB0, 0xD6);
            break;
        case 6:
            SpiWriteLongAddressRegister(REG_AX5043_TXPWRCOEFFB1, 0x04);
            SpiWriteLongAddressRegister(REG_AX5043_TXPWRCOEFFB0, 0x06);
            break;
        case 7:
            SpiWriteLongAddressRegister(REG_AX5043_TXPWRCOEFFB1, 0x04);
            SpiWriteLongAddressRegister(REG_AX5043_TXPWRCOEFFB0, 0xA9);
            break;
        case 8:
            SpiWriteLongAddressRegister(REG_AX5043_TXPWRCOEFFB1, 0x05);
            SpiWriteLongAddressRegister(REG_AX5043_TXPWRCOEFFB0, 0x7C);
            break;
        case 9:
            SpiWriteLongAddressRegister(REG_AX5043_TXPWRCOEFFB1, 0x06);
            SpiWriteLongAddressRegister(REG_AX5043_TXPWRCOEFFB0, 0x00);
            break;
        case 10:
            SpiWriteLongAddressRegister(REG_AX5043_TXPWRCOEFFB1, 0x07);
            SpiWriteLongAddressRegister(REG_AX5043_TXPWRCOEFFB0, 0x00);
            break;
        case 11:
            SpiWriteLongAddressRegister(REG_AX5043_TXPWRCOEFFB1, 0x08);
            SpiWriteLongAddressRegister(REG_AX5043_TXPWRCOEFFB0, 0x00);
            break;
        case 12:
            SpiWriteLongAddressRegister(REG_AX5043_TXPWRCOEFFB1, 0x09);
            SpiWriteLongAddressRegister(REG_AX5043_TXPWRCOEFFB0, 0xD4);
            break;
        case 13:
            SpiWriteLongAddressRegister(REG_AX5043_TXPWRCOEFFB1, 0x0C);
            SpiWriteLongAddressRegister(REG_AX5043_TXPWRCOEFFB0, 0x00);
            break;
        case 14:
            SpiWriteLongAddressRegister(REG_AX5043_TXPWRCOEFFB1, 0x0F);
            SpiWriteLongAddressRegister(REG_AX5043_TXPWRCOEFFB0, 0x00);
        case 15:
            SpiWriteLongAddressRegister(REG_AX5043_TXPWRCOEFFB1, 0x0F);
            SpiWriteLongAddressRegister(REG_AX5043_TXPWRCOEFFB0, 0xFF);
            break;
        default:
            SpiWriteLongAddressRegister(REG_AX5043_TXPWRCOEFFB1, 0x02);
            SpiWriteLongAddressRegister(REG_AX5043_TXPWRCOEFFB0, 0x07);
            break;
    }
}
