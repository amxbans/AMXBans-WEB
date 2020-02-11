{extends file="master.tpl"}
{block name="head-title" prepend}{$lang.admin.subtitles.index.sys_info} - {$lang.admin.titles.index} | {/block}

{block name="BODY"}
    {include file="messages.tpl"}
    <style>
        .card-body .text-right { border-right: 1px dashed #dee2e6;font-weight: bold; }

        .card-body .row:not(:last-child) > * { border-bottom: 1px solid #dee2e6; }

        .card-body .title { font-weight: bold; }

        .card-body .item { margin-left: 0.3rem; margin-right: 0.3rem; }
    </style>
    <div class="row">

        <div class="col-md-9">

            <section class="card mb-3">
                <header class="card-header">{$lang.server|ucfirst}</header>
                <div class="card-body">
                    <div class="row">
                        <div class="col-3 text-right">AMXBans</div>
                        <div class="col">v{$version}</div>
                    </div>
                    <div class="row">
                        <div class="col-3 text-right">{$lang.admin.sys_info.webserver}</div>
                        <div class="col">{$php.server_software}</div>
                    </div>
                    <div class="row">
                        <div class="col-3 text-right">MySQL</div>
                        <div class="col">{$php.version_mysql}</div>
                    </div>
                    <div class="row">
                        <div class="col-3 text-right">PHP</div>
                        <div class="col">{$php.version_php}</div>
                    </div>
                </div>
            </section>


        </div>

        <div class="col-md-3">
            <section class="card mb-2">
                <div class="card-header">{$lang.admin.sys_info.stats}</div>
                <div class="card-body">
                    <div class="border-bottom">
                        <span class="title">{$lang.admin.sys_info.db_size}:</span>
                        <span class="item">{$db_size}</span>
                        <a class="btn-link" href="?optimise=true">{$lang.admin.sys_info.optimise}</a>
                    </div>
                    <div class="border-bottom">
                        <span class="title">{$lang.admin.sys_info.active|ucfirst}/{$lang.admin.sys_info.total|ucfirst} {$lang.admin.sys_info.bans}:</span>
                        <span class="item">{$bans.active}/{$bans.total}</span>
                        {if User::hasPermission('prune_db')}<a class="btn-link"
                                                               href="?prune=true">{$lang.admin.sys_info.prune|ucfirst}</a>{/if}
                    </div>
                    <div class="border-bottom">
                        <span class="title">{$lang.admin.sys_info.comments|ucfirst}:</span>
                        <span class="item">{$comment_count}</span>
                        {*   TODO v7.1:                     {if User::hasPermission('prune_db')}<a class="btn-link" href="?prune=true">{$lang.admin.sys_info.prune|ucfirst}</a>{/if}*}
                    </div>
                    <div>
                        <span class="title">{$lang.admin.sys_info.files|ucfirst}:</span>
                        <span class="item">{$file_count}</span>
                        {*   TODO v7.1:                     {if User::hasPermission('prune_db')}<a class="btn-link" href="?prune=true">{$lang.admin.sys_info.prune|ucfirst}</a>{/if}*}
                    </div>
                </div>
            </section>
        </div>
    </div>

    <section class="card">
        <div class="card-header">PHP</div>
        <div class="card-body">
            <div class="row">
                <div class="col-5 text-right">INI: display_errors</div>
                <div class="col">{$php.display_errors}</div>
            </div>
            <div class="row">
                <div class="col-5 text-right">INI: post_max_size</div>
                <div class="col">{$php.post_max_size}</div>
            </div>
            <div class="row">
                <div class="col-5 text-right">INI: upload_max_filesize</div>
                <div class="col">{$php.upload_max_filesize}</div>
            </div>
            <div class="row">
                <div class="col-5 text-right">INI: post_max_size</div>
                <div class="col">{$php.post_max_size}</div>
            </div>
            <div class="row">
                <div class="col-5 text-right">INI: max_execution_time</div>
                <div class="col">{$php.max_execution_time}</div>
            </div>
            <div class="row">
                <div class="col-12">&nbsp;</div>
            </div>
            <div class="row">
                <div class="col-5 text-right">{$lang.admin.sys_info.module}: bc {$lang['or']} gmp</div>
                <div class="col">{$php['bc-gmp']|ucfirst}</div>
            </div>
            <div class="row">
                <div class="col-5 text-right">{$lang.admin.sys_info.module}: gd</div>
                <div class="col">{$php.gd|ucfirst}</div>
            </div>
        </div>
    </section>
{/block}