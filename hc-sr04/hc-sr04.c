#include <reg51.h>
//#include <intrins.h>
						 //数码管数字显示的含义  模块通信的过程 返回值
sbit dula = P2^6;//	段选信号的锁存器控制
sbit wela = P2^7;// 位选信号的锁存器控制

unsigned char code wei[]={0xfe,0xfd,0xfb,0xf7,0xef,0xdf};
						//数码管各位的码表
unsigned char code duan[]={0x76,0x79,0x38,0x38,0x3f,0x80};//HELLO.
unsigned char code duanNum[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d};
						//0-5的码表

unsigned char code total[6][16]={{0x38,0x19,0x29,0x31,0x39,0x39,0x39,0x39,0x39,0x39,0x39,0x39,0x39,0x39,0x39,0x39}, 
{0x09,0x09,0x09,0x09,0x01,0x09,0x09,0x09,0x09,0x09,0x09,0x09,0x09,0x09,0x09,0x08},
{0x09,0x09,0x09,0x09,0x09,0x01,0x09,0x09,0x09,0x09,0x09,0x09,0x09,0x09,0x08,0x09},
{0x09,0x09,0x09,0x09,0x09,0x09,0x01,0x09,0x09,0x09,0x09,0x09,0x09,0x08,0x09,0x09},
{0x09,0x09,0x09,0x09,0x09,0x09,0x09,0x01,0x09,0x09,0x09,0x09,0x08,0x09,0x09,0x09},
{0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x07,0x0a,0x0d,0x0e,0x0f,0x0f,0x0f,0x0f}};//转一圈_

//注意:手把手教程是共阳数码管,0会亮而慧静是共阴数码管,赋1才亮,而且右到左代表低到高位
//dula段选与wela位选:先亮后灭	   P0都是用来选位的,0代表选中
//数码管每次只能显示一个数字,多显示是通过视觉暂留效应实现的
//消抖 去鬼影 

void delay(unsigned int i)//后面用定时器代替
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
		//控制绕圈显示
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
			delay(2);	 //时间间隔短，这是关键（所谓的同时显示，只是间隔较短而已，利用人眼的余辉效应，觉得每个数码管都一直在亮--消抖 去鬼影,消影）。
		 }delay(100);	//为什么右边一直亮
		 }
		
		/*for(num=0;num<6;num++)
		{
			P0=wei[num];	   
			wela=1;
			wela=0;

			P0=duan[num];	  
			dula=1;
			dula=0;
			delay(1000);	 //时间间隔短，这是关键（所谓的同时显示，只是间隔较短而已，利用人眼的余辉效应，觉得每个数码管都一直在亮--消抖 去鬼影,消影）。
		 }*/
	}
	/*while(1)
	{
			P0=0x7d;	   
			wela=1;
			wela=0;

			P0=0x4f;	  //数字“3”的代码
			dula=1;
			dula=0;
			delay(1000);

			P0=0x00;	  //什么都不显示的代码
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
send=0;//先置零
while(1)
{
   receive=0;//置零
   EA=0;
   send=1;
   delay_10us();
   delay_10us();//延时20us
   send=0;
   while(receive==0)//等待高电平
   {};
   
   TMOD=0X01;//设置定时器0的工作方式
   TH0=0;//赋初值
   TL0=0;
   EA=1;///打开总中断开关
   ET0=1;//打开定时器开关
   TR0=1;
   while(receive)//等待低电平
   {
         
   }
    timeh=TH1;//取出定时器的值
    timel=TL1;
    TR0=0;
  
    num=(TH0*255+TL0)/100.0*340/2;
    a=(unsigned int )num%10;//算清各位十位百位
    b=(unsigned int)num%100/10;
    c=(unsigned int )num/100%10;
    d=(unsigned int)num/10;
   
    P0=0xff;//数码管显示输出
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