{extends file="master.tpl"}
{

{block name="BODY"}
	{include file="messages.tpl"}

	<h1>
		<small><a class="text-muted" href="{"login"|url}">{$lang.back}</a></small>
		{$lang.index.login.pass_rec}
	</h1>

	<form method="post" class="row">
		{Site::makeFormAuth()}
		<label class="col-sm-3 text-sm-right col-form-label" for="email">{$lang.index.login.email}</label>
		<div class="col-sm-9"><input name="email" type="email" class="form-control" id="email" required /></div>

		<div class="col-sm-3 text-right"></div>
		<div class="col-sm-9">
			<button class="btn btn-primary">{$lang.send}</button>
		</div>

		<div class="col-sm-3"></div>
		<div class="col-sm-9">
			<a href="{['login', 'lost_pass']|url}">{$lang.index.login.lost_pass}</a> |
			<a href="{['login', 'pass_rec']|url}">{$lang.index.login.pass_rec}</a><br />
		</div>
	</form>
{/block}