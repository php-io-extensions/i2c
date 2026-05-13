<?php

namespace I2c;

class I2CUse
{


    /**
     * @param int $fd
     * @param int $address
     * @return int
     */
    public static function slave(int $fd, int $address): int
    {
    }

    /**
     * @param int $fd
     * @param int $bytes_to_read
     * @return string
     */
    public static function read(int $fd, int $bytes_to_read): string
    {
    }

    /**
     * @param int $fd
     * @param string $data
     * @param int $bytes_to_write
     * @return int
     */
    public static function write(int $fd, string $data, int $bytes_to_write): int
    {
    }
}
