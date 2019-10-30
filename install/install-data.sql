INSERT INTO PREFIX_smilies (code, url, name)
  VALUES (':D', 'big_smile.png', 'Laugh'),
         ('8)', 'cool.png', 'Cool'),
         (':S', 'hmm.png', 'Worried'),
         ('xD', 'lol.png', 'lol'),
         (':<', 'mad.png', 'Mad'),
         (':|', 'neutral.png', 'Neutral'),
         ('^_^', 'roll.png', 'RollEyes'),
         (':(', 'sad.png', 'Sad'),
         (':)', 'smile.png', 'Smile'),
         (':P', 'tongue.png', 'Tongue'),
         (';)', 'wink.png', 'Wink'),
         (':O', 'yikes.png', 'Wow');

INSERT INTO PREFIX_permissions (level, bans_add, bans_edit, bans_delete, bans_unban, amxadmins_view, amxadmins_edit, webadmins_view, webadmins_edit, websettings_view, websettings_edit, permissions_edit, prune_db, servers_edit, ip_view)
  VALUES (1, 1, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1);