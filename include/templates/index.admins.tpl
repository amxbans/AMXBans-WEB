{extends 'master.tpl'}
{block name="head-title" prepend}{'menu_titles'|lang:'admins'} | {/block}

{block name="BODY"}
    {include "messages.tpl"}
    <div class="row">
        <div class="col-lg-9 col-xl-8 table-responsive">
            <table class="table table-hover">
                <thead>
                <tr>
                    <th>{'admin'|lang}</th>
                    <th>{'access_title'|lang}</th>
                    <th>{'admin_since'|lang}</th>
                    <th>{'admin_until'|lang}</th>
                </tr>
                </thead>
                <tbody>
                <!-- Start Loop -->
                {foreach $admins as $admin}
                    <tr>
                        <td>
                            <b>{$admin.nickname}</b>
                            {if $admin.steamid}
                                <a href="http://steamcommunity.com/profiles/{Steam::GetFriendID($admin.comid|htmlentities:ENT_QUOTES)}"
                                   target="_blank"><img src="{'webSources/images/gfx/Steam.png'|res_url}"
                                                        alt="SteamACC" /></a>
                                <br>
                                {$admin.steamid}
                            {/if}
                        </td>
                        <td>{$admin.access}</td>
                        <td>{$admin.created|date_format:$lang_date_format}</td>
                        <td>{if !$admin.expired}<i>{'unlimited'|lang|ucfirst}</i>
                            {else}{$admin.expired|date_format:$lang_date_format}{/if}</td>
                    </tr>
                {/foreach}
                <!-- Stop Loop -->
                </tbody>
            </table>
        </div>

        <div class="col">
            <div class="card">
                <div class="card-header">{'access_title'|lang}</div>
                <div class="card-body">
                    {foreach 'access_flags'|lang as $access}
                        {$access}
                        <br>
                    {/foreach}
                </div>
            </div>
        </div>
    </div>
{/block}