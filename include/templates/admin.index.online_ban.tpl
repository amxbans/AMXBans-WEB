{extends file="master.tpl"}
{block name="head-title" prepend}{'admin_menu_subtitles'|lang:'index':'online_ban'} - {'admin_menu_titles'|lang:'index'} | {/block}

{block name="BODY"}
    {include file="messages.tpl"}
    {if Auth::hasPermission('bans_add')}
        <div class="card mb-3">
            <h2 class="card-header h5">{'menu_titles'|lang:'servers'}</h2>
            <div class="card-body accordion" id="serverPlayers">
                {foreach $servers as $server}
                    <div class="card" data-server-id="{$server.id}">
                        <div class="card-header" data-toggle="collapse" data-target="#collapse{$server@iteration}">
							<span class="mr-2 iconHolder">
								<img alt="{$server.gametype}"
                                     src="{"webSources/images/games/:game.gif"|replace:":game":$server.gametype|res_url}"/>
                            </span>
                            {$server.hostname}
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
        <table class="table table-hover">
            <thead>
            <tr>
                <th>{'mod'|lang}</th>
                <th>{'os'|lang}</th>
                <th>{'server'|lang}</th>
                <th>{'player'|lang}</th>
                <th>{'map'|lang}</th>
            </tr>
            </thead>
            <tbody>
            {foreach $servers as $server}
                <tr onclick="location.href='{array('index', 'online_ban', $server->id)|url}'">
                    <td>{html_image file="webSources/images/details.gif" href=['index', 'online_ban', $server->id]|url}</td>
                    <td><img alt="{$server->liveInfo('mod')}" title="{$server->liveInfo('mod')}"
                             src="webSources/images/games/{$server->liveInfo('mod')}.gif"/></td>
                    <td><img alt="{$server->liveInfo('os')}" title="{$server->liveInfo('os')}"
                             src="webSources/images/os/{$server->liveInfo('os')}.gif"/></td>
                    <td>{$server->hostname}</td>
                    <td>{$server->liveInfo('cur_players')}{if $server->liveInfo('bot_players')} ({$server->liveInfo('bot_players')}
                        {$lang.admin.ban_add.bots}){/if}/{$server->liveInfo('max_players')}</td>
                    <td>{$server->liveInfo('map')}</td>
                </tr>
            {/foreach}
            </tbody>
        </table>
        {if $selected->exists}
            <form method="post">
                <div class="row">
                    <aside class="col-md">
                        <div class="list-group justify-content-between">
                            {foreach $players as $player}
                                <div class="list-group-item" onclick="{*todo: live ban copy vars f-on????*}">
                                    <span class="text-truncate"
                                    <span data-id="{$player.userid}"
                                          {if $player.immunity}class="disabled"{/if} disabled>{$player.name}</span>
                                </div>
                            {/foreach}
                        </div>
                    </aside>
                </div>
                <table>
                    <thead>
                    <tr>
                        <th style="width:250px;">{"_ADDBAN"|lang}</th>
                        <th>&nbsp;</th>
                    </tr>
                    </thead>
                    <tbody>
                    <tr>
                        <td class="fat">{"_BANTYPE"|lang}</td>
                        <td>
                            <select name="ban_type">
                                <option label="Steamid" value="S">{"_STEAMID"|lang}</option>
                                <option label="Steamid &amp; IP" value="SI">{"_STEAMID"|lang}
                                    &amp; {"_IP"|lang}</option>
                            </select>
                        </td>
                    </tr>
                    <tr>
                        <td class="fat">{"_REASON"|lang}</td>
                        <td>
                            <select name="ban_reason">
                                {html_options output=$reasons values=$reasons}
                            </select>
                            {"_OR"|lang} {"_NEWREASON"|lang}: <input type="text" size="30" name="user_reason"
                                                                     onkeyup="document.frm.ban_reason.disabled=(this.value!='');"/>
                        </td>
                    </tr>
                    <tr>
                        <td class="fat">{"_BANLENGHT"|lang}</td>
                        <td>
                            <input type="text" size="8" name="ban_length" disabled="disabled"/> {"_MIN_OR"|lang}
                            <input type="checkbox" name="perm" checked="checked"
                                   onclick="document.frm.ban_length.disabled=this.checked;"/> {"_PERMANENT"|lang}
                        </td>
                    </tr>
                    </tbody>
                </table>
            </form>
        {/if}
        <div class="post">
            <table frame="box" rules="groups" summary="">
                <thead>
                <tr>
                    <th style="width:5px;">{"_NUMBER"|lang}</th>
                    <th>{"_NAME"|lang}</th>
                    <th style="width:150px;">{"_STEAMID"|lang}</th>
                    <th style="width:150px;">{"_IP"|lang}</th>
                    <th style="width:50px;">{"_USERID"|lang}</th>
                    <th style="width:50px;">{"_STATUSNAME"|lang}</th>
                    <th style="width:50px;">&nbsp;</th>
                    <th style="width:50px;">&nbsp;</th>
                </tr>
                </thead>
                <tbody>
                <!-- Users Online -->
                {if $playerscount}
                    {foreach from=$players item=player}
                        <tr {if $smarty.session.bans_add!="yes"  || $players.status == 1 || $players.immunity != 0}class="offline"{/if}>
                            <td class="_center">{counter}.</td>
                            <td>{$players.name}</td>
                            <td>{$players.steamid}</td>
                            <td>{$players.ip}</td>
                            <td class="_center">#{$players.userid}</td>
                            <td class="_center">{$players.statusname|lang}</td>
                            <td class="_center">
                                <input type="submit" class="button" name="ban"
                                       onclick="LiveBanCopyVars('{$players.name}','{$players.steamid}','{$players.ip}','{$players.userid}');
                                               return confirm('{"_BANPLAYER"|lang}');"
                                       value="{"_BAN"|lang}"
                                       {if $smarty.session.bans_add!="yes"  || $players.status == 1 || $players.immunity != 0}disabled="disabled"{/if} />
                            </td>
                            <td class="_center">
                                <input type="submit" class="button" name="kick"
                                       onclick="LiveBanCopyVars('{$players.name}','{$players.steamid}','{$players.ip}','{$players.userid}');
                                               return confirm('{"_KICKPLAYER"|lang}');"
                                       value="{"_KICK"|lang}"
                                       {if $players.immunity != 0}disabled="disabled"{/if} />
                            </td>
                        </tr>
                    {/foreach}
                {else}
                    <tr>
                        <td class="error _center" colspan="8">{if $smsg!=""}<b class="error">{$smsg|lang}{else}
                                <b>
                                {"_NOPLAYERS"|lang}{/if}</td>
                    </tr>
                {/if}
                <!-- Users Online -->
                </tbody>
            </table>
            <div class="clearer">&nbsp;</div>
        </div>
        <input type="hidden" name="server" value="0"/>
        <input type="hidden" name="player_name" id="player_name" value=""/>
        <input type="hidden" name="player_uid" id="player_uid" value=""/>
        <input type="hidden" name="player_steamid" id="player_steamid" value=""/>
        <input type="hidden" name="player_ip" id="player_ip" value=""/>
        </form>
    {else}
        <div class="alert alert-danger">{'no_access'|lang}</div>
    {/if}
{/block}

