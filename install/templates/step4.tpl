<hr/>
<div class="row">
    <div class="col text-right font-weight-bold">{$lang.STEP1_AGREE_LICENCE}</div>
    <div class="col"><img src="{'../webSources/images/accept.png'|res_url}" alt="{$lang.YES}"></div>
</div>

<hr/>

<div class="row">
    <div class="col text-center font-weight-bold">[DB]</div>
</div>

<div class="row">
    <div class="col text-right font-weight-bold"> {$lang.STEP3_HOST}:</div>
    <div class="col">{$smarty.session.db_host}</div>
</div>

<div class="row">
    <div class="col text-right font-weight-bold"> {$lang.STEP3_USERNAME}:</div>
    <div class="col">{$smarty.session.db_user}</div>
</div>

<div class="row">
    <div class="col text-right font-weight-bold"> {$lang.STEP3_DB}:</div>
    <div class="col">{$smarty.session.db_name}</div>
</div>

<div class="row">
    <div class="col text-right font-weight-bold"> {$lang.STEP3_DB_prefix}:</div>
    <div class="col">{$smarty.session.db_prefix}</div>
</div>

<hr/>

<div class="row">
    <div class="col text-center font-weight-bold">[ADMIN]</div>
</div>

<div class="row">
    <div class="col text-right font-weight-bold">{$lang.STEP3_USERNAME}:</div>
    <div class="col">{$smarty.session.admin_user}</div>
</div>

<div class="row">
    <div class="col text-right font-weight-bold">{$lang.STEP3_EMAIL}:</div>
    <div class="col">{$smarty.session.admin_email}</div>
</div>

<hr/>

<div class="text-right">
    <a href="{"5/CHECKED"|url}" class="btn btn-primary">{$lang.INSTALL}</a>
</div>