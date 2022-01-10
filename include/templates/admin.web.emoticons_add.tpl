{extends file="master.tpl"}
{block name="head-title" prepend}{'admin_menu_subtitles'|lang:'web':'settings'} - {'admin_menu_titles'|lang:'web'} | {/block}

{block name="BODY"}
    {include file="messages.tpl"}
    {if Auth::hasPermission('websettings_edit')}
        <h2>
            {'emoticons'|lang}
            <small class="float-right">
                <button form="form" class="btn btn-success">{'add'|lang}</button>
            </small>
        </h2>
        <form id="form" method="post">
            <div class="row mb-2">
                <div class="col-auto col-md-6 col-lg-3 font-weight-bold align-self-center text-md-right">{'symbol'|lang}</div>
                <div class="col">
                    <input name="symbol" placeholder="\o/" value="{"symbol"|input}" class="form-control" required/>
                </div>
            </div>
            <div class="row mb-2">
                <div class="col-auto col-md-6 col-lg-3 font-weight-bold align-self-center text-md-right">{'title'|lang}</div>
                <div class="col">
                    <input name="title" placeholder="Woohoo!" value="{"title"|input}" class="form-control" required/>
                </div>
            </div>
            <div class="row mb-2">
                <div class="col-auto col-md-6 col-lg-3 font-weight-bold align-self-center text-md-right">{'emoticons_file_name'|lang}</div>
                <div class="col">
                    <input name="file" placeholder="file.ext" value="{"file"|input}" class="form-control" required/>
                </div>
            </div>
        </form>
    {else}
        <div class="alert alert-danger">{'no_access'|lang}</div>
    {/if}
{/block}