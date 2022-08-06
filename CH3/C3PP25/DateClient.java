
/**
 * Time-of-day server listening to port 6013.
 *
 * Figure 3.27
 *
 * @author Silberschatz, Gagne, and Galvin. 
 * Operating System Concepts  - Tenth Edition
 * Copyright John Wiley & Sons - 2018.
 */

import java.net.*;

import java.util.Scanner;

import java.io.*;

public class DateClient {
	public static void main(String[] args) {
		try {
			ServerSocket sock = new ServerSocket(6013);

			// now listen for connections
			while (true) {
				Socket client = sock.accept();
				
				// we have a connection
				PrintWriter pout = new PrintWriter(client.getOutputStream(), true);
				
				//Ask for user input 
				Scanner reader = new Scanner(System.in);
				

				System.out.println("Enter a String: ");
				
				// Scans the next token of the input as an int.
				String n = reader.nextLine(); 

				//once finished
				reader.close();
				
				// write the Data
				pout.println(n);

				// close the socket and resume listening for more connections
				client.close();
				sock.close();
			}
		} catch (IOException ioe) {
			System.err.println(ioe);
		}
	}
}
