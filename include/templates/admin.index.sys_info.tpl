{extends file="master.tpl"}
{block name="head-title" prepend}{'admin_menu_subtitles'|lang:'index':'sys_info'} - {'admin_menu_titles'|lang:'index'} | {/block}

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
                <header class="card-header">{'server'|lang}</header>
                <div class="card-body">
                    <div class="row">
                        <div class="col-3 text-right">AMXBans</div>
                        <div class="col">v{$version}</div>
                    </div>
                    <div class="row">
                        <div class="col-3 text-right">{'webserver'|lang}</div>
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
                <div class="card-header">{'stats'|lang}</div>
                <div class="card-body">
                    <ul class="list-group">

                        <li class="d-flex justify-content-between align-items-center">
                            <b>{'db_size'|lang}:</b>
                            <span>{$db_size}</span>
                        </li>

                        <li class="d-flex justify-content-between align-items-center">
                            <span class="ml-2"></span>
                            <a class="btn-link" href="?optimise=true">{'db_optimise'|lang}</a>
                        </li>

                        <li class="d-flex justify-content-between align-items-center">
                            <span>{'active'|lang}/{'total_bans'|lang}:</span>
<span>{$bans.active}/{$bans.total}</span>
                        </li>
                        {if Auth::hasPermission('prune_db')}
                        <li class="d-flex justify-content-between align-items-center">
                            <span></span>
                            <a class="btn-link" href="?prune=true">{'prune_bans'|lang}</a>
                        </li>
                        {/if}
                        <li class="d-flex justify-content-between align-items-center">
                            <b>{'comments'|lang}:</b>
                            <span>{$comment_count}</span>
                        </li>

                        <li class="d-flex justify-content-between align-items-center">
                            <b>{'files'|lang}:</b>
                            <span>{$file_count}</span>
                        </li>
                    </ul>
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
                <div class="col-5 text-right">{'modules'|lang}: bc {'or'|lang} gmp</div>
                <div class="col">{$php['bc-gmp']|ucfirst}</div>
            </div>
            <div class="row">
                <div class="col-5 text-right">{'modules'|lang}: gd</div>
                <div class="col">{$php.gd|ucfirst}</div>
            </div>
        </div>
    </section>
{/block}