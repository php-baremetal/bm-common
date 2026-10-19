# bm-common

Headers shared by php-baremetal packages. Today it holds one: `bm_err.h`, the neutral error type of the bus
extensions ([ext-i2c](package:php-baremetal/ext-i2c), [ext-spi](package:php-baremetal/ext-spi)), their HALs and
their device drivers. It is a `bm-lib` with no sources and no PHP API; you meet it only when you write one of
those packages.

## Who uses it

| Package | Uses |
| --- | --- |
| ext-i2c, ext-spi | Return codes of the transport functions drivers call (`i2c_dev_read_reg()`, `spi_dev_transfer()`), and the errors of their device tables. Both require bm-common. |
| esp32-i2c-hal, esp32-spi-hal | Return ESP-IDF `esp_err_t` values unchanged as `bm_err_t`, and name the php-baremetal codes in their error-name function. |
| Device drivers | The return type of a driver's `init` and sampler callbacks. They get the header through the extension's `bm_i2c_driver.h` or `bm_spi_driver.h`. |

A project never requires bm-common: the extensions bring it.

## The header

`include/bm_err.h`:

| Name | Value | Meaning |
| --- | --- | --- |
| `bm_err_t` | `int` | The error type. Compatible with `esp_err_t`, so an ESP32 HAL returns its own codes unchanged. |
| `BM_OK` | `0` | Success. |
| `BM_ERR_NO_MEM` | `0x101` | Out of memory, or a fixed table is full. Same value as `ESP_ERR_NO_MEM`. |
| `BM_ERR_INVALID_STATE` | `0x103` | The object is not in a state that allows the call. Same value as `ESP_ERR_INVALID_STATE`. |
| `BM_ERR_NOT_FOUND` | `0x105` | The chip did not answer, or answered with the wrong identity. Same value as `ESP_ERR_NOT_FOUND`. |
| `BM_ERR_ADDR_IN_USE` | `0x1F01` | The I2C address is already taken by a different driver. |
| `BM_ERR_CS_IN_USE` | `0x1F02` | The SPI chip select is already taken by a different driver. |
| `BM_ERR_BUS_PINS` | `0x1F03` | The bus is already open with other pins. |

The generic codes share ESP-IDF's values, so on ESP32 `esp_err_to_name()` prints them as `ESP_ERR_...`. A HAL
for another platform maps them in its own error-name function. Codes `0x1F00` to `0x1FFF` are reserved for
php-baremetal's own errors; each HAL gives them a readable name (for example
`chip select already used by another driver on this bus`).

## Using it in a package

Require it and include the header; the default include directory (`include/`) is exported to every package in
the build:

```json
{
  "type": "bm-lib",
  "require": { "php-baremetal/bm-common": "^1.0" }
}
```

```c
#include "bm_err.h"

bm_err_t my_probe(void)
{
    return BM_ERR_NOT_FOUND;
}
```

A device driver does not need to require it: it requires the bus extension, which requires bm-common, and the
driver header includes `bm_err.h`.

## License

MIT.
