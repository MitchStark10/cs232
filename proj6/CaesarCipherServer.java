
import java.net.Socket;
import java.net.ServerSocket;
import java.io.OutputStream;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PrintWriter;

public class CaesarCipherServer {

    public static void main(String[] args) throws Exception {

        // create socket
        int port = 4444;
        ServerSocket serverSocket = new ServerSocket(port);
        System.err.println("Started server on port " + port);

        // repeatedly wait for connections, and process
        while (true) {

            // a "blocking" call which waits until a connection is requested
            Socket clientSocket = serverSocket.accept();
            System.err.println("Accepted connection from client");

            // open up IO streams
            BufferedReader in  = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
            OutputStream os = clientSocket.getOutputStream();
            PrintWriter out = new PrintWriter(os);


            // waits for data and reads it in until connection dies
            // readLine() blocks until the server receives a new line from client
            String s;
            while ((s = in.readLine()) != null) {
                out.append(s).append("\n").flush();
            }

            // close IO streams, then socket
            System.err.println("Closing connection with client");
            out.close();
            in.close();
            clientSocket.close();
        }
    }
}
