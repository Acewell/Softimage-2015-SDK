//
//	Copyright 2008 Autodesk, Inc.  All rights reserved.  
//	Use of this software is subject to the terms of the Autodesk license agreement 
//	provided at the time of installation or download, or which otherwise accompanies 
//	this software in either electronic or hard copy form.   

using System;
using System.Text;
using System.Collections;
using XSI.Helpers;

namespace XSI.TCP
{
	// RequestsService: Example of a ServiceProvider implementation. The service
	// stores all received data from the clients. Each entry are executed by an 
	// Softimage event timer callback to ensure the request is executed in the main
	// thread.

	// The service support 2 type of requests
	// 1) <script|path>: execute a script specified with path
	// 2) <log|message>: log a message.

	public class RequestsService : ServiceProvider
	{
		public override object Clone()
		{
			return new RequestsService();
		}

		public override void OnAcceptConnection(ConnectionState in_state)
		{
			if (!in_state.WriteTo(Encoding.UTF8.GetBytes("Connected to XSIServer!\r\n"), 0, 25))
			{
				in_state.EndConnection(); //if write fails... then close connection
			}
		}

		public override void OnReceiveData(ConnectionState in_state)
		{
			byte[] buffer = new byte[1024];
			while (in_state.AvailableData > 0)
			{
				int readBytes = in_state.ReadFrom(buffer, 0, 1024);
				if (readBytes > 0)
				{
					string receivedStr = Encoding.UTF8.GetString(buffer, 0, readBytes);
					
					// Put data on log stack
					ClientRequests requests = new ClientRequests();
					requests.AddEntry(receivedStr);
				}
				else
				{
					in_state.EndConnection(); //If read fails then close connection
				}
			}
		}

		public override void OnDropConnection(ConnectionState state)
		{
			//Nothing to clean here
		}
	}

	// Manages and process the requests received from clients
	class ClientRequests : Base
	{
		static public Queue m_requests = new Queue();

		public void AddEntry(String in_str)
		{
			lock (ClientRequests.m_requests.SyncRoot)
			{
				ClientRequests.m_requests.Enqueue(in_str);
			}
		}

		public void Log()
		{
			lock (ClientRequests.m_requests.SyncRoot)
			{
				foreach( String req in ClientRequests.m_requests)
				{
					Info(req);
				}
			}
		}

		public void Clear()
		{
			lock (ClientRequests.m_requests.SyncRoot)
			{
				ClientRequests.m_requests.Clear();
			}
		}

		public void Process()
		{
			lock (ClientRequests.m_requests.SyncRoot)
			{
				object param = null;
				while (ClientRequests.m_requests.Count > 0)
				{
					String req = (String)ClientRequests.m_requests.Dequeue();

					string[] tokens = req.Split('|');
					if (tokens[0] == "script")
					{
						Log("Execute script request: " + req);
						GetXSI().ExecuteScript( tokens[1],null,null,ref param);
					}
					else if (tokens[0] == "log")
					{
						Info("Execute message request: " + tokens[1]);
					}
					else
					{
						Error("Unknown request: " + req);
					}
				}
			}
		}
	}
}