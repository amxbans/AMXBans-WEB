{extends 'master.tpl'}
{block name="head-title" prepend}{$lang.index.titles.bans} | {/block}

{block name="BODY"}
	<div class="main">

	<!-- Pagenation -->
	<ul class="pagination justify-content-end">
		<li class="page-item{if !$page_prev} disabled{/if}">
			<a class="page-link"
					href="{['bans', $page-1]|url}"{if !$page_prev} tabindex="-1" aria-disabled="true"{/if}>&laquo;</a>
		</li>
		<li class="page-item active" aria-current="page"><span class="page-link">{$page}
					<span class="sr-only">(current)</span></span>
		</li>
		<li class="page-item{if !$page_next} disabled{/if}">
			<a class="page-link"
					href="{['bans', $page+1]|url}"{if !$page_prev} tabindex="-1" aria-disabled="true"{/if}>&raquo;</a>
		</li>
	</ul>

	<!-- Banlist -->
	<div class="table-responsive">
		<table class="table table-hover table-sm">
			<thead>
			<tr>
				<th style="width: 40px"></th>
				<th>{$lang.index.bans.date|ucfirst}</th>
				<th>{$lang.index.bans.player|ucfirst}</th>
				<th>{$lang.index.bans.admin|ucfirst}</th>
				<th>{$lang.index.bans.reason|ucfirst}</th>
				<th class="text-center">{$lang.index.bans.length|ucfirst}</th>
                {if $config->bans_show_comments}
					<th class="text-center"><img src="{'webSources/images/details.gif'|res_url}" alt="comments"
							title="{$lang.index.bans.comments|ucfirst}"></th>{/if}
				<th class="text-center"><img src="{'webSources/images/disk.png'|res_url}" alt="files"
							title="{$lang.index.bans.files|ucfirst}"></th>
                {if $config->bans_show_kicks}
					<th class="text-center"><i class="stat-icon kicks"></i></th>
                {/if}
			</tr>
			</thead>


			<tbody>
            {foreach $bans as $ban}
				<tr {if $ban.ended}class="table-success"{/if}>

					<td><img alt="{$ban.type}" src="{"webSources/images/games"|res_url}/{$ban.type}.gif" />
					</td>
					<td><a href="{['bans', $ban.id]|url}">{$ban.created|date_format:$lang.date_format}</a></td>
					<td><a href="{['bans', $ban.id]|url}">{$ban.player}</a></td>
					<td>{$ban.admin}</td>
					<td>{$ban.reason}</td>
                    {if $ban.length > 0}
						<td class="timeleft text-center">{$ban.length * 60}</td>
                    {else}
						<td class="text-center">{$lang.index.bans.permanent}</td>
                    {/if}
                    {if $config->bans_show_comments}
						<td class="text-center">{$ban.comment_count}</td>{/if}
					<td class="text-center">{$ban.file_count}</td>
                    {if $config->bans_show_kicks}
						<td class="text-center">{$ban.kick_count}</td>{/if}
				</tr>
            {/foreach}

			</tbody>
		</table>
	</div>

	<!-- Pagenation -->
	<ul class="pagination justify-content-center">
		<li class="page-item{if !$page_prev} disabled{/if}">
			<a class="page-link"
					href="{['bans', $page-1]|url}"{if !$page_prev} tabindex="-1" aria-disabled="true"{/if}>&laquo;</a>
		</li>
		<li class="page-item active" aria-current="page"><span class="page-link">{$page}
					<span class="sr-only">(current)</span></span>
		</li>
		<li class="page-item{if !$page_next} disabled{/if}">
			<a class="page-link"
					href="{['bans', $page+1]|url}"{if !$page_prev} tabindex="-1" aria-disabled="true"{/if}>&raquo;</a>
		</li>
	</ul>
	<script>
		$('.timeleft').each(function () {
			timer(parseInt(this.innerText + '000'), this);
		});
	</script>
{/block}