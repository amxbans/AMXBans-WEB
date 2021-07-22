{extends file="master.tpl"}
{block name="head-title" prepend}{'admin_menu_subtitles'|lang:'index':'sys_info'} - {'admin_menu_titles'|lang:'index'} | {/block}

{block name="BODY"}
	{include file="messages.tpl"}
	{if Auth::hasPermission('permissions_edit')}
		<form method="post"
			  action="{if $level.level}{array('web', 'groups', $level->level)|url}{else}{array('web', 'groups')|url}{/if}">
			{if $level.level}
				{Site::makeFormAuth('PUT')}
				<h3>{'edit_group'|lang}</h3>
			{else}
				{Site::makeFormAuth()}
				<h3>{'new_group'|lang}</h3>
			{/if}

			<div class="row row-cols-md-3 row-cols-1">
				<fieldset class="col align-self-center">
					<label class="input-group">
						<span class="input-group-prepend"><span class="input-group-text">{"bans_add"|lang}</span></span>
						{html_options name=bans_add options=$options selected=$level.bans_add class="form-control"}
					</label>
					<label class="input-group">
						<span class="input-group-prepend"><span class="input-group-text">{"bans_edit"|lang}</span></span>
						{html_options name=bans_edit options=$spec_options selected=$level.bans_edit class="form-control"}
					</label>
					<label class="input-group">
						<span class="input-group-prepend"><span class="input-group-text">{"bans_delete"|lang}</span></span>
						{html_options name=bans_delete options=$spec_options selected=$level.bans_delete class="form-control"}
					</label>
					<label class="input-group">
						<span class="input-group-prepend"><span class="input-group-text">{"bans_unban"|lang}</span></span>
						{html_options name=bans_unban options=$spec_options selected=$level.bans_unban class="form-control"}
					</label>
					<label class="input-group">
						<span class="input-group-prepend"><span class="input-group-text">{"ip_view"|lang}</span></span>
						{html_options name=ip_view options=$options selected=$level.ip_view class="form-control"}
					</label>
				</fieldset>
				<fieldset class="col">
					<label class="input-group">
						<span class="input-group-prepend"><span class="input-group-text">{"amxadmins_view"|lang}</span></span>
						{html_options name=amxadmins_view options=$options selected=$level.amxadmins_view class="form-control"}
					</label>
					<label class="input-group">
						<span class="input-group-prepend"><span class="input-group-text">{"amxadmins_edit"|lang}</span></span>
						{html_options name=amxadmins_edit options=$options selected=$level.amxadmins_edit class="form-control"}
					</label>
					<label class="input-group">
						<span class="input-group-prepend"><span class="input-group-text">{"webadmins_view"|lang}</span></span>
						{html_options name=webadmins_view options=$options selected=$level.webadmins_view class="form-control"}
					</label>
					<label class="input-group">
						<span class="input-group-prepend"><span class="input-group-text">{"webadmins_edit"|lang}</span></span>
						{html_options name=webadmins_edit options=$options selected=$level.webadmins_edit class="form-control"}
					</label>
					<label class="input-group">
						<span class="input-group-prepend"><span class="input-group-text">{"permissions_edit"|lang}</span></span>
						{html_options name=permissions_edit options=$options selected=$level.permissions_edit class="form-control"}
					</label>
				</fieldset>
				<fieldset class="col">
					<label class="input-group">
						<span class="input-group-prepend"><span class="input-group-text">{"websettings_view"|lang}</span></span>
						{html_options name=websettings_view options=$options selected=$level.websettings_view class="form-control"}
					</label>
					<label class="input-group">
						<span class="input-group-prepend"><span class="input-group-text">{"websettings_edit"|lang}</span></span>
						{html_options name=websettings_edit options=$options selected=$level.websettings_edit class="form-control"}
					</label>
					<label class="input-group">
						<span class="input-group-prepend"><span class="input-group-text">{"servers_edit"|lang}</span></span>
						{html_options name=servers_edit options=$options selected=$level.servers_edit class="form-control"}
					</label>
					<label class="input-group">
						<span class="input-group-prepend"><span class="input-group-text">{"prune_db"|lang}</span></span>
						{html_options name=prune_db options=$options selected=$level.prune_db class="form-control"}
					</label>
					<label class="w-100 text-right">
						<button class="btn btn-success">{'save'|lang}</button>
					</label>
				</fieldset>
			</div>
		</form>

		<h3>{'group_list'|lang}</h3>

		{foreach $perm_list as $permission}
			<div class="card my-2">
				<div class="card-header d-flex justify-content-between">
					{"group_id"|lang|sprintf:$permission.level}
					<span>
					<a href="{array('web', 'groups', $permission.level, 'edit')|url}">{"edit"|lang}</a>
					<a href="{array('web', 'groups', $permission.level)|url}" class="ajax text-danger"
					   data-ajax-method="DELETE">{'delete'|lang}</a>
					</span>
				</div>
				<div class="card-body">
					{foreach Auth::PERMISSIONS as $perm}
						<span
						class="text-{if (($perm|substr:0:4 != 'bans' || $perm == 'bans_add') && $permission.$perm == 1) OR ($perm|substr:0:4 == 'bans' && $permission.$perm == 2)}success{elseif $perm|substr:0:4 == 'bans' && $permission.$perm == 1}warning{else}danger{/if}">{$perm|lang}</span>{if !$perm@last},{/if}
					{/foreach}
				</div>
			</div>
		{/foreach}
	{else}
		<div class="alert alert-danger">{'no_access'|lang}</div>
	{/if}
{/block}