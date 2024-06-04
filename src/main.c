#include <reg52.h>
#include "ds1302.h"
#include "lcd.h"
#include "dht11.h"
#include "jq8900.h"
#include "key.h"
#include "lunar.h"
#include "lunarword.h"

sbit Fire = P1 ^ 1;
uchar timedata[7];
CLOCKTIME clockTime = {24,14};
TIME currentTime;
uchar UART_buff;
DHT dht;
uchar pmFlag=0;
uchar menuFlag = 1;
uchar mainFlag = 1;
uchar clockFlag = 0;
uchar musicFlag = 1;
uchar selectSong = 1;
uchar datachangeFlag = 0;
uchar ClockTimeSetSelect=0;
uchar weatherFlag;
unsigned char keyNum, TimeSetSelect = 0;
uchar lunar[2];
void AlarmMode();
void lunarMode();
void Menu();

void fireMode()
{
	uchar alarmkeyNum;
	SendData(0x0a);
	SendData(6);
	SendData(0x0b);
	while(1)
	{
		alarmkeyNum = key_scan();
		LCD_ShowString(1,"火灾来了");
		LCD_ShowString(2,"火灾来了");
		LCD_ShowString(3,"火灾来了");
		LCD_ShowString(4,"任意键取消");
		if(alarmkeyNum != 0)
		{
			SendData(0x13);
			LCD_ClearScreen();
			clockFlag = 0;
			break;
		}	
	}	
}

void TimeShow()
{
	LCD_ShowChar(1,8," ");
	if(Fire == 0)//出现火灾
	{
		fireMode();
	}
	if(clockFlag == 0)
	{
		lunarMode();
	}
	LCD_ShowChar(3,1,"Tem");
	LCD_ShowNum(3, 3, dht.shidu, 2);
	LCD_ShowChar(3,5,"Hum");
	LCD_ShowNum(3, 7, dht.wendu, 2);
	read_time(timedata);
	currentTime.year = timedata[6];
	currentTime.mon = timedata[4];
	currentTime.day = timedata[3];
	currentTime.hour = timedata[2];
	currentTime.min = timedata[1];
	currentTime.sec = timedata[0];
	TimeToChar(&currentTime,pmFlag);
	LCD_ShowString(1, currentTime.date);
	LCD_ShowString(2, currentTime.times);
	if(pmFlag == 1)
	{
		if(timedata[2] > 12) {LCD_ShowChar(2,6,"PM");}
		else if(timedata[2] < 12) {LCD_ShowChar(2,6,"AM");}
	}	
	if(clockFlag == 1)
	{
		LCD_ShowString(4,"闹钟：开");
		if(currentTime.hour == clockTime.hour && currentTime.min == clockTime.min)
		{
			AlarmMode();
		}
	}
}

void blueTimeChange()
{	
	LCD_ShowChar(1,8,"+");
	if(clockFlag == 0)
	{
		lunarMode();
	}
	LCD_ShowChar(3,1,"Tem");
	LCD_ShowNum(3, 3, dht.shidu, 2);
	LCD_ShowChar(3,5,"Hem");
	LCD_ShowNum(3, 7, dht.wendu, 2);
	set_time(timedata);
	read_time(timedata);
	currentTime.year = timedata[6];
	currentTime.mon = timedata[4];
	currentTime.day = timedata[3];
	currentTime.hour = timedata[2];
	currentTime.min = timedata[1];
	currentTime.sec = timedata[0];
	TimeToChar(&currentTime,pmFlag);
	LCD_ShowString(1, currentTime.date);
	LCD_ShowString(2, currentTime.times);
	if(pmFlag == 1)
	{
		if(timedata[2] > 12) {LCD_ShowChar(2,6,"PM");}
		else if(timedata[2] < 12) {LCD_ShowChar(2,6,"AM");}
	}	
	if(clockFlag == 1)
	{
		LCD_ShowString(4,"闹钟：开");
		if(currentTime.hour == clockTime.hour && currentTime.min == clockTime.min)
		{
			AlarmMode();
		}
	}	
}

