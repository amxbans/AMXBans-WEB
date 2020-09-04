{*TODO 7.1: Integrate search into bans *}
{extends 'master.tpl'}
{block name="head-title" prepend}{'menu_titles'|lang:'search'} | {/block}

{block name="BODY"}
    {include "messages.tpl"}
    <div class="card">
        <div class="card-header">{'menu_titles'|lang:'search'}</div>
        <form method="post" class="card-body list-group-flush">
            {Site::makeFormAuth()}
            <div class="form-inline d-flex justify-content-between list-group-item">
                <div class="input-group">
					<span class="input-group-prepend">
						<select name="text" class="input-group-text">
							<option value="name">{'nickname'|lang}</option>
							<option value="steamid">{'steamid'|lang}</option>
							<option value="ip">{'ban_types'|lang:'I'}</option>
							<option value="reason">{'reason'|lang}</option>
						</select>
					</span>
                    <input name="value" class="form-control" />
                </div>
                <button class="btn-outline-info btn" name="search" value="text">{'do_search'|lang}</button>
            </div>

            <div class="form-inline d-flex justify-content-between list-group-item">
                <label class="input-group">
					<span class="input-group-prepend">
						<span class="input-group-text">{'date'|lang}</span>
					</span>
                    <input type="date" name="date" class="form-control" />
                </label>
                <button class="btn-outline-info btn" name="search" value="date">{'do_search'|lang}</button>
            </div>

            <div class="form-inline d-flex justify-content-between list-group-item">
                <label class="input-group">
					<span class="input-group-prepend">
						<span class="input-group-text">{'search_with_bans'|lang}</span>
					</span>
                    <input type="number" name="ban_count" min="2" max="20" class="form-control" />
                    <span class="input-group-append">
						<span class="input-group-text">{'search_prev_bans'|lang}</span>
					</span>
                </label>
                <button class="btn-outline-info btn" name="search" value="ban_count">{'do_search'|lang}</button>
            </div>

            <div class="form-inline d-flex justify-content-between list-group-item">
                <label class="input-group">
					<span class="input-group-prepend">
						<span class="input-group-text">{'admin'|lang}</span>
					</span>
                    <select name="admin" class="form-control">
                        <optgroup label="{'active_admins'|lang}">
                            {foreach from=$amxadmins item=admin}
                                <option value="{$admin.admin_id}">{$admin.admin_nick}</option>
                            {/foreach}
                        </optgroup>
                        <optgroup label="{'other_admins'|lang}">
                            {foreach from=$admins item=admin}
                                <option value="{$admin.steam}">{$admin.nick}</option>
                            {/foreach}
                        </optgroup>
                    </select>
                </label>
                <button class="btn-outline-info btn" name="search" value="admin">{'do_search'|lang}</button>
            </div>

            <div class="form-inline d-flex justify-content-between list-group-item">
                <label class="input-group">
					<span class="input-group-prepend">
						<span class="input-group-text">{'server'|lang}</span>
					</span>
                    {html_options name='server' options=$servers class="form-control"}
                </label>
                <button class="btn-outline-info btn" name="search" value="server">{'do_search'|lang}</button>
            </div>

        </form>
    </div>
    {if isset($bans)}
        <div class="mt-5 h5">{'search_results'|lang}</div>
        <table class="table table-hover table-sm">
            <thead>
            <tr>
                <th>{"date"|lang}</th>
                <th>{"player"|lang}</th>
                <th>{"steamid"|lang}</th>
                <th>{"admin"|lang}</th>
                <th>{"reason"|lang}</th>
                <th>{"length"|lang}</th>
                {if $ban_count}
                    <th>{'times_banned'|lang}</th>{/if}
                <th></th>
            </tr>
            </thead>
            <tbody>
            {foreach $bans as $ban}
                <tr class="list" style="cursor:pointer;" onclick="window.location = '{array('bans', $ban.bid)|url}'">
                    <td>{$ban.ban_created|date_format:$lang_date_format}</td>
                    <td>{$ban.player_nick}</td>
                    <td>{$ban.player_id}</td>
                    <td>{$ban.admin_nick}</td>
                    <td>{$ban.ban_reason}</td>
                    {if $ban_count}
                        <td>{$ban.times_banned}</td>{/if}
                    {if $ban.ban_length>0}
                        <td class="timeleft">{$ban.ban_length*60}</td>
                    {else}
                        <td>{"permanent"|lang}</td>
                    {/if}
                    <td class="text-right"><a href="{array('bans', $ban.bid)|url}">{'menu_titles'|lang:'ban'} &#187;</a>
                    </td>
                </tr>
                {foreachelse}
                <tr>
                    <td colspan="{if $ban_count}8{else}7{/if}" style="text-align:center;">{'empty'|lang}</td>
                </tr>
            {/foreach}
            </tbody>
        </table>
        <script>
			$('.timeleft').each(function () {
				timer(parseInt(this.innerText + '000'), this);
			});
        </script>
    {/if}
{/block}