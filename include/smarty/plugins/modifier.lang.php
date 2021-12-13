<?php

/**
 * Type:     modifier
 * Name:     lang
 * Purpose:  transform string with language replacement
 *
 * @author indianiso1 <indianiso1 at gmail dot com>
 *
 * @param mixed  ...$additional
 * @param string $key input string
 *
 * @return array|string Translation string (or array)
 */
function smarty_modifier_lang(string $key, ...$additional): array|string
{
    return Lang::get(implode(".", [$key, ...$additional]));
}
