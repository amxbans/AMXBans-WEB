{extends file="master.tpl"}
{block name="head-title" prepend}{'admin_menu_subtitles'|lang:'index':'ban_add'} - {'admin_menu_titles'|lang:'index'} | {/block}

{block name="BODY"}
    {include file="messages.tpl"}

    {if Auth::hasPermission('bans_add')}
        <form method="post">
            {Site::makeFormAuth()}
            <h2>{'admin_menu_subtitles'|lang:'index':'ban_add'}</h2>
            <label class="row align-items-center">
                <span class="col-lg-3 col-md-4 col-sm text-right font-weight-bold">{'username'|lang}</span>
                <span class="col"><input name="username" class="form-control" value="{'username'|input}"
                                         autocomplete="off"></span>
            </label>
            <label class="row align-items-center">
                <span class="col-lg-3 col-md-4 col-sm text-right font-weight-bold">{'steamid'|lang}</span>
                <span class="col"><input name="SteamID" class="form-control" value="{'SteamID'|input}"
                                         autocomplete="off"></span>
            </label>
            <label class="row align-items-center">
                <span class="col-lg-3 col-md-4 col-sm text-right font-weight-bold">{'ip'|lang}</span>
                <span class="col"><input name="IP" class="form-control" value="{'IP'|input}" autocomplete="off"></span>
            </label>
            <label class="row align-items-center">
                <span class="col-lg-3 col-md-4 col-sm text-right font-weight-bold">{'ban_type'|lang}</span>
                <span class="col">
				<select name="ban_type" class="form-control">
                    {foreach 'ban_types'|lang as $type}
                        <option value="{$type@key}"{if 'ban_type'|input == $type@key} selected{/if}>{$type}</option>
                        {if $type@iteration == 3}{break}{/if}
                    {/foreach}
				</select>
			</span>
            </label>
            <label class="row align-items-center">
                <span class="col-lg-3 col-md-4 col-sm text-right font-weight-bold">{'reason'|lang}</span>
                <span class="col">
				<span class="input-group">
				<select name="reason" class="form-control">
					{html_options options=$reasons selected='reason'|input}
				</select>
					<span class="input-group-prepend input-group-append"><span
                                class="input-group-text">{'or'|lang}</span></span>
					<input name="custom_reason" placeholder="{'custom_reason'|lang}" class="form-control"
                           value="{'custom_reason'|input}"/>
				</span>
			</span>
            </label>
            <label class="row align-items-center">
                <span class="col-lg-3 col-md-4 col-sm text-right font-weight-bold">{'length'|lang}</span>
                <span class="col form-inline">
					<input name="length" class="form-control"/>&nbsp;&nbsp;{'mins'|lang} {'or'|lang}
					<label class="ml-3"><input name="permanent" type="checkbox" {if 'permanent'|input:true}checked{/if}
                                               class="custom-checkbox mr-1"/> {'permanent'|lang}</label>
			</span>
            </label>
            <div class="row">
                <div class="col-lg-3 col-md-4 col-sm"></div>
                <div class="col">
                    <button class="btn btn-block btn-primary">{'save'|lang}</button>
                </div>
            </div>
        </form>
    {else}
        <div class="alert alert-danger">{'no_access'|lang}</div>
    {/if}
{/block}

{block name="scripts"}
    <script>
        $(function () {
            $('input[name="length"]').keyup(function () {
                document.getElementsByName('permanent')[0].checked = this.value.length === 0;
            })
        });
    </script>
{/block}