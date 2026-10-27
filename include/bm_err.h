/*
   +----------------------------------------------------------------------+
   | php-baremetal: bm-common                                             |
   +----------------------------------------------------------------------+
   | Copyright (c) 2026 Gianfrancesco Aurecchia                           |
   +----------------------------------------------------------------------+
   | This source file is subject to the MIT license, that is bundled with |
   | this package in the file LICENSE.                                    |
   +----------------------------------------------------------------------+
   | Authors: Gianfrancesco Aurecchia <gianfri@php-baremetal.com>         |
   +----------------------------------------------------------------------+
*/

/*
 * Neutral error type of ext-i2c, ext-spi and their drivers. int-compatible with the backend's native
 * code. The generic codes match ESP-IDF's ESP_ERR_*; 0x1F00-0x1FFF are php-baremetal's own.
 */
#pragma once

typedef int bm_err_t;

#define BM_OK                 0
#define BM_ERR_NO_MEM         0x101
#define BM_ERR_INVALID_STATE  0x103
#define BM_ERR_NOT_FOUND      0x105
#define BM_ERR_ADDR_IN_USE    0x1F01   /* the I2C address is already taken by a different driver */
#define BM_ERR_CS_IN_USE      0x1F02   /* the SPI chip select is already taken by a different driver */
#define BM_ERR_BUS_PINS       0x1F03   /* the bus is already open with other pins */
