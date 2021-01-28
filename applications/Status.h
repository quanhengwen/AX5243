/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-11-27     Rick       the first version
 */
#ifndef APPLICATIONS_STATUS_H_
#define APPLICATIONS_STATUS_H_
void WarningInit(void);
void BackToNormal(void);
void Warning_Disable(void);
void Warning_Enable_Num(uint8_t id);
void MasterAlarmWaterDisable(void);
void MasterStatusChangeToDeAvtive(void);
void OfflineDisableWarning(void);
void RadioInitFail(void);
uint8_t Detect_Learn(void);

typedef struct
{
    uint8_t warning_id;
    uint8_t last_id;
    uint8_t priority;
    void (*callback)(void*);
}WariningEvent;

#endif /* APPLICATIONS_STATUS_H_ */
