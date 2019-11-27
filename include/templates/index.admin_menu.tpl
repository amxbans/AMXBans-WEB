<ul class="navbar-nav mr-auto bg-danger">
    {foreach $lang.index.menu as $val} {* TODO: Change to admin menu *}
        <li class="nav-item{if $val == $site->getSite()} active{/if}">
            <a class="nav-link" href="{$val|url:"index.php"}">{$lang.index.titles.$val}</a>
        </li>
    {/foreach}
</ul>