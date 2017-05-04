/*
Created by: Mitch Stark
Date: 5/3/17
Purpose: Client class for project 6 CS 232
*/

import java.util.Scanner;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.net.Socket;

public class CaeserCipherClient {
    //client start point
    public static void main(String[] args) throws IOException {

        if (args.length != 2) {
            System.out.println("ERROR - wrong no. of args...");
            return;
        }

        String testString = "testing";

        Integer portNum;
        String server = args[0];

        try {
            portNum = Integer.parseInt(args[1]);
        } catch (NumberFormatException ex) {
            System.out.println("ERROR - The second value must be a valid port");
            return;
        }

        System.out.println("Welcome to the CaeserCipher service. Please enter the offset integer: ");

        Scanner s = new Scanner(System.in);
        Integer offset = s.nextInt();

        //ready to connect to the server
        Socket mySocket = new Socket(server, portNum);

        OutputStream os = mySocket.getOutputStream();
        PrintWriter out = new PrintWriter(os);

        out.append(offset.toString()).append("\n");
        out.flush();

        BufferedReader input = new BufferedReader(new InputStreamReader(mySocket.getInputStream()));
        String answer = input.readLine();

        if (!answer.equals(offset.toString())) {
            System.out.println("ERROR - Server returned: " + answer);
            return;
        }

        encryptUserInput(out, s, input);
    }


    private static void encryptUserInput(PrintWriter out, Scanner s, BufferedReader input) throws IOException {
        String answer;
        s.nextLine();
        while(true) {
            System.out.println("Please enter the string to encrypt: ");
            String unencryptedString = s.nextLine();

            if (unencryptedString.equals("exit")) {
                System.out.println("Thanks for using the CaesarCipher service...");
                return;
            }

            out.append(unencryptedString).append("\n");
            out.flush();

            answer = input.readLine();
            System.out.println("Encryption: " + answer);
        }
    }

}
