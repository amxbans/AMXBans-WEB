<div class="main">
	<div class="post">
	{if $smarty.session.bans_add=="yes"}
	<form method="post">
		<table frame="box" rules="groups" summary=""> 
			<thead> 
				<tr>
					<th style="width:200px;">{"_ADDBAN"|lang}</th> 
					<th>&nbsp;</th>
				</tr>
			</thead> 
			<tbody> 
				<tr class="settings_line"> 
					<td class="fat">{"_NICKNAME"|lang}</td> 
					<td><input type="text" size="40" name="name" {if $inputs.name != ""}value="{$inputs.name}"{/if}/></td> 
				</tr> 
				<tr class="settings_line"> 
					<td class="fat">{"_STEAMID"|lang}</td> 
					<td><input type="text" size="40" name="steamid" {if $inputs.steamid != ""}value="{$inputs.steamid}"{else}value="STEAM_0:"{/if}/></td> 
				</tr> 
				<tr class="settings_line"> 
					<td class="fat">{"_IP"|lang}</td> 
					<td><input type="text" size="40" name="ip" {if $inputs.ip != ""}value="{$inputs.ip}"{/if}/></td>  
				</tr> 
				<tr class="settings_line"> 
					<td class="fat">{"_BANTYPE"|lang}</td> 
					<td>
						<select name="ban_type">{html_options output=$banby_output values=$banby_values selected=$inputs.type}</select>
					</td> 
				</tr> 
				<tr class="settings_line"> 
					<td class="fat">{"_REASON"|lang}</td> 
					<td>
						<select name="ban_reason">{html_options output=$reasons values=$reasons selected=$inputs.reason}</select>
							{"_OR"|lang} <br /><input type="checkbox" name="reasoncheck" {if $inputs.reason_custom == 1}checked{/if}/>
							{"_REASON"|lang}: <input type="text" size="30" name="user_reason" {if $inputs.reason_custom == 1}value="{$inputs.reason}"{/if}/>
					</td> 
				</tr> 
				<tr class="settings_line"> 
					<td class="fat">{"_BANLENGHT"|lang}</td> 
					<td>
						<input type="text" size="8" name="ban_length" {if $inputs.length > 0}value="{$inputs.length}"{/if}/> {"_MINS"|lang} 
							{"_OR"|lang} <br /><input type="checkbox" name="perm" {if $inputs.length == 0}checked{/if}/> {"_PERMANENT"|lang}
					</td> 
				</tr> 
			</tbody> 
		</table>
		<div class="_right"><input type="submit" class="button" name="save" value="{"_ADD"|lang}" /></div> 
	</form>
		{else}
			<center><div class="admin_msg">{"_NOACCESS"|lang}</div></center>
		{/if}
		</td>
		<div class="clearer">&nbsp;</div>
	</div>

	<div class="clearer">&nbsp;</div>
</div>