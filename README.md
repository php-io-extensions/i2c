# I2C

[![PHP][badge-php]][php]
[![Zephir][badge-zephir]][zephir-install]
[![Platform][badge-platform]][linux]

PHP-controllable Linux I²C extension built with Zephir.

The I2C extension allows PHP to communicate with I²C devices on Linux — selecting slave addresses, performing raw reads and writes, and executing combined transactions. Useful for sensors, displays, ADCs, and other hardware connected to an I²C bus.

```shell
git clone https://github.com/DeptOfScrapyardRobotics/I2C
cd I2C
# Raspberry Pi / Debian Trixie:
bash install-debian-trixie.sh
# NVIDIA JetPack 6 (Jetson):
bash install-jetpack6.sh
```

## Requirements

- PHP 8.3+ with development headers (`php-dev` / `php-devel`)
- [Zephir][zephir-install] 0.19+
- [FD extension][fd-repo] — provides raw integer file descriptors via `Fd\FD::open()`
- Linux with I²C userspace support (`/dev/i2c-N`)
- `i2c-dev` kernel module loaded

## Installation

Install Zephir if you haven't already:

```shell
composer global require phalcon/zephir
```

Install the [FD extension][fd-repo] first — I2C requires raw integer file descriptors that PHP's stream layer cannot provide:

```shell
git clone https://github.com/DeptOfScrapyardRobotics/FD
cd FD && bash install.sh
```

Then clone and build this extension:

```shell
git clone https://github.com/DeptOfScrapyardRobotics/I2C
cd I2C
# Raspberry Pi / Debian Trixie:
bash install-debian-trixie.sh
# NVIDIA JetPack 6 (Jetson):
bash install-jetpack6.sh
```

The install script handles the full workflow: ensures `linux/i2c-dev.h` headers are present, loads the `i2c-dev` kernel module, clean → build → copy `.so` → write `30-i2c.ini` into all detected `conf.d` directories → verify `php -m` → reload php-fpm if present.

To use a specific Zephir binary:

```shell
# Raspberry Pi / Debian Trixie:
ZEPHIR_BIN=/path/to/zephir bash install-debian-trixie.sh
# NVIDIA JetPack 6 (Jetson):
ZEPHIR_BIN=/path/to/zephir bash install-jetpack6.sh
```

## API

All methods are static. File descriptors are plain integers. Use the [FD extension][fd-repo] to open and close them — PHP's stream-based `fopen` does not produce the raw integer FDs the kernel ioctls require.

```php
use Fd\FD;
use I2c\I2CUse;
use I2c\I2CConfig;

$fd = FD::open('/dev/i2c-1', 2); // O_RDWR = 2
// ... use $fd with I2CUse and I2CConfig methods ...
FD::close($fd);
```

### `I2c\I2CUse`

Basic I/O operations on an I²C bus file descriptor.

---

#### `slave(int $fd, int $address): int`

Selects the slave device to communicate with. Must be called before `read()` or `write()`. Returns `0` on success, `-1` on failure.

---

#### `read(int $fd, int $bytes_to_read): string`

Reads raw bytes from the currently selected slave. Returns the bytes as a binary string, or `""` on error.

---

#### `write(int $fd, string $data, int $bytes_to_write): int`

Writes raw bytes to the currently selected slave. Returns the number of bytes written, or `-1` on failure.

---

### `I2c\I2CConfig`

Configuration and advanced transaction operations on an I²C bus file descriptor.

---

#### `tenbit(int $fd, int $enable): int`

Enables (`1`) or disables (`0`) 10-bit slave addressing. Returns `0` on success, `-1` on failure.

---

#### `pec(int $fd, int $enable): int`

Enables (`1`) or disables (`0`) SMBus Packet Error Checking. Returns `0` on success, `-1` on failure.

---

#### `funcs(int $fd): int`

Returns the adapter's functionality bitmask, or `-1` on failure. Compare against `I2C_FUNC_*` values from [`linux/i2c.h`][i2c-h].

---

#### `rdwr(int $fd, array $messages): int`

Performs a combined read/write transaction in a single atomic ioctl. Returns the number of messages transferred on success, or `-1` on failure.

Each element of `$messages` is an associative array:

| Key | Type | Description |
|-----|------|-------------|
| `addr` | `int` | Slave address |
| `flags` | `int` | `I2C_M_*` flags — `0` = write, `0x0001` = read |
| `data` | `string` | Raw bytes; length determines bytes transferred |

---

## Usage

```php
use Fd\FD;
use I2c\I2CUse;
use I2c\I2CConfig;
```

I2C_M flag values for `rdwr`. PHP does not define these — pass the values directly or define your own constants:

| Constant | Value | Description |
|----------|-------|-------------|
| `I2C_M_WR` | `0x0000` | Write to slave |
| `I2C_M_RD` | `0x0001` | Read from slave |
| `I2C_M_TEN` | `0x0010` | Use 10-bit addressing |
| `I2C_M_NOSTART` | `0x4000` | Skip repeated START condition |

---

### Basic read/write

```php
$fd = FD::open('/dev/i2c-1', 2); // O_RDWR

I2CUse::slave($fd, 0x48);
I2CUse::write($fd, "\x00", 1);

$data = I2CUse::read($fd, 2);

FD::close($fd);
```

---

### Combined transaction (write then read, no STOP)

```php
$fd = FD::open('/dev/i2c-1', 2);

$messages = [
    ['addr' => 0x48, 'flags' => 0x0000, 'data' => "\x00"],
    ['addr' => 0x48, 'flags' => 0x0001, 'data' => "\x00\x00"],
];

I2CConfig::rdwr($fd, $messages);

FD::close($fd);
```

---

### Query adapter capabilities

```php
$fd = FD::open('/dev/i2c-1', 2);

$funcs = I2CConfig::funcs($fd);
echo "Adapter funcs bitmask: {$funcs}\n";

FD::close($fd);
```

---

### 10-bit addressing

```php
$fd = FD::open('/dev/i2c-1', 2);

I2CConfig::tenbit($fd, 1);
I2CUse::slave($fd, 0x1A2);
I2CUse::write($fd, "\x00", 1);
$data = I2CUse::read($fd, 4);

FD::close($fd);
```

## License

Copyright © Project Saturn Studios, LLC. All rights reserved.

[badge-php]: https://img.shields.io/badge/php-%3E%3D8.3-blue
[badge-zephir]: https://img.shields.io/badge/zephir-0.19%2B-orange
[badge-platform]: https://img.shields.io/badge/platform-linux-lightgrey
[php]: https://www.php.net
[zephir-install]: https://docs.zephir-lang.com/latest/en/installation
[linux]: https://www.kernel.org
[i2c-h]: https://elixir.bootlin.com/linux/latest/source/include/uapi/linux/i2c.h
[fd-repo]: https://github.com/DeptOfScrapyardRobotics/FD
