<!DOCTYPE html>
<html lang="{$lang.locale}" dir="{$lang.html_direction}">
<head>
    <meta charset="utf-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1" />
    <meta name="description" content="A ban system for the HL1 engine to manage multiple server bans." />
    <meta name="keywords" content="amx, bans, amxbans" />
    <meta name="author" content="setoy, shorty, Sleepwalker, indianiso1" />
    {block name="head-metas"}{/block}

    <title>{block name="head-title"}{$app_name}{/block}</title>

    {*    <link rel="stylesheet" href="{"webSources/css/style.css"|res_url}"/>*}
    <link rel="stylesheet" href="{"webSources/css/bootstrap.min.css"|res_url}">
    {block name="head-links"}{/block}

    <script src="{"webSources/js/jquery.min.js"|res_url}"></script>
    {*	<script src="{"webSources/js/tooltip.js"|res_url}"></script>*}
    {*	<script src="{"webSources/js/layer.js"|res_url}"></script>*}
    <script src="{"webSources/js/bootstrap.min.js"|res_url}"></script>
</head>

<body id="top">
<nav class="navbar navbar-expand-md sticky-top navbar-dark bg-primary">
    <div class="mr-2"> {*TODO: this point unfinished; change back to inline list*}
        <a class="nav-item nav-link dropdown-toggle" href="#" id="langDD" role="button" data-toggle="dropdown"
           aria-haspopup="true" aria-expanded="false">
            <img src="{'webSources/images/world.svg'|res_url}" data-author="Smashicons"
                 data-author-url="https://www.flaticon.com/authors/smashicons" alt="LANG" />
        </a>
        <form class="dropdown-menu" aria-labelledby="langDD" method="post">
            {foreach $availLangs as $l}
                <button name="lang" value="{$l|escape}"
                        class="dropdown-item{if $smarty.session.lang == $l} active{/if}">{$l|escape|ucfirst}</button>
            {/foreach}
        </form>
    </div>
    <button class="navbar-toggler" data-toggle="collapse" data-target="#navbarList" aria-controls="navbarList"
            aria-expanded="false" aria-label="Toggle navigation">
        <span class="navbar-toggler-icon"></span>
    </button>
    <div class="container d-block d-md-flex">
        <div class="collapse navbar-collapse" id="navbarList">
            <ul class="navbar-nav mr-auto">
                {foreach $lang.index.menu as $val}
                    <li class="nav-item{if $val == $site->getSite()} active{/if}">
                        <a class="nav-link" href="{$val|url:"index.php"}">{$lang.index.titles.$val}</a>
                    </li>
                {/foreach}
            </ul>
            {if User::get()}
                {include file="index.admin_menu.tpl"}
                <div class="navbar-nav"><a class="nav-item nav-link"
                                           href="{"logout"|url:"admin.php"}">{$lang.admin.titles.logout}</a></div>
            {else}
                <div class="navbar-nav"><a class="nav-item nav-link"
                                           href="{"login"|url:"index.php"}">{$lang.index.titles.login}</a></div>
            {/if}
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
</body>
</html>