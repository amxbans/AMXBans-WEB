<!DOCTYPE html>
<html lang="{$lang.LANG_SHORTHAND}">
<head>
	<meta charset="UTF-8">
	<title>{$lang.STEPS.$site} | {$app_name}</title>
	<meta name="cache-control" content="no-cache" />
	<meta name="viewport" content="width=device-width,initial-scale=1" />
	<meta name="theme-color" content="#9cb3b3"/>
	<link href="{"../webSources/css/bootstrap.min.css"|res_url}" rel="stylesheet">
	<link rel="stylesheet" href="{"install.css"|res_url}" />
	<script src="{"../webSources/js/jquery.min.js"|res_url}"></script>
</head>
<body>
<header class="text-center">
	<a href="http://www.amxbans.net" target="_blank" rel="noreferrer"><img src="{'../webSources/images/banner/amxbans.png'|res_url}" alt="AMXBans" />
	</a>
	<h1 class="text-center">{$lang.MAIN_TITLE|replace:':version':$version}</h1>
</header>
<div class="container mt-5">

	<section class="row">
		<aside class="col-md-3">
			<ol class="list-group">
				{foreach from=$lang.STEPS item="lng"}
					<li class="list-group-item {if ($site == $lng@iteration)} active{/if}">{$lng}</li>
				{/foreach}
			</ol>
		</aside>
		<main class="col-md-9">
			<header><h4>{$lang.STEP_TITLES.$site}</h4></header>
			{include file="step$site.tpl"}
		</main>
	</section>
	<footer class="mb-2"></footer>
</div>
</body>
</html>