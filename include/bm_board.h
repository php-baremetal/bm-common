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
 * Neutral read API for the board's peripheral blocks. Packages call it to learn what the board has; the SDK
 * implements it, and host tests use the stub in tools/host-ext/stubs/board.c.
 */
#pragma once
#include <stdbool.h>

/* The id of the board the firmware was built for, e.g. "waveshare-esp32-s3-touch-lcd-1.85b". */
const char *bm_board_id(void);
/* The type of a peripheral block of the board, or NULL when the board has no such block. */
const char *bm_board_type(const char *block);
/* block.key as an integer (booleans are 1 and 0); false when the block or the key is missing or not a number. */
bool bm_board_int(const char *block, const char *key, int *out);
/* block.key as a string; NULL when the block or the key is missing or not a string. */
const char *bm_board_str(const char *block, const char *key);
