package test;

	import java.io.IOException;    
	import java.net.DatagramPacket;    
	import java.net.DatagramSocket;    
	import java.net.InetAddress;    
	import java.net.InetSocketAddress;    
	import java.net.SocketException;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;
import test.Device_table;
	      
	public class UdpServerSocket {    
	    private byte[] buffer = new byte[1024];    
	        
	    private DatagramSocket ds = null;    
	    
	    private DatagramPacket packet = null;    
	    
	    private InetSocketAddress socketAddress = null;    
	    
	    private String orgIp;    
	    
  
	    public UdpServerSocket(String host, int port) throws Exception {    
	        socketAddress = new InetSocketAddress(host, port);    
	        ds = new DatagramSocket(socketAddress);    
	        System.out.println("Edge Online!");    
	    }    
	        
	    public final String getOrgIp() {    
	        return orgIp;    
	    }    
	    
  
	    public final void setSoTimeout(int timeout) throws Exception {    
	        ds.setSoTimeout(timeout);    
	    }    
	    
  
	    public final int getSoTimeout() throws Exception {    
	        return ds.getSoTimeout();    
	    }    
	    
  
	    public final void bind(String host, int port) throws SocketException {    
	        socketAddress = new InetSocketAddress(host, port);    
	        ds = new DatagramSocket(socketAddress);    
	    }    
  
	    public final String getip(){
	    	return packet.getAddress().getHostAddress();
	    	
	    }
	    public final String receive() throws IOException {    
	        packet = new DatagramPacket(buffer, buffer.length);    
	        ds.receive(packet);    
	        orgIp = packet.getAddress().getHostAddress();    
	        String info = new String(packet.getData(), 0, packet.getLength());    
	        System.out.println("Received message£º" + info);    
	        return info;    
	    }    
	      
	    public final void response(String info) throws IOException {    
	        System.out.println("Client IP : " + packet.getAddress().getHostAddress()    
	                + ",port£º" + packet.getPort());    
	        DatagramPacket dp = new DatagramPacket(buffer, buffer.length, packet    
	                .getAddress(), packet.getPort());    
	        dp.setData(info.getBytes());    
	        ds.send(dp);    
	    }    
	    

	    public final void setLength(int bufsize) {    
	        packet.setLength(bufsize);    
	    }    
	    

	    public final InetAddress getResponseAddress() {    
	        return packet.getAddress();    
	    }    

	    public final int getResponsePort() {    
	        return packet.getPort();    
	    }    
	    
	    /**  
	     * close port 
	     */    
	    public final DatagramPacket send(final String host, final int port,    
	            final byte[] bytes) throws IOException {    
	        DatagramPacket dp = new DatagramPacket(bytes, bytes.length, InetAddress    
	                .getByName(host), port);    
	        ds.send(dp);    
	        return dp;    
	    }    
	    
	    public final void close() {    
	        try {    
	            ds.close();    
	        } catch (Exception ex) {    
	            ex.printStackTrace();    
	        }     
	    }    
	    
	    public static void main(String[] args) throws Exception {  
	    	String[] message;
	        String serverHost = "192.168.1.102";    
	        int serverPort = 35272;
	        UdpServerSocket udpServerSocket = new UdpServerSocket(serverHost, serverPort);    
	        while (true) {  
//	        	udpServerSocket.send("192.168.1.101",7, ("3100").getBytes());   
	            message=udpServerSocket.receive().split("\\|");
	            switch(message[0]){
	            case "1100":
	            	Device_table.Add_ip(udpServerSocket.getip());
	            	udpServerSocket.send(udpServerSocket.getip(),35271, ("1101").getBytes());
	            	break;
	            case "2100":
	                String sensor=HttpRequest.sendPost("http://localhost:3000/device/sensor_alarm", "utf8=%E2%9C%93&device%5Bip%5D="+udpServerSocket.getip()+"&commit=Create+Device");
	                System.out.println(sensor);
	                break;
	            case "2200":
	                String button=HttpRequest.sendPost("http://localhost:3000/device/button_alarm", "utf8=%E2%9C%93&device%5Bip%5D="+udpServerSocket.getip()+"&commit=Create+Device");
	                System.out.println(button);
	                break;
	            case "4100":
	            	Device_table.Update_temp(Integer.parseInt(message[1]), udpServerSocket.getip());
	            	break;
	            case "3100":
	            	for (int i = 0; i < Device_table.list.size(); i++) {
	            		udpServerSocket.send(Device_table.list.get(i).getIP(),35271, ("3100").getBytes()); 
	            	}	
	            	break;
	            case "5100":
	                Check_time c=new Check_time();
	                c.check();
	                break;
	            }
	        }    
	    }    
	}   

