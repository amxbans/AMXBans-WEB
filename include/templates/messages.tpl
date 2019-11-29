{if $messages instanceof FormErrors}
    <div class="alert alert-danger">
        <ul class="mb-0">
            {foreach $messages->getMessages() as $m}
                <li>{$m}</li>
            {/foreach}
        </ul>
    </div>
{elseif is_array($messages)}
    {foreach $messages as $m}
        <div class="alert alert-{$m.type}">
            <ul class="mb-0">
                {foreach $m.data as $m2}
                    <li>{$m2}</li>
                {/foreach}
            </ul>
        </div>
    {/foreach}
{/if}