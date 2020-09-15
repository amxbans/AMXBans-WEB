<?php
/**
 * Type:     modifier
 * Name:     lang
 * Purpose:  transform string with language replacement
 *
 * @param string $key input string
 *
 * @param mixed  ...$additional
 *
 * @return string made url
 * @author indianiso1 <indianiso1 at gmail dot com>
 */
function smarty_modifier_lang (string $key, ...$additional)
{
    if ($additional) {
        $last = array_pop($additional);
        return smarty_modifier_lang($key, ...$additional)[$last];
    }
    return Lang::get($key);
}
