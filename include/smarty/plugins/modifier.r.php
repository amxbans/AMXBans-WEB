<?php
/**
 * Smarty replace modifier plugin
 * Type:     modifier
 * Name:     r
 * Purpose:  transform string with replaceable attributes
 *
 * @author indianiso1 <indianiso1 at gmail dot com>
 * @param string|array $string input string
 * @param array        $replaceable
 *
 * @return string made url
 *
 */
function smarty_modifier_r($string, array $replaceable)
{
    return str_replace(array_keys($replaceable), array_values($replaceable), $string);
}