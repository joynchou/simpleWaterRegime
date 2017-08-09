显示设备驱动层
LCD1602引脚与单片机连接方法
PORT = P4;从0-7一一对应
RS = P5^0;
RW = P5^1;
EN = P5^2;
Backlight = P5^4;
使用前需先运行LCD1602_Init()进行LCD1602屏幕初始化

LCD5510_V2引脚与单片机连接方法
CLK = P5 ^ 0;
DIN = P5 ^ 1;

DC = P5 ^ 2;

CS = P5 ^ 3;

RST = P5 ^ 4;
使用前需先运行LCD5510_Init()进行LCD5510_V2屏幕初始化

注：更多注释请看LCD1602.H与LCD5510_V2.H

void LCD_clr_scr(void) 该函数实现将LCD5110清屏的作用。其原理是清空DDram，达到清屏的效果。无输入。

void LCD_clr_row(unsigned char num)该函数实现对LCD5110指定行数清行作用。Num为清空行的位置。

void LCD_printc(unsigned char x, unsigned char y, unsigned char c_dat)该函数实现在LCD5110指定输入一个字符。（6*8字体）x，y代表坐标，c_dat代表输入的字符。//x: 0 – 13   y: 0 - 5

void LCD_prints(unsigned char x, unsigned char y, unsigned char *s_dat) 该函数实现在LCD5110指定输入字符串。字符串最多有13个字符，否则将出现乱码（6*8字体）。x，y代表坐标，*s_dat代表输入的字符串。

void LCD_printsl(unsigned char x, unsigned char y, unsigned char *s_dat) 该函数实现在LCD5110指定输入字符串。可实现自动换行。x，y代表坐标，*s_dat代表输入的字符串。

void LCD_printNum_I(u8 x, u8 y, int num,u8 numLength) 该函数实现在LCD5110指定输入整数。可实现对整数显示位数的设置，如显示整数（num）123三位数的数字，则numLength应输入3，若需显示正负号的情况numLength应输入4。

void LCD_printNum_F(u8 x, u8 y, float num,u8 numLength, u8 accuracy) 该函数实现在LCD5110指定输入浮点数。可实现对整数显示整数位数与小数点后显示几位的设置。numLength为整数位数，accuracy小数位数。
