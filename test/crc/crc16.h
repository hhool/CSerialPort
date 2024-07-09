/**
 * @file crc16.h
 * @author hhool (hhool@outlook.com)
 * @brief  crc16 checksum calculation function
 * @version 0.1
 * @date 2024-07-08
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef __CRC16_H__
#define __CRC16_H__

#include <stdint.h>

namespace itas109
{
/**
 * @brief crc16 checksum calculation function
 * 
 * @param data data to be calculated
 * @param length data length
 * @return uint16_t crc16 checksum
 */

uint16_t crc16(const uint8_t *data, uint32_t length);
}

#endif //__CRC16_H__

