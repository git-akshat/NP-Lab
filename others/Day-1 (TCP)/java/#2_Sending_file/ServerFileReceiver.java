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
			String msg = "";
			String inpt;
			
			while( (inpt = br.readLine()) != null)
			{
				msg = msg + inpt + "\n";
			}
			
			byte[] data = msg.getBytes();
			
			
			try
			{
				FileOutputStream fos = new FileOutputStream("Output.txt");	
				fos.write(data);
				System.out.println("File received successfully");
			}
			catch (FileNotFoundException e)
			{
				System.out.println("File not found");
			}

			br.close();
			sock.close();
			sersock.close();
	
			System.out.println("Connection Terminated");
	}
}
