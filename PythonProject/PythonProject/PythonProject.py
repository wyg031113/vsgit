print ("Hello world")
import gevent
from gevent import monkey
monkey.patch_all()
import urllib.request
def f(url):
	print("GET:%s" % url)
	resp = urllib.request.urlopen(url)
	data = resp.read()
	print('%d bytes received from %s.' % (len(data), url))
	resp.close()
gevent.joinall([gevent.spawn(f, 'https://github.com/'),
				gevent.spawn(f, 'https://www.python.org/'),
				gevent.spawn(f,	'https://www.baidu.com/')
				])