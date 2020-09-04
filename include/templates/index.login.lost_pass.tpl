{extends file="master.tpl"}
{block name="head-title" prepend}{'pass_rec'|lang} | {/block}

{block name="BODY"}
    {include file="messages.tpl"}
    <form method="post">
        {Site::makeFormAuth()}
        <h1 class="text-center">{'lost_pass'|lang}</h1>

        <div class="row mb-3">
            <label class="col-sm-3 text-sm-right col-form-label" for="email">{'email'|lang}</label>
            <div class="col-sm-9"><input name="email" type="email" class="form-control" id="email" required/></div>
        </div>

        <div class="row mb-3">
            <div class="col text-right">
                <button class="btn btn-primary">{'send'|lang}</button>
            </div>
        </div>
    </form>
{/block}