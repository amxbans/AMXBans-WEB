<?php
/**
 * Smarty replace modifier plugin
 * Type:     modifier
 * Name:     r
 * Purpose:  transform string with replaceable attributes
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
function smarty_modifier_r ($string, array $replaceable)
{
    return str_replace(array_keys($replaceable), array_values($replaceable), $string);
}
