{extends file="master.tpl"}
{block name="head-title" prepend}{'pass_rec'|lang} | {/block}

{block name="BODY"}
    {include file="messages.tpl"}
        <form method="post">
            {Site::makeFormAuth('put')}
            <h1 class="text-center">{'pass_rec'|lang}</h1>

            <div class="row mb-1">
                <label class="col-md-5 col-lg-4 text-sm-right col-form-label" for="p">{'new_password'|lang}</label>
                <div class="col-md-7 col-lg-8">
                    <input name="{'password'|lang}" type="password" class="form-control" id="p" required autocomplete="off"/>
                </div>
            </div>

            <div class="row mb-3">
                <label class="col-md-5 col-lg-4 text-sm-right col-form-label" for="p2">{'new_password_2'|lang}</label>
                <div class="col-md-7 col-lg-8">
                    <input name="{'password'|lang}_2" type="password" class="form-control" id="p2" required autocomplete="off"/>
                </div>
            </div>

            <div class="row">
                <div class="col text-right">
                    <button class="btn btn-primary">{'save'|lang}</button>
                </div>
            </div>
        </form>
{/block}