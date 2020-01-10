{if User::$logged}
    <ul class="navbar-nav mr-auto">
        {foreach $lang.admin.menu as $val}
            <li class="nav-item{if $val == $site->getSite()} active{/if} dropdown">
                <a class="nav-link text-warning dropdown-toggle" href="#" id="admin{$val@index}" role="button" data-toggle="dropdown"
                   aria-haspopup="true" aria-expanded="false">{$lang.admin.titles.$val}</a>
                <div class="dropdown-menu" aria-labelledby="admin{$val@index}">
                    {foreach $lang.admin.subtitles.$val as $url}
                        <a href="{array($val,$url@key)|url:"admin.php"}" class="dropdown-item">{$url}</a>
                    {/foreach}
                </div>
            </li>
        {/foreach}
        <li class="nav-item">
            <a class="nav-link btn btn-outline-danger text-dark" href="{"logout"|url:"admin.php"}">{$lang.admin.titles.logout}</a>
        </li>
    </ul>
{/if}