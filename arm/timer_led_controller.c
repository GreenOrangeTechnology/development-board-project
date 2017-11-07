#include "s5pv210.h"
#include "stdio.h"

//使用4个定时器使4个LED灯以不同频率进行亮灭(定时器1~定时器4，控制LED灯的闪烁时间)->按键扫描
//使用定时器每隔一段时间去获取温感值

//抠图:ps的学习，主要抠图。(多种方法：抽出、魔术棒、通道、钢笔工具、套索工具、橡皮工具等都可以使用，一般情况下单一的工具可以抠出轮廓分明、背景色泽单一的图像，经常情况下需要几种工具联合使用。)

static volatile unsigned int g_key_flag;//判断按键状态

//按键中断处理函数:解除报警
void key_irq_handler(void)
{
	while(1)
	{
		if(key2==DOWN)
		{
			//改变蜂鸣器值,停止报警
		}
		//不同按键按下,对g_key_flag赋值
	}
}

//定时器1外部中断处理函数
//
void timer1_irq_handler(void)
{
	rTINT_CSTAT|=1<<6;
	
	rGPJ2DAT^=0x1;//异或:相同为1不同为0
	//这里改为获取温度值

	rVIC0ADDRESS=0;
	rVIC1ADDRESS=0;	
	rVIC2ADDRESS=0;
	rVIC3ADDRESS=0;			
}

//定时器2外部中断处理函数
//
void timer2_irq_handler(void)
{
	rTINT_CSTAT|=1<<7;
	
	rGPJ2DAT^=0x2;
	
	rVIC0ADDRESS=0;
	rVIC1ADDRESS=0;	
	rVIC2ADDRESS=0;
	rVIC3ADDRESS=0;		
}

//定时器3外部中断处理函数
//
void timer3_irq_handler(void)
{
	rTINT_CSTAT|=1<<8;
	
	rGPJ2DAT^=0x4;
	
	rVIC0ADDRESS=0;
	rVIC1ADDRESS=0;	
	rVIC2ADDRESS=0;
	rVIC3ADDRESS=0;		
}

//定时器4外部中断处理函数
//
void timer4_irq_handler(void)
{
	rTINT_CSTAT|=1<<9;
	
	rGPJ2DAT^=0x8;  
	
	rVIC0ADDRESS=0;
	rVIC1ADDRESS=0;	
	rVIC2ADDRESS=0;
	rVIC3ADDRESS=0;		
}

//PWM初始化 这里用来控制蜂鸣器报警 频率:1S产生多少个波形 控制输出的电压=5V * 占空比 蜂鸣器响声
void pwm_init(void)／//记住:定时器4是没有PWM输出引脚
{
	//将GPD0_0引脚配置为PWMTOUT0功能 //如何搭配使用
	rGPD0CON&=~0xF;
	rGPD0CON|= 0x2;
	/*原:配合定时器使用
	
	//配置定时器0的输入频率
	//定时器0的输入频率=66MHz/(65+1) /16=62500Hz
	//只要定时器0完成62500次计数的时候，就代表1秒时间的到达
	rTCFG0 &=~(0xFF);
	rTCFG0 |= 65;
	
	rTCFG1 &=~0xF;
	rTCFG1 |= 4;
	
	//设置定时器的计数值,频率为100Hz，占空比=50%
	rTCNTB0 = 62500/100;		//T=1/f=1S/100 用于控制PWM输出的频率
	rTCMPB0 = rTCNTB0/2;        //用于控制PWM波形的占空比
	
	//启动定时器
	rTCON|=1<<1;		//初次运行定时器的时候，先将这两个值传输到定时器运算单元当中。
	rTCON&=~(1<<1);	//后面的一个中断触发依赖于自动重载，不再需要手动更新
	rTCON|=(1<<3)|(1<<0);//启动定时器，并实现自动重载功能
	
	*/
}

