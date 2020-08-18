{extends 'master.tpl'}
{block name="head-title" prepend}{$lang.index.titles.ban} | {/block}

{block name="BODY"}
    {include "messages.tpl"}
    <div class="card mb-4" id="ban-details">
        <div class="card-header">
            {$lang.index.ban.details}
            <a href="#" class="float-right" data-toggle="modal" data-target="#shareModal">#{$ban.bid}</a>
        </div>
        <div class="card-body">
            {if Auth::$logged}
                <form class="text-right" method="post" action="{['bans', $ban.bid]|url}">
                    {Site::makeFormAuth('DELETE')}
                    {if $can_user.edit_bans || ($can_user.edit_own_bans && $ban.username == Auth::get('username'))}
                        <a href="{['bans', $ban.bid, 'edit']|url}"
                           class="btn btn-outline-primary">{$lang.admin.edit|ucfirst}</a>
                    {/if}
                    {if $can_user.unban || ($can_user.unban_own && $ban.username == Auth::get('username'))}
                        <a href="{['bans', $ban.bid, 'unban']|url}"
                           class="btn btn-outline-warning do-confirm">{$lang.admin.unban|ucfirst}</a>
                    {/if}
                    {if $can_user.delete_bans || ($can_user.delete_own_bans && $ban.username == Auth::get('username'))}
                        <button class="btn btn-outline-danger do-confirm">{$lang.admin.delete|ucfirst}</button>
                    {/if}
                </form>
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
                <div class="col"><span class="timeleft">{$ban.ban_length * 60}</span> {if $ban.expired}<i>
                        [{$lang.index.ban.expired}]</i>{/if}</div>
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
    {if Auth::$logged}
        <div class="card mb-4">
            <div class="card-header">{$lang.index.ban.edit_history}</div>
            <div class="card-body">
                {foreach $ban.logs as $log}
                    <div><b>{$log.admin_nick} @ {$log.created_at->format($lang.date_format)}</b>: {$log.edit_reason}
                    </div>
                    {if !$log@last}
                        <hr />
                    {/if}
                    {foreachelse}
                    {$lang.empty}
                {/foreach}
            </div>
        </div>
    {/if}
    <div class="card mb-4">
        <div class="card-header">{$lang.index.ban.comments_files} <span
                    class="text-muted">({$ban.comments|count})</span></div>
        {if Auth::$logged or $config.allow_unregistered_comments}
            <div class="card-body">
                <button onclick="$('#comment_add').slideToggle()"
                        class="btn btn-outline-primary btn-block">{$lang.index.ban.add_comment}</button>
                <form id="comment_add" class="w-100" style="display: none" enctype="multipart/form-data" method="post">
                    {$site->makeFormAuth()}
                    <hr />
                    <div class="row">
                        <div class="col-sm-6"><input name="name" placeholder="{$lang.nickname|ucfirst}" required
                                                     class="form-control"></div>
                        <div class="col-sm-6"><input name="email" type="email" placeholder="{$lang.e_mail|ucfirst}"
                                                     required class="form-control"></div>
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
                                      placeholder="{$lang.index.ban.comment}"></textarea>
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
                                       placeholder="<- {$lang.index.ban.captcha_placeholder}">
                            {/if}
                        </label>
                        <span class="col-sm-3 col-md-2 col-lg-1 text-right"><button
                                    class="btn btn-primary">{$lang.save}</button></span>
                    </div>
                </form>
            </div>
            <hr />
        {/if}

        {foreach $ban.comments as $comment}
            <div class="card-body pt-1">
                <div>
                    {if $comment.admin}{$lang.administrator|ucfirst}{/if}
                    <span class="font-weight-bold">{$comment.name}</span>
                    {if $comment.comment && $comment.file}
                        {$lang.index.ban.list_comment_file}
                    {elseif $comment.file}
                        {$lang.index.ban.list_file}
                    {else}
                        {$lang.index.ban.list_comment}
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
            <div class="card-body text-center">{$lang.index.ban.no_comments}</div>
        {/foreach}
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
                <div class="row">
                    <div class="col-lg-2 col-md-3 col-sm-4 text-sm-right align-self-center">URL:</div>
                    <div class="col"><input class="form-control" readonly value="{['bans', $ban.bid]|full_url}"></div>
                </div>
                <div class="row">
                    <div class="col-lg-2 col-md-3 col-sm-4 text-sm-right align-self-center">HTML:</div>
                    <div class="col"><input class="form-control" readonly
                                            value="<a href=&quot;{['bans', $ban.bid]|full_url}&quot;>{$ban.player_nick} @ {$lang.date_format|date:$ban.ban_created} (#{$ban.bid})</a>">
                    </div>
                </div>
                <div class="row">
                    <div class="col-lg-2 col-md-3 col-sm-4 text-sm-right align-self-center">BBCode:</div>
                    <div class="col"><input class="form-control" readonly
                                            value="[url=&quot;{['bans', $ban.bid]|full_url}&quot;]{$ban.player_nick} @ {$lang.date_format|date:$ban.ban_created} (#{$ban.bid})[/url]">
                    </div>
                </div>
            </div>
        </div>
    </div>

    <script>
		timer($('.timeleft').text() + '000', '.timeleft');
		$('.do-confirm').click(function () {
			return confirm('{$lang.admin.confirm_message}');
		});

		$('#comment_smilies .btn').click(function () {
			typeInTextarea($('#comment_area'), $(this).data('tag'));
		});
    </script>
{/block}