void lunarMode()
{
	uchar i,mon,day;
	unsigned char yue[]="月";
	uchar lunarChar[16] = "                ";
	uchar lunarYearIndex,dizhiIndex,jieqiIndex;;
	read_time(timedata);
	turnToLunar(&currentTime, lunar);
	mon = lunar[0];
	day = lunar[1];
	lunarYearIndex = (currentTime.year%10)*2;
	dizhiIndex = ((2000+currentTime.year)%12)*2+20;
	jieqiIndex = getSolarIndex(&currentTime)*4;
	if(lunarYearIndex==0)lunarYearIndex=22;
	for (i=0; i<2; i++)
	{
		lunarChar[i] = lunarYear[lunarYearIndex+i-1];
		lunarChar[i+2] = lunarYear[dizhiIndex+i-1];
		lunarChar[i+4] = Solar[jieqiIndex+i];
		lunarChar[i+6] = Solar[jieqiIndex+i+2];
		lunarChar[i+4+4] = nong[2*mon+i-2];
		lunarChar[6+4] = yue[0];
		lunarChar[7+4] = yue[1];
	}
	if (day <= 10)
		for (i=0; i<2; i++)
		{
			lunarChar[i+8+4] = nong[26+i-2];
			lunarChar[i+10+4] = newDay[2 * (lunar[1] - 1) + i];//1-10
		} 
	else if ((day > 10) && (day <= 19))
		for (i=0; i<2; i++)
		{
			lunarChar[i+8+4] = nong[20+i-2];
			lunarChar[i+10+4] = newDay[2 * (lunar[1] - 10 - 1) + i];//1-10
		} 
	else
		for (i=0; i<2; i++)
		{
			lunarChar[i+8+4] = nong[28+i-2];
			lunarChar[i+10+4] = newDay[2 * (lunar[1] - 20 - 1) + i];//1-10
		}		
	LCD_ShowString(4,lunarChar);
}


void TimeSet()
{
	LCD_ShowString(1, currentTime.date);
	LCD_ShowString(2, currentTime.times);
	LCD_ShowString(4, "3add 4diff");
    switch (TimeSetSelect) {
        case 0:
            LCD_ShowString(3, "修改秒");
            break;
        case 1:
            LCD_ShowString(3, "修改分");
            break;
        case 2:
            LCD_ShowString(3, "修改时");
            break;
        case 3:
            LCD_ShowString(3, "修改日");
            break;
        case 4:
            LCD_ShowString(3, "修改月");
            break;
        case 5:
            LCD_ShowString(3, "修改年");
            break;
        case 6:
            LCD_ShowString(3, "key3->AMPMchange");
            break;
    }
	if (keyNum == 2)
	{
		TimeSetSelect++;
		TimeSetSelect %= 7;
	}
	else if(keyNum==3 || keyNum==4) //按键3和4用来确认或者加减
	{
		if(TimeSetSelect==0)
		{
			if(keyNum==3){timedata[0]++;}
			if(keyNum==4){timedata[0]--;}
			if(timedata[0]<0)
				timedata[0]=59;
			else if(timedata[0]>59)
				timedata[0]=0;
			currentTime.sec = timedata[0];
			TimeToChar(&currentTime,pmFlag);
			LCD_ShowString(2, currentTime.times);
		}
		if(TimeSetSelect==1)
		{
			if(keyNum==3){timedata[1]++;}
			if(keyNum==4){timedata[1]--;}
			if(timedata[1] < 0)
				timedata[1]=59;
			else if(timedata[1]>59)
				timedata[1]=0;
			currentTime.min = timedata[1];
			TimeToChar(&currentTime,pmFlag);
			LCD_ShowString(2, currentTime.times);
		}
		if(TimeSetSelect==2)
		{
			if(keyNum==3){timedata[2]++;}
			if(keyNum==4){timedata[2]--;}
			if(timedata[2] < 0)
				timedata[2]=23;
			else if(timedata[2] > 23)
				timedata[2]=0;
			currentTime.hour = timedata[2];
			TimeToChar(&currentTime,pmFlag);
			LCD_ShowString(2, currentTime.times);
		}
		
		if(TimeSetSelect==3)
		{
			if(keyNum==3){timedata[3]++;}
			if(keyNum==4){timedata[3]--;}
			if(timedata[3] <= 0){timedata[3]=31;}
			else if(timedata[3] > 31)
				timedata[3]=1;
			currentTime.day = timedata[3];
			TimeToChar(&currentTime,pmFlag);
			LCD_ShowString(1, currentTime.date);
		}
		
		if(TimeSetSelect==4)
		{
			if(keyNum==3){timedata[4]++;}
			if(keyNum==4){timedata[4]--;}
			if(timedata[4]<= 0)
				timedata[4]=12;
			else if(timedata[4]>12)
				timedata[4]=1;
			currentTime.mon = timedata[4];
			TimeToChar(&currentTime,pmFlag);
			LCD_ShowString(1, currentTime.date);
		}	
		if(TimeSetSelect==5)
		{
			if(keyNum==3){timedata[6]++;}
			if(keyNum==4){timedata[6]--;}
			if(timedata[6]<=0)
				timedata[6]=99;
			else if(timedata[6]>99)
				timedata[6]=1;
			currentTime.year = timedata[6];
			TimeToChar(&currentTime,pmFlag);
			LCD_ShowString(1, currentTime.date);
		}		
		if (TimeSetSelect == 6)
		{
			if (pmFlag == 0)
			{
				pmFlag = 1;
			}
			else if (pmFlag == 1)
			{
				pmFlag = 0;
			}
		}
	}
	set_time(timedata);
}

