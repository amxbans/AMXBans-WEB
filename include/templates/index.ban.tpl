{extends 'master.tpl'}
{block name="head-title" prepend}{$lang.index.titles.ban} | {/block}

{block name="BODY"}
    {if isset($errors)}{include "messages.tpl"}{/if}

    <div class="card mb-4" id="ban-details">
        <div class="card-header">
            {$lang.index.ban.details}
            <a href="#" class="float-right" data-toggle="modal" data-target="#shareModal">#{$ban.bid}</a>
        </div>
        <div class="card-body">
            {if User::$logged}
                <div class="text-right">
                    {if $can_user.edit_bans || ($can_user.edit_own_bans && $ban.username == User::get('username'))}
                        <a href="{['ban', $ban.bid, 'edit']|url}" class="btn btn-outline-primary">{$lang.admin.edit|ucfirst}</a>
                    {/if}
                    {if $can_user.unban || ($can_user.unban_own && $ban.username == User::get('username'))}
                        <a href="{['ban', $ban.bid, 'unban']|url}" class="btn btn-outline-warning do-confirm">{$lang.admin.unban|ucfirst}</a>
                    {/if}
                    {if $can_user.delete_bans || ($can_user.delete_own_bans && $ban.username == User::get('username'))}
                        <a href="{['ban', $ban.bid, 'delete']|url}" class="btn btn-outline-danger do-confirm">{$lang.admin.delete|ucfirst}</a>
                    {/if}
                </div>
            {/if}
            <div class="row">
                <div class="col-lg-3 col-sm-5 text-sm-right">{$lang.nickname|ucfirst}</div>
                <div class="col">{$ban.player_nick|escape}</div>
            </div>
            <div class="row">
                <div class="col-lg-3 col-sm-5 text-sm-right">{$lang.index.ban.steamid|ucfirst}</div>
                <div class="col">{$ban.player_id}</div>
            </div>
            {if $ban.com_id}
                <div class="row">
                    <div class="col-lg-3 col-sm-5 text-sm-right">{$lang.index.ban.steamcomid|ucfirst}</div>
                    <div class="col"><a href="http://steamcommunity.com/profiles/{$ban.com_id}">{$ban.com_id}</a></div>
                </div>
            {/if}
            {if $can_user.view_ips && $ban.player_ip}
                <div class="row">
                    <div class="col-lg-3 col-sm-5 text-sm-right">{$lang.ip}</div>
                    <div class="col">{$ban.player_ip}</div>
                </div>
            {/if}
            <div class="row">
                <div class="col-lg-3 col-sm-5 text-sm-right">{$lang.index.ban.type}</div>
                <div class="col">{$lang.index.ban.types[$ban.ban_type]}</div>
            </div>
            <div class="row">
                <div class="col-lg-3 col-sm-5 text-sm-right">{$lang.index.bans.reason|ucfirst}</div>
                <div class="col">{$ban.ban_reason}</div>
            </div>
            <div class="row">
                <div class="col-lg-3 col-sm-5 text-sm-right">{$lang.index.ban.invoked|ucfirst}</div>
                <div class="col">{$lang.date_format|date:$ban.ban_created}</div>
            </div>
            <div class="row">
                <div class="col-lg-3 col-sm-5 text-sm-right">{$lang.index.bans.length|ucfirst}</div>
                <div class="col"><span class="timeleft">{$ban.ban_length * 60}</span> {if $ban.expired}<i>[{$lang.index.ban.expired}]</i>{/if}</div>
            </div>
            <div class="row">
                <div class="col-lg-3 col-sm-5 text-sm-right">{$lang.index.bans.admin|ucfirst}</div>
                <div class="col">{$ban.admin_nick} {if $can_user.view_admins}({$ban.nickname}{if $can_user.view_ips}, {$ban.admin_id}{/if}){/if}</div>
            </div>
            <div class="row">
                <div class="col-lg-3 col-sm-5 text-sm-right">{$lang.server|ucfirst}</div>
                <div class="col">{if $ban.server_name == 'website'}{$lang.website|ucfirst}{else}{$ban.server_name}{/if}</div>
            </div>
        </div>
        {*{include file="layer_banedit.tpl"}*}
    </div>

    <div class="card">
        <div class="card-header">{$lang.index.ban.comments_files}</div>
        <div class="card-body">
            {if  $vars.use_demo == 1}
                <div class="post">

                    <table frame="box" rules="groups" summary="">

                        <thead>

                        <tr>

                            <th colspan="8">{"_BL_FILES"|lang}</th>

                        </tr>

                        <tr>

                            <th style="width:130px;">{"_DATE"|lang}</th>

                            <th style="width:100px;">{"_FILE"|lang}</th>

                            <th style="width:50px;">{"_SIZE"|lang}</th>

                            <th>{"_COMMENT"|lang}</th>

                            <th style="width:100px;">{"_BY"|lang}</th>

                            <th style="width:150px;">{"_IP"|lang}</th>

                            <th style="width:20px;">{"_DOWNLOADS"|lang}</th>

                            <th style="width:80px;">&nbsp;</th>

                        </tr>

                        </thead>

                        <tbody>

                        {foreach from=$demos item=dmeo}
                            <form method="post">

                                <input type="hidden" name="bid" value="{$ban_detail.bid}" />

                                <input type="hidden" name="site" value="{$site}" />

                                <input type="hidden" name="did" value="{$dmeo.id}" />

                                <input type="hidden" name="details_x" value="1" />

                                <tr>

                                    <td>{$dmeo.upload_time|date_format:"%d. %b %Y - %T"}</td>

                                    <td>{$dmeo.demo_real}</td>

                                    <td>{$dmeo.file_size} (MODIFIER: FILE_SIZE)</td>

                                    <td>{if $dmeo.comment}{$dmeo.comment|nl2br}{else}{"_NOCOMMENT"|lang}{/if}</td>

                                    <td>{$dmeo.name}</td>

                                    <td>{if $smarty.session.ip_view=="yes"}{$dmeo.addr}{/if}</td>

                                    <td class="_center">{$dmeo.down_count}</td>

                                    <td class="_right">

                                        <form method="POST" style="display:inline;">

                                            <a href="mailto:{$dmeo.email}"><img src="images/email_go.png" border="0"
                                                                                title="{"_TIP_SENDMAIL"|lang}" /></a>

                                            <input name="down_demo" type="image" src="images/disk.png" border="0"
                                                   title="{"_TIP_DOWNLOAD"|lang}" />

                                            {if $smarty.session.bans_edit=="yes" || ($smarty.session.bans_edit=="own" && $smarty.session.uname == $dmeo.name)}
                                                <img src="images/page_edit.png" border="0"
                                                     onClick="NewToggleLayer('demedit_{$dmeo.id}');" title="{"_TIP_EDIT"|lang}"
                                                     style="cursor:pointer;" />
                                            {/if}

                                            {if $smarty.session.bans_delete=="yes" || ($smarty.session.bans_delete=="own" && $smarty.session.uname == $dmeo.name)}
                                                <input name="del_demo" type="image"
                                                       src="templates/{$design}_gfx/page_delete.png" border="0"
                                                       onclick="return confirm('{"_DELDEMO"|lang}{"_DATALOSS"|lang}');"
                                                       title="{"_TIP_DEL"|lang}" />
                                            {/if}

                                            <input type="hidden" name="site" value="{$site}" />

                                            <input type="hidden" name="bid" value="{$ban_detail.bid}" />

                                            <input type="hidden" name="details_x" value="1" />

                                        </form>

                                    </td>

                                </tr>

                                <tr id="demedit_{$dmeo.id}" style="display: none">

                                    {*	{include file="layer_demedit.tpl"}*}

                                </tr>

                            </form>
                            {foreachelse}
                            <td class="_center" colspan="8">{"_NOFILES"|lang}</td>
                        {/foreach}

                        </tbody>

                    </table>

                    <div class="clearer">&nbsp;</div>

                </div>
                {if $vars.comment_all=="1" || $smarty.session.loggedin == "true"}
                    <div class="post _center">

                        <form method="post" action="">

                            <input type="button" class="button" name="newfile" value="{"_NEWFILE"|lang}"
                                   onclick="$('#add_file').slideToggle('slow');" /><br /><br />

                        </form>

                    </div>
                    <div id="add_file" class="post" style="display:none;">

                        {*{include file="layer_demadd.tpl"}*}

                    </div>
                {/if}

            {/if}
            {if  $vars.use_comment == 1}
                <div class="post">

                    <table frame="box" rules="groups">

                        <thead>

                        <tr>

                            <th colspan="5">{"_BL_COMMENTS"|lang}</th>

                        </tr>

                        <tr>

                            <th style="width:130px;">{"_DATE"|lang}</th>

                            <th>{"_COMMENT"|lang}</th>

                            <th style="width:100px;">{"_BY"|lang}</th>

                            <th style="width:150px;">{"_IP"|lang}</th>

                            <th style="width:80px;">&nbsp;</th>

                        </tr>

                        </thead>

                    </table>

                    {foreach from=$comments item=comment}
                        <form method="POST">

                            <input type="hidden" name="bid" value="{$ban_detail.bid}" />

                            <input type="hidden" name="site" value="{$site}" />

                            <input type="hidden" name="cid" value="{$comment.id}" />

                            <input type="hidden" name="details_x" value="1" />

                            <table frame="box" rules="groups" summary="">

                                <tbody>

                                <!-- Comment List -->

                                <tr>

                                    <td style="width:130px;">{$comment.date|date_format:"%d. %b %Y - %T"}</td>

                                    <td>{$comment.comment}</td>

                                    <td style="width:100px;">{$comment.name}</td>

                                    <td style="width:150px;">{if $smarty.session.ip_view=="yes"}{$comment.addr}{else}<span
                                                style='font-style:italic;font-weight:bold'>{"_HIDDEN"|lang}</span>{/if}</td>

                                    <td class="_right" style="width:80px;">

                                        {if $smarty.session.bans_edit=="yes"}
                                            <img src="images/page_edit.png" title="{"_EDIT"|lang}" border="0"
                                                 style="cursor:pointer;" onClick="NewToggleLayer('comedit_{$comment.id}');" />
                                            <input name="del_comment" type="image" src="templates/{$design}_gfx/page_delete.png"
                                                   border="0"
                                                   onclick="return confirm('{"_DELCOMMENT"|lang}{"_DATALOSS"|lang}');"
                                                   title="{"_DELETE"|lang}" />
                                        {/if}

                                    </td>

                                    <!-- Comment List -->

                        </form>
                        {foreachelse}
                        <div class="_center">{"_NOCOMMENTS"|lang}</div>
                        </tr>

                    {/foreach}

                    </tbody>

                    </table>

                    <div class="clearer">&nbsp;</div>

                </div>
                {if $vars.comment_all=="1" || $smarty.session.loggedin == "true"}
                    <div class="post _center">

                        <form method="post" action="">

                            <input type="button" class="button" name="newcomment" value="{"_NEWCOMMENT"|lang}"
                                   onclick="$('#add_comment').slideToggle('slow');" /><br /><br />

                        </form>

                    </div>
                    <div id="add_comment" class="post" style="display:none;">

                        <tr id="comadd_{$ban_detail.bid}" {if $comment_layer!="1"}style="display: none"{/if}>

                            {*{include file="layer_comadd.tpl"}*}

                        </tr>

                    </div>
                    <tr id="comedit_{$comments.id}" style="display: none">

                        {*{include file="layer_comedit.tpl"}*}

                    </tr>
                {/if}

            {/if}
        </div>
    </div>
    <!-- Modal -->
    <div class="modal fade" id="shareModal" tabindex="-1" role="dialog" aria-labelledby="shareLabel" aria-hidden="true">
        <div class="modal-dialog" role="document">
            <div class="modal-content">
                <div class="modal-header">
                    <h5 class="modal-title" id="shareLabel">{$lang.index.ban.share}</h5>
                    <button type="button" class="close" data-dismiss="modal" aria-label="Close">
                        <span aria-hidden="true">&times;</span>
                    </button>
                </div>
                <div class="modal-body">
                    <pre>{$ban|var_dump}</pre>
                    <div class="row">
                        <div class="col-lg-2 col-md-3 col-sm-4 text-sm-right align-self-center">URL:</div>
                        <div class="col"><input class="form-control" readonly value="{['ban', $ban.bid]|full_url}"></div>
                    </div>
                    <div class="row">
                        <div class="col-lg-2 col-md-3 col-sm-4 text-sm-right align-self-center">HTML:</div>
                        <div class="col"><input class="form-control" readonly value="<a href=&quot;{['ban', $ban.bid]|full_url}&quot;>{$ban.player_nick} @ {$lang.date_format|date:$ban.ban_created} (#{$ban.bid})</a>"></div>
                    </div>
                    <div class="row">
                        <div class="col-lg-2 col-md-3 col-sm-4 text-sm-right align-self-center">BBCode:</div>
                        <div class="col"><input class="form-control" readonly value="[url=&quot;{['ban', $ban.bid]|full_url}&quot;]{$ban.player_nick} @ {$lang.date_format|date:$ban.ban_created} (#{$ban.bid})[/url]"></div>
                    </div>
                </div>
        </div>
    </div>

    <script>
        timer($('.timeleft').text() + '000', '.timeleft');
		$('.do-confirm').click(function () {
			return confirm('{$lang.admin.confirm_message}');
		});
    </script>
{/block}