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
        {foreach $settings as $key => $setting}
            <div class="row">
                <div class="col-auto col-md-6 col-lg-3 font-weight-bold">{'settings_names'|lang:$key}</div>
                <div class="col">
                    {if $key|in_array:$arrays}          {"; "|implode:$setting}
                    {elseif $key|in_array:$booleans}    {$bool.$setting}
                    {else}                              {$setting}
                    {/if}
                </div>
            </div>
        {/foreach}
        <div class="row">
            <div class="col font-weight-bold">{'emoticons'|lang}</div>
            <div class="col-auto"><a href="{'web/settings/emoticons/create'|url}">{'add_new'|lang}</a></div>
        </div>
        <div class="row">
            {foreach $smilies as $code => $data}
                <div class="col-sm-4 col-md-3 col-xl-2 text-center justify-content-between d-flex">
                    <span>
                        {$code} → <img title="{$data.1}"
                                       src="{'/'|implode:['webSources/images/emoticons',$data.0]|res_url}" />
                    </span>
                    {if Auth::hasPermission('websettings_edit')}
                        <form method="post" action="{'web/settings/emoticons/delete'|url}">
                            {Site::makeFormAuth('delete')}
                            <input type="hidden" name="code" value="{$code|htmlspecialchars}">
                            <button class="btn btn-outline-danger">{'delete'|lang}</button>
                        </form>
                    {/if}
                </div>
            {/foreach}
        </div>
    {else}
        <div class="alert alert-danger">{'no_access'|lang}</div>
    {/if}
{/block}