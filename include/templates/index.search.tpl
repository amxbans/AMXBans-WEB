{*TODO 7.1: Integrate search into bans *}
{extends 'master.tpl'}
{block name="head-title" prepend}{'menu_titles'|lang:'search'} | {/block}

{block name="BODY"}
	{include "messages.tpl"}
	<div class="card">
		<div class="card-header">{'menu_titles'|lang:'search'}</div>
		<div class="card-body list-group-flush">
			<form method="post" class="form-inline d-flex justify-content-between list-group-item">
				<div class="input-group">
					<span class="input-group-prepend">
						<select name="text" class="input-group-text">
							<option value="name">{'nickname'|lang}</option>
							<option value="steamid">{'steamid'|lang}</option>
							<option value="ip">{'ban_types'|lang:'I'}</option>
							<option value="reason">{'reason'|lang}</option>
						</select>
					</span>
					<input name="text" class="form-control" />
				</div>
				<button class="btn-outline-info btn">{'do_search'|lang}</button>
			</form>

			<form method="post" class="form-inline d-flex justify-content-between list-group-item">
				<div class="input-group">
					<span class="input-group-prepend">
						<span class="input-group-text">{'date'|lang}</span>
					</span>
					<input type="date" name="date" class="form-control" />
				</div>
				<button class="btn-outline-info btn">{'do_search'|lang}</button>
			</form>

			<form method="post" class="form-inline d-flex justify-content-between list-group-item">
				<div class="input-group">
					<span class="input-group-prepend">
						<span class="input-group-text">{'date'|lang}</span>
					</span>
					<input type="date" name="date" class="form-control" />
				</div>
				<button class="btn-outline-info btn">{'do_search'|lang}</button>
			</form>

			<table frame="box" rules="groups" summary="">
				<tbody>
				<tr>
					<form method="post" style="display:inline;">
						<td class="fat">{"_PLAYERSWITH"|lang}</td>
						<td>
							<select name='timesbanned'>
								<option value='2'>2</option>
								<option value='3'>3</option>
								<option value='4'>4</option>
								<option value='5'>5</option>
								<option value='6'>6</option>
								<option value='7'>7</option>
								<option value='8'>8</option>
								<option value='9'>9</option>
								<option value='10'>10</option>
							</select>
							{"_MOREBANSHIS"|lang}
						</td>
						<td><input type="submit" class="button" name="submit" value="{"_SEARCH"|lang}"/></td>
					</form>
				</tr>
				<tr>
					<td class="fat">{"_ADMIN"|lang}</td>
					<td>
						<form method="post" name="form_admin" style="display:inline;">
							<select name="admin" size="1">
								<optgroup label="{"_AMXADMINS"|lang}">
									{foreach from=$amxadmins item=admin}
										<option value="{$admin.admin_id}">{$admin.admin_nick}</option>
									{/foreach}
								</optgroup>
								<optgroup label="{"_OTHER"|lang} {"_ADMINS"|lang}">
									{foreach from=$admins item=admin}
										<option value="{$admin.steam}">{$admin.nick}</option>
									{/foreach}
								</optgroup>
							</select>
						</form>
					</td>
					<td><form method="post"><input type="button" class="button" onclick="form_admin.submit();" value="{"_SEARCH"|lang}"/></form></td>
				</tr>
				<tr>
					<td class="fat">{"_SERVER"|lang}</td>
					<td>
						<form method="post" name="form_server" style="display:inline;">
							{html_options name=server options=$servers|lang}
						</form>
					</td>
					<td><form method="post"><input type="button" class="button" onclick="form_server.submit();" value="{"_SEARCH"|lang}"/></form></td>
				</tr>
				</tbody>
			</table>
			<div class="clearer">&nbsp;</div>
		</div>

		<div class="clearer">&nbsp;</div>
	</div>


	{if isset($msg)}<center class="admin_msg">{$msg|lang}</center><br />{/if}
	{if isset($search_done)}
		<fieldset><legend><span class="title">{"_SEARCHRESULT"|lang}</span></legend>
		<table width="95%" cellpadding="2">
		<tr><td>
		<table width="80%" cellpadding="2">
			<tr>
				<td width="100%" colspan="6"><span style="font-weight:bold;color:red">{"_ACTIVEBANS"|lang} ({$ban_list_aktiv_count})</span></td>
			</tr>
			<tr class="htable">
				<td class="fat" width="1%">{"_DATE"|lang}</td>
				<td class="fat" width="24%">{"_PLAYER"|lang}</td>
				<td class="fat" width="1%">{"_STEAMID"|lang}</td>
				<td class="fat" width="24%">{"_ADMIN"|lang}</td>
				<td class="fat" width="24%">{"_REASON"|lang}</td>
				<td class="fat" width="1%">{"_LENGHT"|lang}</td>
			</tr>
			{foreach from=$ban_list_aktiv item=ban}
				<form name="details" method="POST" action="../../index.php">
					<tr class="list" style="cursor:pointer;" onClick="NewToggleLayer('layer_{$ban.bid}');">
						<td>{$ban.ban_created|date_format:"%d.%m.%Y"}</td>
						<td>{$ban.player_nick}</td>
						<td>{$ban.player_id}</td>
						<td>{$ban.admin_nick}</td>
						<td>{$ban.ban_reason}</td>
						<td nowrap>{if $ban.ban_length>0}{$ban.ban_length*60}{else}{"_PERMANENT"|lang}{/if}</td>
					</tr>
					<tr id="layer_{$ban.bid}" style="display: none">
						<td colspan=10><div style="display: none">
								<input type="hidden" name="bid" value="{$ban.bid}" />
								<table width="90%" class="table_details" cellspacing="0">
									<tr>
										<td class="table_details_head" width="20%"><b>{"_BANDETAILS"|lang}</b></td>
										<td align="right" class="table_details_head">
											<input name="details" type="image" src="images/page.png" border="0" title="{"_DETAILS"|lang}"/>
										</td>
									</tr>
									<tr><td width="15%"><b>{"_NICKNAME"|lang}:</b></td><td>{$ban.player_nick}</td></tr>
									<tr><td><b>{"_STEAMID"|lang}:</b></td><td>{if $ban.player_id <> ""}{$ban.player_id}{else}{"_NOSTEAMID"|lang}{/if}</td></tr>
									<tr><td><b>{"_STEAMCOMID"|lang}:</b></td><td>
											{if $ban.player_id <> ""}
												<a href="http://steamcommunity.com/profiles/{$ban.player_comid}" target="_blank">{$ban.player_comid}</a>
											{else}
												{"_NOTAVAILABLE"|lang}
											{/if}</td></tr>
									<tr><td><b>{"_IP"|lang}:</b></td><td>
											{if $smarty.session.ip_view=="yes"}
												{if $ban.player_ip}{$ban.player_ip}{else}<i>{"_NOTAVAILABLE"|lang}</i>{/if}
											{else}<i>{"_HIDDEN"|lang}</i>
											{/if}</td></tr>
									<tr><td><b>{"_BANTYPE"|lang}:</b></td><td>{if $ban.ban_type=="S"}{"_STEAMID"|lang}
											{elseif $ban.ban_type=="SI"}{"_STEAMID&IP"|lang}
											{else}{"_NOTAVAILABLE"|lang}{/if}
										</td></tr>
									<tr><td><b>{"_REASON"|lang}:</b></td><td>{$ban.ban_reason}</td></tr>
									<tr><td><b>{"_INVOKED"|lang}:</b></td><td>{$ban.ban_created|date_format:"%d. %b %Y - %T"}</td></tr>
									<tr><td><b>{"_BANLENGHT"|lang}:</b></td><td>{if $ban.ban_length==0}{"_PERMANENT"|lang}{else}{$ban.ban_length} {"_MINS"|lang}{/if}</td></tr>
									<tr><td><b>{"_EXPIRES"|lang}:</b></td><td>
											{if $ban.ban_length==0}<i>{"_NOTAPPLICABLE"|lang}</i>{else}{$ban.ban_end|date_format:"%d. %b %Y - %T"}
												{if $ban.ban_end < $smarty.now} ({"_ALREADYEXP"|lang}){/if}
											{/if}
										</td></tr>
									<tr><td><b>{"_BANBY"|lang}:</b></td><td>{$ban.admin_nick}</td></tr>
									<tr><td><b>{"_BANON"|lang}:</b></td><td>{if $ban.server_name == "website"}{"_WEB"|lang}{else}{$ban.server_name}{/if}</td></tr>
									<tr><td><b>{"_TOTALEXPBANS"|lang}:</b></td><td>{$ban.bancount}</td></tr>
								</table>
							</div></td>

					</tr></form>
			{/foreach}
		</table>
		<br />
		<table width="80%" align="center" border="1" cellpadding="2">
			<tr class="search_head2">
				<td width="100%" colspan="6"><span style="font-weight:bold;color:green">{"_EXPIREDBANS"|lang}  ({$ban_list_exp_count})</span></td>
			</tr>
			<tr class="htable">
				<td class="fat" width="1%" nowrap>{"_DATE"|lang}</td>
				<td class="fat" width="24%">{"_PLAYER"|lang}</td>
				<td class="fat" width="1%" nowrap>{"_STEAMID"|lang}</td>
				<td class="fat" width="24%">{"_ADMIN"|lang}</td>
				<td class="fat" width="24%">{"_REASON"|lang}</td>
				<td class="fat" width="1%" nowrap>{"_LENGHT"|lang}</td>
			</tr>
			{foreach from=$ban_list_exp item=ban}
				<form name="details" method="POST" action="../../index.php">
					<tr class="list"  style="cursor:pointer;" onClick="NewToggleLayer('layer_{$ban.bid}');">
						<td>{$ban.ban_created|date_format:"%d.%m.%Y"}</td>
						<td>{$ban.player_nick}</td>
						<td>{$ban.player_id}</td>
						<td>{$ban.admin_nick}</td>
						<td>{$ban.ban_reason}</td>
						<td nowrap>{if $ban.ban_length>0}{$ban.ban_length*60}{else}{"_PERMANENT"|lang}{/if}</td>
					</tr>
					<tr id="layer_{$ban.bid}" style="display: none">
						<td class="table_list" colspan=10><div style="display: none">
								<input type="hidden" name="bid" value="{$ban.bid}" />
								<table width="90%" class="table_details" cellspacing="0">
									<tr>
										<td class="table_details_head" width="20%"><b>{"_BANDETAILS"|lang}</b></td>
										<td align="right" class="table_details_head">
											<input name="details" type="image" src="images/page.png" border="0" title="{"_DETAILS"|lang}"/>
										</td>
									</tr>
									<tr><td width="15%"><b>{"_NICKNAME"|lang}:</b></td><td>{$ban.player_nick}</td></tr>
									<tr><td><b>{"_STEAMID"|lang}:</b></td><td>{if $ban.player_id <> ""}{$ban.player_id}{else}{"_NOSTEAMID"|lang}{/if}</td></tr>
									<tr><td><b>{"_STEAMCOMID"|lang}:</b></td><td>
											{if $ban.player_id <> ""}
												<a href="http://steamcommunity.com/profiles/{$ban.player_comid}" target="_blank">{$ban.player_comid}</a>
											{else}
												{"_NOTAVAILABLE"|lang};
											{/if}</td></tr>

									<tr><td><b>{"_IP"|lang}:</b></td><td>{if $smarty.session.ip_view=="yes"}{$ban.player_ip}{else}<i>{"_HIDDEN"|lang}</i>{/if}</td></tr>
									<tr><td><b>{"_BANTYPE"|lang}:</b></td><td>{if $ban.ban_type=="S"}{"_STEAMID"|lang}
											{elseif $ban.ban_type=="SI"}{"_STEAMID&IP"|lang}
											{else}{"_NOTAVAILABLE"|lang}{/if}
										</td></tr>
									<tr><td><b>{"_REASON"|lang}:</b></td><td>{$ban.ban_reason}</td></tr>
									<tr><td><b>{"_INVOKED"|lang}:</b></td><td>{$ban.ban_created|date_format:"%d. %b %Y - %T"}</td></tr>
									<tr><td><b>{"_BANLENGHT"|lang}:</b></td><td>{if $ban.ban_length==0}{"_PERMANENT"|lang}{else}{$ban.ban_length} {"_MINS"|lang}{/if}</td></tr>
									<tr><td><b>{"_EXPIRES"|lang}:</b></td><td>
											{if $ban.ban_length==0}<i>{"_NOTAPPLICABLE"|lang}</i>{else}{$ban.ban_end|date_format:"%d. %b %Y - %T"}
												{if $ban.ban_end < $smarty.now} ({"_ALREADYEXP"|lang}){/if}
											{/if}
										</td></tr>
									<tr><td><b>{"_BANBY"|lang}:</b></td><td>{$ban.admin_nick}</td></tr>
									<tr><td><b>{"_BANON"|lang}:</b></td><td>{if $ban.server_name == "website"}{"_WEB"|lang}{else}{$ban.server_name}{/if}</td></tr>
									<tr><td><b>{"_TOTALEXPBANS"|lang}:</b></td><td>{$ban.bancount}</td></tr>
								</table>
							</div></td>
					</tr></form>
			{/foreach}
		</table>
	{/if}
	</td></tr>
	</table></fieldset>
{/block}