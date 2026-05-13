
/* This file was generated automatically by Zephir do not modify it! */

#ifndef PHP_I2C_H
#define PHP_I2C_H 1

#ifdef PHP_WIN32
#define ZEPHIR_RELEASE 1
#endif

#include "kernel/globals.h"

#define PHP_I2C_NAME        "i2c"
#define PHP_I2C_VERSION     "0.1.4"
#define PHP_I2C_EXTNAME     "i2c"
#define PHP_I2C_AUTHOR      "Project Saturn Studios, LLC"
#define PHP_I2C_ZEPVERSION  "0.19.0-$Id$"
#define PHP_I2C_DESCRIPTION "PHP-Controllable I2C Extension"



ZEND_BEGIN_MODULE_GLOBALS(i2c)

	int initialized;

	/** Function cache */
	HashTable *fcache;

	zephir_fcall_cache_entry *scache[ZEPHIR_MAX_CACHE_SLOTS];

	/* Cache enabled */
	unsigned int cache_enabled;

	/* Max recursion control */
	unsigned int recursive_lock;

	
ZEND_END_MODULE_GLOBALS(i2c)

#ifdef ZTS
#include "TSRM.h"
#endif

ZEND_EXTERN_MODULE_GLOBALS(i2c)

#ifdef ZTS
	#define ZEPHIR_GLOBAL(v) ZEND_MODULE_GLOBALS_ACCESSOR(i2c, v)
#else
	#define ZEPHIR_GLOBAL(v) (i2c_globals.v)
#endif

#ifdef ZTS
	ZEND_TSRMLS_CACHE_EXTERN()
	#define ZEPHIR_VGLOBAL ((zend_i2c_globals *) (*((void ***) tsrm_get_ls_cache()))[TSRM_UNSHUFFLE_RSRC_ID(i2c_globals_id)])
#else
	#define ZEPHIR_VGLOBAL &(i2c_globals)
#endif

#define ZEPHIR_API ZEND_API

#define zephir_globals_def i2c_globals
#define zend_zephir_globals_def zend_i2c_globals

extern zend_module_entry i2c_module_entry;
#define phpext_i2c_ptr &i2c_module_entry

#endif
