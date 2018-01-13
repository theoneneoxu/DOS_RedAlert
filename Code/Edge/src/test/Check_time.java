package test;

import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Calendar;

public class Check_time {
public void check() throws ParseException{
	if(Device_table.list.size()!=0){
	for (int i = 0; i < Device_table.list.size(); i++){
		long between=Device_table.gettime().getTime()-Device_table.list.get(i).getUpdate_time().getTime();
		if(between>10000){
            String off=HttpRequest.sendPost("http://localhost:3000/device/device_offline", "utf8=%E2%9C%93&device%5Bip%5D="+Device_table.list.get(i).getIP()+"&commit=Create+Device");
            System.out.println(off);
            Device_table.list.remove(i);
            i--;
		}		
	}
	}
}
public static void main(String[] args) throws Exception{
	String serverHost = "192.168.1.102";    
    int serverPort = 35274;
    UdpServerSocket udpServerSocket1 = new UdpServerSocket(serverHost, serverPort); 
	while(true){
		udpServerSocket1.send("192.168.19.102",35272, ("5100").getBytes());
        Thread.sleep(1000);
	}
}
}
