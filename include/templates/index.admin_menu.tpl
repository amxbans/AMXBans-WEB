{if Auth::$logged}
    <ul class="navbar-nav mr-auto">
        {foreach 'admin_menu'|lang as $val}
            <li class="nav-item{if $val == Support\Path::getFakePathWay()} active{/if} dropdown">
                <a class="nav-link text-warning dropdown-toggle" href="#" id="admin{$val@index}" role="button" data-toggle="dropdown"
                   aria-haspopup="true" aria-expanded="false">{'admin_menu_titles'|lang:$val}</a>
                <div class="dropdown-menu" aria-labelledby="admin{$val@index}">
                    {foreach admin_menu_subtitles|lang:$val as $url}
                        <a href="{array($val,$url@key)|url:"admin.php"}"
                           class="dropdown-item{if $url@key == Support\Path::getFakePathWay(1)} active{/if}">{$url}</a>
                    {/foreach}
                </div>
            </li>
        {/foreach}
        <li class="nav-item">
            <a class="nav-link btn btn-outline-danger text-dark" href="{"logout"|url:"admin.php"}">{'logout'|lang}</a>
        </li>
    </ul>
{/if}