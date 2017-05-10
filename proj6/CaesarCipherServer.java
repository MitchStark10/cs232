
import java.net.Socket;
import java.net.ServerSocket;
import java.io.OutputStream;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.concurrent.*;

public class CaesarCipherServer {

    public static void main(String[] args) throws Exception {

        ExecutorService threadPool = Executors.newFixedThreadPool(8);

        // create socket
        int port = 4444;
        ServerSocket serverSocket = new ServerSocket(port);
        System.err.println("Started server on port " + port);

        // repeatedly wait for connections, and process
        while (true) {
            Socket clientSocket = serverSocket.accept();
            ConnectionCallable connection = new ConnectionCallable(clientSocket);
            threadPool.submit(connection);
        }
    }

    private static class ConnectionCallable implements Callable<Integer>
    {
        private Socket clientSocket;

        public ConnectionCallable(Socket socketConnection) {
            this.clientSocket = socketConnection;
        }

        public Integer call() throws Exception {
            // a "blocking" call which waits until a connection is requested
            Boolean firstInput = true;
            Integer cipherNum = 0;
            System.err.println("Accepted connection from client");

            // open up IO streams
            BufferedReader in  = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
            OutputStream os = clientSocket.getOutputStream();
            PrintWriter out = new PrintWriter(os);


            // waits for data and reads it in until connection dies
            // readLine() blocks until the server receives a new line from client
            String s;
            while ((s = in.readLine()) != null) {
                if (firstInput) {
                    try {
                        cipherNum = Integer.parseInt(s);
                        out.append(cipherNum.toString()).append("\n").flush();
                        firstInput = false;
                        continue;
                    } catch (NumberFormatException ex) {
                        out.append("1st input must be an integer 1-25").flush();
                        break;
                    }
                }

                //cipher logic
                out.append(createCipher(s, cipherNum)).append("\n").flush();
            }

            // close IO streams, then socket
            System.err.println("Closing connection with client");
            out.close();
            in.close();
            clientSocket.close();
            return 0;
        }
    }

    /*
    Takes a regular string, and ciphers it using the given cipherNum
    */
    private static String createCipher(String s, Integer cipherNum) {
        String cipheredString = "";
	    for(int x = 0; x < s.length(); x++) {
            char c = (char)(s.charAt(x) + cipherNum);
		    if (c > 'z') {
			    cipheredString += (char)(s.charAt(x) - (26 - cipherNum));
		    }
		    else {
			    if (Character.isLetter(c)) {
				    cipheredString += c;
			    } else {
				    cipheredString += s.charAt(x);
			    }
		    }
	   }
	   return cipheredString;
    }
}
