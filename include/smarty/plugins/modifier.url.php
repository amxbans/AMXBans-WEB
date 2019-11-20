<?php
/**
 * Smarty url modifier plugin
 * Type:     modifier
 * Name:     url
 * Purpose:  transform URL to appropriate
 * @author indianiso1 <indianiso1 at gmail dot com>
 *
 * @param string      $string    input string
 * @param string|null $php
 * @param string|null $real_path If set will take custom link which needs to prepend index
 *
 * @return string made url
 *
 */
function smarty_modifier_url(string $string, string $php = NULL, string $real_path = NULL)
{
    return Route::makeURL($string, $php, $real_path);
}
