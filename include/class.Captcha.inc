<?php


class Captcha
{
    public static function generateCode () {
        $rand = mt_rand(1000000, 9999999);
        $rand = base64_encode($rand);
        $rand = substr($rand, -7);
        $rand = str_replace([ 'J', 'I', 'j', 'i', '0', 'O' ], [ 'Z', 'Y', 'z', 'y', 'B', 'C' ], $rand);

        $_SESSION[self::getSessKey()] = $rand;
    }

    public static function isValid (string $code): bool {
        return $code && $code == self::getSessionCode();
    }

    private static function getSessionCode (): string {
        $out = $_SESSION[self::getSessKey()] ?? '';
        unset($_SESSION[self::getSessKey()]);
        return $out;
    }

    /**
     * @return string
     */
    private static function getSessKey (): string {
        $config = Site::$instance->config;
        return ($config->cookie ? $config->cookie . '_' : '') . 'captcha_value';
    }
}