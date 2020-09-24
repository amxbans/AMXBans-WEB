{extends 'master.tpl'}
{block name="head-title" prepend}{'menu_titles'|lang:'servers'} | {/block}

{block name="BODY"}
    {include "messages.tpl"}
    <div class="row">
    <div class="col-lg-9">
        <div class="card mb-3">
            <h2 class="card-header h5">{'menu_titles'|lang:'servers'}</h2>
            <div class="card-body accordion" id="serverInfoContainer">
                {foreach $servers as $server}
                    <div class="card" data-server-id="{$server.id}">
                        <div class="card-header" data-toggle="collapse" data-target="#collapse{$server@iteration}">
								<span class="mr-2 iconHolder">
									<img alt="{$server.gametype}"
                                         src="{"webSources/images/games/:game.gif"|replace:":game":$server.gametype|res_url}" />
                                </span>
                            {$server.hostname}
                            <a href="steam://connect/{$server.address}" title="{'connect'|lang}"
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
        <div class="col-lg-3">
            <div class="row">
                <div class="col-sm col-lg-12">
                    <div class="card bg-light mb-3">
                        <h3 class="card-header d-flex justify-content-between align-items-center h6">
                            {'stats'|lang}
                        <span class="float-right stat-icon stats"></span>
                    </h3>
                    <div class="card-body">
                        <ul class="list-group">

                            <li class="d-flex justify-content-between align-items-center">
                                <b>{'total_bans'|lang}:</b>
                                <span>{$stats.total}</span>
                            </li>

                            <li class="d-flex justify-content-between align-items-center">
                                <span class="ml-2">{'active_bans'|lang}:</span>
                                <span>{$stats.permanent+$stats.temp}</span>
                            </li>

                            <li class="d-flex justify-content-between align-items-center">
                                <span></span>
                                <i>{'permanent'|lang}: {$stats.permanent}</i>
                            </li>

                            <li class=" d-flex justify-content-between align-items-center">
                                <span></span>
                                <i>{'temp_bans'|lang}: {$stats.temp}</i>
                            </li>

                            <li class="d-flex justify-content-between align-items-center">
                                <b>{'admins'|lang}:</b>
                                <span>{$stats.admins}</span>
                            </li>

                            <li class="d-flex justify-content-between align-items-center">
                                <b>{'servers'|lang}:</b>
                                <span>{$stats.servers}</span>
                            </li>
                        </ul>
                    </div>
                </div>
            </div>
            <div class="col">
                <div class="card bg-light mb-3">
                    <h3 class="card-header d-flex justify-content-between align-items-center h6">
                        {'latest_ban'|lang}
                        <span class="float-right stat-icon clock"></span>
                    </h3>
                    <div class="card-body">
                        <ul class="list-group">

                            <li class="d-flex justify-content-between align-items-center">
                                <b>{'player'|lang}:</b>
                                <span>{$last_ban.player_nick}</span>
                            </li>

                            <li class="d-flex justify-content-between align-items-center">
                                <b>{*{'steamid'|lang}:*}</b>
                                <span>{$last_ban.player_id}</span>
                            </li>

                            <li class="d-flex justify-content-between align-items-center">
                                <b>{'reason'|lang}:</b>
                                <span>{$last_ban.ban_reason}</span>
                            </li>

                            <li class="d-flex justify-content-between align-items-center">
                                <b>{'length'|lang}:</b>
                                {if $last_ban.ban_length > 0}
                                    <span class="timeleft">{$last_ban.ban_length}</span>
                                {elseif $last_ban.ban_length == 0}
                                    <i>{'permanent'|lang}</i>
                                {else}
                                    <i>{'expired'|lang}</i>
                                {/if}
                            </li>

                            <li class="d-flex justify-content-between align-items-center">
                                <b>{'date'|lang}:</b>
                                <span>{$last_ban.ban_created|date_format:$lang_date_format}</span>
                            </li>

                            <li class="d-flex justify-content-between align-items-center">
                                <a href="{['bans']|url}">&#171; {'menu_titles'|lang:'bans'}</a>
                                <a href="{['bans', $last_ban.bid]|url}">{'menu_titles'|lang:'ban'} &#187;</a>
                            </li>

                        </ul>
                    </div>
                </div>
            </div>
            </div>
        </div>
    </div>
    <script>
        timer($('.timeleft').text() + '000', '.timeleft');
    </script>
{/block}