<form method="post" class="form-inline">
	<select name="lang" onchange="this.form.submit()" class="form-control">
		{foreach from=$languages item="lng"}
			<option value="{$lng|escape}" {if $smarty.session.lang == $lng}selected{/if}>{$lng|ucfirst}</option>
		{/foreach}
	</select>
</form>
<br/><br/>
<textarea style="width: 100%;height:500px;" readonly>{include file="../../COPYING"}</textarea>
<a href="http://creativecommons.org/licenses/by-nc-sa/3.0/" target="_blank">
	<img alt="Creative Commons License" style="border-width:0" src="https://licensebuttons.net/l/by-nc-sa/3.0/88x31.png"/>
</a>
<div class="float-right">
	<a href="{'2'|url}" class="btn btn-primary" rel="noreferrer">{$lang.STEP1_AGREE_LICENCE}</a>
</div>