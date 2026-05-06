namespace I2c;

%{
#include <fcntl.h>
#include <unistd.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
}%
class I2CUse
{
    public static function slave(int fd, int address) -> int
    {
        int results;

        %{
            results = ioctl(fd, I2C_SLAVE, address);
        }%

        return results;
    }

    public static function read(int fd, int bytes_to_read) -> string
    {
        var result;

        %{
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
        }%

        return result;
    }

    public static function write(int fd, string data, int bytes_to_write) -> int
    {
        int results;

        %{
            results = write(fd, (uint8_t*)Z_STRVAL(data), bytes_to_write);
        }%

        return results;
    }
}