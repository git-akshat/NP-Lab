import java.util.*;
import java.io.*;
import java.lang.*;
import java.net.*;

class ClientDemo{

	public static void main(String[] args) throws IOException
	{
		Socket sock = new Socket("127.0.0.1",4000);
		System.out.println("Connection established");
		
		PrintWriter pout = new PrintWriter(sock.getOutputStream(), true);
		pout.println("Hello Server");
		
		BufferedReader br = new BufferedReader(new InputStreamReader(sock.getInputStream()));
		String msg = br.readLine();
		System.out.println("msg from Server: " + msg);
		
		
		pout.close();
		br.close();
		sock.close();
		
	}
}
