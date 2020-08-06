<?php
/**
 * Smarty instance checker plugin
 * Type:     modifier
 * Name:     typeof
 * Purpose:  check instance validity
 *
 * @author indianiso1 <indianiso1 at gmail dot com>
 * @param       $comparable
 * @param mixed $item
 *
 * @return bool
 *
 *             TODO recovery: Check if it works at all
 */
function smarty_modifier_typeof ($item, $comparable)
{
    return $item instanceof $comparable;
}