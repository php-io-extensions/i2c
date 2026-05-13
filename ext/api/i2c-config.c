#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ext.h"
#include "i2c-config.h"
#include <string.h>
#include <unistd.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>

zend_long i2c_tenbit(zval *fd, zval *enable)
{
    return (zend_long) ioctl((int) Z_LVAL_P(fd), I2C_TENBIT, (int) Z_LVAL_P(enable));
}

zend_long i2c_pec(zval *fd, zval *enable)
{
    return (zend_long) ioctl((int) Z_LVAL_P(fd), I2C_PEC, (int) Z_LVAL_P(enable));
}

zend_long i2c_funcs(zval *fd)
{
    unsigned long functionality;
    int result = ioctl((int) Z_LVAL_P(fd), I2C_FUNCS, &functionality);

    if (result < 0) {
        return -1;
    }

    return (zend_long) functionality;
}

zend_long i2c_rdwr(zval *fd, zval *messages)
{
    zend_long nmsgs = (zend_long) zend_array_count(Z_ARRVAL_P(messages));
    struct i2c_msg *msgs = ecalloc(nmsgs, sizeof(struct i2c_msg));
    struct i2c_rdwr_ioctl_data msgset;
    zend_long _results = 0;

    for (zend_long i = 0; i < nmsgs; i++) {
        zval *message = zend_hash_index_find(Z_ARRVAL_P(messages), i);
        if (message == NULL) { _results = -1; break; }

        zval *addr_val = zend_hash_str_find(Z_ARRVAL_P(message), "addr", sizeof("addr") - 1);
        if (addr_val == NULL) { _results = -1; break; }
        msgs[i].addr = (__u16) zval_get_long(addr_val);

        zval *flags_val = zend_hash_str_find(Z_ARRVAL_P(message), "flags", sizeof("flags") - 1);
        if (flags_val == NULL) { _results = -1; break; }
        msgs[i].flags = (__u16) zval_get_long(flags_val);

        zval *data_val = zend_hash_str_find(Z_ARRVAL_P(message), "data", sizeof("data") - 1);
        if (data_val == NULL) { _results = -1; break; }
        msgs[i].len = (__u16) Z_STRLEN_P(data_val);
        msgs[i].buf = (__u8 *) Z_STRVAL_P(data_val);
    }

    if (_results != -1) {
        msgset.msgs  = msgs;
        msgset.nmsgs = (int) nmsgs;
        _results = (zend_long) ioctl((int) Z_LVAL_P(fd), I2C_RDWR, &msgset);
    }

    efree(msgs);
    return _results;
}
