/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-11-27     Rick       the first version
 */
#ifndef APPLICATIONS_MOTO_H_
#define APPLICATIONS_MOTO_H_

void Moto_Open(uint8_t ActFlag);
void Moto_Close(uint8_t ActFlag);
void Moto_Init(void);
void Moto_Detect(void);
void Moto_OpenByWifi(void);
void Moto_CloseByWifi(void);


#endif /* APPLICATIONS_MOTO_H_ */
