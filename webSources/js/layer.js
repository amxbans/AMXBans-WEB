function timer(diff, place) {
	let y = 0, mo = 0, d = 0, h = 0, m = 0, s = 0, o = '';
	diff = Math.floor(diff / 1000);

	if (diff <= 0) {
		$(place).text('0s');
		return false;
	}
	y = Math.floor(diff / (3600 * 24 * 365));
	if (y) {
		diff = diff - (y * 3600 * 24 * 365);
		o += y.toString() + 'y ';
	}

	mo = Math.floor(diff / (3600 * 24 * 30));
	if (mo) {
		diff = diff - (mo * 3600 * 24 * 30);
		o += mo.toString() + 'mo ';
	}

	d = Math.floor(diff / (3600 * 24));
	if (d) {
		diff = diff - (d * 3600 * 24);
		o += d.toString() + 'd ';
	}

	h = Math.floor(diff / 3600);
	if (h) {
		diff = diff - (h * 3600);
		o += h.toString() + 'h ';
	}

	m = Math.floor(diff / 60);
	if (m) {
		diff = diff - (m * 60);
		o += m.toString() + 'm ';
	}

	s = Math.floor(diff);
	if (s) {
		o += s.toString() + 's';
	}

	$(place).text(o);
	return true;
}

function typeInTextarea(el, newText) {
	var start = el.prop("selectionStart");
	var end = el.prop("selectionEnd");
	var text = el.val();
	var before = text.substring(0, start);
	var after  = text.substring(end, text.length);
	el.val(before + newText + after);
	el[0].selectionStart = el[0].selectionEnd = start + newText.length;
	el.focus();
}

$(function () {
	$('#serverInfoContainer > .card').click(function (e) {
		if ($('.card-body.show', this).length) {
			return e;
		}
		const $this = $(this);
		if (!$this.children().last().hasClass('spinner')) {
			return e;

		}
		$this.children().last().html('<div style="padding: 15vh;" class="d-flex justify-content-center"><div class="spinner-border" role="status"><span class="sr-only">Loading...</span></div></div>');
		let server = $this.data('server-id');
		$.get('servers/' + server, data => {
			if (!data.success) {
				$this.children().last().html('<div class="alert alert-warning">' + data.message + '</div>');
				return e;
			}

			let tpl = '<div class="row">' +
				'<div class="col-12 col-md"><div class="mx-auto text-center" style="max-width: 150px"><img /></div><ul class="list-group"></ul></div>' +
				'<div class="col"><div class="h6">'+data.lang.players + ' ('+ (data.info.players.active - data.info.players.bots) + ' ' + data.lang.player.active + ', ' + data.info.players.bots + ' ' + data.lang.player.bots + ' // ' + data.info.players.max + ' ' + data.lang.player.total + ')' +
				'</div><ul class="list-group players"></ul></div>' +
				'</div>';
			const $child = $this.children().last().removeClass('spinner').html(tpl);
			$('img', $child).attr('src', data.info.picture).attr('alt', data.info.map).parent().append('<small class="text-muted">' + data.info.map + '</small>');
			data.players.forEach(function (player) {
				$('ul.players', $child).append('<li class="list-group-item d-flex justify-content-between align-items-center">\n' +
					(player.name? player.name : '<span class="font-italic">' + data.lang.player.connecting + '</span>') +
					'<span>' +
					// '<span class="badge badge-secondary badge-pill">' + player.time + '</span>' +
					'<span class="badge badge-secondary badge-pill">' + player.kills + '</span>' +
					'</span>\n' +
					'  </li>');
			});
			if (data.players.length === 0) {
				$('ul.players', $child).parent().html('<p class="text-center">' + data.lang.player.none + '</p>')
			}

			tpl = '<li class="list-group-item d-flex justify-content-between align-items-center"></li>';
			$('ul:not(.players)', $child).append('<li class="list-group-item text-center"><div class="font-weight-bold">' + data.info.hostname + '</div>' + data.info.address + '</li>');
			$('ul:not(.players)', $child).append($(tpl).clone().html('<b>' + data.lang.password + ':</b> ' + (data.info.password ? data.lang.yes : data.lang.no)));
			$('ul:not(.players)', $child).append($(tpl).clone().html('<b>' + data.lang.friendlyFire + ':</b> ' + (data.info.friendlyFire ? data.lang.yes : data.lang.no)));
			$('ul:not(.players)', $child).append($(tpl).clone().html('<b>' + data.lang.map + ':</b> ' + data.info.map));
			$('ul:not(.players)', $child).append($(tpl).clone().html('<b>' + data.lang.timeleft + ':</b> ' + data.info.timeleft));
			$('ul:not(.players)', $child).append($(tpl).clone().html('<b>' + data.lang.nextmap + ':</b> ' + data.info.nextmap));
		});
	});

	$('.ajax').click((e) => {
		e.preventDefault();
		let $this = $(this);
		$.ajax($this.attr('href'), {
			method: $this.data('ajax-method') ?? 'post',

		});
		//TODO: permission_list ajax call unification
		// 1. idk what else but definitely need to remove list element - data-ajax elem to point to?? @see admin.web.permission_list.tpl
	});
});

