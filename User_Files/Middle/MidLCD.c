/**
  ******************************************************************************
  * @file		MidLcd.c
  * @author	Best Team
  * @version	V1.0.0
  * @date		24-June-2021
  * @brief	This file provides the function about display modules.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS ONLY FOR INTERNAL USE.SPREAD AND COPY SHOULD
  * NOT BE ALLOWED.
  *
  * COPYRIGHT 2021 BSET TEAM
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "MidLcd.h"

//Define the color of pen and background of LCD   
u16 point_color = WHITE;	
u16 back_color = BLACK; 
	
/*Define the structure of lcddev*/
_lcddev lcddev; 	  

void Mid_LCD_WriteOnePix(u16 x,u16 y,u16 color)
{
	BlockWrite(x,x,y,y);

	Mid_LCD_WriteOneDot(color);		

}

void Mid_LCD_WriteOneDot(u16 color)
{
	Drv_LCD_WR_DATA(color >> 8);		
	Drv_LCD_WR_DATA(color & 0XFF);
}

void Mid_LCD_WriteCoordinate(u16 coordinate)
{
	Drv_LCD_WR_DATA(coordinate >> 8);		
	Drv_LCD_WR_DATA(coordinate & 0XFF);
}


/**
	* @brief  		Set the cursor scope on the LCD. 
  *         
  * @param[in]	u16 Xstart,u16 Xend,u16 Ystart,u16 Yend
  *         
  * @return 		none
  * 
  */
void BlockWrite(u16 Xstart,u16 Xend,u16 Ystart,u16 Yend)
{
	
	Drv_LCD_WR_REG(0x2A);                      
	Mid_LCD_WriteCoordinate(Xstart);                         
	Mid_LCD_WriteCoordinate(Xend);             
	
	Drv_LCD_WR_REG(0x2B);                         
	Mid_LCD_WriteCoordinate(Ystart);                        
	Mid_LCD_WriteCoordinate(Yend);   
	
	Drv_LCD_WR_REG(0x2c);

}


void DrawLine(u16 Xstart,u16 Xend,u16 Ystart,u16 Yend,u16 color)
{
	u16 i,j;

	BlockWrite(Xstart,Xend,Ystart,Yend);

	for(i=Ystart;i<Yend+1;i++)
	{
		for(j=Xstart;j<Xend+1;j++)
		{
			Mid_LCD_WriteOneDot(color);
		}
	}
}


u8 ToOrd(u8 ch)
{
	if(ch<32)
	{
		ch=95;
	}
	else if((ch>=32)&&(ch<=47)) //(32~47)空格~/
	{
		ch=(ch-32)+10+62;
	}
	else if((ch>=48)&&(ch<=57))//(48~57)0~9
	{
		ch=ch-48;
	}
	else if((ch>=58)&&(ch<=64))//(58~64):~@
	{
		ch=(ch-58)+10+62+16;
	}
	else if((ch>=65)&&(ch<=126))//(65~126)A~~
	{
		ch=(ch-65)+10;
	}
	else if(ch>126)
	{		
		ch=95;
	}

	return ch;
}


void DispOneChar(u8 ord,u16 Xstart,u16 Ystart,u16 TextColor,u16 BackColor,u16 FontWidth,u16 FontHeight)
{													  
   u8 i,j;
   unsigned char *p;
   u8 dat;
   u16 index;

   BlockWrite(Xstart,Xstart+(FontWidth - 1),Ystart,Ystart+(FontHeight - 1));

   index = ord;

   if(index>95)	   //95:ASCII CHAR NUM
   		index=95;

   index = index*((FontWidth/8)*FontHeight);	 

   p = ascii;
	 
   p = p+index;

   for(i = 0;i < (FontWidth /8 * FontHeight); i++)
    {
       dat = *p++;
       for(j=0;j<8;j++)
        {
           if((dat<<j) & 0x80)
             {
                Mid_LCD_WriteOneDot(TextColor);
             }
           else 
             {
                Mid_LCD_WriteOneDot(BackColor);	  
             }
         }
     }
}




void DispStr(u8 *str,u16 Xstart,u16 Ystart,u16 TextColor,u16 BackColor,u16 FontWidth,u16 FontHeight)
{

	while(!(*str=='\0'))
	{
		DispOneChar(ToOrd(*str++),Xstart,Ystart,TextColor,BackColor,FontWidth,FontHeight);

		if(Xstart>((SSD_VER_RESOLUTION-1)-FontWidth))
		{
			Xstart=0;
		  Ystart=Ystart+FontHeight;
		}
		else
		{
			Xstart=Xstart+FontWidth;
		}

		if(Ystart>((SSD_HOR_RESOLUTION-1)-FontHeight))
		{
			Ystart=0;
		}
	}	
	BlockWrite(0,SSD_VER_RESOLUTION-1,0,SSD_HOR_RESOLUTION-1);
}



