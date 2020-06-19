<?php
/**
 *    AMXBans v7
 * Copyright 2019 by indianiso1
 * This file is part of AMXBans.
 *
 * AMXBans is free software, but it's licensed under the Creative Commons - Attribution-NonCommercial-ShareAlike 2.0
 * AMXBans is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * You should have received a copy of the cc-nC-SA along with AMXBans.
 * If not, see http://creativecommons.org/licenses/by-nc-sa/2.0/
 */

class Captcha
{
    public static function generateCode()
    {
        $rand = mt_rand(1000000, 9999999);
        $rand = base64_encode($rand);
        $rand = substr($rand, 3, 7);
        $rand = str_replace(['J', 'I', 'j', 'i', '0', 'O'], ['Z', 'Y', 'z', 'y', 'B', 'C'], $rand);

        $_SESSION[self::getSessKey()] = $rand;
    }

    public static function isValid(string $code): bool
    {
        return $code && $code == self::getSessionCode();
    }

    private static function getSessionCode(): string
    {
        $out = $_SESSION[self::getSessKey()] ?? '';
        unset($_SESSION[self::getSessKey()]);
        return $out;
    }

    /**
     * @return string
     */
    private static function getSessKey(): string
    {
        $config = Site::$instance->config;
        return ($config->cookie ? $config->cookie . '_' : '') . 'captcha_value';
    }

    public static function makeImage()
    {
        $img_size = [160, 38];
        $img_text = $_SESSION[self::getSessKey()];

        $img = imagecreate(...$img_size);        // Make an image
        imagecolorallocate($img, 255, 255, 255); // Fill it with white color
        $col_txt = imageColorAllocate($img, mt_rand(0, 200), mt_rand(0, 200),
            mt_rand(0, 200)); // Choose random color for texts

        $img_challenge = ($img_size[0] * $img_size[1]) / 15;
        for ($i = 0; $i < $img_challenge; $i++) { // Draw challenge
            imagesetpixel($img, mt_rand(0, $img_size[0]), mt_rand(0, $img_size[1]), $col_txt);
        }

        $col_border = imageColorAllocate($img, 206, 212, 218);
        imagerectangle($img, 0, 0, $img_size[0]-1, $img_size[1]-1, $col_border);

        imagestring($img, 5, 50, 10, $img_text, $col_txt);

        $img_location = "/webSources/uploads/tmp/" . session_id() . '.png';
        imagepng($img, \Support\Path::getRootPath() . $img_location, 5);
        imagedestroy($img);
        return $img_location;
    }
}