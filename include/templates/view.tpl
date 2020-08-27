{extends 'master.tpl'}
{block name="head-title" prepend}{$lang.index.titles.servers} | {/block}

{block name="BODY"}
    {include "messages.tpl"}
    <div class="row">
    <div class="col-lg-9">
        <div class="card mb-3">
            <h2 class="card-header h5">{$lang.index.titles.servers}</h2>
            <div class="card-body accordion" id="serverInfoContainer">
                {foreach $servers as $server}
                    <div class="card" data-server-id="{$server.id}">
                        <div class="card-header" data-toggle="collapse" data-target="#collapse{$server@iteration}">
								<span class="mr-2 iconHolder">
									<img alt="{$server.gametype}"
                                         src="{"webSources/images/games/:game.gif"|replace:":game":$server.gametype|res_url}" />
                                </span>
                            {$server.hostname}
                            <a href="steam://connect/{$server.address}" title="{$lang.index.servers.connect}"
                               class="icon-connect float-right"
                               style="background-image: url({"webSources/images/gfx/connect.png"|res_url});"></a>
                        </div>
                        <div class="card-body collapse spinner" id="collapse{$server@iteration}">
                            <div style="padding: 15vh;" class="d-flex justify-content-center">
                                <div class="spinner-border" role="status">
                                    <span class="sr-only">Loading...</span>
                                </div>
                            </div>
                        </div>
                    </div>
                {/foreach}
            </div>
        </div>
    </div>
    <div class="col">
        <div class="row">
            <div class="col-sm col-lg-12">
                <div class="card bg-light mb-3">
                    <h3 class="card-header d-flex justify-content-between align-items-center h6">
                        {$lang.index.servers.stats}
                        <span class="float-right stat-icon stats"></span>
                    </h3>
                    <div class="card-body">
                        <ul class="list-group">

                            <li class="d-flex justify-content-between align-items-center">
                                <b>{$lang.index.servers.total_bans}:</b>
                                <span>{$stats.total}</span>
                            </li>

                            <li class="d-flex justify-content-between align-items-center">
                                <span class="ml-2">{$lang.admin.sys_info.active|ucfirst}:</span>
                                <span>{$stats.permanent+$stats.temp}</span>
                            </li>

                            <li class="d-flex justify-content-between align-items-center">
                                <span></span>
                                <i>{$lang.index.bans.permanent|ucfirst}: {$stats.permanent}</i>
                            </li>

                            <li class=" d-flex justify-content-between align-items-center">
                                <span></span>
                                <i>{$lang.index.servers.temp_bans|ucfirst}: {$stats.temp}</i>
                            </li>

                            <li class="d-flex justify-content-between align-items-center">
                                <b>{$lang.admin.subtitles.server.admins}:</b>
                                <span>{$stats.admins}</span>
                            </li>

                            <li class="d-flex justify-content-between align-items-center">
                                <b>{$lang.index.servers.servers}:</b>
                                <span>{$stats.servers}</span>
                            </li>
                        </ul>
                    </div>
                </div>
            </div>
            <div class="col">
                <div class="card bg-light mb-3">
                    <h3 class="card-header d-flex justify-content-between align-items-center h6">
                        {$lang.index.servers.last_ban}
                        <span class="float-right stat-icon clock"></span>
                    </h3>
                    <div class="card-body">
                        <ul class="list-group">

                            <li class="d-flex justify-content-between align-items-center">
                                <b>{$lang.index.bans.player|ucfirst}:</b>
                                <span>{$last_ban.player_nick}</span>
                            </li>

                            <li class="d-flex justify-content-between align-items-center">
                                <b>{$lang.index.ban.steamid|ucfirst}:</b>
                                <span>{$last_ban.player_id}</span>
                            </li>

                            <li class="d-flex justify-content-between align-items-center">
                                <b>{$lang.index.bans.reason|ucfirst}:</b>
                                <span>{$last_ban.ban_reason}</span>
                            </li>

                            <li class="d-flex justify-content-between align-items-center">
                                <b>{$lang.index.bans.length|ucfirst}:</b>
                                {if $last_ban.ban_length > 0}
                                    <span class="timeleft">{$last_ban.ban_length}</span>
                                {elseif $last_ban.ban_length == 0}
                                    <i>{$lang.index.bans.permanent}</i>
                                {else}
                                    <i>{$lang.index.ban.expired}</i>
                                {/if}
                            </li>

                            <li class="d-flex justify-content-between align-items-center">
                                <b>{$lang.index.bans.date|ucfirst}:</b>
                                <span>{$last_ban.ban_created|date_format:$lang.date_format}</span>
                            </li>

                            <li class="d-flex justify-content-between align-items-center">
                                <a href="{['bans']|url}">&#171; {$lang.index.titles.bans|ucfirst}</a>
                                <a href="{['bans', $last_ban.bid]|url}">{$lang.index.titles.ban} &#187;</a>
                            </li>

                        </ul>
                    </div>
                </div>
            </div>
        </div>
    </div>
    <script>
		timer($('.timeleft').text() + '000', '.timeleft');
    </script>
{/block}