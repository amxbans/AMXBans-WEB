<form method="post" enctype="multipart/form-data">
	{if $errors->has()}
		<div class="alert alert-danger">
			<ul>{foreach $errors->getMessages() as $m}<li>{$m}</li>{/foreach}</ul>
		</div>
	{/if}
	{if isset($next)}
		<div class="alert alert-success">{$lang.step3_success}</div>
	{/if}
	<fieldset>
		<legend>{$lang.STEP3_DB_TITLE}</legend>
		<label class="input-group">
			<span class="input-group-prepend"><span class="input-group-text">{$lang.STEP3_HOST}</span></span>
			<input class="form-control {if $errors->has('db_host')}is-invalid{/if}" name="db_host" value="{"db_host"|input}" />
		</label>
		<label class="input-group">
			<span class="input-group-prepend"><span class="input-group-text">{$lang.STEP3_USERNAME}</span></span>
			<input class="form-control {if $errors->has('db_user')}is-invalid{/if}" name="db_user" value="{"db_user"|input}" />
		</label>
		<label class="input-group">
			<span class="input-group-prepend"><span class="input-group-text">{$lang.STEP3_PASSWORD}</span></span>
			<input type="password" class="form-control" name="db_pass" value="{"db_pass"|input}" />
		</label>
		<label class="input-group">
			<span class="input-group-prepend"><span class="input-group-text">{$lang.STEP3_DB}</span></span>
			<input class="form-control {if $errors->has('db_name')}is-invalid{/if}" name="db_name" value="{"db_name"|input}" />
		</label>
		<label class="input-group">
			<span class="input-group-prepend"><span class="input-group-text">{$lang.STEP3_DB_prefix}</span></span>
			<input class="form-control" name="db_prefix" value="{"db_prefix"|input:"amx_"}" />
		</label>
	</fieldset>


	<fieldset>
		<legend>{$lang.STEP3_ADMIN_TITLE}</legend>
		<label class="input-group">
			<span class="input-group-prepend"><span class="input-group-text">{$lang.STEP3_EMAIL}</span></span>
			<input type="email" class="form-control {if $errors->has('admin_email')}is-invalid{/if}" name="admin_email" value="{'admin_email'|input}" />
		</label>
		<label class="input-group">
			<span class="input-group-prepend"><span class="input-group-text">{$lang.STEP3_USERNAME}</span></span>
			<input class="form-control {if $errors->has('admin_user')}is-invalid{/if}" name="admin_user" value="{'admin_user'|input}" />
		</label>
		<label class="input-group">
			<span class="input-group-prepend"><span class="input-group-text">{$lang.STEP3_PASSWORD}</span></span>
			<input type="password" class="form-control {if $errors->has('admin_pass')}is-invalid{/if}" name="admin_pass" value="{'admin_pass'|input}" />
		</label>
		<label class="input-group">
			<span class="input-group-prepend"><span class="input-group-text">{$lang.STEP3_PASSWORD} x2</span></span>
			<input type="password" class="form-control {if $errors->has('admin_pass2')}is-invalid{/if}" name="admin_pass2" value="{'admin_pass2'|input}" />
		</label>
	</fieldset>

	<div class="m-3 text-right">
			<button name="validate" class="btn btn-secondary">{$lang.VALIDATE}</button>
        {if isset($next)}<a href="{$site+1|url}" class="btn btn-primary">{$lang.NEXT}</a>{/if}
	</div>
</form>