//设置闹钟模式
void ClockMode()
{
	LCD_ShowString(1,"闹钟模式");
	LCD_ShowNum(3, 1, clockTime.hour, 2);
	LCD_ShowChar(3, 2,":");
	LCD_ShowNum(3,3, clockTime.min, 2);
	if(selectSong == 1)
	{
		LCD_ShowString(4,"音乐：杰尼龟");
	}
	else if(selectSong == 2)
	{
		LCD_ShowString(4,"音乐：记念");
	}
	else if(selectSong == 3)
	{
		LCD_ShowString(4,"音乐：我记得");
	}
	else if(selectSong == 4)
	{
		LCD_ShowString(4,"音乐：水星记");
	}
	else if(selectSong == 5)
	{
		LCD_ShowString(4,"音乐：Cruel");
	}
	
	if(clockFlag == 0)
	{
		LCD_ShowString(2,"状态：关");
	}
	else if (clockFlag == 1)
	{
		LCD_ShowString(2,"状态：开");
	}
	
	if(keyNum == 2)
	{
		ClockTimeSetSelect++;
		ClockTimeSetSelect %= 3;
	}
	
	else if(keyNum == 3 || keyNum == 4)
	{
		if(ClockTimeSetSelect == 0)
		{
			if(keyNum == 3)
			{
				clockTime.min++;
			}
			else if (keyNum == 4)
			{
				clockTime.min--;
			}
			if(clockTime.min<0){clockTime.min = 59;}
			else if(clockTime.min>59){clockTime.min = 0;}
			LCD_ShowNum(3,3, clockTime.min, 2);
		}
		else if(ClockTimeSetSelect == 1)
		{
			if(keyNum == 3)
			{
				clockTime.hour++;
			}
			else if (keyNum == 4)
			{
				clockTime.hour--;
			}
			if(clockTime.hour<0){clockTime.hour = 23;}
			else if(clockTime.hour>23){clockTime.hour = 0;}
			LCD_ShowNum(3, 1, clockTime.hour, 2);
		}
		else if(ClockTimeSetSelect == 2)
		{
			if(clockFlag == 0)
				clockFlag = 1;
			else if(clockFlag == 1)
				clockFlag = 0;
			if(clockFlag == 0)
			{
				LCD_ShowString(2,"状态：关");
			}
			else if (clockFlag == 1)
			{
				LCD_ShowString(2,"状态：开");
			}			
		}
	}
}

//选择音乐模式
void MusicMode()
{
	uchar musicKey;
	while(1)
	{
		musicKey = key_scan();
		LCD_ShowString(1,"请选择音乐");
		if (musicFlag == 1)
		{
			LCD_ShowString(2,"1.杰尼龟     <-");
			LCD_ShowString(3,"2.记念         ");
			LCD_ShowString(4,"3.我记得       ");				
		}
		else if (musicFlag == 2)
		{
			LCD_ShowString(2,"1.杰尼龟       ");
			LCD_ShowString(3,"2.记念       <-");
			LCD_ShowString(4,"3.我记得       ");			
		}
		else if (musicFlag == 3)
		{
			LCD_ShowString(2,"1.杰尼龟       ");
			LCD_ShowString(3,"2.记念         ");
			LCD_ShowString(4,"3.我记得     <-");			
		}
		else if (musicFlag == 4)
		{
			LCD_ShowString(2,"2.记念         ");
			LCD_ShowString(3,"3.我记得       ");
			LCD_ShowString(4,"4.水星记     <-");			
		}
		else if (musicFlag == 5)
		{
			LCD_ShowString(2,"3.我记得       ");
			LCD_ShowString(3,"4.水星记       ");
			LCD_ShowString(4,"5.Cruel 	    <-");			
		}
		
		if(musicKey == 2)
		{
			musicFlag++;
			if(musicFlag>5) {musicFlag=1;}
		}
		else if(musicKey == 3)
		{
			selectSong = musicFlag;
			menuFlag = 4;
			LCD_ClearScreen();
			break;
		}
		else if(musicKey == 1)
		{
			LCD_ClearScreen();
			Menu();
			break;
		}
	}
}

