<?php
/**
 * Smarty url modifier plugin
 * Type:     modifier
 * Name:     url
 * Purpose:  transform URL to appropriate
 *
 * @param string|array $string    input string
 * @param string|null  $php
 * @param string|null  $real_path If set will take custom link which needs to prepend index
 *
 * @return string made url
 *
 * @author indianiso1 <indianiso1 at gmail dot com>
 *
 */
function smarty_modifier_url($string, string $php = null, string $real_path = null)
{
    return \Support\Path::makeURL(is_array($string) ? implode('/', $string) : $string, $php, $real_path);
}
