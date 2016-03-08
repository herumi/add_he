import SimpleHTTPServer
import SocketServer
import urlparse
import json
import os, sys, subprocess

EXE='./sum_crypto.exe'

def execCommand(args, inputStr):
	p = subprocess.Popen(args, stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=sys.stderr)
	ifs = p.stdin
	ifs.write(inputStr)
	ifs.close()
	ofs = p.stdout
	s = ofs.read()
	ret = p.wait()
	ofs.close()
	if ret != 0:
		raise Exception("bad command", args, ret)
	return s

def enc(v):
	s = execCommand([EXE, 'enc', '-l', str(v)], '')
	s = s.strip('"')
	print 'enc', s
	return s

def sumEnc(v):
	s = execCommand([EXE, 'sum'], v)
	print 'sumEnc', s
	return s

def dec(v):
	s = execCommand([EXE, 'dec'], v)
	s = s.strip('"')
	print 'dec', s
	return s

class ServerHandler(SimpleHTTPServer.SimpleHTTPRequestHandler):
	def do_POST(self):
		self.postData = self.rfile.read(int(self.headers.getheader('content-length')))
		self.do_GET()

	def do_GET(self):
		uri = self.path
		print uri
		ret = urlparse.parse_qs(urlparse.urlparse(uri).query, keep_blank_values = True)
		print "ret", ret
		data = None

		if 'enc' in ret.keys():
			v = int(ret['enc'][0])
			data = enc(v)
		elif 'sum' in ret.keys():
			print 'posted data', data
			data = sumEnc(self.postData)
		elif 'dec' in ret.keys():
			data = dec(self.postData)

		if data is None:
			return

		ret = json.dumps(data)
		print ret

		body = ret.encode('utf-8')
		self.send_response(200)
		self.send_header('Content-Type', 'application/json')
		self.send_header('Access-Control-Allow-Origin', '*')
		self.send_header('Content-length', len(body))
		self.end_headers()
		self.wfile.write(body)

def main():
	Handler = ServerHandler
	SocketServer.TCPServer(("", 8000), Handler).serve_forever()

if __name__ == '__main__':
	main()
