{extends file="master.tpl"}
{block name="head-title" prepend}{$lang.index.titles.login} | {/block}

{block name="BODY"}
	{include file="messages.tpl"}

	<form method="post" class="row">
		{Site::makeFormAuth()}
		<label class="col-sm-3 text-sm-right col-form-label" for="name">{$lang.index.login.username}</label>
		<div class="col-sm-9"><input name="username" class="form-control" id="name" required /></div>

		<label class="col-sm-3 text-sm-right col-form-label" for="pass">{$lang.index.login.pass}</label>
		<div class="col-sm-9"><input type="password" name="password" class="form-control" id="pass" required /></div>

		<div class="col-sm-3 text-sm-right"><input type="checkbox" name="rem" class="form" id="rem" /></div>
		<label for="rem" class="col-sm-9">{$lang.index.login.remember}</label>

		<div class="col-sm-3 text-right">{if $blocked}{$lang.index.login.blocked}:{/if}</div>
		<div class="col-sm-9">
			<button class="btn btn-primary">{$lang.index.titles.login}</button>
			{if $blocked}<span id="block"></span>{/if}
		</div>

		<div class="col-sm-3"></div>
		<div class="col-sm-9">
			<a href="{['login', 'lost_pass']|url}">{$lang.index.login.lost_pass}</a> |
			<a href="{['login', 'pass_rec']|url}">{$lang.index.login.pass_rec}</a>
		</div>
	</form>

	{if $blocked}
		<script>
		let blocked = {
			until: {$blocked|intval}000,
			timerSetup: '',


			init: function () {
				this.timerSetup = setInterval('blocked.check()', 990);
			},

			check: function () {
				if (this.until > Date.now()) {
					$('input').attr('disabled', '');
					$('main button.btn').hide();
					timer(this.until - Date.now(), '#block');
				}
				else {
					$('input').attr('disabled', null);
					$("main button.btn").show();
					clearInterval(this.timerSetup);
				}
			},
		};

		blocked.init();
		</script>
	{/if}
{/block}