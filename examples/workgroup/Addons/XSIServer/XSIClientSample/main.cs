// XSIClientSample
// 
// Command-line application used for sending requests to the TCP/IP server setup
// by the XSIServer plug-in example.
//
// In Softimage load and start the XSIServer first (see help file) Execute the following from a
// command prompt.
// E.g.
// Note: These examples work if the XSIServer is connected on the localhost (127.0.0.1) on port 10000.
// XSIClientSample.exe "log|my message" -> logs "my message" in the history window
// XSIClientSample.exe "script|c:\\temp\\test.vbs" -> executes the test.vbs script in Softimage (any Softimage script language can be used)
//
//
//	Copyright 2008 Autodesk, Inc.  All rights reserved.  
//	Use of this software is subject to the terms of the Autodesk license agreement 
//	provided at the time of installation or download, or which otherwise accompanies 
//	this software in either electronic or hard copy form.   

using System;
using System.Collections.Generic;
using System.Text;
using System.Net.Sockets;

namespace XSIClientSample
{
	class Program
	{
		static void Main(string[] args)
		{
			String server = "127.0.0.1";
			int port = 10000;
			String request = "log|Log request from XSIClientSample";

			// Connect to host and port 
			if (args.Length == 1)
			{
				if (args[0] == "-help" || args[0] == "-h" || args[0] == "-?")
				{
					ShowHelp();
					return;
				}
				request = args[0];
			}
			else if (args.Length == 3)
			{
				request = args[0];
				server = args[1];
				port = Convert.ToInt32(args[2]);
			}
			else if (args.Length > 0)
			{
				// Bad usage:
				Console.WriteLine("Wrong arguments used...\n");
				ShowHelp();
				return;
			}

			Connect(server, port, request);
		}

		static void Connect(String server, int port, String request)
		{
			try
			{
				// Create a TcpClient.
				// Note, for this client to work you need to have an XSIServer 
				// connected to the same address as specified by the server, port
				// combination.
				TcpClient client = new TcpClient(server, port);

				// Translate the passed message into ASCII and store it as a Byte array.
				Byte[] data = System.Text.Encoding.ASCII.GetBytes(request);

				// Get a client stream for reading and writing.
				NetworkStream stream = client.GetStream();

				// Send the message to the connected XSIServer. 
				stream.Write(data, 0, data.Length);

				Console.WriteLine("Sent: {0}", request);

				// Receive the Softimage Server response.

				// Buffer to store the response bytes.
				data = new Byte[256];

				// String to store the response ASCII representation.
				String responseData = String.Empty;

				// Read the first batch of the XSIServer response bytes.
				Int32 bytes = stream.Read(data, 0, data.Length);
				responseData = System.Text.Encoding.ASCII.GetString(data, 0, bytes);
				Console.WriteLine("Received: {0}", responseData);

				// Close everything.
				stream.Close();
				client.Close();
			}

			catch (ArgumentOutOfRangeException e)
			{
				Console.WriteLine("ArgumentOutOfRangeException: {0}", e);
			}
			catch (ArgumentNullException e)
			{
				Console.WriteLine("ArgumentNullException: {0}", e);
			}
			catch (SocketException e)
			{
				Console.WriteLine("SocketException: {0}", e);
			}

			Console.WriteLine("\n Press Enter to continue...");
			Console.Read();
		}

		static void ShowHelp()
		{
			Console.WriteLine("Use:");
			Console.WriteLine("\tXSIClientSample: <request> [<server> <port>]");
			Console.WriteLine("\t\trequest: log|<message to log> | script|<script file name to execute>");
			Console.WriteLine("\t\tserver: Host address to connect to (default: 127.0.0.1)");
			Console.WriteLine("\t\tport: Connection port (default: 10000)");
			Console.WriteLine("\nExamples:");
			Console.WriteLine("\tXSIClientSample \"log|Send to 127.0.0.1 on port 10000\"");
			Console.WriteLine("\tXSIClientSample \"log|Send to 172.24.40.132 on port 50010\" \"172.24.40.132\" 50010");
			Console.WriteLine("\tXSIClientSample \"script|c:\\\\temp\\\\test.vbs\" \"172.24.40.126\" 50010");
			Console.WriteLine("\n");
		}
	}
}
