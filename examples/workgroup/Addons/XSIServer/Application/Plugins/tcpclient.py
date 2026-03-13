##tcpclient.py
from socket import *
 
HOST = 'localhost'
PORT = 5007    #our port from before
ADDR = (HOST,PORT)
BUFSIZE = 4096
 
cli = socket( AF_INET,SOCK_STREAM)
cli.connect((ADDR))

cli.send('xyz_request:Torus')
 
data = cli.recv(1024)
	
print 'request result %s' % (data) 

cli.close()