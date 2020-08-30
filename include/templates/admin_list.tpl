{extends 'master.tpl'}
{block name="head-title" prepend}{$lang.index.titles.ban} | {/block}

{block name="BODY"}
{include "messages.tpl"}
<div class="row">
	<div class="col-md-10 col-xl-9">
		<table class="table table-hover">
			<thead>
				<tr>
					<th style="width:18px;">&nbsp;</th>
					<th>{$lang.nickname|ucfirst}</th>
					<th style="width:150px;">{"_STEAMID"|lang}</th>
					<th style="width:150px;">{"_ACCESS"|lang}</th>
					<th style="width:150px;">{"_ADMINSINCE"|lang}</th>
					<th style="width:150px;">{"_ADMINTO"|lang}</th>
				</tr> 
			</thead> 
			<tbody> 
				<!-- Start Loop -->
				{foreach $admins as $admin}
					<tr class="list"> 
						<td class="">{if $admin.steamid}
								<a href="http://steamcommunity.com/profiles/{Steam::GetFriendID($admin.comid|htmlentities:ENT_QUOTES)}" target="_blank"><img src="{'webSources/images/gfx/Steam.png'|res_url}" alt="{"_OPENSTEAMCOMSITE"|lang}"/></a>
						{/if}</td>
						<td>{$admin.nickname}</td>
						<td>{$admin.steamid}</td>
						<td>{$admin.access}</td>
						<td>{$admin.created|date_format:"%d. %b %Y - %T"}</td>
						<td><em>
							{if $admin.expired=="0"}
								<i>{"_UNLIMITED"|lang}</i>
							{else}
								{$admin.expired|date_format:"%d. %b %Y - %T"}
							{/if}
						</em></td> 
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
					{$access}<br>
				{/foreach}
			</div>
				<thead>
				<tr>
					<th>{"_ACCESSPERMS"|lang}</th>
					<th style="width:350px;">{"_ACCESSFLAGS"|lang}</th>
				</tr>
				</thead>
				<tbody>
				<tr>
					<td>
						{"_ACCESS_FLAGS"|lang}
					</td>
					<td class="vtop">
						{"_FLAG_FLAGS"|lang}
					</td>
				</tr>
				</tbody>
			</div>
		</div>
		<!--<a href="javascript:void(0);" class="button" onclick="ToggleLayer('info_access');">{"_INFO_ACCESS"|lang}</a>-->
	</div>

	<div class="clearer">&nbsp;</div>
</div>
{/block}