//报警模式进行闹钟声光报警
void AlarmMode()
{
	uchar alarmkeyNum;
	SendData(0x0a);
	SendData(selectSong);
	SendData(0x0b);
	while(1)
	{
		alarmkeyNum = key_scan();
		LCD_ShowString(1,"闹钟到了");
		LCD_ShowString(2,"闹钟到了");
		LCD_ShowString(3,"闹钟到了");
		LCD_ShowString(4,"任意键取消");
		if(alarmkeyNum != 0)
		{
			SendData(0x13);
			LCD_ClearScreen();
			clockFlag = 0;
			break;
		}	
	}

}

void Menu()
{
	uchar KeyNum1;
	while(1)
	{
		KeyNum1 = key_scan();
		if(KeyNum1 == 2)
		{
			menuFlag++;
			if(menuFlag==7) {menuFlag = 1;}
		}
		else if(KeyNum1 == 3)
		{
			LCD_ClearScreen();
			break;
		}
		else if(KeyNum1 == 4)
		{
			menuFlag = 2;
			LCD_ClearScreen();
			break;
		}		
		if(menuFlag==1)
		{
			LCD_ShowString(1, "S2选S3进S4退");
			LCD_ShowString(2, "1.主页面         ");
			LCD_ShowString(3, "2.时间修改       ");
			LCD_ShowString(4, "3.设置闹钟       ");
		}
		else if (menuFlag == 2)
		{
			LCD_ShowString(1, "S2选S3进S4退");
			LCD_ShowString(2, "1.主页面      <-");
			LCD_ShowString(3, "2.时间修改      ");
			LCD_ShowString(4, "3.设置闹钟       ");
		}
		else if (menuFlag == 3)
		{
			LCD_ShowString(1, "S2选S3进S4退");
			LCD_ShowString(2, "1.主页面        ");
			LCD_ShowString(3, "2.时间修改    <-");
			LCD_ShowString(4, "3.设置闹钟      ");
		}
		else if (menuFlag == 4)
		{
			LCD_ShowString(1, "S2选S3进S4退");
			LCD_ShowString(2, "1.主页面        ");
			LCD_ShowString(3, "2.时间修改      ");
			LCD_ShowString(4, "3.设置闹钟    <-");
		}
		else if (menuFlag == 5)
		{
			LCD_ShowString(1, "1.主页面       ");
			LCD_ShowString(2, "2.时间修改      ");
			LCD_ShowString(3, "3.设置闹钟      ");
			LCD_ShowString(4, "4.天气模式    <-");
		}
		else if (menuFlag == 6)
		{
			LCD_ShowString(1, "2.时间修改      ");
			LCD_ShowString(2, "3.设置闹钟      ");
			LCD_ShowString(3, "4.天气模式      ");
			LCD_ShowString(4, "5.音乐选择    <-");
		}
	}
}

void WeatherMode()
{
	LCD_ShowString(1,"在线获取天气");
	LCD_ShowString(4,"崇新学堂倾力打造");
	if(weatherFlag==27)
	{
		LCD_ShowString(2,"晴天");
		LCD_ShowString(3,"适合吹空调");
	}
	else if(weatherFlag==28)
	{
		LCD_ShowString(2,"多云");
		LCD_ShowString(3,"适合户外运动");
	}
	else if(weatherFlag==29)
	{
		LCD_ShowString(2,"少云");
	}
	else if(weatherFlag==30)
	{
		LCD_ShowString(2,"晴间多云");
	}
	else if(weatherFlag==31)
	{
		LCD_ShowString(2,"阴天");
		LCD_ShowString(3,"适合呆宿舍");
	}
	else if(weatherFlag==36)
	{
		LCD_ShowString(2,"小雨天");
		LCD_ShowString(3,"呼吸新鲜空气");
	}
	else if(weatherFlag==37)
	{
		LCD_ShowString(2,"中雨天");
		LCD_ShowString(3,"适合点外卖");
	}
	else if(weatherFlag==38)
	{
		LCD_ShowString(2,"暴雨天");
		LCD_ShowString(3,"适合睡觉  ");
	}
}