void LCD_ShowIcon(u16 x,u16 y,u16 icon,u16 front_color,u16 background_color,u8 mode)
{  							  
	u8 temp = 0;
	u16 t1 = 0,t = 0;
	u16 width = 0,height = 0;
	u16 y0=y,x0=x;
	u16 csize = 0;

	switch (icon)
	{
		case CASE_XNUO:						width = 132;height = 40;	break;	/* (132 X 40 )*/
		
		case CASE_OMRON:					width = 269;height = 56;	break;	/* (269 X 56 )*/
		
		case CASE_ELLIPSE:				width = 225;height = 122;	break;	/* (225 X 122 )*/			
		
		case CASE_PERCENTAGE:			width = 23;	height = 22;	break;	/* (23 X 22 )*/
			
		case CASE_AI:							width = 20;	height = 20;	break;	/* (20 X 20 )*/
			
		case CASE_BLUETOOTH:			width = 13;	height = 21;	break;	/* (13 X 21 )*/
						
		case CASE_DOT:						width = 11;	height = 11;	break;	/* (11 X 11 )*/
			
		case CASE_CONCENTRATION:	width = 142;height = 19;	break;	/* (142 X 19 )*/
							
		case CASE_FLOW:						width = 124;height = 20;	break;	/* (124 X 20 )*/		
		
		case CASE_HOUR:						width = 46;	height = 15;	break;	/* (46 X 15 )*/

		case CASE_MINUTE:					width = 49;	height = 18;	break;	/* (49 X 18 )*/
		
		case CASE_O2:							width = 21;	height = 21;	break;	/* (21 X 21 )*/		
		
		case CASE_TOTAL:					width = 50;	height = 15;	break;	/* (50 X 15 )*/
		
		case CASE_SHORT_LINE:			width = 18;	height = 10;	break;	/* (18 X 10 )*/

		case CASE_LONG_LINE:			width = 44;	height = 8;		break;	/* (44 X 8 )*/

		case CASE_BELL:						width = 18;	height = 18;	break;	/* (18 X 18 )*/

		case CASE_ATOMIZATION:		width = 13;	height = 21;	break;	/* (13 X 21 )*/

		case CASE_TEST:						width = 9;	height = 9;		break;	/* (9 X 9 )*/

		default:																						break;
	}

//	这里没有确认正确
//	BlockWrite(x,x+width-1,y,y+height-1);	
	
	BlockWrite(x,SSD_HOR_RESOLUTION-1,y,SSD_VER_RESOLUTION-1);
	
	csize=(height/8+((height%8)?1:0))*width;		
		
	for(t=0;t<csize;t++){   	
		switch (icon)
		{
				case CASE_XNUO:						temp = icon_XNUO[t]; 					break;	/* (132 X 40 )*/
				
				case CASE_OMRON:					temp = icon_OMRON[t]; 				break;	/* (269 X 56 )*/

				case CASE_ELLIPSE:				temp = icon_ellipse[t];				break;	/* (225 X 122 )*/
			
				case CASE_PERCENTAGE:			temp = icon_percentage[t]; 		break;	/* (23 X 22 )*/
					
				case CASE_AI:							temp = icon_AI[t]; 						break;	/* (20 X 20 )*/
					
				case CASE_BLUETOOTH:			temp = icon_bluetooth[t];			break;	/* (13 X 21 )*/
								
				case CASE_DOT:						temp = icon_dot[t]; 					break;	/* (11 X 11 )*/
					
				case CASE_CONCENTRATION:	temp = icon_concentration[t];	break;	/* (142 X 19 )*/
									
				case CASE_FLOW:						temp = icon_flow[t];					break;	/* (124 X 20 )*/		
				
				case CASE_HOUR:						temp = icon_hour[t];					break;	/* (46 X 15 )*/

				case CASE_MINUTE:					temp = icon_minute[t];				break;	/* (49 X 18 )*/
				
				case CASE_O2:							temp = icon_O2[t];						break;	/* (21 X 21 )*/		
				
				case CASE_TOTAL:					temp = icon_total[t];					break;	/* (50 X 15 )*/
				
				case CASE_SHORT_LINE:			temp = icon_short_line[t];		break;	/* (18 X 10 )*/

				case CASE_LONG_LINE:			temp = icon_long_line[t];			break;	/* (44 X 8 )*/

				case CASE_BELL:						temp = icon_bell[t];					break;	/* (18 X 18 )*/

				case CASE_ATOMIZATION:		temp = icon_nebulization[t];	break;	/* (13 X 21 )*/
				
				case CASE_TEST:						temp = icon_test[t];					break;	/* (9 X 9 )*/
					
				default:																								break;				
		}

///////////////////////////////////////////////////////		
		for(t1=0;t1<8;t1++){
		/*Draw point*/
				if(temp&0x01){
					Mid_LCD_WriteOneDot(front_color);
				}
				else if(mode==0){
					Mid_LCD_WriteOneDot(background_color);
				}
				temp>>=1;	
				

		}  	
				
	}
///////////////////////////////////////////////////////		
		
//		for(t1=0;t1<8;t1++){
//			/*Draw point*/
//				if(temp&0x01){
//					Mid_LCD_WriteOnePix(x,y,front_color);
//				}
//				else if(mode==0){
//					Mid_LCD_WriteOnePix(x,y,background_color);
//				}
//				temp>>=1;
//				y++;

//			/*One Byte Sent*/
//			if((y-y0)==8)
//			{
//				/*Start with another line*/
//				if((x-x0) == (width-1)){
//					x=x0;
//					y0+=8;
//				}
//				else{
//					y=y0;
//					x++;
//				}			

//			}

//			/*Out of range*/
//			if(y>=lcddev.height){
//				return;					
//			}
//			if(x>=lcddev.width){
//				return;		
//			}
//		}  	
		
//	}  
///////////////////////////////////////////////////////		

	BlockWrite(0,SSD_VER_RESOLUTION-1,0,SSD_HOR_RESOLUTION-1);	
}
	
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////



