<?php
/**
 * Smarty input modifier plugin
 * Type:     modifier
 * Name:     input
 * Purpose:  output an old input if any set
 *
 * @author indianiso1 <indianiso1 at gmail dot com>
 *
 * @param string      $string        input string
 * @param string|null $default  What to return if nothing set in POST array
 *
 * @return string made url
 */
function smarty_modifier_input($string, $default = NULL)
{
        return $_POST[$string] ?? $default;
}
