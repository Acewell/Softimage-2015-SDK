# Python TCP server demo: Demonstrate how to run an asynchronous TCP server in XSI to respond to external client requests. You can use the tcpclient.py example 
# to send request to the TCP server.
# 
# Author: M.A.Belzile
# Date: Feb 2011
# 
# Copyright 2008 Autodesk, Inc.  All rights reserved.  
# Use of this software is subject to the terms of the Autodesk license agreement 
# provided at the time of installation or download, or which otherwise accompanies 
# this software in either electronic or hard copy form.   


import socket
import sipyutils
import sys

PORT = 5007
HOST = 'localhost'
NCNX = 5
BLOCKSIZE = 4096

# the SIServer instance
theServer = None

class SITCPServer(object):
	"""
	A class supporting TCP socket connections with the IP protocol. This server supports multiple 
	connections asynchronously (default to 5). Client requests processing is preemptive and are handled 
	one at a time through an SDK timer event. Using a preemptive processing makes sure that client 
	requests are executed in the UI thread which avoids dealing with a multi-threaded server 
	implementation.
	"""
	def __init__(self, handler_class, port=PORT, ncnx = NCNX):
		self._trace = False
		self._socket_server = None
		self._handler_class = handler_class
		self._port = port
		self._ncnx = ncnx
		self._address_family = socket.AF_INET
		self._socket_type = socket.SOCK_STREAM		
		
	def start(self):
		"""
		Creates the server socket
		"""
		# make sure to stop the server first if required
		self.stop()

		try:
			self._socket_server = socket.socket(self._address_family, self._socket_type)
		except:
			self._log_exception( 'failed to start server' )

		self._socket_server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
		self._socket_server.bind((HOST, self._port))
		self._socket_server.listen(self._ncnx)
		self._socket_server.settimeout(0.1)			
		self._log( "socket created" )
				
	def stop(self):
		"""
		Terminates the server socket connection
		"""
		self._log( "stopping server" )
			
		if self._socket_server != None:
			self._socket_server.settimeout(0.1)
			self._socket_server.close()
			self._socket_server = None
							
	def process(self):
		if self._socket_server == None:
			return
			
		self._log( "begin processing connection" )

		try:
			conn, addr = self._socket_server.accept()
		except:
			#self._log_exception( 'reading connection' )
			return
			
		self._log('connection: %s' % (str(conn)) )		
		
		# read incoming message
		data = conn.recv(BLOCKSIZE)				
					
		self._log( 'data received: %s' % (data) )
			
		#handle the request with the current request handler class
		self._handle_request( data, conn, addr )

		conn.close()
		
		self._log('end processing connection')
	
	def _handle_request( self, data, client_conn, client_addr ):
		self._log( 'Serving %s' % (data) )
		self._handler_class( data, client_conn, client_addr )
		
	def _log(self,msg):
		if self._trace: 
			sipyutils.log( msg )      
	
	def _log_exception( self, msg ):
		sipyutils.log( '%s: %s' % (msg, sys.exc_info()[1]) )
		
class BaseRequestHandler:
	"""
	Base class for request handler classes. This class is intanciated for each 
	new request to be handled. To implement a specific service, you need to derive 
	a class which defines a handle() method for processing the request. Optionally, you can
	define a begin() and end() methods which are called before and after the handle() method.
	
	The request handler class has access to the client request, socket connection and address. The 
	format of the request must match the protocol defined by the request handler class. Typically, 
	the request is a string object type which can define either an action, a command name with arguments 
	or a script. 
	"""
	def __init__(self, request, client_conn, client_addr ):
		self.request = request
		self.client_conn = client_conn
		self.client_addr = client_addr

		try:
			self.begin()
			self.handle()
			self.end()
		finally:
			sys.exc_traceback = None    # Help garbage collection

	def begin(self):	
		pass

	def handle(self):
		pass

	def end(self):
		pass
		
class MeshRequestHandler(BaseRequestHandler):
	"""
	Test handler that simply creates a primitive as requested and return a message to 
	the sender when the request has been processed.
	"""
	
	def handle(self):
		"""
		message request format: 'name:primitive type to create'
		"""
		tokens = self.request.split(':')
		Application.CreatePrim( tokens[1], "MeshSurface", tokens[0], "")

	def end(self):
		self.client_conn.send('done')

def start_siserver( ctxt ):
	sipyutils.log("server started", sipyutils.C.siComment)

	ev = Application.EventInfos('Timer')
	ev.Mute = False

	global theServer
	try:
		theServer.stop()
	except:
		sipyutils.log('failed while terminating server: %s'%(sys.exc_info()[1]))

	theServer = SITCPServer( handler_class = MeshRequestHandler )		

	theServer.start()
			
	return True

def stop_siserver( ctxt ):
	sipyutils.log("server stopped", sipyutils.C.siComment)

	global theServer
	
	ev = Application.EventInfos('Timer')
	ev.Mute = True
	
	try:
		theServer.stop()
	except:
		sipyutils.log('failed while terminating server: %s' %(sys.exc_info()[1]))
	
	return True

def SITCPServer_Init( in_ctxt ):
	oMenu = in_ctxt.Source
	oMenu.AddCallbackItem("Start","start_siserver")
	oMenu.AddCallbackItem("Stop","stop_siserver")
	return True

def Timer_OnEvent( in_ctxt ):
	"""
	Timer for processing client requests
	"""
	#sipyutils.log("Timer_OnEvent called",sipyutils.C.siVerbose)

	global theServer
	
	if theServer == None:
		return False
		
	theServer.process( )
	
	return False

def run_testclient_Init( ctxt ):

	cmd = ctxt.source
	cmd.Arguments.Add( "msg", sipyutils.C.siArgumentInput, "testclient:sphere")
	
	return True;

def run_testclient_Execute( msg ):		
	conn = socket.socket()
	
	try:
		conn.connect((HOST, PORT))
	except:
		sipyutils.log('connection failed: %s' % sys.exc_info()[1])
		
	conn.sendall( msg )
		
	conn.close()
	
	return True
		
def XSILoadPlugin( in_reg ):
	in_reg.Author = "Marc-Andre Belzile"
	in_reg.Name = "SITCPServer"
	
	# timer to process a request every 2 sec. 
	in_reg.RegisterTimerEvent("Timer",2000,0) 
	Application.EventInfos('Timer').Mute = True

	in_reg.RegisterMenu(sipyutils.C.siMenuMainTopLevelID,"SI TCP Server",False,False)

	in_reg.RegisterCommand("run_testclient","run_testclient")
	
	return True

def XSIUnloadPlugin( in_reg ):
	strPluginName = in_reg.Name
	sipyutils.log(str(strPluginName) + str(" has been unloaded."),sipyutils.C.siVerbose)
	if theServer:
		theServer.end()
	return True
