{extends file="master.tpl"}
{block name="head-title" prepend}{'admin_menu_subtitles'|lang:'web':'users'} - {'admin_menu_titles'|lang:'index'} | {/block}

{block name="BODY"}
    {include file="messages.tpl"}
    {if Auth::hasPermission('webadmins_view')}
        <h2 class="title">{'admin_menu_subtitles'|lang:'web':'users'}</h2>
        <ul class="list-group list-group-flush">
            {foreach $users as $user}
                <li class="list-group-item">
                    <span class="float-right">
                        <a class="btn btn-outline-info" href="{array('web', 'users', $user.id)|url}">{'edit'|lang}</a>
                    </span>
                    <b>{$user.username}</b><br/>

                </li>
            {/foreach}
        </ul>
        <table class="table table-hover">
            <tr class="htablebottom">
                <td>{"_NAME"|lang}</td>
                <td align="center" width="1%">{"_LEVEL"|lang}</td>
                <td width="1%">{"_EMAIL"|lang}
                <td align="center" width="1%">{"_LASTLOGIN"|lang}</td>
                <td width="1%"><b>&nbsp;</b></td>
            </tr>
            {foreach from=$users item=user}
                <form method="POST" name="{$user.uid}">
                    <input type="hidden" name="uid" value="{$user.uid}"/>
                    <input type="hidden" name="newpw" id="newpw{$user.uid}" value=""/>
                    <tr class="settings_line">
                        <td align="center">
                            {if $smarty.session.webadmins_edit == "yes"}
                                <input type="text" name="name" value="{$user.name}"/>
                            {else}
                                <input type="hidden" name="name" value="{$user.name}"/>
                                <b>{$user.name}</b>
                            {/if}
                        </td>
                        <td align="center" width="1%">
                            {if $smarty.session.webadmins_edit == "yes"}
                                {html_options name=level values=$levels output=$levels selected=$user.level}
                            {else}
                                <input type="hidden" name="level" value="{$user.level}"/>
                                {$user.level}
                            {/if}
                        </td>
                        <td align="center"><input type="text" size="40" name="email" value="{$user.email}"
                                                  {if !($smarty.session.uname == $user.name || $smarty.session.webadmins_edit == "yes")}disabled{/if}/>
                        </td>
                        <td align="center">
                            <nobr>
                                {if $user.last_action}
                                    {$user.last_action|date_format:"%d. %b %Y - %T"}
                                {else}
                                    <i>{"_NEVER"|lang}</i>
                                {/if}
                            </nobr>
                        </td>
                        <td align="center">
                            <nobr>
                                <input type="submit" class="button" name="save" value="{"_SAVE"|lang}"
                                       {if !($smarty.session.uname == $user.name || $smarty.session.webadmins_edit == "yes")}disabled{/if} />
                                &nbsp;
                                <input type="submit" class="button" name="del" value="{"_DELETE"|lang}"
                                       onclick="return confirm('{"_DELADMIN"|lang}');"
                                       {if $smarty.session.webadmins_edit !== "yes"}disabled{/if} />
                                &nbsp;
                                <input type="submit" class="button" name="setnewpw" value="{"_NEWPASSWORD"|lang}"
                                       onclick="{if $smarty.session.uname == $user.name}alert('{"_YOURPASSWORD"|lang}');{/if}return SetNewPassword('newpw{$users.uid}','{"_ENTERPASSWORD"|lang}','{"_PASSWORD2"|lang}','{"_PASSWORDNOTMATCH"|lang}');"
                                       {if !($smarty.session.uname == $user.name || $smarty.session.webadmins_edit == "yes")}disabled{/if} />

                            </nobr>
                        </td>
                    </tr>
                </form>
            {/foreach}
        </table>
        {if $smarty.session.webadmins_edit == "yes"}
            <form method="POST">
                <table border="1" width="50%">
                    <tr class="htable">
                        <td colspan="4"><b>{"_WEBADMINADD"|lang}</b></td>
                    </tr>
                    <tr class="settings_line">
                        <td>{"_NAME"|lang}:</td>
                        <td align="left"><input type="text" name="name" value="{$input.name}"/></td>
                    </tr>
                    <tr class="settings_line">
                        <td>{"_EMAIL"|lang}:</td>
                        <td align="left"><input type="text" size="40" name="email" value="{$input.email}"/></td>
                    </tr>
                    <tr class="settings_line">
                        <td>{"_PASSWORD"|lang}:</td>
                        <td align="left"><input type="password" name="pw"/></td>
                    </tr>
                    <tr class="settings_line">
                        <td>{"_PASSWORD2"|lang}:</td>
                        <td align="left"><input type="password" name="pw2"/></td>
                    </tr>
                    <tr class="settings_line">
                        <td>{"_LEVEL"|lang}:</td>
                        <td>{html_options name=level values=$levels output=$levels selected=$input.level}</td>
                        <td>
                            <input type="submit" class="button" name="new" value="{"_ADD"|lang}"
                                   {if $smarty.session.webadmins_edit !== "yes"}disabled{/if} />&nbsp;
                            <input type="reset" class="button" value="{"_CLEAR"|lang}">
                        </td>
                    </tr>
                </table>
            </form>
        {/if}
    {else}
        <div class="alert alert-danger">{'no_access'|lang}</div>
    {/if}
{/block}