/**
	* @brief  		Turn on the LCD. 
  *         
  * @param[in]	none
  *         
  * @return 		none
  * 
  */
void Mid_LCD_DisplayOn(void)
{					   
	Drv_LCD_On();
}	 

/**
	* @brief  		Turn off the LCD. 
  *         
  * @param[in]	none
  *         
  * @return 		none
  * 
  */

void Mid_LCD_DisplayOff(void)
{	   
	Drv_LCD_Off();
}   



/**
	* @brief  		Set the curesor postion on the LCD. 
  *         
  * @param[in]	u16 Xpos, u16 Ypos
  *         
  * @return 		none
  * 
  */
void Mid_LCD_SetCursor(u16 Xpos, u16 Ypos)
{
	Drv_LCD_WR_REG(lcddev.setxcmd); 
	Drv_LCD_WR_DATA(Xpos>>8);
	Drv_LCD_WR_DATA(Xpos&0XFF); 	
	
	Drv_LCD_WR_REG(lcddev.setycmd); 
	Drv_LCD_WR_DATA(Ypos>>8);
	Drv_LCD_WR_DATA(Ypos&0XFF); 	
} 



/**
	* @brief  		Draw point of LCD function. 
  *         
  * @param[in]	u16 x,u16 y,u16 color
  *         
  * @return 		none
  */
void Mid_LCD_DrawPoint(u16 x,u16 y,u16 color)
{
	Mid_LCD_SetCursor(x,y);			
	
	Drv_LCD_WR_REG(lcddev.wramcmd);
		
	Drv_LCD_WR_DATA(color >> 8);		
	Drv_LCD_WR_DATA(color & 0XFF);
}

/**
	* @brief  		LCD clear with a new color. 
  *         
  * @param[in]	u16 color
  *         
  * @return 		none
  */
void Mid_LCD_Clear(u16 color)
{
	u32 index = 0;      
	u32 totalpoint = 0;
	
	totalpoint = (u32)lcddev.height * (u32)lcddev.width; 
	
	Mid_LCD_SetCursor(0,0);
	 
	Drv_LCD_WR_REG(lcddev.wramcmd);	
  
	for(index=0;index<totalpoint;index++)
	{
		Drv_LCD_WR_DATA(color>>8);
		Drv_LCD_WR_DATA(color&0XFF);			
	}
}  



/**
	* @brief  		LCD fill color function. 
  *         
  * @param[in]	u16 sx,u16 sy,u16 ex,u16 ey,u16 color
  *         
  * @return 		none
  */
void Mid_LCD_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 color)
{          
	u16 i,j;
	u16 xlen=0;

	xlen=ex-sx+1;	 
	for(i=sx;i<xlen;i++){
		Mid_LCD_SetCursor(i,sy);      			
		Drv_LCD_WR_REG(lcddev.wramcmd);
		for(j=sy;j<=ey;j++){
			Drv_LCD_WR_DATA(color>>8);
			Drv_LCD_WR_DATA(color&0XFF);	
		}				
	}
}  

/**
	* @brief  		LCD draw line function. 
  *         
  * @param[in]	u16 x1, u16 y1, u16 x2, u16 y2
  *         
  * @return 		none
  */
void Mid_LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2)
{
	u16 t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow,uCol; 
	delta_x=x2-x1; 
	delta_y=y2-y1; 
	uRow=x1; 
	uCol=y1; 
	if(delta_x>0)incx=1; 
	else if(delta_x==0)incx=0;
	else {incx=-1;delta_x=-delta_x;} 
	if(delta_y>0)incy=1; 
	else if(delta_y==0)incy=0; 
	else{incy=-1;delta_y=-delta_y;} 
	if( delta_x>delta_y)distance=delta_x; 
	else distance=delta_y; 
	for(t=0;t<=distance+1;t++ ){  
		Mid_LCD_DrawPoint(uRow,uCol,point_color); 
		xerr+=delta_x ; 
		yerr+=delta_y ; 
		if(xerr>distance){ 		
			xerr-=distance; 
			uRow+=incx; 
		} 
		if(yerr>distance){ 		
			yerr-=distance; 
			uCol+=incy; 
		} 
	}  
}    

/**
	* @brief  		LCD draw circle function. 
  *         
  * @param[in]	u16 x1, u16 y1, u16 x2, u16 y2
  *         
  * @return 		none
  */
void Mid_LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2)
{
	Mid_LCD_DrawLine(x1,y1,x2,y1);
	Mid_LCD_DrawLine(x1,y1,x1,y2);
	Mid_LCD_DrawLine(x1,y2,x2,y2);
	Mid_LCD_DrawLine(x2,y1,x2,y2);
}

