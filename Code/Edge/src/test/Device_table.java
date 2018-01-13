package test;

import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.List;
import test.Device;
import java.util.Date;
public class Device_table {
	public static List<Device> list = new ArrayList<Device>();
	public static void Add_ip(String ip){
		if(list.size()==0){
			Device a=new Device();
			a.setIP(ip);
			list.add(a);
		    String sr=HttpRequest.sendPost("http://localhost:3000/devices", "utf8=%E2%9C%93&device%5Bip%5D="+ip+"&device%5Bstatus%5D=Online&commit=Create+Device");
		    System.out.println(sr);
		}
		else{
			int flag=0;
			for (int i = 0; i < list.size(); i++) {
				if(list.get(i).getIP().equals(ip)){
					flag++;
				}
			}
			if(flag==0){
				Device b=new Device();
				b.setIP(ip);
				list.add(b);
			}
		}
	}
    public static Date gettime() throws ParseException{
    	Calendar calendar = Calendar.getInstance();  
        String str; 
        str = (new SimpleDateFormat("yyyy-MM-dd HH:mm:ss")).format(calendar.getTime());
        SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
        Date date=sdf.parse(str);
    	return date;
    }
	public static void Update_temp(int temp,String ip) throws ParseException{
		int flag=0;
		for (int i = 0; i < list.size(); i++) {
			if(list.get(i).getIP().equals(ip)){
				flag++;
				if(list.get(i).getTemp()!=temp){
					list.get(i).setTemp(temp);
					list.get(i).setUpdate_time(gettime());
				    String sr=HttpRequest.sendPost("http://localhost:3000/device/update_temp", "utf8=%E2%9C%93&device%5Bip%5D="+ip+"&device%5Btemp%5D="+temp);
				    String on=HttpRequest.sendPost("http://localhost:3000/device/device_online", "utf8=%E2%9C%93&device%5Bip%5D="+ip+"&device%5Btemp%5D="+temp);
				    System.out.println(on);
				    System.out.println(sr);
				}
				else{
					list.get(i).setUpdate_time(gettime());
				}
			}
		}
		if(flag==0){
			Device b=new Device();
			b.setIP(ip);
			b.setTemp(temp);
			b.setUpdate_time(gettime());
			String find=HttpRequest.sendPost("http://localhost:3000/devices", "utf8=%E2%9C%93&device%5Bip%5D="+ip+"&device%5Bstatus%5D=Online&commit=Create+Device");
		    String sr=HttpRequest.sendPost("http://localhost:3000/device/update_temp", "utf8=%E2%9C%93&device%5Bip%5D="+ip+"&device%5Btemp%5D="+temp);
		    String on=HttpRequest.sendPost("http://localhost:3000/device/device_online", "utf8=%E2%9C%93&device%5Bip%5D="+ip);
		    System.out.println(sr);
		    System.out.println(on);
			list.add(b);
		}
		
	}
}
