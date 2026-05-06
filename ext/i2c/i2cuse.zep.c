
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
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>



ZEPHIR_INIT_CLASS(I2c_I2CUse)
{
	ZEPHIR_REGISTER_CLASS(I2c, I2CUse, i2c, i2cuse, i2c_i2cuse_method_entry, 0);

	return SUCCESS;
}

PHP_METHOD(I2c_I2CUse, slave)
{
	zval *fd_param = NULL, *address_param = NULL;
	zend_long fd, address, results = 0;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(fd)
		Z_PARAM_LONG(address)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &fd_param, &address_param);
	
            results = ioctl(fd, I2C_SLAVE, address);
        
	RETURN_LONG(results);
}

PHP_METHOD(I2c_I2CUse, read)
{
	zval *fd_param = NULL, *bytes_to_read_param = NULL, result;
	zend_long fd, bytes_to_read;

	ZVAL_UNDEF(&result);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(fd)
		Z_PARAM_LONG(bytes_to_read)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &fd_param, &bytes_to_read_param);
	
            char *_buf = emalloc((size_t) bytes_to_read + 1);
            ssize_t _n = read((int) fd, _buf, (size_t) bytes_to_read);

            if (_n < 0) {
                efree(_buf);
                ZVAL_EMPTY_STRING(&result);
            } else {
                _buf[_n] = '\0';
                ZVAL_STRINGL(&result, _buf, (size_t) _n);
                efree(_buf);
            }
        
	RETURN_CCTORW(&result);
}

PHP_METHOD(I2c_I2CUse, write)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval data;
	zval *fd_param = NULL, *data_param = NULL, *bytes_to_write_param = NULL;
	zend_long fd, bytes_to_write, results = 0;

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
	
            results = write(fd, (uint8_t*)Z_STRVAL(data), bytes_to_write);
        
	RETURN_MM_LONG(results);
}