/**
	* @brief  		LCD draw circle function. 
  *         
  * @param[in]	u16 x0,u16 y0,u8 r
  *         
  * @return 		none
  */
void Mid_LCD_Draw_Circle(u16 x0,u16 y0,u8 r)
{
	int a,b;
	int di;
	a=0;b=r;	  
	di=3-(r<<1);  
	while(a<=b)
	{
		Mid_LCD_DrawPoint(x0+a,y0-b,point_color);             //5
 		Mid_LCD_DrawPoint(x0+b,y0-a,point_color);             //0           
		Mid_LCD_DrawPoint(x0+b,y0+a,point_color);             //4               
		Mid_LCD_DrawPoint(x0+a,y0+b,point_color);             //6 
		Mid_LCD_DrawPoint(x0-a,y0+b,point_color);             //1       
 		Mid_LCD_DrawPoint(x0-b,y0+a,point_color);             
		Mid_LCD_DrawPoint(x0-a,y0-b,point_color);             //2             
  	Mid_LCD_DrawPoint(x0-b,y0-a,point_color);             //7     	         
		a++;
		/*Bresenham*/     
		if(di<0){
			di +=4*a+6;	  
			}
		else{
			di+=10+4*(a-b);   
			b--;
		}
	}
}


/**
	* @brief  		Pow function : result = m^n . 
  *         
  * @param[in]	u8 m,u8 n
  *         
  * @return 		u32 result
  */
u32 Mid_LCD_Pow(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)result*=m;    
	return result;
}		


/**
  * @brief  		LCD show char function. 
  *         
  * @param[in]	u16 x,u16 y,u8 num,u8 size,u8 mode
  *         
  * @return 		None
  */ 
void Mid_LCD_ShowChar1(u16 x,u16 y,u8 num,u8 size,u8 mode)
{  							  
  u8 temp,t1,t;
	u16 y0=y;
	u8 csize=(size/8+((size%8)?1:0))*(size/2);		
 	num=num-' ';
	for(t=0;t<csize;t++)
	{   
		if(12==size)temp=asc2_1206[num][t]; 	 	
//		else if(16==size)temp=asc2_1608[num][t];	
//		else if(24==size)temp=asc2_2412[num][t];	
		else
			return;								
		for(t1=0;t1<8;t1++)
		{			    
			if(temp&0x80)
				Mid_LCD_DrawPoint(x,y,point_color);
			else if(0==mode)
				Mid_LCD_DrawPoint(x,y,back_color);
			
			temp<<=1;
			y++;
			
			if(y>=lcddev.height)
				return;		
			if(size==(y-y0))
			{
				y=y0;
				x++;
				if(x>=lcddev.width)
					return;
				break;
			}
		}  	 
	}  	    	   	 	  
} 

/**
  * @brief  		LCD show string function. 
  *         
  * @param[in]	u16 x,u16 y,u16 width,u16 height,u8 size,u8 *p
  *         
  * @return 		None
  */  
void Mid_LCD_ShowString(u16 x,u16 y,u16 width,u16 height,u8 size,u8 *p)
{         
	u8 x0=x;
	
	width+=x;
	height+=y;
	
	while((*p<='~')&&(*p>=' ')) 
	{       
		if(x>=width)
			{x=x0;y+=size;}
		if(y>=height)
			break; 
		
		Mid_LCD_ShowChar1(x,y,*p,size,0);
		x+=size/2;
		p++;
	}  
}

/**
  * @brief  		LCD show num function. 
  *         
  * @param[in]	u16 x,u16 y,u32 num,u8 len,u8 size
  *         
  * @return 		None
  */
void Mid_LCD_ShowNum(u16 x,u16 y,u32 num,u8 len,u8 size)
{         	
	u8 t,temp;
	u8 enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/Mid_LCD_Pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				Mid_LCD_ShowChar1(x+(size/2)*t,y,' ',size,0);
				continue;
			}
			else
				enshow=1; 		 	 
		}
	 	Mid_LCD_ShowChar1(x+(size/2)*t,y,temp+'0',size,0); 
	}
} 



/**
  * @brief  		LCD show num function. 
  *         
  * @param[in]	u16 x,u16 y,u32 num,u8 len,u8 size,u8 mode(mode:overlaied(1)or not overlaied(0))
  *         
  * @return 		None
  */
void Mid_LCD_ShowxNum(u16 x,u16 y,u32 num,u8 len,u8 size,u8 mode)
{  
	u8 t,temp;
	u8 enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/Mid_LCD_Pow(10,len-t-1))%10;
		
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				if(mode&0X80)
					Mid_LCD_ShowChar1(x+(size/2)*t,y,'0',size,mode&0X01);  
				else
					Mid_LCD_ShowChar1(x+(size/2)*t,y,' ',size,mode&0X01);  
 				continue;
			}
			else
				enshow=1; 
		 	 
		}
	 	Mid_LCD_ShowChar1(x+(size/2)*t,y,temp+'0',size,mode&0X01); 
	}
} 




/**
  * @brief  		LCD show char function. 
  *         
  * @param[in]	u16 x,u16 y,u16 num,u16 size,u8 mode(mode:overlaied(1)or not overlaied(0))
  *         
  * @return 		None
  */
