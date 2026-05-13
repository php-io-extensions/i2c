#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ext.h"
#include "i2c-use.h"
#include <unistd.h>
#include <stdint.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>

zend_long i2c_slave(zval *fd, zval *address)
{
    return (zend_long) ioctl((int) Z_LVAL_P(fd), I2C_SLAVE, (int) Z_LVAL_P(address));
}

void i2c_read(zval *return_value, zval *fd, zval *bytes_to_read)
{
    size_t n = (size_t) Z_LVAL_P(bytes_to_read);
    char *buf = emalloc(n + 1);
    ssize_t read_n = read((int) Z_LVAL_P(fd), buf, n);

    if (read_n < 0) {
        efree(buf);
        ZVAL_EMPTY_STRING(return_value);
    } else {
        buf[read_n] = '\0';
        ZVAL_STRINGL(return_value, buf, (size_t) read_n);
        efree(buf);
    }
}

zend_long i2c_write(zval *fd, zval *data, zval *bytes_to_write)
{
    return (zend_long) write(
        (int)      Z_LVAL_P(fd),
        (uint8_t*) Z_STRVAL_P(data),
        (size_t)   Z_LVAL_P(bytes_to_write)
    );
}
