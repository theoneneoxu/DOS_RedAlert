package test;

import java.util.Date;

public class Device {
String IP;
int Temp;
Date Update_time;
public String getIP() {
	return IP;
}
public void setIP(String iP) {
	IP = iP;
}
public int getTemp() {
	return Temp;
}
public void setTemp(int temp) {
	Temp = temp;
}
public Date getUpdate_time() {
	return Update_time;
}
public void setUpdate_time(Date update_time) {
	Update_time = update_time;
}
}
