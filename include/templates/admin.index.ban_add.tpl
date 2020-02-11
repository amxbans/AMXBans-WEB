{extends file="master.tpl"}
{block name="head-title" prepend}{$lang.admin.subtitles.index.ban_add} - {$lang.admin.titles.index} | {/block}

{block name="BODY"}
    {include file="messages.tpl"}

    {if User::hasPermission('bans_add')}
        <form method="post">
            {Site::makeFormAuth()}
            <h2>{$lang.admin.subtitles.index.ban_add}</h2>
            <label class="row align-items-center">
                <span class="col-lg-3 col-md-4 col-sm text-right font-weight-bold">{$lang.admin.ban_add.username|ucfirst}</span>
                <span class="col"><input name="username" class="form-control" value="{'username'|input}"
                                         autocomplete="off"></span>
            </label>
            <label class="row align-items-center">
                <span class="col-lg-3 col-md-4 col-sm text-right font-weight-bold">{$lang.index.ban.steamid}</span>
                <span class="col"><input name="SteamID" class="form-control" value="{'SteamID'|input}"
                                         autocomplete="off"></span>
            </label>
            <label class="row align-items-center">
                <span class="col-lg-3 col-md-4 col-sm text-right font-weight-bold">{$lang.ip}</span>
                <span class="col"><input name="IP" class="form-control" value="{'IP'|input}" autocomplete="off"></span>
            </label>
            <label class="row align-items-center">
                <span class="col-lg-3 col-md-4 col-sm text-right font-weight-bold">{$lang.index.ban.type}</span>
                <span class="col">
				<select name="ban_type" class="form-control">
					{html_options options=$lang.index.ban.types|array_reverse selected='ban_type'|input}
				</select>
			</span>
            </label>
            <label class="row align-items-center">
                <span class="col-lg-3 col-md-4 col-sm text-right font-weight-bold">{$lang.index.bans.reason|ucfirst}</span>
                <span class="col">
				<span class="input-group">
				<select name="reason" class="form-control">
					{html_options options=$reasons selected='reason'|input}
				</select>
					<span class="input-group-prepend input-group-append"><span
                                class="input-group-text">{$lang['or']}</span></span>
					<input name="custom_reason" class="form-control"/>
				</span>
			</span>
            </label>
            <label class="row align-items-center">
                <span class="col-lg-3 col-md-4 col-sm text-right font-weight-bold">{$lang.index.bans.length|ucfirst}</span>
                <span class="col form-inline">
					<input name="length" class="form-control"/> {$lang.admin.ban_add.mins} {$lang['or']}
					<label class="ml-3"><input name="permanent" type="checkbox"
                                               class="custom-checkbox mr-1"/> {$lang.index.bans.permanent|ucfirst}</label>
			</span>
            </label>
            <div class="row">
                <div class="col-lg-3 col-md-4 col-sm"></div>
                <div class="col">
                    <button class="btn btn-block btn-primary">{$lang.save}</button>
                </div>
            </div>
        </form>
    {else}
		<div class="alert alert-danger">{$lang.admin.no_access}</div>
    {/if}
{/block}