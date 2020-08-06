<!DOCTYPE html>
<html lang="{$lang.locale}" dir="{$lang.html_direction}">
<head>
    <meta charset="utf-8"/>
    <meta name="viewport" content="width=device-width, initial-scale=1"/>
    <meta name="author" content="indianiso1"/>
    <title>{$lang.email.subject}</title>
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

        h1 { padding-left: 2% };
    </style>
</head>
<body>

<h1>{$lang.email.greet|r:$replace}</h1>

<p>{$lang.email.intro|r:$replace}</p>
<p>{$lang.email.site}: <br/><a href="{['login', 'pass_rec']|full_url}?code={$code}">{['login', 'pass_rec']|full_url}?code={$code}</a></p>

</body>
</html>