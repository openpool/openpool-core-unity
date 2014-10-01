
using System;
using UnityEngine;
using System.Collections.Generic;
using System.Net.Sockets;
using System.Threading;
using System.Net;
using System.Linq;

namespace OSC {
	public class OSCServer : IDisposable {
		public Queue<OSCMessage> current;
		
		UdpClient udpreceiver;
		UdpClient udpsender;
	    Thread thr;
	    
		bool isrunning;
	    
		object m_lock = new object();
	
	    public void Start(int port)
	    {
	        if (!isrunning)
	        {	
	        	// sender
	        	this.udpsender = new UdpClient();
	        	
	        	// receiver
	            IPEndPoint endpoint = new IPEndPoint(IPAddress.Any, port);
	            this.udpreceiver = new UdpClient(endpoint);
	            this.current = new Queue<OSCMessage>();
	
	            this.isrunning = true;
	            this.thr = new Thread(new ThreadStart(this.receive));
	            this.thr.Start();
	        }
	    }
	
	    public void Stop()
	    {
	        if (isrunning)
	        {
	            isrunning = false;
	            close();
	        }
	    }
	    
	    // implements
	    public void Dispose()
	    {
	    	Stop();
	    }
	    
	    public void Send(OSCPacket packet, IPEndPoint endPoint)
	    {
	    	if(isrunning)
			{
				byte[] data = packet.BinaryData;
				udpsender.Send(data, data.Length, endPoint);
			}
	    }
	    
	    public void Send(OSCPacket packet, string hostname, int port)
	    {	
			if(isrunning)
			{
				byte[] data = packet.BinaryData;
				udpsender.Send(data, data.Length, hostname, port);
			}
	    }
	    
	    public OSCMessage[] Update() {
	    	if(isrunning) {
	    		OSCMessage[] arr = null;
	    		lock (m_lock) {
	    			arr = this.current.ToArray();
	    			this.current.Clear();
	    		}
	    		return arr;
	    	}
	    	return null;
	    }
	
	    void close()
	    {
	        try
	        {
	            //Might throw an exception which is meaningless when we are shutting down
	            this.udpreceiver.Close();
	        }
	        catch
	        {
	
	        }
	    }
	
	    public void ForceRefresh()
	    {
	        lock (m_lock)
	        {
	            this.current.Clear();
	        }
	    }
		
	    void receive()
	    {
	        try
	        {
	            receiveData();
	        }
	        catch
	        {				
	        }
	        finally
	        {
	            // Try to stop cleanly on termination of the blocking receivedata function
	            this.Stop();
	        }
	    }
	
	    void receiveData()
	    {
	        while (isrunning)
	        {
				IPEndPoint ip = null;
	
	            byte[] buffer = this.udpreceiver.Receive(ref ip);
	            OSCPacket packet = OSCPacket.Unpack(buffer);
	            
	            lock(m_lock)
				{
					if(packet.IsBundle()) {
						OSCBundle bundle = packet as OSCBundle;
						foreach (object o in bundle.Values)
				        {
				            OSCMessage msg = (OSCMessage)o;
				            this.current.Enqueue(msg);
				        }
					}
					else {
						this.current.Enqueue(packet as OSCMessage);
					}
		        	
				}
	        }
	    }
	    
	}
}

