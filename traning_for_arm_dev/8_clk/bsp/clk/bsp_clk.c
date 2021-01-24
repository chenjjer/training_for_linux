#include "bsp_clk.h"

/***************************************************************
Copyright © zuozhongkai Co., Ltd. 1998-2019. All rights reserved.
文件名	: 	 bsp_clk.c
作者	   : 左忠凯
版本	   : V1.0
描述	   : 系统时钟驱动。
其他	   : 无
论坛 	   : www.openedv.com
日志	   : 初版V1.0 2019/1/4 左忠凯创建
***************************************************************/

/*
 * @description	: 使能I.MX6U所有外设时钟
 * @param 		: 无
 * @return 		: 无
 */
void clk_enable(void)
{
	CCM->CCGR0 = 0XFFFFFFFF;
	CCM->CCGR1 = 0XFFFFFFFF;
	CCM->CCGR2 = 0XFFFFFFFF;
	CCM->CCGR3 = 0XFFFFFFFF;
	CCM->CCGR4 = 0XFFFFFFFF;
	CCM->CCGR5 = 0XFFFFFFFF;
	CCM->CCGR6 = 0XFFFFFFFF;
}

void imx6u_clkinit(void)
{
	unsigned int reg = 0;
	if((((CCM->CCR) >> 2) & 0x1) == 0) 
	{
		CCM->CCSR &= ~(1 << 8);
		CCM->CCSR |= (1 << 2);
	}
	CCM_ANALOG->PLL_ARM = (1 << 13) | ((88 << 0) & 0x7F);
	CCM->CACRR = 1;
	CCM->CCSR &= ~(1 << 2);


	reg = CCM_ANALOG->PFD_528;
	reg &= ~(0x3f3f3f3f);
	reg |= 32 << 24;
	reg |= 24 << 16;
	reg |= 16 << 8;
	reg |= 27 << 0;
	CCM_ANALOG->PFD_528 = reg;

	reg = 0;
	reg = CCM_ANALOG->PFD_480;
	reg &= ~(0x3f3f3f3f);
	reg |= 19 << 24;
	reg |= 17 << 16;
	reg |= 16 << 8;
	reg |= 12 << 0;
	CCM_ANALOG->PFD_480 = reg;

	CCM->CBCMR &= ~(3 << 18);
	CCM->CBCMR |= (1 << 18);
	CCM->CBCDR &= ~(1 << 25);
	while(CCM->CDHIPR & (1 << 5));

	CCM->CBCDR &= ~(3 << 8);
	CCM->CBCDR |= 1 << 8;

	CCM->CSCMR1 &= ~(1 << 6) ;
	CCM->CSCMR1 &= ~(7 << 0);

}




