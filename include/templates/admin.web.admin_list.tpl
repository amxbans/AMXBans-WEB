{extends file="master.tpl"}
{block name="head-title" prepend}{'admin_menu_subtitles'|lang:'web':'users'} - {'admin_menu_titles'|lang:'index'} | {/block}

{block name="BODY"}
    {include file="messages.tpl"}
    {if Auth::hasPermission('webadmins_view')}
        <h2 class="title">{'admin_menu_subtitles'|lang:'web':'users'}</h2>
        {if Auth::hasPermission('webadmins_edit')}
            <form class="form-inline border-secondary border-bottom border-top bg-light p-sm-2" method="post">
                <h4 class="mr-2">{'add_new'|lang}:</h4>
                <input name="new_username" placeholder="{'username'|lang}" required class="form-control-sm form-control"
                       autocomplete="off">
                <input name="email" type="email" placeholder="{'email'|lang}" required
                       class="form-control-sm form-control" autocomplete="off">
                <input name="new_password" type="password" placeholder="{'password'|lang}" required
                       class="form-control-sm form-control" autocomplete="off">
                <span class="ml-2 mr-1">{'level'|lang}:</span>
                {html_options name='level' values=$perm_levels output="what_level"|lang|array_map:$perm_levels class='form-control form-control-sm'}
                <button class="btn btn-success btn-sm ml-2">{'save'|lang}</button>
            </form>
        {/if}
        <ul class="list-group list-group-flush">
            {foreach $users as $user}
                <li class="list-group-item">
                    {if Auth::hasPermission('webadmins_edit')}
                        <form method="post" class="float-right" action="{array('web', 'users', $user.id)|url}">
                            {Site::makeFormAuth('DELETE')}
                            <a class="btn btn-outline-info"
                               href="{array('web', 'users', $user.id, 'edit')|url}">{'edit'|lang}</a>
                            <button class="btn btn-outline-danger do-confirm">{'delete'|lang}</button>
                        </form>
                    {/if}
                    <b>{$user.username}</b> ({$user.email})<br>
                    {'last_seen'|lang}: {$user.last_action|date_format:$lang_date_format}
                </li>
            {/foreach}
        </ul>
        {if Auth::hasPermission('webadmins_edit')}
            <script>
                $('.do-confirm').click(function () {
                    return confirm('{'confirm_message'|lang}');
                });
            </script>
        {/if}
    {else}
        <div class="alert alert-danger">{'no_access'|lang}</div>
    {/if}
{/block}