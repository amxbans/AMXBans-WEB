<?php
/**
 * Type:     modifier
 * Name:     lang
 * Purpose:  transform string with language replacement
 *
 * @author indianiso1 <indianiso1 at gmail dot com>
 *
 * @param string $key input string
 *
 * @return string made url
 *
 */
function smarty_modifier_lang($key, $additional = null)
{
    return $additional? Lang::get($key)[$additional] : Lang::get($key);
}
