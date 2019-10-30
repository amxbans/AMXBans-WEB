<table class="table table-hover" align="center">
    <thead>
    <tr>
        <th></th>
        <th>{$lang.STEP2_REQUIRED}</th>
        <th>{$lang.STEP2_CLIENT}</th>
        <th width="1"></th>
    </tr>
    </thead>
    <tbody>
    <tr>
        <th>PHP</th>
        <td>7.2</td>
        <td>{$php_settings.version_php}</td>
        <td>
            {if version_compare($php_settings.version_php, 7.2) > -1}
                <img src="{"../webSources/images/success.gif"|res_url}"/>
            {else}
                <img src="{"../webSources/images/warning.gif"|res_url}"
            {/if}
        </td>
    </tr>
    <tr>
        <th>PDO: MySQL</th>
        <td>TRUE</td>
        <td>{if $php_settings.mysql_enabled}TRUE{else}FALSE{/if}</td>
        <td>
            {if $php_settings.mysql_enabled}
                <img src="{"../webSources/images/success.gif"|res_url}"/>
            {else}
                <img src="{"../webSources/images/warning.gif"|res_url}"
            {/if}
        </td>
    </tr>
    <tr class="settings_line">
        <th>register_globals</th>
        <td>FALSE</td>
        <td>{if $php_settings.register_globals}TRUE{else}FALSE{/if}</td>
        <td>
            {if !$php_settings.register_globals}
                <img src="{"../webSources/images/success.gif"|res_url}"/>
            {else}
                <img src="{"../webSources/images/warning.gif"|res_url}"
            {/if}
        </td>
    </tr>
    <tr class="settings_line">
        <th>display_errors</th>
        <td>FALSE</td>
        <td>{if $php_settings.display_errors}TRUE{else}FALSE{/if}</td>
        <td>
            {if !$php_settings.display_errors}
                <img src="{"../webSources/images/success.gif"|res_url}"/>
            {else}
                <img src="{"../webSources/images/warning.gif"|res_url}"
            {/if}
        </td>
    </tr>
    <tr>
        <td colspan="4"></td>
    </tr>
    <tr>
        <th>{$lang.STEP2_WRITEABLE}: /include</th>
        <td>TRUE</td>
        <td>{if $dirs_settings.include}TRUE{else}FALSE{/if}</td>
        <td>
            {if $dirs_settings.include}
                <img src="{"../webSources/images/success.gif"|res_url}"/>
            {else}
                <img src="{"../webSources/images/warning.gif"|res_url}"
            {/if}
        </td>
    </tr>
    <tr>
        <th>{$lang.STEP2_WRITEABLE}: /webSources/uploads</th>
        <td>TRUE</td>
        <td>{if $dirs_settings.uploads}TRUE{else}FALSE{/if}</td>
        <td>
            {if $dirs_settings.uploads}
                <img src="{"../webSources/images/success.gif"|res_url}"/>
            {else}
                <img src="{"../webSources/images/warning.gif"|res_url}"
            {/if}
        </td>
    </tr>
    <tr>
        <th>{$lang.STEP2_WRITEABLE}: /templates/compiled</th>
        <td>TRUE</td>
        <td>{if $dirs_settings.templates_c}TRUE{else}FALSE{/if}</td>
        <td>
            {if $dirs_settings.templates_c}
                <img src="{"../webSources/images/success.gif"|res_url}"/>
            {else}
                <img src="{"../webSources/images/warning.gif"|res_url}"
            {/if}
        </td>
    </tr>
    </tbody>
    <tfoot>
    <tr>
        <td colspan="4" class="text-right">{if isset($next) && $next}<a href="{'3'|url}" class="btn btn-primary">{$lang.NEXT}</a>{/if}</td>
    </tr>
    </tfoot>
</table>