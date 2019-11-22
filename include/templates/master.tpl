<!DOCTYPE html>
<html lang="{$lang.locale1}" dir="{$lang.html_direction}">
<head>
	<meta charset="utf-8" />
	<meta name="viewport" content="width=device-width, initial-scale=1" />
	<meta name="description" content="A ban system for the HL1 engine to manage multiple server bans."/>
	<meta name="keywords" content="amx, bans, amxbans" />
	<meta name="author" content="setoy, shorty, Sleepwalker, indianiso1" />
	{block name="head-metas"}{/block}

	<title>{block name="head-title"}{$app_name}{/block}</title>

	<link rel="stylesheet" href="{"webSources/css/style.css"|res_url}" />
	{block name="head-links"}{/block}

	<script src="{"webSources/js/jquery.min.js"|res_url}"></script>
	<script src="{"webSources/js/tooltip.js"|res_url}"></script>
	<script src="{"webSources/js/layer.js"|res_url}"></script>
</head>

<body id="top">
<div id="network">
	<div class="center-wrapper">
		<div class="left">
			<ul class="tabbed" id="menu-tabs">
				<li>
					<form method="post" action="" style="padding:5px 8px 0 0;margin:0;">
						<select name="newlang" style="padding:0;margin:0;" onchange="this.form.submit()">
						{foreach from=$lang item="lang"}
							<option value="{$lang|escape}" {if empty($select_lang) && $default_lang == $lang}selected="selected"{/if} {if $select_lang == $lang}selected="selected"{/if}>{$lang|escape}</option>
						{/foreach}
						</select>
					</form>
				</li>
      		</ul>
		</div>
		<div class="right">
			
			<ul class="tabbed" id="admin-tabs">
				{if $smarty.session.loggedin == "true"}
					<li><a href="../../index.php">{"_ADMINAREA"|lang}</a></li>
					<li><a href="../../index.php">{"_LOGOUT"|lang} {$smarty.session.uname}</a></li>
				{else}
					<li>
						<form name="loginform" action="../../index.php" method="post">
							<script type="text/javascript">
								var languser = '{"_USERNAME"|lang}';
								var langpass = '{"_PASSWORD"|lang}';
							</script>
							<input
								type="text" 
								size="17"
								name="user" 
								value="{"_USERNAME"|lang}" 
								onfocus="javascript:if(this.value=languser)this.value='';" 
								
								/>
							<input 
								type="password"
								size="12" 
								name="pass" 
								value="{"_PASSWORD"|lang}" 
								onfocus="javascript:if(this.value=langpass)this.value='';" 
								
								/>
							<input type='checkbox' checked="checked" name='remember' title='{"_REMEMBERME"|lang}' />
							<button type="submit" name="action" id="action" value="Login">{"_LOGIN"|lang}</button>
						</form>
					</li>
				{/if}
			</ul>
			
		</div>
		<div class="clearer">&nbsp;</div>
	</div>
</div>

<div id="site">
	<div class="center-wrapper">
		{if $banner <> ""}
			<div id="header">
				<div id="site-title" style="text-align: center;">
					<a href="{$banner_url}" target="_blank"><img src="images/banner/{$banner}" alt="{$banner_url}" title="{$banner_url}" /></a>
				</div>
			</div>
		{else}
			<div class="spacer">&nbsp;</div>
		{/if}