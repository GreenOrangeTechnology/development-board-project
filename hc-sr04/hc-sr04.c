#include <reg51.h>
//#include <intrins.h>
						 //�����������ʾ�ĺ���  ģ��ͨ�ŵĹ��� ����ֵ
sbit dula = P2^6;//	��ѡ�źŵ�����������
sbit wela = P2^7;// λѡ�źŵ�����������

unsigned char code wei[]={0xfe,0xfd,0xfb,0xf7,0xef,0xdf};
						//����ܸ�λ�����
unsigned char code duan[]={0x76,0x79,0x38,0x38,0x3f,0x80};//HELLO.
unsigned char code duanNum[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d};
						//0-5�����

unsigned char code total[6][16]={{0x38,0x19,0x29,0x31,0x39,0x39,0x39,0x39,0x39,0x39,0x39,0x39,0x39,0x39,0x39,0x39}, 
{0x09,0x09,0x09,0x09,0x01,0x09,0x09,0x09,0x09,0x09,0x09,0x09,0x09,0x09,0x09,0x08},
{0x09,0x09,0x09,0x09,0x09,0x01,0x09,0x09,0x09,0x09,0x09,0x09,0x09,0x09,0x08,0x09},
{0x09,0x09,0x09,0x09,0x09,0x09,0x01,0x09,0x09,0x09,0x09,0x09,0x09,0x08,0x09,0x09},
{0x09,0x09,0x09,0x09,0x09,0x09,0x09,0x01,0x09,0x09,0x09,0x09,0x08,0x09,0x09,0x09},
{0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x07,0x0a,0x0d,0x0e,0x0f,0x0f,0x0f,0x0f}};//תһȦ_

//ע��:�ְ��ֽ̳��ǹ��������,0�������۾��ǹ��������,��1����,�����ҵ������͵���λ
//dula��ѡ��welaλѡ:��������	   P0��������ѡλ��,0����ѡ��
//�����ÿ��ֻ����ʾһ������,����ʾ��ͨ���Ӿ�����ЧӦʵ�ֵ�
//���� ȥ��Ӱ 

void delay(unsigned int i)//�����ö�ʱ������
{
	unsigned int m,n;
	for(m=i;m>0;m--)
		for(n=90;n>0;n--);
}

void main()
{
	unsigned char num;
	unsigned char que;
	while(1)
	{
		//������Ȧ��ʾ
	for(que=0;que<16;que++)
		{
		
		for(num=0;num<6;num++)
		{
			P0=wei[num];	   
			wela=1;
			wela=0;

			P0=total[num][que];	  
			dula=1;
			dula=0;
			delay(2);	 //ʱ�����̣����ǹؼ�����ν��ͬʱ��ʾ��ֻ�Ǽ���϶̶��ѣ��������۵����ЧӦ������ÿ������ܶ�һֱ����--���� ȥ��Ӱ,��Ӱ����
		 }delay(100);	//Ϊʲô�ұ�һֱ��
		 }
		
		/*for(num=0;num<6;num++)
		{
			P0=wei[num];	   
			wela=1;
			wela=0;

			P0=duan[num];	  
			dula=1;
			dula=0;
			delay(1000);	 //ʱ�����̣����ǹؼ�����ν��ͬʱ��ʾ��ֻ�Ǽ���϶̶��ѣ��������۵����ЧӦ������ÿ������ܶ�һֱ����--���� ȥ��Ӱ,��Ӱ����
		 }*/
	}
	/*while(1)
	{
			P0=0x7d;	   
			wela=1;
			wela=0;

			P0=0x4f;	  //���֡�3���Ĵ���
			dula=1;
			dula=0;
			delay(1000);

			P0=0x00;	  //ʲô������ʾ�Ĵ���
			dula=1;
			dula=0;
			delay(1000);
	}	*/
	
}

/*

unsigned char a,b,c,d;
float num=0.0;
sbit du=P2^6;
sbit we= P2^7;
sbit send=P2^1;
sbit receive=P2^2;

unsigned char duan[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
unsigned char wei []={0xfe,0xfd,0xfb,0xf7,0x2f,0x1f};

void delay_10us()
{
_nop_();
_nop_();
_nop_();
_nop_();
_nop_();
_nop_(); 
}

void delay_200ms(void)
{
unsigned char i,j,k; 
for(i=5;i>0;i--)
for(j=132;j>0;j--)
for(k=150;k>0;k--); 
}

void main ()
{
unsigned int timeh,timel;
send=0;//������
while(1)
{
   receive=0;//����
   EA=0;
   send=1;
   delay_10us();
   delay_10us();//��ʱ20us
   send=0;
   while(receive==0)//�ȴ��ߵ�ƽ
   {};
   
   TMOD=0X01;//���ö�ʱ��0�Ĺ�����ʽ
   TH0=0;//����ֵ
   TL0=0;
   EA=1;///�����жϿ���
   ET0=1;//�򿪶�ʱ������
   TR0=1;
   while(receive)//�ȴ��͵�ƽ
   {
         
   }
    timeh=TH1;//ȡ����ʱ����ֵ
    timel=TL1;
    TR0=0;
  
    num=(TH0*255+TL0)/100.0*340/2;
    a=(unsigned int )num%10;//�����λʮλ��λ
    b=(unsigned int)num%100/10;
    c=(unsigned int )num/100%10;
    d=(unsigned int)num/10;
   
    P0=0xff;//�������ʾ���
    we=1;
    P0=0xfe;
    we=0;
    P0=0x00;
    du=1;
    P0=duan[a];
    delay_200ms();
    delay_200ms();
    delay_200ms();
    delay_200ms();
    delay_200ms();
    delay_200ms();
    delay_200ms();
    delay_200ms();
    P0=0x00;  
    du=0;
    
    P0=0xff;
    we=1;
    P0=0xfd;
    we=0;
    P0=0x00;
    du=1;
    P0=duan;
    delay_200ms();
    delay_200ms();
    delay_200ms();
    delay_200ms();
    delay_200ms();
    delay_200ms();
    delay_200ms();
    delay_200ms();
    P0=0x00;
    du=0;
    P0=0xff;
    we=1;
    P0=0xfb;
    we=0;
    P0=0x00;
    du=1;
    P0=duan[c];
    delay_200ms();
    delay_200ms();
    delay_200ms();
    delay_200ms();
    delay_200ms();
    delay_200ms();
    delay_200ms();
    delay_200ms();
    P0=0x00;
    du=0;
    P0=0xff;
    we=1;
    P0=0xf7;
    we=0;
    P0=0x00;
    du=1;
    P0=duan[d];
    delay_200ms();
    delay_200ms();
    delay_200ms();
    delay_200ms();
    delay_200ms();
    delay_200ms();
    P0=0x00;
    du=0;
}
   
}
void timer0 ()interrupt 1
{
TH0=0;
TL0=0;
}
*/