void Mid_LCD_ShowChar(u16 x,u16 y,u16 num,u16 size,u8 mode)
{  							  
  u16 temp,t1,t;
	u16 width = 0,height = 0;
	u16 y0=y,x0=x;
	u16 csize = 0;	

	switch (size)
	{
		case ALIBABA_FONT22:			width = 17;	height = 34;		csize=(height/8+((height%8)?1:0))*width;				break;	/* (17 X 34 )*/
			
		case ALIBABA_FONT36:			width = 27;	height = 54;		csize=(height/8+((height%8)?1:0))*width;				break;	/* (27 X 54 )*/
			
		case ALIBABA_FONT38:			width = 29;	height = 58;		csize=(height/8+((height%8)?1:0))*width;				break;	/* (29 X 58 )*/
		
		case 12:									num = num - ' ';						csize=(size/8+((size%8)?1:0))*(size/2);					break;	
		
		case 16:									num = num - ' ';						csize=(size/8+((size%8)?1:0))*(size/2);					break;	
		
		case 24:									num = num - ' ';						csize=(size/8+((size%8)?1:0))*(size/2);					break;	
			
		default:																																															break;				
	}
 	
	for(t=0;t<csize;t++)
	{   
		if(size == 12)
		{
			temp=asc2_1206[num][t];	
		} 
		else if(size==ALIBABA_FONT22)
		{
			temp=Alibaba_Font22[num][t];	
		}
		else if(size==ALIBABA_FONT36)
		{
			temp=Alibaba_Font36[num][t];
		}
		else if(size==ALIBABA_FONT38)
		{	
			temp=Alibaba_Font38[num][t];
		}
		else 
			return;	

		for(t1=0;t1<8;t1++){
			/*Draw point*/
				if(temp&0x01){
					Mid_LCD_DrawPoint(x,y,point_color);
				}
				else if(mode==0){
					Mid_LCD_DrawPoint(x,y,back_color);
				}
				temp>>=1;
				y++;

			/*One Byte Sent*/
			if((y-y0)==8)
			{
				/*Start with another line*/
				if((x-x0) == (width-1)){
					x=x0;
					y0+=8;
				}
				else{
					y=y0;
					x++;
				}			

			}
		}  
	}
}


/**
  * @brief  		LCD show flow function. 
  *         
  * @param[in]	u16 x,u16 y,u16 num,u8 size
  *         
  * @return 		None
  */
void Mid_LCD_ShowFlow(u16 x,u16 y,u8 num,u8 size)
{         	
	u8 num_num1,num_num2;
	
	point_color=Color2;	
	back_color=Color1;

	num_num1 = num/10;
	num_num2 = num%10;	

	Mid_LCD_ShowChar(x,y,num_num1,size,0);
	x += 71;
	Mid_LCD_ShowChar(x,y,num_num2,size,0);
	
	Mid_LCD_ShowIcon(69,95,CASE_DOT,0);
} 	


/**
  * @brief  		LCD show concentration function. 
  *         
  * @param[in]	u16 x,u16 y,u16 num,u8 size
  *         
  * @return 		None
  */
void Mid_LCD_ShowConcentration(u16 x,u16 y,u8 num,u8 size)
{         	
	u8 num_num1,num_num2;
	
	if((num < 21)||(num > 96))
	
	point_color=Color2;	
	back_color=Color1;

	num_num1 = num/10;
	num_num2 = num%10;	

	x += size/2;
	Mid_LCD_ShowChar(x,y,num_num1,size,0);
	x += size/2;
	Mid_LCD_ShowChar(x,y,num_num2,size,0);
} 


/**
  * @brief  		LCD show respiratory rate function. 
  *         
  * @param[in]	u16 x,u16 y,u16 num,u8 size
  *         
  * @return 		None
  */
void Mid_LCD_ShowRespiratoryRate(u16 x,u16 y,u8 num,u8 size)
{         	
	u8 num_num1,num_num2;
	
	point_color=Color1;	 
	back_color=Color2;

	num_num1 = num/10;
	num_num2 = num%10;	

	x += size/2;
	Mid_LCD_ShowChar(x,y,num_num1,size,0);
	x += size/2;
	Mid_LCD_ShowChar(x,y,num_num2,size,0);
} 


/**
  * @brief  		LCD Show running time function. 
  *         
  * @param[in]	u16 x,u16 y,u16 num,u8 size
  *         
  * @return 		None
  */
void Mid_LCD_ShowRunningTime(u16 x,u16 y,u32 num,u8 size)
{         	
	u8 num_num1,num_num2,num_num3,num_num4,num_num5;
	
	point_color=Color2;	
	back_color=BLACK;

	if(num >= 99999){
		num = 99999;
	}
	
	num_num1 = num/10000;
	num_num2 = num/1000%10;
	num_num3 = num/100%10;
	num_num4 = num/10%10;
	num_num5 = num%10;	

	Mid_LCD_ShowChar(x,y,num_num1,size,0);
	x += size/2;
	Mid_LCD_ShowChar(x,y,num_num2,size,0);
	x += size/2;
	Mid_LCD_ShowChar(x,y,num_num3,size,0);
	x += size/2;
	Mid_LCD_ShowChar(x,y,num_num4,size,0);
	x += size/2;
	Mid_LCD_ShowChar(x,y,num_num5,size,0);	
	
} 




