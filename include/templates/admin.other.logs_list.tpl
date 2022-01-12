{extends file="master.tpl"}
{block name="head-title" prepend}{'admin_menu_subtitles'|lang:'other':'sys_logs'} - {'admin_menu_titles'|lang:'other'} | {/block}

{block name="BODY"}
    {include file="messages.tpl"}
    <h2>{'admin_menu_subtitles'|lang:'other':'sys_logs'}</h2>
    <h5>{"filter"|lang}</h5>
    <form>
        <label class="input-group w-100">
            <span class="input-group-prepend"><span class="input-group-text">{"user"|lang}</span></span>
            {html_options name="search_user" options=$search_users selected=$smarty.get.search_user class="form-control"}
        </label>
        <label class="input-group w-100">
            <span class="input-group-prepend"><span class="input-group-text">{"action"|lang}</span></span>
            {html_options name="search_action" options=$search_actions selected=$smarty.get.search_action class="form-control"}
        </label>
    </form>
    {if Auth::hasPermission("websettings_edit")}
        <form method="post" action="{"other/sys_logs/delete"|url}">
            <h5>{"delete"|lang}</h5>
            <div class="row">
                <div class="col">
                    <label class="input-group">
                        <span class="input-group-prepend"><span
                                    class="input-group-text">{"older_then"|lang}</span></span>
                        <input type="number" min="1" name="wipe_data" value="1" class="form-control"/>
                        <span class="input-group-append">
                <span class="input-group-text">{"days"|lang}</span>
            <button class="btn btn-danger">{"go"|lang}</button>
            </span>
                    </label>
                </div>
                <div class="col-auto p-1">{"or"|lang}</div>
                <div class="col">
                    <button class="form-control btn btn-danger" name="wipe_data" value="0">
                        {"wipe_all_entries"|lang|sprintf:($logs|count)}
                    </button>
                </div>
            </div>
        </form>
    {/if}
    <table width="95%">
        <tr>
            <td>
        <tr>
            <td>
                <table border="1" width="100%">
                    <tr class="htabletop">
                        <td colspan="4"><b>{"_ACTIONLOGS"|lang}</b></td>
                    </tr>
                    <tr class="htablebottom">
                        <td width="1%">
                            <nobr>{"_INVOKED"|lang}</nobr>
                        </td>
                        <td width="1%" align="center">{"_USER"|lang}</td>
                        <td width="1%" align="center">
                            <nobr>{"_ACTION"|lang}</nobr>
                        </td>
                        <td>{"_REMARKS"|lang}</td>
                    </tr>
                    {foreach from=$logs item=log_item}
                        <tr class="list">
                            <td width="1%">
                                <nobr>{$log_item.timestamp|date_format:"%d.%m.%Y - %T"}</nobr>
                            </td>
                            <td width="1%" align="center">{$log_item.username|escape}</td>
                            <td width="1%" align="center">
                                <nobr>{$log_item.action|escape}</nobr>
                            </td>
                            <td>{$log_item.remarks|escape}</td>
                        </tr>
                    {/foreach}
                </table>
            </td>
        </tr>
    </table>
{/block}