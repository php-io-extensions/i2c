namespace I2c;

class I2CUse
{
    public static function slave(int fd, int address) -> int
    {
        int results;

        let results = i2c_slave(fd, address);

        return results;
    }

    public static function read(int fd, int bytes_to_read) -> string
    {
        var result;

        let result = i2c_read(fd, bytes_to_read);

        return result;
    }

    public static function write(int fd, string data, int bytes_to_write) -> int
    {
        int results;

        let results = i2c_write(fd, data, bytes_to_write);

        return results;
    }
}
