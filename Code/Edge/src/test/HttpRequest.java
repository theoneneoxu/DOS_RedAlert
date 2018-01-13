package test;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.URL;
import java.net.URLConnection;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.List;
import java.util.Map;

public class HttpRequest {
    /**
     * send get and post
     * 
     * @param url
     *            send request to url
     * @param param
     *            parameters
     * @return URL result
     */
    public static String sendGet(String url, String param) {
        String result = "";
        BufferedReader in = null;
        try {
            String urlNameString = url + "?" + param;
            URL realUrl = new URL(urlNameString);
            // open the connection
            URLConnection connection = realUrl.openConnection();
            // set properties
            connection.setRequestProperty("accept", "*/*");
            connection.setRequestProperty("connection", "Keep-Alive");
            connection.setRequestProperty("user-agent",
                    "Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1;SV1)");
            // set connection
            connection.connect();
            // get response
            Map<String, List<String>> map = connection.getHeaderFields();

            for (String key : map.keySet()) {
                System.out.println(key + "--->" + map.get(key));
            }
            // use BufferedReader to read response
            in = new BufferedReader(new InputStreamReader(
                    connection.getInputStream()));
            String line;
            while ((line = in.readLine()) != null) {
                result += line;
            }
        } catch (Exception e) {
            System.out.println("error£¡" + e);
            e.printStackTrace();
        }
        // shut down
        finally {
            try {
                if (in != null) {
                    in.close();
                }
            } catch (Exception e2) {
                e2.printStackTrace();
            }
        }
        return result;
    }

    /**
     * send post to url
     * 
     * @param url
     *            send request
     * @param param
     *            parameters
     * @return result
     */
    public static String sendPost(String url, String param) {
        PrintWriter out = null;
        BufferedReader in = null;
        String result = "";
        try {
            URL realUrl = new URL(url);
            // open connection
            URLConnection conn = realUrl.openConnection();
            // set properties
            conn.setRequestProperty("accept", "*/*");
            conn.setRequestProperty("connection", "Keep-Alive");
            conn.setRequestProperty("user-agent",
                    "Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1;SV1)");
            conn.setDoOutput(true);
            conn.setDoInput(true);
            // get the output
            out = new PrintWriter(conn.getOutputStream());
            // send parameters
            out.print(param);
            // flush
            out.flush();
            in = new BufferedReader(
                    new InputStreamReader(conn.getInputStream()));
            String line;
            while ((line = in.readLine()) != null) {
                result += line;
            }
        } catch (Exception e) {
            System.out.println("error!"+e);
            e.printStackTrace();
        }
        //shut down
        finally{
            try{
                if(out!=null){
                    out.close();
                }
                if(in!=null){
                    in.close();
                }
            }
            catch(IOException ex){
                ex.printStackTrace();
            }
        }
        return result;
    }    

public static void main(String[] args) {
    //send get
    //String s=HttpRequest.sendGet("http://localhost:3000/devices", "");
    //System.out.println(s);
    
    //send post
	String ip="333";
    String sr=HttpRequest.sendPost("http://localhost:3000/device/button_alarm", "utf8=%E2%9C%93&device%5Bip%5D="+"192.168.19.138"+"&commit=Create+Device");
    System.out.println(sr);

}
}