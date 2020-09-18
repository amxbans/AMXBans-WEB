	<td id="main" valign="top" >
		{if $smarty.session.permissions_edit == "yes"}
			<span class="title">{"_ADMINLEVELSETTINGS"|lang}</span>
			<table width="60%" align="center"><tr><td>
				{foreach from=$levels item=levels}
				<form method="POST">
				<input type="hidden" name="lid" value="{$levels.level}"></input>
				<fieldset><legend><span class="title">{"_LEVEL"|lang} #{$levels.level}</span></legend>
				<table style="border:1px;" width="100%">
					<tr class="htabletop">
						<td><b>{"_LEVEL"|lang}</b></td><td colspan="6" align="center"><b>{"_BANS"|lang}</b></td><td colspan="2"><b>{"_AMXADMINS"|lang}</b></td><td>&nbsp</td>
							
					</tr>
					<tr class="htablebottom">
						<td>&nbsp</td>
						<td>{"_ADD"|lang}</td><td>{"_EDIT"|lang}</td><td>{"_DELETE"|lang}</td><td>{"_LEVELUNBAN"|lang}</td><td>{"_LEVELIMPORT"|lang}</td><td>{"_LEVELEXPORT"|lang}</td>
						<td>{"_LEVELVIEW"|lang}</td><td>{"_EDIT"|lang}</td><td>&nbsp</td>
					</tr>
					<tr>
						<td rowspan="4" style="{if $levels.level==$smarty.session.level}background-color:#00aa00;{/if}text-align:center;"><b>{$levels.level}</b></td>
						<td>{html_options name=bans_add values=$choose1 output=$output1|lang selected=$levels.bans_add}</td>
						<td>{html_options name=bans_edit values=$choose2 output=$output2|lang selected=$levels.bans_edit}</td>
						<td>{html_options name=bans_delete values=$choose2 output=$output2|lang selected=$levels.bans_delete}</td>
						<td>{html_options name=bans_unban values=$choose2 output=$output2|lang selected=$levels.bans_unban}</td>
						<td>{html_options name=bans_import values=$choose1 output=$output1|lang selected=$levels.bans_import}</td>
						<td>{html_options name=bans_export values=$choose1 output=$output1|lang selected=$levels.bans_export}</td>
						<td>{html_options name=amxadmins_view values=$choose1 output=$output1|lang selected=$levels.amxadmins_view}</td>
						<td>{html_options name=amxadmins_edit values=$choose1 output=$output1|lang selected=$levels.amxadmins_edit}</td>
						<td rowspan="4" {if $levels.level==$smarty.session.level}style="background-color: #00aa00;" {/if}>
								<input style="margin:0 auto;display:block;" type="submit" class="button" name="save" value="{"_SAVE"|lang}" {if $smarty.session.permissions_edit !== "yes"}disabled{/if} />
								{if ($levels.level == $level_max && $levels.level > 1)}
								<input style="margin:0 auto;display:block;" type="submit" class="button" name="del" value="{"_DELETE"|lang}" onclick="return confirm('{"_DELLEVEL"|lang}');" {if $smarty.session.permissions_edit !== "yes"}disabled{/if} />
								{/if}
							</td>
					</tr><tr class="htabletop">
						<td colspan="2"><b>{"_WEBADMINS"|lang}</b></td><td colspan="2"><b>{"_WEBSETTINGS"|lang}</b></td><td colspan="4"><b>{"_OTHER"|lang}</b></td>
					</tr><tr class="htablebottom">
						<td>{"_LEVELVIEW"|lang}</td><td>{"_EDIT"|lang}</td>
						<td>{"_LEVELVIEW"|lang}</td><td>{"_EDIT"|lang}</td>
						<td>{"_PERM"|lang}</td><td>{"_DBPRUNE"|lang}</td><td>{"_SERVEREDIT"|lang}</td><td>{"_VIEWIP"|lang}</td>
					</tr><tr align="center">
						<td>{html_options name=webadmins_view values=$choose1 output=$output1|lang selected=$levels.webadmins_view}</td>
						<td>{html_options name=webadmins_edit values=$choose1 output=$output1|lang selected=$levels.webadmins_edit}</td>
						<td>{html_options name=websettings_view values=$choose1 output=$output1|lang selected=$levels.websettings_view}</td>
						<td>{html_options name=websettings_edit values=$choose1 output=$output1|lang selected=$levels.websettings_edit}</td>
						
						<td>{html_options name=permissions_edit values=$choose1 output=$output1|lang selected=$levels.permissions_edit}</td>
						<td>{html_options name=prune_db values=$choose1 output=$output1|lang selected=$levels.prune_db}</td>
						<td>{html_options name=servers_edit values=$choose1 output=$output1|lang selected=$levels.servers_edit}</td>
						<td>{html_options name=ip_view values=$choose1 output=$output1|lang selected=$levels.ip_view}</td>
					</tr>
				</table></fieldset>
				<div class="clearer">&nbsp</div>
				</form>
				{/foreach}
				<form method="POST">
					<div class="_right">
						<input type="submit" class="button" name="new" value="{"_NEWLEVEL"|lang}" {if $smarty.session.permissions_edit !== "yes"}disabled{/if} />
					</div>
				</form>
			{else}
				<center><div class="admin_msg">{"_NOACCESS"|lang}</div></center>
			{/if}
			{if $msg}<br /><div class="notice">{$msg|lang}</div>{/if}
			</td></tr></table>
		</td>
	</tr>
</table>