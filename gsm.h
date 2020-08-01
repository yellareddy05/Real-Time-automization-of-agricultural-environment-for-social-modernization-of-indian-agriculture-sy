 void gsminit()
 {

	//	 while(1)
	//	{
		 string_0("AT\r\n");	
	//	 rec=receive_0();
	//	 if((rec=='O')||(rec=='K'))
	//	 break;
	//	}
	  delay(1400);
		string_0("AT+CREG?\r\n");//network registration command
		delay(1400);
		string_0("AT+CMGF=1\r\n"); //flash message to read message
		delay(1400);
		string_0("AT+CNMI=1,2,0,0\r\n");	//new message to read message
		delay(1400);
		
		stringlcd(0x80,"Modem Intilized..");
 }
 void sendmsg(unsigned char *num,unsigned char *chrm)
{													                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             
int i=0;
string_0("AT+CMGS=\"");
for(i=0;num[i]!='\0';i++)
{
	send_0(num[i]);	 //number sending
}
	string_0("\"\r\n");
	delay(3000);

for(i=0;chrm[i]!='\0';i++)
{
	send_0(chrm[i]); //string
}
	  //gps();
//	send_0(0x1a);  //control+z()1a)
//	delay(1400);
//	stringlcd(0X01,"MSG SENT ");
}

