<hr/>
<div class="row">
    <div class="col text-right font-weight-bold"> {$lang.STEP5_DB_CONFIG}:</div>
    <div id="credentials" class="col">{$lang.STEP5_WAITING}</div>
</div>

<div class="row">
    <div class="col text-right font-weight-bold"> {$lang.STEP5_TABLES}:</div>
    <div id="tables" class="col">{$lang.STEP5_WAITING}</div>
</div>

<div class="row">
    <div class="col text-right font-weight-bold"> {$lang.STEP5_SYS_CONFIG}:</div>
    <div id="system" class="col">{$lang.STEP5_WAITING}</div>
</div>

<div class="row">
    <div class="col text-right font-weight-bold"> {$lang.STEP5_ADMIN}:</div>
    <div id="admin" class="col">{$lang.STEP5_WAITING}</div>
</div>

<hr/>

    <div id="final"></div>
    <div class="text-right">
        <a href="{'../'|res_url}" class="disabled btn btn-primary">{$lang.STEP5_FIN_GOTO}</a>
    </div>

{if isset($securit)}
    <script>
        var data = [
            { id: '#credentials', ajax: 'dbc' },
            { id: '#tables', ajax: 'dbt' },
            { id: '#system', ajax: 'dbd' },
            { id: '#admin', ajax: 'acc' },
        ];
        var lang = {
            installing: "{$lang.STEP5_ING}",
            ok: "{$lang.STEP5_OK}",
            failed: "{$lang.STEP5_FAILED}",
            finished: "{$lang.STEP5_FINISHED}",
            fin_desc: "{$lang.STEP5_FIN_DESC}"
        };

        var ok = true;
        let ins = setTimeout('install()', 3000);


        function install(i = 0) {
            let itm = $(data[i].id);
            itm.text(lang.installing);
            $.get('{$route}/ajax.php?action=' + data[i].ajax)
                .done(function (income) {
                    if (income.status === 'success') {
                        itm.text(lang.ok);
                        if (++i < data.length)
                            install(i);
                        else {
                            $('#final').html('<b>' + lang.finished + '</b><br />' + lang.fin_desc);
                            $('a.btn.btn-primary').removeClass('disabled').click(function (event) {
                                event.preventDefault();
                                if (ok)
                                    $.get('{$route}/ajax.php?action=cif');
                                setTimeout('location.href = "{$route}/.."', 3000);
                            });
                        }
                    } else if (income.status === 'error')
                        itm.text(lang.failed + ' ' + income.text);
                    else
                        itm.html(lang.failed + ' ' + income);
                })
                .fail(function (jqXHR, textStatus) {
                    itm.text(lang.failed + ' ' + textStatus);
                    ok = false;
                });
        }
    </script>
{/if}