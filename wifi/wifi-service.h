/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-12-30     Rick       the first version
 */
void wifi_service_init(void);
void WariningUpload(uint32_t device_id,uint8_t state,uint8_t value);
void MotoUpload(uint8_t state);
void Show_WiFi(void);
void Exit_WiFi(void);
void Reset_WiFi(void);
void RemoteOpenUpload(uint32_t device_id,uint8_t state);
void KidLockUp(uint8_t state);
void RemoteOpenUpload(uint32_t device_id,uint8_t state);
void Slave_Heart(uint32_t device_id,uint8_t rssi,uint8_t bat);
void Device_Add_WiFi(uint32_t device_id);
void Device_Delete_WiFi(uint32_t device_id);
