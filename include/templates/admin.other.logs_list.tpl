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

        <button class="btn btn-outline-primary">{"do_search"|lang}</button>
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
                        {"wipe_all_entries"|lang|sprintf:$logs_count}
                    </button>
                </div>
            </div>
        </form>
    {/if}
    <div class="table-responsive">
        <table class="table">
            <thead>
            <tr>
                <th>{"invoked"|lang}</th>
                <th>{"user"|lang}</th>
                <th>{"action"|lang}</th>
                <th>{"remarks"|lang}</th>
            </tr>
            </thead>
            <tbody>
            {foreach from=$logs item=log_item}
                <tr>
                    <td>{$log_item.created_at|date_format:$lang_date_format}</td>
                    <td>{$log_item.username|escape}</td>
                    <td>{$log_item.action|escape}</td>
                    <td>{$log_item.remarks|escape}</td>
                </tr>
            {/foreach}
            </tbody>
        </table>
    </div>
{/block}