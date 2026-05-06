
/* This file was generated automatically by Zephir do not modify it! */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <php.h>

#include "php_ext.h"
#include "i2c.h"

#include <ext/standard/info.h>

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/globals.h"
#include "kernel/main.h"
#include "kernel/fcall.h"
#include "kernel/memory.h"



zend_class_entry *i2c_i2cconfig_ce;
zend_class_entry *i2c_i2cuse_ce;

ZEND_DECLARE_MODULE_GLOBALS(i2c)

PHP_INI_BEGIN()
	
PHP_INI_END()

static PHP_MINIT_FUNCTION(i2c)
{
	REGISTER_INI_ENTRIES();
	zephir_module_init();
	ZEPHIR_INIT(I2c_I2CConfig);
	ZEPHIR_INIT(I2c_I2CUse);
	
	return SUCCESS;
}

#ifndef ZEPHIR_RELEASE
static PHP_MSHUTDOWN_FUNCTION(i2c)
{
	
	zephir_deinitialize_memory();
	UNREGISTER_INI_ENTRIES();
	return SUCCESS;
}
#endif

/**
 * Initialize globals on each request or each thread started
 */
static void php_zephir_init_globals(zend_i2c_globals *i2c_globals)
{
	i2c_globals->initialized = 0;

	/* Cache Enabled */
	i2c_globals->cache_enabled = 1;

	/* Recursive Lock */
	i2c_globals->recursive_lock = 0;

	/* Static cache */
	memset(i2c_globals->scache, '\0', sizeof(zephir_fcall_cache_entry*) * ZEPHIR_MAX_CACHE_SLOTS);

	
	
}

/**
 * Initialize globals only on each thread started
 */
static void php_zephir_init_module_globals(zend_i2c_globals *i2c_globals)
{
	
}

static PHP_RINIT_FUNCTION(i2c)
{
	zend_i2c_globals *i2c_globals_ptr;
	i2c_globals_ptr = ZEPHIR_VGLOBAL;

	php_zephir_init_globals(i2c_globals_ptr);
	zephir_initialize_memory(i2c_globals_ptr);

	
	return SUCCESS;
}

static PHP_RSHUTDOWN_FUNCTION(i2c)
{
	
	zephir_deinitialize_memory();
	return SUCCESS;
}



static PHP_MINFO_FUNCTION(i2c)
{
	php_info_print_box_start(0);
	php_printf("%s", PHP_I2C_DESCRIPTION);
	php_info_print_box_end();

	php_info_print_table_start();
	php_info_print_table_header(2, PHP_I2C_NAME, "enabled");
	php_info_print_table_row(2, "Author", PHP_I2C_AUTHOR);
	php_info_print_table_row(2, "Version", PHP_I2C_VERSION);
	php_info_print_table_row(2, "Build Date", __DATE__ " " __TIME__ );
	php_info_print_table_row(2, "Powered by Zephir", "Version " PHP_I2C_ZEPVERSION);
	php_info_print_table_end();
	
	DISPLAY_INI_ENTRIES();
}

static PHP_GINIT_FUNCTION(i2c)
{
#if defined(COMPILE_DL_I2C) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif

	php_zephir_init_globals(i2c_globals);
	php_zephir_init_module_globals(i2c_globals);
}

static PHP_GSHUTDOWN_FUNCTION(i2c)
{
	
}


zend_function_entry php_i2c_functions[] = {
	ZEND_FE_END

};

static const zend_module_dep php_i2c_deps[] = {
	
	ZEND_MOD_END
};

zend_module_entry i2c_module_entry = {
	STANDARD_MODULE_HEADER_EX,
	NULL,
	php_i2c_deps,
	PHP_I2C_EXTNAME,
	php_i2c_functions,
	PHP_MINIT(i2c),
#ifndef ZEPHIR_RELEASE
	PHP_MSHUTDOWN(i2c),
#else
	NULL,
#endif
	PHP_RINIT(i2c),
	PHP_RSHUTDOWN(i2c),
	PHP_MINFO(i2c),
	PHP_I2C_VERSION,
	ZEND_MODULE_GLOBALS(i2c),
	PHP_GINIT(i2c),
	PHP_GSHUTDOWN(i2c),
#ifdef ZEPHIR_POST_REQUEST
	PHP_PRSHUTDOWN(i2c),
#else
	NULL,
#endif
	STANDARD_MODULE_PROPERTIES_EX
};

/* implement standard "stub" routine to introduce ourselves to Zend */
#ifdef COMPILE_DL_I2C
# ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
# endif
ZEND_GET_MODULE(i2c)
#endif
