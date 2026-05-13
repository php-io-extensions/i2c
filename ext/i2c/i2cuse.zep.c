
#ifdef HAVE_CONFIG_H
#include "../ext_config.h"
#endif

#include <php.h>
#include "../php_ext.h"
#include "../ext.h"

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/main.h"
#include "api/i2c-use.h"
#include "kernel/operators.h"
#include "kernel/memory.h"
#include "kernel/object.h"
#include "kernel/string.h"


ZEPHIR_INIT_CLASS(I2c_I2CUse)
{
	ZEPHIR_REGISTER_CLASS(I2c, I2CUse, i2c, i2cuse, i2c_i2cuse_method_entry, 0);

	return SUCCESS;
}

PHP_METHOD(I2c_I2CUse, slave)
{
	zval *fd_param = NULL, *address_param = NULL, _0, _1;
	zend_long fd, address, results = 0;

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(fd)
		Z_PARAM_LONG(address)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &fd_param, &address_param);
	ZVAL_LONG(&_0, fd);
	ZVAL_LONG(&_1, address);
	results = i2c_slave(&_0, &_1);
	RETURN_LONG(results);
}

PHP_METHOD(I2c_I2CUse, read)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *fd_param = NULL, *bytes_to_read_param = NULL, result, _0, _1;
	zend_long fd, bytes_to_read;

	ZVAL_UNDEF(&result);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(fd)
		Z_PARAM_LONG(bytes_to_read)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 2, 0, &fd_param, &bytes_to_read_param);
	ZVAL_LONG(&_0, fd);
	ZVAL_LONG(&_1, bytes_to_read);
	ZEPHIR_INIT_VAR(&result);
	i2c_read(&result, &_0, &_1);
	RETURN_CCTOR(&result);
}

PHP_METHOD(I2c_I2CUse, write)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval data;
	zval *fd_param = NULL, *data_param = NULL, *bytes_to_write_param = NULL, _0, _1;
	zend_long fd, bytes_to_write, results = 0;

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&data);
	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_LONG(fd)
		Z_PARAM_STR(data)
		Z_PARAM_LONG(bytes_to_write)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 3, 0, &fd_param, &data_param, &bytes_to_write_param);
	zephir_get_strval(&data, data_param);
	ZVAL_LONG(&_0, fd);
	ZVAL_LONG(&_1, bytes_to_write);
	results = i2c_write(&_0, &data, &_1);
	RETURN_MM_LONG(results);
}

