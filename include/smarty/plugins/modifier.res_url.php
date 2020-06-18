<?php
/**
 * Smarty url modifier plugin
 * Type:     modifier
 * Name:     url
 * Purpose:  transform URL to appropriate
 *
 * @param string      $string    input string
 * @param string|null $real_path If set will take custom link which needs to prepend index
 *
 * @return string made url
 * @author indianiso1 <indianiso1 at gmail dot com>
 *
 */
function smarty_modifier_res_url($string)
{
    return str_replace(DIRECTORY_SEPARATOR . '/', '/', \Support\Path::getBaseURL() . '/' . $string);
}
