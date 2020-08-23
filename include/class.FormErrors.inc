<?php
/**
 *    AMXBans v7
 * Copyright 2018 by indianiso1
 * This file is part of AMXBans.
 *
 * AMXBans is free software, but it's licensed under the Creative Commons - Attribution-NonCommercial-ShareAlike 2.0
 * AMXBans is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * You should have received a copy of the cc-nC-SA along with AMXBans.
 * If not, see http://creativecommons.org/licenses/by-nc-sa/2.0/
 */

/**
 * Class FormErrors
 */
class FormErrors
{
    /**
     * @var array
     */
    private $messages = [];
    /**
     * @var array
     */
    private $fields = [];
    /**
     * @var array
     */
    private $msgTemplates = [];
    /**
     * @var array
     */
    private $badge = [];

    /**
     * FormErrors constructor.
     * @param array $badge
     * @param array $validationMessages
     */
    public function __construct(array $badge, array $validationMessages)
    {
        $this->msgTemplates = $validationMessages;
        $this->badge = $badge;
    }

    /**
     * @param string $field
     * @return bool
     */
    public function has(string $field = NULL)
    {
        if (isset($field))
            return in_array($field, $this->fields);
        return !empty($this->fields);
    }

    /**
     * @return array
     */
    public function getMessages(): array
    {
        return $this->messages;
    }

    /**
     * @param string $message
     * @param string|array $fields
     * @param array $replace
     */
    public function addError(string $message, $fields = [], $replace = [])
    {
        if (is_string($fields))
            $fields = [$fields];
        $this->fields = array_merge($this->fields, $fields);
        foreach ($replace as $k => $v) {
            $message = str_ireplace(':' . $k, $v, $message);
        }
        $this->messages[] = $message;
    }

    /**
     * @param string $field
     * @param string $rule
     * @param array $replace
     */
    public function addValidationError(string $field, string $rule, array $replace = [])
    {
        $this->fields[] = $field;
        $message = $this->msgTemplates[$rule];
        $field = $this->justifyName($field, stristr($message, ':attribute'));
        $message = str_ireplace(':attribute', $field, $message);
        foreach ($replace as $k => $v) {
            $message = str_ireplace(':' . $k, $this->justifyName($v), $message);
        }
        $this->messages[] = $message;
    }

    public function validate(array $rules)
    {
        $fields = array_keys($rules);
        foreach ($fields as $field) {
            $value = $this->badge[$field];
            $rule = explode('|', $rules[$field]);

            foreach ($rule as $r) {
                $o = explode(':', $r)[1] ?? '';
                $o = explode(',', $o);
                $r = explode(':', $r)[0];
                if (!$this->{'val' . ucfirst($r)}($value, $o))
                    $this->addValidationError($field, $r, $o);
            }
        }
    }

    /**
     * @param string $field
     * @param string $case
     * @return string
     */
    private function justifyName(string $field, string $case = ':attribute'): string
    {
        $case = substr($case, 1);
        $field = str_replace('_', ' ', $field);
        if (ctype_upper($case))
            return strtoupper($field);
        elseif (ctype_upper(substr($case, 0, 1)))
            return ucfirst($field);
        return $field;
    }


    private function valRequired($value, $otherValues = null)
    {
        return isset($value) && !empty(trim($value));
    }

    private function valSame($value, array $otherValues = [])
    {
        return $value == $this->badge[$otherValues[0]];
    }

    private function valMin($value, array $otherValues = [])
    {
        return is_string($value) ?
            strlen($value) >= $otherValues[0] :
            $value >= $otherValues[0];
    }

    private function valMax($value, array $otherValues = [])
    {
        return is_string($value) ?
            strlen($value) <= $otherValues[0] :
            $value <= $otherValues[0];
    }

    private function valLater($value, array $otherValues = [])
    {
        $value = $value instanceof DateTime? $value : new DateTime((is_int($value)? '@' : '') . $value);
        $now = new DateTime();
        return $value > $now;
    }

    private function valIp($value, array $otherValues = [])
    {
        return $value? preg_match('/^(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$/', $value) : true;
    }

    private function valSteamid($value, array $otherValues = [])
    {
        return $value? preg_match('/^STEAM_0:[01]:[0-9]{1,10}$/', $value) : true;
    }

    private function valEmail($value, array $otherValues = [])
    {
        return $value? preg_match('/^[a-zA-Z0-9-_.]{2,64}@[a-zA-Z0-9-_.]{2,251}.[a-z]{2,4}$/', $value) : true; // https://stackoverflow.com/a/386302
    }

    private function valCaptcha($value, array $otherValues = [])
    {
        return $value? Captcha::isValid($value) : true;
    }
}