/**
  * @brief  		LCD show icon function. 
  *         
  * @param[in]	u16 x,u16 y,u16 Icon,u8 mode
  *         
  * @return 		None
  */
void Mid_LCD_ShowIcon(u16 x,u16 y,u16 icon,u8 mode)
{  							  
	u16 temp = 0,t1 = 0,t = 0;
	u16 width = 0,height = 0;
	u16 y0=y,x0=x;
	u16 csize = 0;
	
	switch (icon)
	{
		case CASE_XNUO:						width = 132;height = 40;				break;	/* (132 X 40 )*/
		
		case CASE_OMRON:					width = 269;height = 56;				break;	/* (269 X 56 )*/			
			
		case CASE_PERCENTAGE:			width = 23;	height = 22;				break;	/* (23 X 22 )*/
			
		case CASE_AI:							width = 20;	height = 20;				break;	/* (20 X 20 )*/
			
		case CASE_BLUETOOTH:			width = 13;	height = 21;				break;	/* (13 X 21 )*/
						
		case CASE_DOT:						width = 11;	height = 11;				break;	/* (11 X 11 )*/
			
		case CASE_CONCENTRATION:	width = 142;height = 19;				break;	/* (142 X 19 )*/
							
		case CASE_FLOW:						width = 124;height = 20;				break;	/* (124 X 20 )*/		
		
		case CASE_HOUR:						width = 46;	height = 15;				break;	/* (46 X 15 )*/

		case CASE_MINUTE:					width = 49;	height = 18;				break;	/* (49 X 18 )*/
		
		case CASE_O2:							width = 21;	height = 21;				break;	/* (21 X 21 )*/		
		
		case CASE_TOTAL:					width = 50;	height = 15;				break;	/* (50 X 15 )*/
		
		case CASE_SHORT_LINE:			width = 18;	height = 10;				break;	/* (18 X 10 )*/

		case CASE_LONG_LINE:			width = 44;	height = 8;					break;	/* (44 X 8 )*/

		case CASE_BELL:						width = 18;	height = 18;				break;	/* (18 X 18 )*/

		case CASE_ATOMIZATION:		width = 13;	height = 21;				break;	/* (13 X 21 )*/
			
		default:																									break;				
	}
	
	csize=(height/8+((height%8)?1:0))*width;		
		
	for(t=0;t<csize;t++){   	
		switch (icon)
		{
				case CASE_XNUO:						temp = icon_XNUO[t]; 					break;	/* (132 X 40 )*/
				
				case CASE_OMRON:					temp = icon_OMRON[t]; 				break;	/* (269 X 56 )*/
					
				case CASE_PERCENTAGE:			temp = icon_percentage[t]; 		break;	/* (23 X 22 )*/
					
				case CASE_AI:							temp = icon_AI[t]; 						break;	/* (20 X 20 )*/
					
				case CASE_BLUETOOTH:			temp = icon_bluetooth[t];			break;	/* (13 X 21 )*/
								
				case CASE_DOT:						temp = icon_dot[t]; 					break;	/* (11 X 11 )*/
					
				case CASE_CONCENTRATION:	temp = icon_concentration[t];	break;	/* (142 X 19 )*/
									
				case CASE_FLOW:						temp = icon_flow[t];					break;	/* (124 X 20 )*/		
				
				case CASE_HOUR:						temp = icon_hour[t];					break;	/* (46 X 15 )*/

				case CASE_MINUTE:					temp = icon_minute[t];				break;	/* (49 X 18 )*/
				
				case CASE_O2:							temp = icon_O2[t];						break;	/* (21 X 21 )*/		
				
				case CASE_TOTAL:					temp = icon_total[t];					break;	/* (50 X 15 )*/
				
				case CASE_SHORT_LINE:			temp = icon_short_line[t];		break;	/* (18 X 10 )*/

				case CASE_LONG_LINE:			temp = icon_long_line[t];			break;	/* (44 X 8 )*/

				case CASE_BELL:						temp = icon_bell[t];					break;	/* (18 X 18 )*/

				case CASE_ATOMIZATION:		temp = icon_nebulization[t];	break;	/* (13 X 21 )*/
				
				case CASE_ELLIPSE:				temp = icon_ellipse[t];				break;	/* (240 X 240 )*/
					
				default:																								break;				
		}
	
		for(t1=0;t1<8;t1++){
			/*Draw point*/
				if(temp&0x01){
					Mid_LCD_DrawPoint(x,y,point_color);
				}
				else if(mode==0){
					Mid_LCD_DrawPoint(x,y,back_color);
				}
				temp>>=1;
				y++;

			/*One Byte Sent*/
			if((y-y0)==8)
			{
				/*Start with another line*/
				if((x-x0) == (width-1)){
					x=x0;
					y0+=8;
				}
				else{
					y=y0;
					x++;
				}			

			}

			/*Out of range*/
			if(y>=lcddev.height){
				return;					
			}
			if(x>=lcddev.width){
				return;		
			}
		}  	
		
	}  	    	   	 	    
}



