import java.util.*;
import java.net.*;
import java.io.*;

class ServerUDPDemo{
	
	public static void main(String[] args) throws IOException
	{
		
		DatagramSocket dsock = new DatagramSocket(1200);
		System.out.println("Waiting for data from client");
		
		byte[] data = new byte[65535]; 
		
		DatagramPacket pack = new DatagramPacket(data, data.length);
		dsock.receive(pack);
		
		System.out.println("Client : " + (new String(data)));
			
		dsock.close();
	}
}
			
