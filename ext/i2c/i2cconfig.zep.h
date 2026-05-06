
extern zend_class_entry *i2c_i2cconfig_ce;

ZEPHIR_INIT_CLASS(I2c_I2CConfig);

PHP_METHOD(I2c_I2CConfig, tenbit);
PHP_METHOD(I2c_I2CConfig, pec);
PHP_METHOD(I2c_I2CConfig, funcs);
PHP_METHOD(I2c_I2CConfig, rdwr);

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_i2c_i2cconfig_tenbit, 0, 2, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, fd, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, enable, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_i2c_i2cconfig_pec, 0, 2, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, fd, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, enable, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_i2c_i2cconfig_funcs, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, fd, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_i2c_i2cconfig_rdwr, 0, 2, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, fd, IS_LONG, 0)
	ZEND_ARG_ARRAY_INFO(0, messages, 0)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(i2c_i2cconfig_method_entry) {
	PHP_ME(I2c_I2CConfig, tenbit, arginfo_i2c_i2cconfig_tenbit, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(I2c_I2CConfig, pec, arginfo_i2c_i2cconfig_pec, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(I2c_I2CConfig, funcs, arginfo_i2c_i2cconfig_funcs, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(I2c_I2CConfig, rdwr, arginfo_i2c_i2cconfig_rdwr, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_FE_END
};
