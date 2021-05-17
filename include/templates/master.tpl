<!DOCTYPE html>
<html lang="{$lang_locale}" dir="{$lang_html_direction}">
<head>
    <meta charset="utf-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1" />
    <meta name="description" content="A ban system for the HL1 engine to manage multiple server bans." />
    <meta name="keywords" content="amx, bans, amxbans" />
    <meta name="author" content="setoy, shorty, Sleepwalker, indianiso1" />
    {block name="head-metas"}{/block}

    <title>{block name="head-title"}{$app_name}{/block}</title>

    <link rel="stylesheet" href="{"webSources/css/style.css"|res_url}" />
    <link rel="stylesheet" href="{"webSources/css/bootstrap.min.css"|res_url}">
    {block name="head-links"}{/block}

    <script src="{"webSources/js/jquery.min.js"|res_url}"></script>
    <script src="{"webSources/js/layer.js"|res_url}"></script>
    <script src="{"webSources/js/bootstrap.min.js"|res_url}"></script>
</head>

<body id="top">
<div class="wrapper">
    <nav class="navbar navbar-expand-md sticky-top navbar-dark bg-primary">
        <div class="container">
            <div class="collapse navbar-collapse" id="navbarList">
                <ul class="navbar-nav mr-auto">
                    {foreach "menu"|lang as $val}
                        <li class="nav-item{if $val == Support\Path::getFakePathWay()} active{/if}">
                            <a class="nav-link" href="{$val|url:"index.php"}">{'menu_titles'|lang:$val}</a>
                        </li>
                    {/foreach}
                </ul>
                {include file="index.admin_menu.tpl"}
            </div>
            <button class="navbar-toggler" data-toggle="collapse" data-target="#navbarList" aria-controls="navbarList"
                    aria-expanded="false" aria-label="Toggle navigation">
                <span class="navbar-toggler-icon"></span>
            </button>
            <div class="navbar-nav dropdown">
                <a class="nav-item nav-link dropdown-toggle" href="#" id="langDD" role="button" data-toggle="dropdown"
                   aria-haspopup="true" aria-expanded="false">{$lang}</a>
                <div class="dropdown-menu" aria-labelledby="langDD">
                    {foreach $availLangs as $l}
                        <a href="?lang={$l@key}"
                                class="dropdown-item{if $smarty.session.lang == $l} active{/if}">{$l|escape}</a>
                    {/foreach}
                </div>
            </div>
        </div>
    </nav>
    <header class="my-3 my-md-5 text-center">
        {if $config->banner_src}
            <a href="{$config->banner_url}" target="_blank">
                <img src="{"webSources/images/banner/{$config->banner_src}"|res_url}" alt="{$config->banner_url}"
                     title="{$app_name}" />
            </a>
        {/if}
    </header>

    <main class="container">
        {block name="BODY"}{/block}
    </main>
</div>
<footer class="footer d-flex justify-content-between align-items-center">
    <small class="font-italic">
        {'powered_by'|lang} <a href="//amxbans.net" target="_blank" class="text-muted">AMXBans</a> v{$version} &copy; 2020
        <!-- {'design_by'|lang} Bootstrap original -->
    </small>
    {if !$site->user->get() }<a href="{"login"|url}">{'login'|lang}</a>{/if}
</footer>
{block name="scripts"}{/block}
</body>
</html>