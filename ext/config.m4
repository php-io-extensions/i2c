PHP_ARG_ENABLE(i2c, whether to enable i2c, [ --enable-i2c   Enable I2c])

if test "$PHP_I2C" = "yes"; then

	dnl GCC 14 promoted several long-standing warnings to hard errors by default.
	dnl Zephir-generated C code trips these in dead-code paths that are
	dnl runtime-safe and have built cleanly on gcc <= 13 and clang for years.
	dnl Each flag is silently ignored by compilers that don't know it.
	CFLAGS="$CFLAGS -Wno-error=incompatible-pointer-types -Wno-error=int-conversion -Wno-error=implicit-function-declaration -Wno-error=implicit-int"

	if ! test "x" = "x"; then
		PHP_EVAL_LIBLINE(, I2C_SHARED_LIBADD)
	fi

	AC_DEFINE(HAVE_I2C, 1, [Whether you have I2c])
	i2c_sources="i2c.c kernel/main.c kernel/memory.c kernel/exception.c kernel/debug.c kernel/backtrace.c kernel/object.c kernel/array.c kernel/string.c kernel/fcall.c kernel/require.c kernel/file.c kernel/operators.c kernel/math.c kernel/concat.c kernel/variables.c kernel/filter.c kernel/iterator.c kernel/time.c kernel/exit.c i2c/i2cconfig.zep.c
	i2c/i2cuse.zep.c "
	PHP_NEW_EXTENSION(i2c, $i2c_sources, $ext_shared,, )
	PHP_ADD_BUILD_DIR([$ext_builddir/kernel/])
	for dir in "i2c"; do
		PHP_ADD_BUILD_DIR([$ext_builddir/$dir])
	done
	PHP_SUBST(I2C_SHARED_LIBADD)

	old_CPPFLAGS=$CPPFLAGS
	CPPFLAGS="$CPPFLAGS $INCLUDES"

	AC_CHECK_DECL(
		[HAVE_BUNDLED_PCRE],
		[
			AC_CHECK_HEADERS(
				[ext/pcre/php_pcre.h],
				[
					PHP_ADD_EXTENSION_DEP([i2c], [pcre])
					AC_DEFINE([ZEPHIR_USE_PHP_PCRE], [1], [Whether PHP pcre extension is present at compile time])
				],
				,
				[[#include "main/php.h"]]
			)
		],
		,
		[[#include "php_config.h"]]
	)

	AC_CHECK_DECL(
		[HAVE_JSON],
		[
			AC_CHECK_HEADERS(
				[ext/json/php_json.h],
				[
					PHP_ADD_EXTENSION_DEP([i2c], [json])
					AC_DEFINE([ZEPHIR_USE_PHP_JSON], [1], [Whether PHP json extension is present at compile time])
				],
				,
				[[#include "main/php.h"]]
			)
		],
		,
		[[#include "php_config.h"]]
	)

	CPPFLAGS=$old_CPPFLAGS

	PHP_INSTALL_HEADERS([ext/i2c], [php_i2c.h])

fi
