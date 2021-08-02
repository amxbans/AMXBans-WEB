{extends file="master.tpl"}
{block name="head-title" prepend}{'admin_menu_subtitles'|lang:'web':'settings'} - {'admin_menu_titles'|lang:'web'} | {/block}

{block name="BODY"}
    {include file="messages.tpl"}
    {if Auth::hasPermission('websettings_view')}
        <h2>
            {'web_settings'|lang}
            {if Auth::hasPermission('websettings_edit')}<small class="float-right">
                <a href="{'web/settings/edit'|url}" class="btn btn-outline-primary">{'edit'|lang}</a>
                </small>{/if}
        </h2>
        <div>
            {foreach $settings as $key => $setting}
                <div class="row">
                    <div class="col-sm-2">{'settings_names'|lang:$key}</div>
                    <div class="col">
                        {if $key|in_array:$arrays}          {" "|implode:$setting}
                        {elseif $key|in_array:$booleans}    {$bool.$setting}
                        {else}                              {$setting}
                        {/if}
                    </div>
                </div>
            {/foreach}
        </div>
    {else}
        <div class="alert alert-danger">{'no_access'|lang}</div>
    {/if}
{/block}