//初始化定时器
void timer_init(void)
{
	//定时器使用步骤1
	/*	配置定时器1,2,3,4的(输入,定时器的时间)时钟频率=66MHz/(65+1)/16=62500Hz */
	//只要定时器0完成62500次计数的时候，就代表1秒时间的到达
	rTCFG0 &=~ (0xFFFF);//配置0~7位为0,手册决定
	rTCFG0 |=  (65<<8)|65;//(不需要16位)设置预分频值	

	rTCFG1 &=~((0xF<<16)|(0xF<<12)|(0xF<<8)|(0xF<<4));//设置二分频
	rTCFG1 |= ((0x4<<16)|(0x4<<12)|(0x4<<8)|(0x4<<4));
	
	/*	配置定时器1的时间 */
	//设置定时器的计数值   一级分频?
	rTCNTB1=62500*0.1;//0.1s,修改这里来修改定时时间	
	rTCMPB1=0;//方波占空比
	/*	配置定时器2的时间 */
	rTCNTB2=62500*0.3;	
	rTCMPB2=0;
	/*	配置定时器3的时间 */
	rTCNTB3=62500*1.5;	
	rTCMPB3=0;
	/*	配置定时器4的时间 */
	rTCNTB4=62500*2.5;	

	/*	安装中断服务函数 */
	rVIC0VECTADDR22=(unsigned int)timer1_irq_handler;
	rVIC0VECTADDR23=(unsigned int)timer2_irq_handler;
	rVIC0VECTADDR24=(unsigned int)timer3_irq_handler;
	rVIC0VECTADDR25=(unsigned int)timer4_irq_handler;
	/*	设置VIC0通道22~25当前中断类型为IRQ中断 */
	rVIC0INTSELECT &=~((1<<25)|(1<<24)|(1<<23)|(1<<22));
	/*	使能定时器1~4中断与清空标志位 */  //二级分频?
	rTINT_CSTAT |=(1<<6)|(1<<1);
	rTINT_CSTAT |=(1<<7)|(1<<2);
	rTINT_CSTAT |=(1<<8)|(1<<3);
	rTINT_CSTAT |=(1<<9)|(1<<4);
	/*	使能VIC0通道22~25触发中断 */
	rVIC0INTENABLE |= (1<<25)|(1<<24)|(1<<23)|(1<<22);	
	/*	启动定时器1 */  //TCON寄存器控制定时器的启动与停止;三星公司的做法 串口还是用04年代码
	rTCON |=1<<9;			//手动更新TCNTB1、TCMPB1到定时器1逻辑运算单元
	//初次运行定时器的时候，先将这两个值(TCNTB,TCMPB)传输到定时器运算单元当中。
	rTCON &=~(1<<9);//后面的一个中断触发依赖于自动重载，不再需要手动更新
	rTCON|=(1<<11)|(1<<8);	//实现自动重载(没减完一秒又自动开始减)与启动定时器1
	/*	启动定时器2 */
	rTCON |=1<<13;			//手动更新TCNTB2、TCMPB2到定时器2逻辑运算单元
	rTCON &=~(1<<13);
	rTCON|=(1<<15)|(1<<12);//实现自动重载与启动定时器2
	/*	启动定时器3 */
	rTCON |=1<<17;			//手动更新TCNTB3、TCMPB3到定时器3逻辑运算单元
	rTCON &=~(1<<17);
	rTCON|=(1<<19)|(1<<16);//实现自动重载与启动定时器3	
	/*	启动定时器4 */
	rTCON |=1<<21;			//手动更新TCNTB4到定时器4逻辑运算单元
	rTCON &=~(1<<21);
	rTCON|=(1<<22)|(1<<20);//实现自动重载与启动定时器4	
}

//初始化LED灯
void led_init(void)
{
	rGPJ2CON &= ~0xFFFF;//四盏
	rGPJ2CON |=  0x1111;
	/*	熄灭所有LED灯 */
	rGPJ2DAT |= 0XF;
}

int main(void)
{
	printf("This is lezhi smart home\r\n");
	
	timer_init();
	
	led_init();

	while(1)
	{
		//对g_key_flag值进行判断
	}
	return 0;
}



