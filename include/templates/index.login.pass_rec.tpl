{extends file="master.tpl"}
{block name="head-title" prepend}{$lang.index.login.pass_rec} | {/block}

{block name="BODY"}
    {include file="messages.tpl"}
        <form>
            <h1 class="text-center">{$lang.index.login.pass_rec}</h1>

            <div class="row mb-3">
                <label class="col-md-5 col-lg-4 text-sm-right col-form-label"
                       for="code">{$lang.index.login.rec_code}</label>
                <div class="col-md-7 col-lg-8">
                    <input name="code" type="password" class="form-control" id="code" required autocomplete="off"/>
                </div>
            </div>

            <div class="row">
                <div class="col text-right">
                    <button class="btn btn-primary">{$lang.next}</button>
                </div>
            </div>
        </form>
{/block}