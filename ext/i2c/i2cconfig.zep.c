
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
#include "api/i2c-config.h"
#include "kernel/operators.h"
#include "kernel/memory.h"
#include "kernel/object.h"


ZEPHIR_INIT_CLASS(I2c_I2CConfig)
{
	ZEPHIR_REGISTER_CLASS(I2c, I2CConfig, i2c, i2cconfig, i2c_i2cconfig_method_entry, 0);

	return SUCCESS;
}

/**
 * Enable/disable 10-bit addressing mode
 * @param int fd File descriptor
 * @param int enable 1 to enable, 0 to disable
 * @return int 0 on success, -1 on failure
 */
PHP_METHOD(I2c_I2CConfig, tenbit)
{
	zval *fd_param = NULL, *enable_param = NULL, _0, _1;
	zend_long fd, enable, results = 0;

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(fd)
		Z_PARAM_LONG(enable)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &fd_param, &enable_param);
	ZVAL_LONG(&_0, fd);
	ZVAL_LONG(&_1, enable);
	results = i2c_tenbit(&_0, &_1);
	RETURN_LONG(results);
}

/**
 * Enable/disable SMBus packet error checking
 * @param int fd File descriptor
 * @param int enable 1 to enable, 0 to disable
 * @return int 0 on success, -1 on failure
 */
PHP_METHOD(I2c_I2CConfig, pec)
{
	zval *fd_param = NULL, *enable_param = NULL, _0, _1;
	zend_long fd, enable, results = 0;

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(fd)
		Z_PARAM_LONG(enable)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &fd_param, &enable_param);
	ZVAL_LONG(&_0, fd);
	ZVAL_LONG(&_1, enable);
	results = i2c_pec(&_0, &_1);
	RETURN_LONG(results);
}

/**
 * Query adapter functionality
 * @param int fd File descriptor
 * @return int Functionality bitmask, -1 on failure
 */
PHP_METHOD(I2c_I2CConfig, funcs)
{
	zval *fd_param = NULL, _0;
	zend_long fd, results = 0;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(fd)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &fd_param);
	ZVAL_LONG(&_0, fd);
	results = i2c_funcs(&_0);
	RETURN_LONG(results);
}

/**
 * Perform combined read/write transaction
 * @param int fd File descriptor
 * @param array messages Array of message arrays, each containing: addr, flags, data
 * @return int Number of messages transferred on success, -1 on failure
 */
PHP_METHOD(I2c_I2CConfig, rdwr)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval messages;
	zval *fd_param = NULL, *messages_param = NULL, _0;
	zend_long fd, results = 0;

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&messages);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(fd)
		Z_PARAM_ARRAY(messages)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 2, 0, &fd_param, &messages_param);
	zephir_get_arrval(&messages, messages_param);
	ZVAL_LONG(&_0, fd);
	results = i2c_rdwr(&_0, &messages);
	RETURN_MM_LONG(results);
}

