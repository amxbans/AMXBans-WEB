<?php

include_once "modifier.url.php";
include_once "modifier.res_url.php";
/**
 * Smarty url modifier plugin
 * Type:     modifier
 * Name:     full_url
 * Purpose:  transform URL to appropriate
 *
 * @param string|array $string    input string
 *
 * @return string made url
 *
 * @author indianiso1 <indianiso1 at gmail dot com>
 *
 */
function smarty_modifier_full_url ($string, bool $fake = true)
{
    return (isset($_SERVER['HTTPS']) && $_SERVER['HTTPS']? 'https://' : 'http://') . $_SERVER['SERVER_NAME'] . ($fake? smarty_modifier_url($string) : smarty_modifier_res_url($string));
}
