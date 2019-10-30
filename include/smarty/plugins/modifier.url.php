<?php
/**
 * Smarty url modifier plugin
 * Type:     modifier
 * Name:     url
 * Purpose:  transform URL to appropriate
 *
 * @author indianiso1 <indianiso1 at gmail dot com>
 *
 * @param string      $string        input string
 * @param string|null $real_path  If set will take custom link which needs to prepend index
 *
 * @return string made url
 */
function smarty_modifier_url($string, string $real_path = NULL)
{
    if ($real_path)
        return Route::getBaseURL() . '/' . $real_path . '/index.php/' . $string;
    return Route::makeURL($string);
}
