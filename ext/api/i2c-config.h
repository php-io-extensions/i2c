#ifndef PHP_I2C_CONFIG_API_H
#define PHP_I2C_CONFIG_API_H

#include "php.h"

zend_long i2c_tenbit(zval *fd, zval *enable);
zend_long i2c_pec(zval *fd, zval *enable);
zend_long i2c_funcs(zval *fd);
zend_long i2c_rdwr(zval *fd, zval *messages);

#endif /* PHP_I2C_CONFIG_API_H */