/**
  * @brief  		Handling the animation function of LCD. 
  *         
  * @param[in]	None
  *         
  * @return 		None
  */
void Mid_LCD_ShowAnimation(void)
{
	point_color = GBLUE;
	back_color = BLACK;
	
	Mid_LCD_ShowIcon(94,101,CASE_XNUO,0);
	Delay_Ms(1000);
	
	Mid_LCD_Clear(BLACK);
	Delay_Ms(1000);
	
	Mid_LCD_ShowIcon(94,101,CASE_XNUO,0);
	Delay_Ms(500);
	
	Mid_LCD_Clear(BLACK);
	Delay_Ms(500);
	
	Mid_LCD_ShowIcon(94,101,CASE_XNUO,0);
	Delay_Ms(500);
	
	Mid_LCD_Clear(BLACK);
	Delay_Ms(500);
	
	Mid_LCD_ShowIcon(94,101,CASE_XNUO,0);
}

/**
  * @brief  		Show the background of LCD. 
  *         
  * @param[in]	None
  *         
  * @return 		None
  */
void Mid_LCD_ShowBackground(void)
{
	/*Show the icons when the mode is not debug mode.*/
	if(system.mode != MODE_DEBUG){
		
//		Mid_LCD_DrawLine(0,0,240,240);

		/*Fill a rectangle at the left of background*/
//		Mid_LCD_Fill(0,0,150,240,Color1);

		/*Fill a rectangle at the top of background*/
//		Mid_LCD_Fill(150,0,480,31,BLACK);

		/*Fill a rectangle in the middle of background*/
//		Mid_LCD_Fill(0,100,200,120,Color2);
		
		/*Fill a rectangle at the bottom of background*/
//		Mid_LCD_Fill(150,122,480,240,BLACK);

//		point_color = RED;
//		back_color = WHITE;	
//		Mid_LCD_ShowIcon(0,12,CASE_FLOW,0);
//		Mid_LCD_ShowIcon(0,34,CASE_CONCENTRATION,0);
		
//		point_color = RED;
//		back_color = WHITE;
//		Mid_LCD_ShowIcon(0,0,CASE_ELLIPSE,0);

//		point_color = BLUE;
//		back_color = WHITE;
//		Mid_LCD_Draw_Circle(120,120,50);

//		Mid_LCD_ShowChar(100,50,22,ALIBABA_FONT22,0);

//		point_color = RED;
//		back_color = WHITE;	
//		Mid_LCD_ShowIcon(0,89,CASE_MINUTE,0);
//		
//		point_color = RED;
//		back_color = WHITE;		
//		Mid_LCD_ShowIcon(0,110,CASE_BELL,0);
//		
//		point_color = RED;
//		back_color = WHITE;	
//		Mid_LCD_ShowIcon(0,135,CASE_TOTAL,0);
//		
//		point_color = RED;
//		back_color = BLACK;	
//		Mid_LCD_ShowIcon(0,210,CASE_HOUR,0);
	}
	else{
		/*Clear LCD with black in debug mode.*/	
//		Mid_LCD_Clear(Color1);	
	}
}



/**
  * @brief  		Handling the initial function of LCD. 
  *         
  * @param[in]	None
  *         
  * @return 		None
  */
void Mid_LCD_Init(void)
{
	/*Initial the IOS of LCD*/
	Drv_LCD_IO_Init();

	/*Initial SPI2*/
	Drv_SPI2_Init();
	
	/*Turn off the LCD.*/ 
	Drv_LCD_On();

	/*Reset LCD.*/ 
	Drv_LCD_Reset();

	/*Sleep Out*/
	Drv_LCD_SleepOut();

	/*The orignal settings of the LCD*/
	Drv_LCD_Orignal();

//	Delay_Us(1);

	/*Set the direction of the LCD*/
	Drv_LCD_Display_Dir();	

	lcddev.width	=	SSD_HOR_RESOLUTION; 
	lcddev.height	=	SSD_VER_RESOLUTION;	

	lcddev.wramcmd	=	0X2C;//Memory Write
	lcddev.setycmd	=	0X2B;//Row Address Set
	lcddev.setxcmd	=	0X2A;//Column Address Set
	
	/*Clear LCD with black*/	
	Mid_LCD_Clear(WHITE);	

	/*LCD_ShowAnimation*/
//	LCD_ShowAnimation();

	/*Show background*/	
	Mid_LCD_ShowBackground();
	
	/*Turn on the LCD.*/ 
	Drv_LCD_On();

}



/**
  * @brief  		UI for standby mode. 
  *         
  * @param[in]	None
  *         
  * @return 		None
  */
void Mid_UI_Standby(void)
{
	/*Show flow value*/
	Mid_LCD_ShowFlow(21,48,0,ALIBABA_FONT38);
	
	/*Show concentration value*/
	Mid_LCD_ShowConcentration(21,166,21,ALIBABA_FONT38);
		
	/*Show Respiratory rate value*/
	Mid_LCD_ShowRespiratoryRate(168,50,0,ALIBABA_FONT36);
			
	/*Show Running time value*/
	Mid_LCD_ShowRunningTime(164,166,(u16)system.accumulate_display_time,ALIBABA_FONT22);

	/*Show Running icon O2*/	
//	LCD_ShowIcon(283,6,CASE_O2,0);	
}

