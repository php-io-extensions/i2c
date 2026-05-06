
extern zend_class_entry *i2c_i2cuse_ce;

ZEPHIR_INIT_CLASS(I2c_I2CUse);

PHP_METHOD(I2c_I2CUse, slave);
PHP_METHOD(I2c_I2CUse, read);
PHP_METHOD(I2c_I2CUse, write);

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_i2c_i2cuse_slave, 0, 2, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, fd, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, address, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_i2c_i2cuse_read, 0, 2, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, fd, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, bytes_to_read, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_i2c_i2cuse_write, 0, 3, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, fd, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, data, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, bytes_to_write, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(i2c_i2cuse_method_entry) {
	PHP_ME(I2c_I2CUse, slave, arginfo_i2c_i2cuse_slave, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(I2c_I2CUse, read, arginfo_i2c_i2cuse_read, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(I2c_I2CUse, write, arginfo_i2c_i2cuse_write, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_FE_END
};
