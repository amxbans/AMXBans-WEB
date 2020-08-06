{if isset($messages) && $messages|typeof:FormErrors}
    <div class="alert alert-danger">
        <ul class="mb-0">
            {foreach $messages->getMessages() as $m}
                <li>{$m}</li>
            {/foreach}
        </ul>
    </div>
{elseif isset($messages) && is_array($messages)}
    {foreach $messages as $m}
        <div class="alert alert-{$m.type}">{$m.text}</div>
    {/foreach}
{elseif isset($message) && $message|is_array}
    <div class="alert alert-{$message.type}">{$message.text}</div>
{elseif isset($message) && $message|is_string}
    <div class="alert alert-info">{$message}</div>
{/if}