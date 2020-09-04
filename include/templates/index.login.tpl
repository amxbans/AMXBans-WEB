{extends file="master.tpl"}
{block name="head-title" prepend}{'menu_titles'|lang:'login'} | {/block}

{block name="BODY"}
	{include file="messages.tpl"}

	<form method="post" class="row" action="{['login']|url}">
		{Site::makeFormAuth()}
		<label class="col-sm-3 text-sm-right col-form-label" for="name">{'username'|lang}</label>
		<div class="col-sm-9"><input name="username" class="form-control" id="name" required value="{'username'|input}" /></div>

		<label class="col-sm-3 text-sm-right col-form-label" for="pass">{'password'|lang}</label>
		<div class="col-sm-9"><input type="password" name="password" class="form-control" id="pass" required value="{'password'|input}" /></div>

		<div class="col-sm-3 text-sm-right"><input type="checkbox" name="rem" class="form" id="rem"{if 'rem'|input:false} checked{/if} /></div>
		<label for="rem" class="col-sm-9">{'remember'|lang}</label>

		<div class="col-sm-3 text-right">{if $blocked}{'login_blocked'|lang}:{/if}</div>
		<div class="col-sm-9">
			<button class="btn btn-primary">{'login'|lang}</button>
			{if $blocked}<span id="block"></span>{/if}
		</div>

		<div class="col-sm-3"></div>
		<div class="col-sm-9">
			{'lost_pass'|lang}? <a href="{['login', 'pass_rec']|url}">{'pass_rec'|lang}</a>
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