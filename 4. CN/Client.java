
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.net.Socket;
import java.util.Scanner;

public class Client {

    @SuppressWarnings("ConvertToTryWithResources")
    public static void main(String[] args) throws Exception {
        Socket socket = new Socket("localhost", 7777);
        DataInputStream dis = new DataInputStream(socket.getInputStream());
        DataOutputStream dos = new DataOutputStream(socket.getOutputStream());
        Scanner scanner = new Scanner(System.in);

        System.out.println("Connected to server");
        System.out.println("Commands: hello | date | time | ip | msg | exit");

        while (true) {
            System.out.println("ENTER COMMAND: ");
            String command = scanner.nextLine();
            dos.writeUTF(command);
            String response = dis.readUTF();
            System.out.println("Server: " + response);
            if (command.equalsIgnoreCase("exit")) {
                break;
            }
        }
        socket.close();
        scanner.close();
    }
}
