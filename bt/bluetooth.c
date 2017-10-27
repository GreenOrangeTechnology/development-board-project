#include <reg52.h> //ͷ�ļ����ã�д����ʱ��Ҫ����
#include <stdlib.h>

#define uint unsigned int //�궨�壬Ϊ�˺��涨�������д���
#define uchar unsigned char

code unsigned char  LED[] ={~0xFE,~0xFD,~0xFB,~0xF7,~0xEF,~0xDF,~0xBF,~0x7F,~0xFF,~0x3F,~0x1F,~0x0F,~0x07,~0x03,~0x01,~0x00};
code unsigned char  LED2[] ={~0x3F,~0x06,~0x5B,~0x4F,~0x66,~0x6D,~0x7D,~0x07,~0x7F,~0x6F,~0x77,~0x7C,~0x39,~0x5E,~0x79,~0x71};

void main (void)
{
       SCON= 0x50;      // SCON: ģʽ1, 8-bit UART, ʹ�ܽ���
       TMOD|= 0x20;
       TH1=0xfd;           //������9600 ��ֵ
       TL1=0xfd;
       TR1=1;
       EA=1;                 //�����ж�
       ES=1;                 //�򿪴����ж�
       while(1)              //��ѭ�������κζ���
       {
       }
}

/******************************************************************/
/* �����жϳ���*/
/******************************************************************/
void UART_SER () interrupt 4
{
       uchar n;  //������ʱ����
       if(RI)           //�ж��ǽ����жϲ���
       {
              RI=0;    //��־λ����
              n=SBUF;//���뻺������ֵ
 
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
              SBUF=n;//�ѽ��յ���ֵ�ٷ���
       }
       if(TI)           //����Ƿ��ͱ�־λ������
       TI=0;
}

/*
#include <SoftwareSerial.h>
    SoftwareSerial BluetoothSerial(8, 9); // RX, TX
    char value;       //������ת����
    void setup() {
        //�򿪴���ͨ�ţ��ȴ��˿ڴ򿪣�
        Serial.begin(9600);
        while (!Serial) {
            ; // �ȴ��������ӡ�
        }
        Serial.println("Serial Connected!");

        // ������������ͨѶ������ HC06Ĭ����9600
        BluetoothSerial.begin(9600);
    }

    void loop() { // ѭ��
        if (Serial.available()) {   //��ⵥƬ������״̬
            value = Serial.read();
            BluetoothSerial.write(value);//����ģ�齫���ݷ��͸���Ƭ��
        }

        if (BluetoothSerial.available()) {//�������ģ�鴮��״̬
            value = BluetoothSerial.read();
            Serial.write(value); //��Ƭ����ָ��͵�����ģ��
        }

    }	*/