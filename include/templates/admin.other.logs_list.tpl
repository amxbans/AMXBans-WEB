		<td id="main" valign="top">
		{if $smarty.session.amxadmins_view == "yes"}
			<span class="title">{"_LOGS"|lang}</span>
			<table width="95%"><tr><td>
				<tr>
				<td>
					<table border="1" width="50%">
						<tr class="htable">
							<td colspan="3"><b>{"_FILTER"|lang}</b></td>
						</tr>
						<form method="POST" name="sort">
							<tr class="settings_line" colspan="3"><td>{"_USER"|lang}</td><td>{html_options name=username options=$usernames selected=$username_checked}</td></tr>
							<tr class="settings_line" colspan="3">
									<td>{"_ACTION"|lang}</td><td>{html_options name=action options=$actions selected=$action_checked}</td>
									<td colspan="3"><input type="submit" class="button" name="sort" value="{"_GO"|lang}" /></td>
							</tr>
						</form>
					</table><br />
					<table class="admin_list" border="1" width="50%">
						<tr class="htable">
							<td colspan="3"><b>{"_DELETE"|lang}</b></td>
						</tr>
						<form method="POST" name="clear">
							<tr class="settings_line"><td>{"_ALL"|lang}</td><td width="1%"><input type="submit" class="button" name="delall" onclick="return confirm('{"_DELLOGSALL"|lang}{"_DATALOSS"|lang}');" value="{"_DELETE"|lang}" /></td></tr>
							<tr class="settings_line"><td>{"_OLDERTHEN"|lang} <input type="text" size="3" name="days" > {"_DAYS"|lang}</td><td><input size="1" type="submit" class="button" name="delolder" onclick="return confirm('{"_DELLOGS"|lang}{"_DATALOSS"|lang}');" value="{"_DELETE"|lang}" /></td></tr>	
						</form>
					</table>
					<br />
					<table border="1" width="100%">
						<tr class="htabletop">
							<td colspan="4"><b>{"_ACTIONLOGS"|lang}</b></td>
						</tr>
						<tr class="htablebottom">
							<td width="1%"><nobr>{"_INVOKED"|lang}</nobr></td>
							<td width="1%" align="center">{"_USER"|lang}</td>
							<td width="1%" align="center"><nobr>{"_ACTION"|lang}</nobr></td>
							<td>{"_REMARKS"|lang}</td>
						</tr>
						{foreach from=$logs item=logs}
							<tr class="list">
								<td width="1%"><nobr>{$logs.timestamp|date_format:"%d.%m.%Y - %T"}</nobr></td>
								<td width="1%" align="center">{$logs.username|escape}</td>
								<td width="1%" align="center"><nobr>{$logs.action|escape}</nobr></td>
								<td>{$logs.remarks|escape}</td>
							</tr>
						{/foreach}
					</table>
				</td>
				</tr>
			</table>
				{if $msg}<center><div class="notice">{$msg|lang}<br /></div></center>{/if}
		{else}
			<center><div class="admin_msg">{"_NOACCESS"|lang}</div></center>
		{/if}
		</td>