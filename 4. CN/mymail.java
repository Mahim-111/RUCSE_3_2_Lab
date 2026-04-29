import java.io.*;
import java.time.LocalDate;
import java.util.Base64;
import javax.net.ssl.*;

class MyMail {

    private static DataOutputStream dos;
    private static BufferedReader br;

    public static void main(String[] args) throws Exception {

        String user = "s2210176124@ru.ac.bd";
        String pass = "bmcdmmcrjqphjnky"; // App password

        // Encode credentials
        String username = Base64.getEncoder().encodeToString(user.getBytes());
        String password = Base64.getEncoder().encodeToString(pass.getBytes());

        // Connect to Gmail SMTP over SSL
        SSLSocket socket = (SSLSocket) SSLSocketFactory
                .getDefault()
                .createSocket("smtp.gmail.com", 465);

        dos = new DataOutputStream(socket.getOutputStream());
        br = new BufferedReader(new InputStreamReader(socket.getInputStream()));

        // Read initial response
        System.out.println("SERVER: " + br.readLine());

        // SMTP Commands
        send("EHLO smtp.gmail.com\r\n");
        readMultipleLines();

        send("AUTH LOGIN\r\n");
        System.out.println("SERVER: " + br.readLine());

        send(username + "\r\n");
        System.out.println("SERVER: " + br.readLine());

        send(password + "\r\n");
        System.out.println("SERVER: " + br.readLine());

        // MAIL FROM
        send("MAIL FROM:<" + user + ">\r\n");
        System.out.println("SERVER: " + br.readLine());

        // ============================
        // RECIPIENTS (IMPORTANT PART)
        // ============================

        // TO
        send("RCPT TO:<mahimbabu111111@gmail.com>\r\n");
        System.out.println("SERVER: " + br.readLine());

        // CC
        send("RCPT TO:<mahimgate@gmail.com>\r\n");
        System.out.println("SERVER: " + br.readLine());

        // BCC (hidden)
        send("RCPT TO:<babumahim169@gmail.com>\r\n");
        System.out.println("SERVER: " + br.readLine());

        // DATA
        send("DATA\r\n");
        System.out.println("SERVER: " + br.readLine());

        // ============================
        // EMAIL HEADERS
        // ============================

        send("FROM: " + user + "\r\n");
        send("TO: mahimbabu111111@gmail.com\r\n");
        send("CC: mahimgate@gmail.com\r\n");
        // ❌ No BCC here

        send("Subject: Email Test " + LocalDate.now() + "\r\n");

        // Important: blank line separates header & body
        send("\r\n");

        // BODY
        send("This is a test email sent using Java SMTP.\r\n");
        send("TO, CC, and BCC are working correctly.\r\n");

        // End of message
        send(".\r\n");
        System.out.println("SERVER: " + br.readLine());

        // QUIT
        send("QUIT\r\n");
        System.out.println("SERVER: " + br.readLine());

        socket.close();
    }

    // Send data to server
    public static void send(String data) throws Exception {
        dos.writeBytes(data);
        dos.flush();
        System.out.print("CLIENT: " + data);
        Thread.sleep(500);
    }

    // Read multiple response lines after EHLO
    public static void readMultipleLines() throws Exception {
        String line;
        while ((line = br.readLine()) != null) {
            System.out.println("SERVER: " + line);
            if (!line.startsWith("250-")) break;
        }
    }
}