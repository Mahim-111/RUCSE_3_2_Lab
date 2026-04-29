
import java.net.ServerSocket;
import java.net.Socket;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.time.LocalDate;
import java.time.LocalTime;

public class Server {

    @SuppressWarnings("ConvertToTryWithResources")
    public static void main(String[] args) throws Exception {
        ServerSocket serverSocket = new ServerSocket(7777);
        System.out.println("Server started on port 7777...");

        Socket socket = serverSocket.accept();
        System.out.println("Client connected");

        DataInputStream dis = new DataInputStream(socket.getInputStream());
        DataOutputStream dos = new DataOutputStream(socket.getOutputStream());

        while (true) {
            String command = dis.readUTF();
            System.out.println("Client: " + command);
            if (command.equalsIgnoreCase("exit")) {
                dos.writeUTF("Connection closed");
                break;
            } else if (command.equalsIgnoreCase("hello")) {
                dos.writeUTF("Hi");
            } else if (command.equalsIgnoreCase("date")) {
                dos.writeUTF(LocalDate.now().toString());
            } else if (command.equalsIgnoreCase("time")) {
                dos.writeUTF(LocalTime.now().toString());
            } else if (command.equalsIgnoreCase("ip")) {
                dos.writeUTF(socket.getInetAddress().getHostAddress());
            } else if (command.toLowerCase().startsWith("msg ")) {
                String message = command.substring(4);
                dos.writeUTF("You said: " + message);
            } else {
                dos.writeUTF("Unknown command");
            }
        }
        socket.close();
        serverSocket.close();
    }
}
