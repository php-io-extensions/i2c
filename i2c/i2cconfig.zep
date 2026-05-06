namespace I2c;

%{
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <linux/i2c-dev.h>
#include <linux/i2c.h>
#include <sys/ioctl.h>
}%
class I2CConfig
{
    /**
     * Enable/disable 10-bit addressing mode
     * @param int fd File descriptor
     * @param int enable 1 to enable, 0 to disable
     * @return int 0 on success, -1 on failure
     */
    public static function tenbit(int fd, int enable) -> int
    {
        int results;

        %{
            results = ioctl(fd, I2C_TENBIT, enable);
        }%

        return results;
    }

    /**
     * Enable/disable SMBus packet error checking
     * @param int fd File descriptor
     * @param int enable 1 to enable, 0 to disable
     * @return int 0 on success, -1 on failure
     */
    public static function pec(int fd, int enable) -> int
    {
        int results;

        %{
            results = ioctl(fd, I2C_PEC, enable);
        }%

        return results;
    }

    /**
     * Query adapter functionality
     * @param int fd File descriptor
     * @return int Functionality bitmask, -1 on failure
     */
    public static function funcs(int fd) -> int
    {
        int results;
        int funcs = 0;

        %{
            unsigned long functionality;
            results = ioctl(fd, I2C_FUNCS, &functionality);

            if (results >= 0) {
                funcs = (int)functionality;
            }
        }%

        if (results < 0) {
            return -1;
        }

        return funcs;
    }

    /**
     * Perform combined read/write transaction
     * @param int fd File descriptor
     * @param array messages Array of message arrays, each containing: addr, flags, data
     * @return int Number of messages transferred on success, -1 on failure
     */
    public static function rdwr(int fd, array messages) -> int
    {
        int results = 0;
        int nmsgs;

        let nmsgs = count(messages);

        %{
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
        }%

        return results;
    }
}