{extends file="master.tpl"}
{block name="head-title" prepend}{$lang.index.login.pass_rec} | {/block}

{block name="BODY"}
    {include file="messages.tpl"}
        <form method="post">
            {Site::makeFormAuth('put')}
            <h1 class="text-center">{$lang.index.login.pass_rec}</h1>

            <div class="row mb-1">
                <label class="col-md-5 col-lg-4 text-sm-right col-form-label" for="p">{$lang.index.login.new_pass}</label>
                <div class="col-md-7 col-lg-8">
                    <input name="{$lang.index.login.pass}" type="password" class="form-control" id="p" required autocomplete="off"/>
                </div>
            </div>

            <div class="row mb-3">
                <label class="col-md-5 col-lg-4 text-sm-right col-form-label" for="p2">{$lang.index.login.new_pass_2}</label>
                <div class="col-md-7 col-lg-8">
                    <input name="{$lang.index.login.pass}_2" type="password" class="form-control" id="p2" required autocomplete="off"/>
                </div>
            </div>

            <div class="row">
                <div class="col text-right">
                    <button class="btn btn-primary">{$lang.save}</button>
                </div>
            </div>
        </form>
{/block}