void UsartInit()
{
	SCON=0X50;			//设置为工作方式1
	TMOD=0X20;			//设置计数器工作方式2
	PCON=0X00;			//波特率加倍
	TH1=0XFD;				//计数器初始值设置，注意波特率是4800的
	TL1=0XFD;
	ES=1;						//打开接收中断
	EA=1;						//打开总中断
	TR1=1;					//打开计数器
}


void ser_int (void) interrupt 4   
{	 
    if(RI == 1) {  //如果收到.  
      RI = 0;      //清除标志.  
      UART_buff = SBUF;  //接收.
	if(UART_buff >= 27) 
	{		
		weatherFlag = UART_buff;
	}
	if(UART_buff==1)
	 {	
		 if(pmFlag==1)
	 		pmFlag=0;
		 else
			pmFlag=1;
	 }	
	else if(UART_buff==2) 
	{
		 if(clockFlag==1)
			clockFlag=0;
		 else
			clockFlag=1;
	}
	else if(UART_buff==3) 
	{
		 timedata[2]++;
	}
	else if(UART_buff==4) 
	{
		 timedata[2]--;
	}
	else if(UART_buff==5) 
	{
		 timedata[1]++;
	}
	else if(UART_buff==6) 
	{
		 timedata[1]--;
	}
	else if(UART_buff==7) 
	{
		 timedata[0]++;
	}
	else if(UART_buff==8) 
	{
		 timedata[0]--;
	}
	else if(UART_buff==9) 
	{
		 timedata[6]++;
	}
	else if(UART_buff==10) 
	{
		 timedata[6]--;
	}
	else if(UART_buff==11) 
	{
		 timedata[4]++;
	}
	else if(UART_buff==12) 
	{
		 timedata[4]--;
	}
	else if(UART_buff==13) 
	{
		 timedata[3]++;
	}
	else if(UART_buff==14) 
	{
		 timedata[3]--;
		 if(timedata[3] <= 0){timedata[3]=31;}
	}
	else if(UART_buff==15) 
	{		
		 if(datachangeFlag==1)
			datachangeFlag=0;
		 else
			datachangeFlag=1;		
	}
	else if(UART_buff==16) 
	{		
		selectSong = 1;//杰尼龟
	}
	else if(UART_buff==17) 
	{		
		selectSong = 2;//记念
	}
	else if(UART_buff==18) 
	{
		clockTime.hour++;
	}
	else if(UART_buff==19) 
	{		
		clockTime.hour--;
	}
	else if(UART_buff==20) 
	{		
		clockTime.min++;
	}
	else if(UART_buff==21) 
	{		
		clockTime.min--;
	}
	else if(UART_buff==22) 
	{		
		selectSong = 3;//我记得
	}
	else if(UART_buff==23) 
	{		
		selectSong = 4;//水星记
	}
	else if(UART_buff==24) 
	{		
		selectSong = 5;//Cruel
	}
	else if(UART_buff==25) 
	{		
		SendData(0x0a);
		SendData(selectSong);
		SendData(0x0b);
	}
	else if(UART_buff==26) 
	{		
		SendData(0x13);
	}	
	} 
	
  
}
void main()
{
	Lcd_Init();
	UsartInit();
	Ds1302Init();
	TemHum((uchar *)&dht);

	while (1)
	{

		keyNum = key_scan();
		if (keyNum == 1)
		{
			Menu();
			if (mainFlag == 1) {mainFlag=0;}
		}
		if (mainFlag == 1)
		{
			if(datachangeFlag==0){TimeShow();}
			else if(datachangeFlag==1){blueTimeChange();}
		}	
		
		switch (menuFlag)
		{
		case 2:
			if(datachangeFlag==0){TimeShow();}
			else if(datachangeFlag==1){blueTimeChange();}
			break;
		case 3:
			TimeSet();
			break;
		case 4:
			ClockMode();
			break;
		case 5:
			WeatherMode();
			break;
		case 6:
			MusicMode();
			break;
		}
	}
}