/*

function ToggleLayer(obj) {
	if(document.all) {
	  if(document.all[obj].style.display == 'none') {
			document.all[obj].style.display = 'block';
		} else {
			document.all[obj].style.display = 'none';
		}
	} else{
		if(document.getElementById(obj).style.display == 'none') {
			document.getElementById(obj).style.display = 'table-row';
		} else {
			document.getElementById(obj).style.display = 'none';
		}
  }
}

function openURI() {
	var control = document.navigator.nav;
	if (control.options[control.selectedIndex].value != 'no-url') {
		location.href = control.options[control.selectedIndex].value;
	}
}

function insertAtCaret (textarea, icon) { 
	if (document.getElementById(textarea).createTextRange && document.getElementById(textarea).caretPos) { 
		var caretPos = document.getElementById(textarea).caretPos; 
		selectedtext = caretPos.text; 
		caretPos.text = caretPos.text.charAt(caretPos.text.length - 1) == '' ? icon + '' : icon; 
		caretPos.text = caretPos.text + selectedtext; 
	} else if (document.getElementById(textarea).textLength > 0) {
		Deb = document.getElementById(textarea).value.substring( 0 , document.getElementById(textarea).selectionStart );
		Fin = document.getElementById(textarea).value.substring( document.getElementById(textarea).selectionEnd , document.getElementById(textarea).textLength );
		document.getElementById(textarea).value = Deb + icon + Fin; 
	} else{ 
		document.getElementById(textarea).value = document.getElementById(textarea).value + icon; 
	}
	document.getElementById(textarea).focus(); 
}

function LiveBanCopyVars (name,steamid,ip,userid) {
	document.getElementById('player_name').value = name;
	document.getElementById('player_uid').value = userid;
	document.getElementById('player_steamid').value = steamid;
	document.getElementById('player_ip').value = ip;
}

function SetNewPassword(fieldid,lang1,lang2,notmatch) {
	var pw1 = window.prompt(lang1, '');
	if(!pw1) return false;
	
	var pw2 = window.prompt(lang2, '');
	if(pw1 != pw2) { 
		alert(notmatch);
		return false;
	} else {
		document.getElementById(fieldid).value = pw1;
		return true;
	}
}
 // login security
var wseconds;
var wbuttontext;
function countdown(trys) {
    var button = document.getElementById('action');
    var button2 = document.getElementById('action2');
	
    if(trys <= 3) {
        wseconds = 10;
    } else {
        wseconds = 120;
    }
    wbuttontext = button.value;
    button.disabled = true;
	if (button2)
		button2.disabled = true;
    for(i = 0; i <= wseconds; ++i) {
        window.setTimeout('timer()', i * 1000);
    }
}
function timer() {
    var button = document.getElementById('action');
    var button2 = document.getElementById('action2');
    if(wseconds == 0) {
        if(button.childNodes[0]) {
            button.childNodes[0].nodeValue = wbuttontext;
			if (button2)
				button2.childNodes[0].nodeValue = wbuttontext;
        } else if (button.value) {
            button.value = wbuttontext;
			if (button2)
				button2.value = wbuttontext;
        } else {
            button.innerHTML = wbuttontext;
			if (button2)
				button2.innerHTML = wbuttontext;
        }
        button.disabled = false;
		if (button2)
			button2.disabled = false;
    } else {
        if(button.childNodes[0]) {
            
			if (button2)
				button2.childNodes[0].nodeValue = wbuttontext + ' ( ' + wseconds + ' )';
			button.childNodes[0].nodeValue = wbuttontext + ' ( ' + wseconds-- + ' )';
        } else if (button.value) {
            
			if (button2)
				button2.value = wbuttontext + ' ( ' + wseconds + ' )';
			button.value = wbuttontext + ' ( ' + wseconds-- + ' )';	
        } else {
            
			if (button2)
				button2.innerHTML = wbuttontext + ' ( ' + wseconds + ' )';
			button.innerHTML = wbuttontext + ' ( ' + wseconds-- + ' )';
        }
    }
}*/
