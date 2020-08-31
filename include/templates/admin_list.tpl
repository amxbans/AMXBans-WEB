{extends 'master.tpl'}
{block name="head-title" prepend}{$lang.index.titles.ban} | {/block}

{block name="BODY"}
    {include "messages.tpl"}
    <div class="row">
        <div class="col-lg-9 col-xl-8 table-responsive">
            <table class="table table-hover">
                <thead>
                <tr>
                    <th>{$lang.index.bans.admin|ucfirst}</th>
                    <th>{$lang.index.admins.access_title}</th>
                    <th>{$lang.from|ucfirst}</th>
                    <th>{$lang.until|ucfirst}</th>
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
                        <td>{$admin.created|date_format:$lang.date_format}</td>
                        <td>{if !$admin.expired}<i>{$lang.index.bans.permanent|ucfirst}</i>
                            {else}{$admin.expired|date_format:$lang.date_format}{/if}</td>
                    </tr>
                {/foreach}
                <!-- Stop Loop -->
                </tbody>
            </table>
        </div>

        <div class="col">
            <div class="card">
                <div class="card-header">{$lang.index.admins.access_title}</div>
                <div class="card-body">
                    {foreach $lang.index.admins.accesses as $access}
                        {$access}
                        <br>
                    {/foreach}
                </div>
            </div>
        </div>
    </div>
{/block}