/**
  * @brief  		UI for oxygen generating mode. 
  *         
  * @param[in]	None
  *         
  * @return 		None
  */
void Mid_UI_OxygenGenerating(void)
{	
	/*Show flow value*/
	Mid_LCD_ShowFlow(21,48,(u8)5,ALIBABA_FONT38);
	
	/*Show concentration value*/
	Mid_LCD_ShowConcentration(21,166,system.density,ALIBABA_FONT38);
		
	/*Show Respiratory rate value*/
	Mid_LCD_ShowRespiratoryRate(168,50,(u8)system.respiratory_rate,ALIBABA_FONT36);
			
	/*Show Running time value*/
	Mid_LCD_ShowRunningTime(164,166,(u16)system.accumulate_display_time,ALIBABA_FONT22);

	/*Show Running icon bluetooth*/		
//	Mid_LCD_ShowIcon(254,6,CASE_BLUETOOTH,0);	
	
	/*Show Running icon O2*/	
	Mid_LCD_ShowIcon(283,6,CASE_O2,0);	
}

/**
  * @brief  		UI for atomization mode. 
  *         
  * @param[in]	None
  *         
  * @return 		None
  */
void Mid_UI_Atomization(void)
{	
	/*Show Running time value*/
	Mid_LCD_ShowRunningTime(164,166,(u16)system.accumulate_display_time,ALIBABA_FONT22);

	/*Show icon atomization*/
	Mid_LCD_ShowIcon(223,7,CASE_ATOMIZATION,0);
	
	point_color=Color2;	
	back_color=Color1;	
	
	Mid_LCD_ShowIcon(20,72,CASE_SHORT_LINE,0);
	
	Mid_LCD_ShowIcon(69,95,CASE_DOT,0);
	
	Mid_LCD_ShowIcon(91,72,CASE_SHORT_LINE,0);
	
	Mid_LCD_ShowIcon(15,190,CASE_LONG_LINE,0);
	
	point_color=Color1;	
	back_color=Color2;
	
	Mid_LCD_ShowIcon(163,73,CASE_LONG_LINE,0);	
}


 /**
  * @brief  		UI for AI mode. 
  *         
  * @param[in]	None
  *         
  * @return 		None
  */
void Mid_UI_AI(void)
{
	/*Show Running icon AI*/
	Mid_LCD_ShowIcon(283,6,CASE_AI,0);	
	
	/*Show flow value(10 times of actual flow)*/
	Mid_LCD_ShowFlow(21,48,(u8)5,ALIBABA_FONT38);
	
	/*Show concentration value*/
	Mid_LCD_ShowConcentration(21,166,system.density,ALIBABA_FONT38);
		
	/*Show Respiratory rate value*/
	Mid_LCD_ShowRespiratoryRate(168,50,(u8)system.respiratory_rate,ALIBABA_FONT36);

	/*Show Running time value*/
	Mid_LCD_ShowRunningTime(164,166,(u16)system.accumulate_display_time,ALIBABA_FONT22);

}

 /**
  * @brief  		UI for debug mode. 
  *         
  * @param[in]	None
  *         
  * @return 		None
  */
void Mid_UI_Debug(void)
{
	point_color = Color2;
	back_color = BLACK;	

	Mid_LCD_ShowString(80,5,200,12,12,"Welcome to debug mode!"); 

	Mid_LCD_ShowString(10,35,252,12,12,"Pressure time1:");
	
	Mid_LCD_ShowString(10,65,264,12,12,"Pressure time2:");
	
	Mid_LCD_ShowString(10,95,252,12,12,"Pressure time3:");
	
	Mid_LCD_ShowString(10,125,264,12,12,"Pressure time4:");
	
	Mid_LCD_ShowString(10,155,252,12,12,"Pressure time5:");
	
	Mid_LCD_ShowString(10,185,264,12,12,"Pressure time6:");

}

 /**
  * @brief  		Display UI in the screen. 
  *         
  * @param[in]	None
  *         
  * @return 		None
  */
void Mid_UI_Display(void)
{
	int screen_refresh_times = 0;
	
	/*Update the background when the mode changes.*/		
	if((system.mode_last != system.mode)){

		/*Clear LCD with black*/	
		for(screen_refresh_times = 0; screen_refresh_times < 2; screen_refresh_times++){
			Mid_LCD_Clear(BLACK);	
		}		
		/*Show background*/	
		Mid_LCD_ShowBackground();
	
		system.mode_last = system.mode;		
	}

	switch(system.mode)
	{
		case MODE_STANDBY:
			Mid_UI_Standby();
			break;

		case MODE_OXYGENERATE:
			Mid_UI_OxygenGenerating();
			break;

		case MODE_ATOMIZATION:
			Mid_UI_Atomization();
			break;
		
		case MODE_DEBUG:
			Mid_UI_Debug();
			break;	
		
		case MODE_AI:
			Mid_UI_AI();
			break;	
		
		default:
			break;
	}

}

/******************* (C) COPYRIGHT 2021 Best team *****END OF FILE****/