{block name="scripts"}
    <script>
        $(function () {
            $('#serverPlayers > .card').click(function (e) {
                if ($('.card-body.show', this).length) {
                    return e;
                }
                const $this = $(this);
                if (!$this.children().last().hasClass('spinner')) {
                    return e;

                }
                $this.children().last().html('<div style="padding: 15vh;" class="d-flex justify-content-center"><div class="spinner-border" role="status"><span class="sr-only">Loading...</span></div></div>');
                let server = $this.data('server-id');
                $.get('servers/' + server, data => {
                    if (!data.success) {
                        $this.children().last().html('<div class="alert alert-warning">' + data.message + '</div>');
                        return e;
                    }

                    {* TODO: Continue development of this ajax when having info of online server *}

                    let tpl = '<div class="row">' +
                        '<div class="col-12 col-md"><div class="mx-auto text-center" style="max-width: 150px"><img /></div><ul class="list-group"></ul></div>' +
                        '<div class="col"><div class="h6">' + data.lang.players + ' (' + (data.info.players.active - data.info.players.bots) + ' ' + data.lang.player.active + ', ' + data.info.players.bots + ' ' + data.lang.player.bots + ' // ' + data.info.players.max + ' ' + data.lang.player.total + ')' +
                        '</div><ul class="list-group players"></ul></div>' +
                        '</div>';
                    const $child = $this.children().last().removeClass('spinner').html(tpl);
                    $('img', $child).attr('src', data.info.picture).attr('alt', data.info.map).parent().append('<small class="text-muted">' + data.info.map + '</small>');
                    data.players.forEach(function (player) {
                        $('ul.players', $child).append('<li class="list-group-item d-flex justify-content-between align-items-center">\n' +
                            (player.name ? player.name : '<span class="font-italic">' + data.lang.player.connecting + '</span>') +
                            '<span>' +
                            // '<span class="badge badge-secondary badge-pill">' + player.time + '</span>' +
                            '<span class="badge badge-secondary badge-pill">' + player.kills + '</span>' +
                            '</span>\n' +
                            '  </li>');
                    });
                    if (data.players.length === 0) {
                        $('ul.players', $child).parent().html('<p class="text-center">' + data.lang.player.none + '</p>')
                    }

                    tpl = '<li class="list-group-item d-flex justify-content-between align-items-center"></li>';
                    $('ul:not(.players)', $child).append('<li class="list-group-item text-center"><p class="font-bold">' + data.info.hostname + '</p></li>');
                    $('ul:not(.players)', $child).append($(tpl).clone().html('<b>' + data.lang.hostname + ':</b> ' + data.info.address));
                    $('ul:not(.players)', $child).append($(tpl).clone().html('<b>' + data.lang.password + ':</b> ' + (data.info.password ? data.lang.yes : data.lang.no)));
                    $('ul:not(.players)', $child).append($(tpl).clone().html('<b>' + data.lang.friendlyFire + ':</b> ' + (data.info.friendlyFire ? data.lang.yes : data.lang.no)));
                    $('ul:not(.players)', $child).append($(tpl).clone().html('<b>' + data.lang.map + ':</b> ' + data.info.map));
                    $('ul:not(.players)', $child).append($(tpl).clone().html('<b>' + data.lang.timeleft + ':</b> ' + data.info.timeleft));
                    $('ul:not(.players)', $child).append($(tpl).clone().html('<b>' + data.lang.nextmap + ':</b> ' + data.info.nextmap));
                });
            });
        });
    </script>
{/block}