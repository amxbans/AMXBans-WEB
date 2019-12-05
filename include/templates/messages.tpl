{if isset($messages) && $messages instanceof FormErrors}
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
{/if}