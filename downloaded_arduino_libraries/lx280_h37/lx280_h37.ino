
#define LCD_RD   A0
#define LCD_WR   A1     
#define LCD_RS   A2        
#define LCD_CS   A3       
#define LCD_REST A4

void Lcd_Writ_Bus(unsigned char VH)
{
  unsigned int i,temp,data; 
  data=VH;
  for(i=8;i<=9;i++)
  {
    temp=(data&0x01);
    if(temp)
      digitalWrite(i,HIGH);
    else
      digitalWrite(i,LOW);
    data=data>>1;
  }	
  for(i=2;i<=7;i++)
  {
    temp=(data&0x01);
    if(temp)
      digitalWrite(i,HIGH);
    else
      digitalWrite(i,LOW);
    data=data>>1;
  }	 

  digitalWrite(LCD_WR,LOW);
  digitalWrite(LCD_WR,HIGH);
}


void Lcd_Write_Com(unsigned char VH)  
{   
  digitalWrite(LCD_RS,LOW);
  Lcd_Writ_Bus(VH);
}

void Lcd_Write_Data(unsigned char VH)
{
  digitalWrite(LCD_RS,HIGH);
  Lcd_Writ_Bus(VH);
}

void Lcd_Write_Com_Data(unsigned char com,unsigned char dat)
{
  Lcd_Write_Com(com);
  Lcd_Write_Data(dat);
}

void Address_set(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2)
{
        Lcd_Write_Com(0x2a);
        Lcd_Write_Data(x1>>8);
        Lcd_Write_Data(x1);
        Lcd_Write_Data(x2>>8);
        Lcd_Write_Data(x2);
        Lcd_Write_Com(0x2b);
        Lcd_Write_Data(y1>>8);
        Lcd_Write_Data(y1);
        Lcd_Write_Data(y2>>8);
        Lcd_Write_Data(y2);
	Lcd_Write_Com(0x2c); 							 
}

void Lcd_Init(void)
{
  digitalWrite(LCD_REST,HIGH);
  delay(5); 
  digitalWrite(LCD_REST,LOW);
  delay(15);
  digitalWrite(LCD_REST,HIGH);
  delay(15);

  digitalWrite(LCD_CS,HIGH);
  digitalWrite(LCD_WR,HIGH);
  digitalWrite(LCD_CS,LOW);  //CS

 /*  Lcd_Write_Com(0x11);//sleep out 
	delay(20);
  //Lcd_Write_Com(0x01); //reset
  //delay(15);
  Lcd_Write_Com(0x28); //display off
  delay(5);
  Lcd_Write_Com(0xCF); //power control b
  Lcd_Write_Data(0x00);
  Lcd_Write_Data(0x83); //83 81 AA
  Lcd_Write_Data(0x30);
  Lcd_Write_Com(0xED); //power on seq control
  Lcd_Write_Data(0x64); //64 67
  Lcd_Write_Data(0x03);
  Lcd_Write_Data(0x12);
  Lcd_Write_Data(0x81);
  Lcd_Write_Com(0xE8); //timing control a
  Lcd_Write_Data(0x85);
  Lcd_Write_Data(0x01);
  Lcd_Write_Data(0x79); //79 78
  Lcd_Write_Com(0xCB); //power control a
  Lcd_Write_Data(0x39);
  Lcd_Write_Data(0X2C);
  Lcd_Write_Data(0x00);
  Lcd_Write_Data(0x34);
  Lcd_Write_Data(0x02);
  Lcd_Write_Com(0xF7); //pump ratio control
  Lcd_Write_Data(0x20);
  Lcd_Write_Com(0xEA); //timing control b
  Lcd_Write_Data(0x00);
  Lcd_Write_Data(0x00);
  Lcd_Write_Com(0xC0); //power control 2
  Lcd_Write_Data(0x26); //26 25
  Lcd_Write_Com(0xC1); //power control 2
  Lcd_Write_Data(0x11);
  Lcd_Write_Com(0xC5); //vcom control 1
  Lcd_Write_Data(0x35);
  Lcd_Write_Data(0x3E);
  Lcd_Write_Com(0xC7); //vcom control 2
  Lcd_Write_Data(0xBE); //BE 94
  Lcd_Write_Com(0xB1); //frame control
  Lcd_Write_Data(0x00);
  Lcd_Write_Data(0x1B); //1B 70
  Lcd_Write_Com(0xB6); //display control
  Lcd_Write_Data(0x0A);
  Lcd_Write_Data(0x82);
  Lcd_Write_Data(0x27);
  Lcd_Write_Data(0x00);
  Lcd_Write_Com(0xB7); //emtry mode
  Lcd_Write_Data(0x07);
  Lcd_Write_Com(0x3A); //pixel format
  Lcd_Write_Data(0x55); //16bit
  Lcd_Write_Com(0x36); //mem access
  Lcd_Write_Data((1<<3)|(1<<6));
  //Lcd_Write_Data((1<<3)|(1<<7)); //rotate 180
  Lcd_Write_Com(0x29); //display on
  delay(5);
    digitalWrite(LCD_CS,HIGH);
    */
     Lcd_Write_Com(0xCB);  
    Lcd_Write_Data(0x39); 
    Lcd_Write_Data(0x2C); 
    Lcd_Write_Data(0x00); 
    Lcd_Write_Data(0x34); 
    Lcd_Write_Data(0x02); 

    Lcd_Write_Com(0xCF);  
    Lcd_Write_Data(0x00); 
    Lcd_Write_Data(0XC1); 
    Lcd_Write_Data(0X30); 

    Lcd_Write_Com(0xE8);  
    Lcd_Write_Data(0x85); 
    Lcd_Write_Data(0x00); 
    Lcd_Write_Data(0x78); 

    Lcd_Write_Com(0xEA);  
    Lcd_Write_Data(0x00); 
    Lcd_Write_Data(0x00); 
 
    Lcd_Write_Com(0xED);  
    Lcd_Write_Data(0x64); 
    Lcd_Write_Data(0x03); 
    Lcd_Write_Data(0X12); 
    Lcd_Write_Data(0X81); 

    Lcd_Write_Com(0xF7);  
    Lcd_Write_Data(0x20); 
  
    Lcd_Write_Com(0xC0);    //Power control 
    Lcd_Write_Data(0x23);   //VRH[5:0] 
 
    Lcd_Write_Com(0xC1);    //Power control 
    Lcd_Write_Data(0x10);   //SAP[2:0];BT[3:0] 

    Lcd_Write_Com(0xC5);    //VCM control 
    Lcd_Write_Data(0x3e);   //Contrast
    Lcd_Write_Data(0x28); 
 
    Lcd_Write_Com(0xC7);    //VCM control2 
    Lcd_Write_Data(0x86);   //--
 
    Lcd_Write_Com(0x36);    // Memory Access Control 
    Lcd_Write_Data(0x48);   

    Lcd_Write_Com(0x3A);    
    Lcd_Write_Data(0x55); 

    Lcd_Write_Com(0xB1);    
    Lcd_Write_Data(0x00);  
    Lcd_Write_Data(0x18); 
 
    Lcd_Write_Com(0xB6);    // Display Function Control 
    Lcd_Write_Data(0x08); 
    Lcd_Write_Data(0x82);
    Lcd_Write_Data(0x27);  

    Lcd_Write_Com(0x11);    //Exit Sleep 
    delay(120); 
				
    Lcd_Write_Com(0x29);    //Display on 
    Lcd_Write_Com(0x2c); 
}

