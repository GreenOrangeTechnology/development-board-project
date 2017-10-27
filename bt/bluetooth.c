#include <reg52.h> //头文件调用，写程序时都要加上
#include <stdlib.h>

#define uint unsigned int //宏定义，为了后面定义变量书写简便
#define uchar unsigned char

code unsigned char  LED[] ={~0xFE,~0xFD,~0xFB,~0xF7,~0xEF,~0xDF,~0xBF,~0x7F,~0xFF,~0x3F,~0x1F,~0x0F,~0x07,~0x03,~0x01,~0x00};
code unsigned char  LED2[] ={~0x3F,~0x06,~0x5B,~0x4F,~0x66,~0x6D,~0x7D,~0x07,~0x7F,~0x6F,~0x77,~0x7C,~0x39,~0x5E,~0x79,~0x71};

void main (void)
{
       SCON= 0x50;      // SCON: 模式1, 8-bit UART, 使能接收
       TMOD|= 0x20;
       TH1=0xfd;           //波特率9600 初值
       TL1=0xfd;
       TR1=1;
       EA=1;                 //打开总中断
       ES=1;                 //打开串口中断
       while(1)              //主循环不做任何动作
       {
       }
}

/******************************************************************/
/* 串口中断程序*/
/******************************************************************/
void UART_SER () interrupt 4
{
       uchar n;  //定义临时变量
       if(RI)           //判断是接收中断产生
       {
              RI=0;    //标志位清零
              n=SBUF;//读入缓冲区的值
 
              switch(n)
              {
                     case'0':P1=~LED[0];break;
                     case'1':P1=~LED[1];break;
                     case'2':P1=~LED[2];break;
                     case'3':P1=~LED[3];break;
                     case'4':P1=~LED[4];break;
                     case'5':P1=~LED[5];break;
                     case'6':P1=~LED[6];break;
                     case'7':P1=~LED[7];break;
                     case'8':P1=~LED[8];break;
                     case'9':P1=~LED[9];break;
                     case'A':P1=~LED[10];break;
                     case'B':P1=~LED[11];break;
                     case'C':P1=~LED[12];break;
                     case'D':P1=~LED[13];break;
										 case'E':P1=~LED[14];break;
										 case'F':P1=~LED[15];break;
                     default: P1=~LED[0];
              }
							
              TI=1;
              SBUF=n;//把接收到的值再发回
       }
       if(TI)           //如果是发送标志位，清零
       TI=0;
}

/*
#include <SoftwareSerial.h>
    SoftwareSerial BluetoothSerial(8, 9); // RX, TX
    char value;       //用于中转数据
    void setup() {
        //打开串行通信，等待端口打开：
        Serial.begin(9600);
        while (!Serial) {
            ; // 等待串口连接。
        }
        Serial.println("Serial Connected!");

        // 设置蓝牙串口通讯的速率 HC06默认是9600
        BluetoothSerial.begin(9600);
    }

    void loop() { // 循环
        if (Serial.available()) {   //检测单片机串口状态
            value = Serial.read();
            BluetoothSerial.write(value);//蓝牙模块将数据发送给单片机
        }

        if (BluetoothSerial.available()) {//检测蓝牙模块串口状态
            value = BluetoothSerial.read();
            Serial.write(value); //单片机将指令发送到蓝牙模块
        }

    }	*/