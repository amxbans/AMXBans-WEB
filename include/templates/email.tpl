<!DOCTYPE html>
<html lang="{$lang.locale}" dir="{$lang.html_direction}">
<head>
    <meta charset="utf-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1" />
    <meta name="author" content="indianiso1" />
    {*TODO: restructure $lang to "something"|lang:"sub-something"} *}
    <title>{$lang.lost_pass_email.subject}</title>
    <style>
		* {
			box-sizing: border-box;
		}

		body {
			width: 100%;
			margin: 0;
			padding: 0;
		}

        body > * {
            width: 75%;
			min-width: 350px;
			margin-left: auto;
			margin-right: auto;
		}

		h1 {
			padding-left: 2%
		}

		;
    </style>
</head>
<body>

<h1>{$lang.lost_pass_email.greet|r:$replace}</h1>

<p>{$lang.lost_pass_email.intro|r:$replace}</p>
<p>{$lang.lost_pass_email.site}: <br /><a
            href="{['login', 'pass_rec']|full_url}?code={$code}">{['login', 'pass_rec']|full_url}?code={$code}</a></p>

</body>
</html>