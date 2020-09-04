{extends 'master.tpl'}
{block name="head-title" prepend}{'menu_titles'|lang:'ban'} | {/block}

{block name="BODY"}
    {include "messages.tpl"}
    <div class="card mb-4" id="ban-details">
        <div class="card-header">
            {'menu_titles'|lang:'ban'}
            <a href="#" class="float-right" data-toggle="modal" data-target="#shareModal">#{$ban.bid}</a>
        </div>
        <div class="card-body">
            {if Auth::$logged}
                <form class="text-right" method="post" action="{['bans', $ban.bid]|url}">
                    {Site::makeFormAuth('DELETE')}
                    {if $can_user.edit_bans || ($can_user.edit_own_bans && $ban.username == Auth::get('username'))}
                        <a href="{['bans', $ban.bid, 'edit']|url}"
                           class="btn btn-outline-primary">{'edit'|lang}</a>
                    {/if}
                    {if $can_user.unban || ($can_user.unban_own && $ban.username == Auth::get('username'))}
                        <a href="{['bans', $ban.bid, 'unban']|url}"
                           class="btn btn-outline-warning do-confirm">{'unban_player'|lang}</a>
                    {/if}
                    {if $can_user.delete_bans || ($can_user.delete_own_bans && $ban.username == Auth::get('username'))}
                        <button class="btn btn-outline-danger do-confirm">{'delete'|lang}</button>
                    {/if}
                </form>
            {/if}
            <div class="row">
                <div class="col-lg-3 col-sm-5 text-sm-right">{'nickname'|lang}</div>
                <div class="col">{$ban.player_nick|escape}</div>
            </div>
            <div class="row">
                <div class="col-lg-3 col-sm-5 text-sm-right">{'steamid'|lang}</div>
                <div class="col">{$ban.player_id}</div>
            </div>
            {if $ban.com_id}
                <div class="row">
                    <div class="col-lg-3 col-sm-5 text-sm-right">{'steamcomid'|lang}</div>
                    <div class="col"><a href="http://steamcommunity.com/profiles/{$ban.com_id}">{$ban.com_id}</a></div>
                </div>
            {/if}
            {if $can_user.view_ips && $ban.player_ip}
                <div class="row">
                    <div class="col-lg-3 col-sm-5 text-sm-right">{'ip'|lang}</div>
                    <div class="col">{$ban.player_ip}</div>
                </div>
            {/if}
            <div class="row">
                <div class="col-lg-3 col-sm-5 text-sm-right">{'ban_type'|lang}</div>
                <div class="col">{'ban_types'|lang:$ban.ban_type}</div>
            </div>
            <div class="row">
                <div class="col-lg-3 col-sm-5 text-sm-right">{'reason'|lang}</div>
                <div class="col">{$ban.ban_reason}</div>
            </div>
            <div class="row">
                <div class="col-lg-3 col-sm-5 text-sm-right">{'invoked'|lang}</div>
                <div class="col">{$ban.ban_created|date_format:$lang_date_format}</div>
            </div>
            <div class="row">
                <div class="col-lg-3 col-sm-5 text-sm-right">{'length'|lang}</div>
                <div class="col"><span class="timeleft">{$ban.ban_length * 60}</span> {if $ban.expired}<i>
                        [{'expired'|lang}]</i>{/if}</div>
            </div>
            <div class="row">
                <div class="col-lg-3 col-sm-5 text-sm-right">{'admin'|lang}</div>
                <div class="col">{$ban.admin_nick} {if $can_user.view_admins}({$ban.nickname}{if $can_user.view_ips}, {$ban.admin_id}{/if}){/if}</div>
            </div>
            <div class="row">
                <div class="col-lg-3 col-sm-5 text-sm-right">{'server'|lang}</div>
                <div class="col">{if $ban.server_name == 'website'}{'web'|lang}{else}{$ban.server_name}{/if}</div>
            </div>
        </div>
        {*{include file="layer_banedit.tpl"}*}
    </div>
    {if Auth::$logged}
        <div class="card mb-4">
            <div class="card-header">{'edit_history'|lang}</div>
            <div class="card-body">
                {foreach $ban.logs as $log}
                    <div><b>{$log.admin_nick} @ {$log.created_at->format($lang_date_format)}</b>: {$log.edit_reason}
                    </div>
                    {if !$log@last}
                        <hr />
                    {/if}
                    {foreachelse}
                    {'empty'|lang}
                {/foreach}
            </div>
        </div>
    {/if}
    <div class="card mb-4">
        <div class="card-header">{'comments_files'|lang} <span
                    class="text-muted">({$ban.comments|count})</span></div>
        {if Auth::$logged or $config.allow_unregistered_comments}
            <div class="card-body">
                <button onclick="$('#comment_add').slideToggle()"
                        class="btn btn-outline-primary btn-block">{'add_comment'|lang}</button>
                <form id="comment_add" class="w-100" style="display: none" enctype="multipart/form-data" method="post">
                    {$site->makeFormAuth()}
                    <hr />
                    <div class="row">
                        <div class="col-sm-6"><input name="name" placeholder="{'nickname'|lang}"
                                                     class="form-control" value="{'name'|input}"></div>
                        <div class="col-sm-6"><input name="email" type="email" placeholder="{'email'|lang}"
                                                     class="form-control" value="{'email'|input}"></div>
                    </div>
                    <div id="comment_smilies" class="w-100">
                        {foreach $config->smilies as $tag => $info}
                            <button type="button" data-tag="{$tag}" title="{$info.1}" class="btn btn-link p-0 m-1"
                                    tabindex="-1">
                                <img
                                        src="{"webSources/images/emoticons/{$info[0]}"|res_url}" alt="{$tag}">
                            </button>
                        {/foreach}
                    </div>
                    <label class="w-100">
                            <textarea id="comment_area" name="comment" class="form-control" rows="6"
                                      placeholder="{'comment'|lang}">{"comment"|input}</textarea>
                    </label>

                    <div class="form-group">
                        <input name="file" type="file" class="form-control-file">
                    </div>
                    <div class="row">
                        <label class="col-sm form-group input-group">
                            {if !Auth::$logged}
                                <span class="input-group-prepend">
                                <img src="{Captcha::makeImage()|res_url}" alt="Captcha code"
                                     class="input-group-prepend">
                            </span>
                                <input class="form-control" name="captcha" autocomplete="off"
                                       placeholder="<- {'captcha_placeholder'|lang}">
                            {/if}
                        </label>
                        <span class="col-sm-3 col-md-2 col-lg-1 text-right"><button
                                    class="btn btn-primary">{'save'|lang}</button></span>
                    </div>
                </form>
            </div>
            <hr />
        {/if}

        {foreach $ban.comments as $comment}
            <div class="card-body pt-1">
                <div>
                    {if $comment.admin}{'admin'|lang}{/if}
                    <span class="font-weight-bold">{$comment.name}</span>
                    {if $comment.comment && $comment.file}
                        {'list_comment_file'|lang}
                    {elseif $comment.file}
                        {'list_file'|lang}
                    {else}
                        {'list_comment'|lang}
                    {/if}
                </div>
                <hr class="mt-1" />
                <div>
                    {if $comment.file}
                        <a href="{$comment.file|res_url}" target="_blank" class="card px-3 py-1 d-inline-block"
                           style="border-radius: 50px;font-size: 12px;">
                            <img src="{"webSources/images/page.png"|res_url}" alt="File" height="16px">
                            {$comment.file|basename|upper}
                        </a>
                    {/if}
                </div>
                <p>{$comment.comment}</p>
            </div>
            {if !$comment@last}
                <hr />
            {/if}
            {foreachelse}
            <div class="card-body text-center">{'no_comments'|lang}</div>
        {/foreach}
    </div>
    <!-- Modal -->
    <div class="modal fade" id="shareModal" tabindex="-1" role="dialog" aria-labelledby="shareLabel" aria-hidden="true">
    <div class="modal-dialog" role="document">
        <div class="modal-content">
            <div class="modal-header">
                <h5 class="modal-title" id="shareLabel">{'share_ban'|lang}</h5>
                <button type="button" class="close" data-dismiss="modal" aria-label="Close">
                    <span aria-hidden="true">&times;</span>
                </button>
            </div>
            <div class="modal-body">
                <div class="row">
                    <div class="col-lg-2 col-md-3 col-sm-4 text-sm-right align-self-center">URL:</div>
                    <div class="col"><input class="form-control" readonly value="{['bans', $ban.bid]|full_url}"></div>
                </div>
                <div class="row">
                    <div class="col-lg-2 col-md-3 col-sm-4 text-sm-right align-self-center">HTML:</div>
                    <div class="col"><input class="form-control" readonly
                                            value="<a href=&quot;{['bans', $ban.bid]|full_url}&quot;>{$ban.player_nick} @ {$ban.ban_created|date_format:$lang_date_format} (#{$ban.bid})</a>">
                    </div>
                </div>
                <div class="row">
                    <div class="col-lg-2 col-md-3 col-sm-4 text-sm-right align-self-center">BBCode:</div>
                    <div class="col"><input class="form-control" readonly
                                            value="[url=&quot;{['bans', $ban.bid]|full_url}&quot;]{$ban.player_nick} @ {$ban.ban_created|date_format:$lang_date_format} (#{$ban.bid})[/url]">
                    </div>
                </div>
            </div>
        </div>
    </div>

    <script>
		timer($('.timeleft').text() + '000', '.timeleft');
		$('.do-confirm').click(function () {
			return confirm('{'confirm_message'|lang}');
		});

		$('#comment_smilies .btn').click(function () {
			typeInTextarea($('#comment_area'), $(this).data('tag'));
		});
    </script>
{/block}