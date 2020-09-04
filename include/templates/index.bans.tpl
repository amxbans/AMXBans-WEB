{extends 'master.tpl'}
{block name="head-title" prepend}{'menu_titles'|lang:'bans'} | {/block}

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
				<th>{'date'|lang}</th>
				<th>{'player'|lang}</th>
				<th>{'admin'|lang}</th>
				<th>{'reason'|lang}</th>
				<th class="text-center">{'length'|lang}</th>
                {if $config->bans_show_comments}
					<th class="text-center"><img src="{'webSources/images/details.gif'|res_url}" alt="comments"
							title="{'comments'|lang}"></th>{/if}
				<th class="text-center"><img src="{'webSources/images/disk.png'|res_url}" alt="files"
							title="{'files'|lang}"></th>
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
					<td><a href="{['bans', $ban.id]|url}">{$ban.created|date_format:$lang_date_format}</a></td>
					<td><a href="{['bans', $ban.id]|url}">{$ban.player}</a></td>
					<td>{$ban.admin}</td>
					<td>{$ban.reason}</td>
                    {if $ban.length > 0}
						<td class="timeleft text-center">{$ban.length * 60}</td>
                    {else}
						<td class="text-center">{'permanent'|lang}</td>
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