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

<hr />

<div class="row">
    <div class="col" id="final"></div>
    <div class="col text-right">
        <a href="{'../'|res_url}" class="disabled btn btn-primary">{$lang.STEP5_FIN_GOTO}</a>
    </div>
</div>

{if isset($securit)}
    {* TODO: write script to ajax the installation *}
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
        /*for (let i = 0; i < data.length; i++) {
            let itm = $(data[i].id);
            itm.text(lang.installing);
            $.get('/install/ajax.php?action=' + data[i].ajax, {
                success: function ( income ) {
                    if (income.status === 'success')
                        itm.text(lang.ok);
                    else if (income.status === 'error')
                        itm.text(lang.failed + ' ' + income.text);
                }
                error: function ( jqXHR, textStatus ) {
                    itm.text(lang.failed + ' ' + textStatus);
                }
            });
        }*/

        $('a.btn.btn-primary').click(function (event) {
            let $this = $(this);

        });
        function clearInstallation(btn) {
            $btn = $(btn);
            $.get('/install/ajax.php?action=cif');
        }
    </script>
{/if}