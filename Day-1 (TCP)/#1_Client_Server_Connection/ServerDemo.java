import java.util.*;
import java.io.*;
import java.lang.*;
import java.net.*;

class ServerDemo{

	public static void main(String[] args) throws IOException
	{
		ServerSocket sersock = new ServerSocket(4000);
		Socket sock = sersock.accept();
		System.out.println("Connection established");
		
		BufferedReader br = new BufferedReader(new InputStreamReader(sock.getInputStream()));
		String msg = br.readLine();
		System.out.println("msg from client: " + msg);
	
		PrintWriter pout = new PrintWriter(sock.getOutputStream(), true);
		pout.println("Hello Client");
		
		pout.close();
		br.close();
		sock.close();
		sersock.close();
	
	}
}
