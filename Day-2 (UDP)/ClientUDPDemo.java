import java.util.*;
import java.net.*;
import java.io.*;

class ClientUDPDemo{
	
	public static void main(String[] args) throws IOException
	{
		DatagramSocket dsock = new DatagramSocket();
		InetAddress ip = InetAddress.getLocalHost();
		
		System.out.println("Enter message to send : ");
		Scanner s = new Scanner(System.in);
		String inp = s.nextLine();
		byte[] data = inp.getBytes();
		
		DatagramPacket pack = new DatagramPacket(data, data.length, ip, 1200);
		dsock.send(pack);
		System.out.println("Data sent");
			
		dsock.close();
	}
}
			
