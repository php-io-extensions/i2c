#ifndef PHP_I2C_USE_API_H
#define PHP_I2C_USE_API_H

#include "php.h"

zend_long i2c_slave(zval *fd, zval *address);
void      i2c_read(zval *return_value, zval *fd, zval *bytes_to_read);
zend_long i2c_write(zval *fd, zval *data, zval *bytes_to_write);

#endif /* PHP_I2C_USE_API_H */