void H_line(unsigned int x, unsigned int y, unsigned int l, unsigned int c)                   
{	
  unsigned int i,j;
  digitalWrite(LCD_RS,HIGH);
  digitalWrite(LCD_CS,LOW);
  l=l+x;
  Address_set(x,y,l,y);
  j=l*2;
  for(i=1;i<=j;i++)
  {
    Lcd_Write_Data(c);
  }
  digitalWrite(LCD_CS,HIGH);   
}

void V_line(unsigned int x, unsigned int y, unsigned int l, unsigned int c)                   
{	
  unsigned int i,j;
  //Lcd_Write_Com(0x02c); //write_memory_start
  digitalWrite(LCD_RS,HIGH);
  digitalWrite(LCD_CS,LOW);
  l=l+y;
  Address_set(x,y,x,l);
  j=l*2;
  for(i=1;i<=j;i++)
  { 
    Lcd_Write_Data(c);
  }
  digitalWrite(LCD_CS,HIGH);   
}

void Rect(unsigned int x,unsigned int y,unsigned int w,unsigned int h,unsigned int c)
{
  H_line(x  , y  , w, c);
  H_line(x  , y+h, w, c);
  V_line(x  , y  , h, c);
  V_line(x+w, y  , h, c);
}

void Rectf(unsigned int x,unsigned int y,unsigned int w,unsigned int h,unsigned int c)
{
  unsigned int i;
  for(i=0;i<h;i++)
  {
    H_line(x  , y  , w, c);
    H_line(x  , y+i, w, c);
  }
}
int RGB(int r,int g,int b)
{return r << 16 | g << 8 | b;
}
void LCD_Clear(unsigned int j)                   
{	
  unsigned int i,m;
 Address_set(0,0,240-1,320-1);
  Lcd_Write_Com(0x02c); //write_memory_start
  digitalWrite(LCD_RS,HIGH);
  digitalWrite(LCD_CS,LOW);


  for(i=0;i<320;i++)
    for(m=0;m<240;m++)
    {
      Lcd_Write_Data(j>>8);
      Lcd_Write_Data(j);

    }
  digitalWrite(LCD_CS,HIGH);   
}

void setup()
{
  for(int p=2;p<10;p++)
  {
    pinMode(p,OUTPUT);
  }
  pinMode(A0,OUTPUT);
  pinMode(A1,OUTPUT);
  pinMode(A2,OUTPUT);
  pinMode(A3,OUTPUT);
  pinMode(A4,OUTPUT);
  digitalWrite(A0, HIGH);
  digitalWrite(A1, HIGH);
  digitalWrite(A2, HIGH);
  digitalWrite(A3, HIGH);
  digitalWrite(A4, HIGH);
  Lcd_Init();
 LCD_Clear(0xf800);
 LCD_Clear(0x07e0);
 LCD_Clear(0x001F);
}

void loop()
{  

  for(int i=0;i<1000;i++)
  {
    Rect(random(300),random(300),random(300),random(300),random(65535)); // rectangle at x, y, with, hight, color
  }
  
//  LCD_Clear(0xf800);
}
