
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
#include "kernel/operators.h"
#include "kernel/memory.h"
#include "kernel/object.h"

#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <linux/i2c-dev.h>
#include <linux/i2c.h>
#include <sys/ioctl.h>



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
	zval *fd_param = NULL, *enable_param = NULL;
	zend_long fd, enable, results = 0;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(fd)
		Z_PARAM_LONG(enable)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &fd_param, &enable_param);
	
            results = ioctl(fd, I2C_TENBIT, enable);
        
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
	zval *fd_param = NULL, *enable_param = NULL;
	zend_long fd, enable, results = 0;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(fd)
		Z_PARAM_LONG(enable)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &fd_param, &enable_param);
	
            results = ioctl(fd, I2C_PEC, enable);
        
	RETURN_LONG(results);
}

/**
 * Query adapter functionality
 * @param int fd File descriptor
 * @return int Functionality bitmask, -1 on failure
 */
PHP_METHOD(I2c_I2CConfig, funcs)
{
	zval *fd_param = NULL;
	zend_long fd, results = 0, funcs;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(fd)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &fd_param);
	funcs = 0;
	
            unsigned long functionality;
            results = ioctl(fd, I2C_FUNCS, &functionality);

            if (results >= 0) {
                funcs = (int)functionality;
            }
        
	if (results < 0) {
		RETURN_LONG(-1);
	}
	RETURN_LONG(funcs);
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
	zval *fd_param = NULL, *messages_param = NULL;
	zend_long fd, results, nmsgs = 0;

	ZVAL_UNDEF(&messages);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(fd)
		Z_PARAM_ARRAY(messages)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 2, 0, &fd_param, &messages_param);
	zephir_get_arrval(&messages, messages_param);
	results = 0;
	nmsgs = zephir_fast_count_int(&messages);
	
            struct i2c_msg msgs[nmsgs];
            struct i2c_rdwr_ioctl_data msgset;
            int i;
            int _results = 0;

            memset(msgs, 0, sizeof(msgs));

            // Build message array
            for (i = 0; i < nmsgs; i++) {
                zval *message = zend_hash_index_find(Z_ARRVAL_P(&messages), i);
                if (message == NULL) {
                    _results = -1;
                    break;
                }

                // Get address
                zval *addr_val = zend_hash_str_find(Z_ARRVAL_P(message), "addr", sizeof("addr")-1);
                if (addr_val == NULL) {
                    _results = -1;
                    break;
                }
                msgs[i].addr = (__u16)zval_get_long(addr_val);

                // Get flags
                zval *flags_val = zend_hash_str_find(Z_ARRVAL_P(message), "flags", sizeof("flags")-1);
                if (flags_val == NULL) {
                    _results = -1;
                    break;
                }
                msgs[i].flags = (__u16)zval_get_long(flags_val);

                // Get data
                zval *data_val = zend_hash_str_find(Z_ARRVAL_P(message), "data", sizeof("data")-1);
                if (data_val == NULL) {
                    _results = -1;
                    break;
                }
                msgs[i].len = (__u16)Z_STRLEN_P(data_val);
                msgs[i].buf = (__u8 *)Z_STRVAL_P(data_val);
            }

            if (_results != -1) {
                msgset.msgs = msgs;
                msgset.nmsgs = nmsgs;

                _results = ioctl(fd, I2C_RDWR, &msgset);
            }

            results = (zend_long) _results;
        
	RETURN_MM_LONG(results);
}

