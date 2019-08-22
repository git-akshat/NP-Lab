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
		
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		System.out.println("Enter file name: ");
		String fname = br.readLine();
		
		try
		{
			FileInputStream fis = new FileInputStream(fname);
			int size = fis.available();
			byte[] data = new byte[size];
			fis.read(data);
			pout.write(new String(data));
			System.out.println("File sent");
			
		}
		catch(FileNotFoundException e)
		{
			System.out.println("File not found");
		}
		
		pout.close();
		br.close();
		sock.close();
		
		System.out.println("Connection Terminated");
		
	}
}
