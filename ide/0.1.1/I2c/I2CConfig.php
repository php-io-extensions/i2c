<?php

namespace I2c;

class I2CConfig
{


    /**
     * Enable/disable 10-bit addressing mode
     *
     * @param int $fd File descriptor
     * @param int $enable 1 to enable, 0 to disable
     * @return int 0 on success, -1 on failure
     */
    public static function tenbit(int $fd, int $enable): int
    {
    }

    /**
     * Enable/disable SMBus packet error checking
     *
     * @param int $fd File descriptor
     * @param int $enable 1 to enable, 0 to disable
     * @return int 0 on success, -1 on failure
     */
    public static function pec(int $fd, int $enable): int
    {
    }

    /**
     * Query adapter functionality
     *
     * @param int $fd File descriptor
     * @return int Functionality bitmask, -1 on failure
     */
    public static function funcs(int $fd): int
    {
    }

    /**
     * Perform combined read/write transaction
     *
     * @param int $fd File descriptor
     * @param array $messages Array of message arrays, each containing: addr, flags, data
     * @return int Number of messages transferred on success, -1 on failure
     */
    public static function rdwr(int $fd, array $messages): int
    {
    }
}
