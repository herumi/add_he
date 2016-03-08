URL = 'http://localhost:8000/'

function bin2hex(s) {
	var o = ''
	for (var i = 0; i < s.length; i++) {
		n = s.charCodeAt(i).toString(16)
		o += (n.length < 2 ? '0' + n : n) + ' '
	}
	return o
}

function strip(s) {
	s = s.trim()
	var begin = 0
	var end = s.length
	if (end == 0) {
		return s
	}
	if (s[0] == '"') {
		begin++
	}
	if (begin < end && s[end - 1] == '"') {
		end--
	}
	return s.substr(begin, end - begin)
}

function getJson(callback, method, url, data) {
	var req = new XMLHttpRequest()
	req.onreadystatechange = function() {
		if (req.readyState == 4 && req.status == 200) {
			callback(req.response)
		}
	}
	var d = new Date()
	url += '&datetime=' + d.toISOString() // avoid same value on IE
	req.open(method, url, true)
	req.responseType = 'json'
	req.send(data)
}

function append() {
	var v = document.getElementsByName('append')[0].value
	console.log(v)

	appendTable = function(e) {
		console.log('appendTable', v, e)
		$('#client_table').append(
			$('<tr>').append(
				$('<td>').text(v)
			).append(
				$('<td class="encMsgC">').text(strip(e))
			)
		)
	}
	getJson(appendTable, 'GET', URL + '?enc=' + v)
}

function send() {
	var a=[]
	$('.encMsgC').each(function() {
		a.push($(this).text())
	})
	console.log('a=', a)
	var obj = $('#server_table')
	obj.html('')
	{
		var header = [
			'ëúÎç¾¹ëö‡'
		]
		var t = $('<tr>').attr('id', 'header')
		for (var i = 0; i < header.length; i++) {
			t.append(
				$('<th>').append(header[i])
			)
		}
		obj.append(t)
	}
	for (var i = 0; i < a.length; i++) {
		var t = $('<tr>')
		t.append(
			$('<td class="encMsgS">').append(a[i])
		)
		obj.append(t)
	}
}

function sum() {
	var s = ''
	$('.encMsgS').each(function() {
		if (s.length > 0) s += ','
		s += '"' + $(this).text() + '"'
	})
	console.log('s', s)
	getJson(function(e) {
		$('#encSumS').text(strip(e))
	}, 'POST', URL + '?sum', s)
}

function recv() {
	$('#encSumC').text($('#encSumS').text())
}

function dec() {
	var s = $('#encSumC').text()
	getJson(function(e) {
		$('#sum').text(strip(e))
	}, 'POST', URL + '?dec', s)
}
