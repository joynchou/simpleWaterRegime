��ʾ�豸������
LCD1602�����뵥Ƭ�����ӷ���
PORT = P4;��0-7һһ��Ӧ
RS = P5^0;
RW = P5^1;
EN = P5^2;
Backlight = P5^4;
ʹ��ǰ��������LCD1602_Init()����LCD1602��Ļ��ʼ��

LCD5510_V2�����뵥Ƭ�����ӷ���
CLK = P5 ^ 0;
DIN = P5 ^ 1;

DC = P5 ^ 2;

CS = P5 ^ 3;

RST = P5 ^ 4;
ʹ��ǰ��������LCD5510_Init()����LCD5510_V2��Ļ��ʼ��

ע������ע���뿴LCD1602.H��LCD5510_V2.H

void LCD_clr_scr(void) �ú���ʵ�ֽ�LCD5110���������á���ԭ�������DDram���ﵽ������Ч���������롣

void LCD_clr_row(unsigned char num)�ú���ʵ�ֶ�LCD5110ָ�������������á�NumΪ����е�λ�á�

void LCD_printc(unsigned char x, unsigned char y, unsigned char c_dat)�ú���ʵ����LCD5110ָ������һ���ַ�����6*8���壩x��y�������꣬c_dat����������ַ���//x: 0 �C 13   y: 0 - 5

void LCD_prints(unsigned char x, unsigned char y, unsigned char *s_dat) �ú���ʵ����LCD5110ָ�������ַ������ַ��������13���ַ������򽫳������루6*8���壩��x��y�������꣬*s_dat����������ַ�����

void LCD_printsl(unsigned char x, unsigned char y, unsigned char *s_dat) �ú���ʵ����LCD5110ָ�������ַ�������ʵ���Զ����С�x��y�������꣬*s_dat����������ַ�����

void LCD_printNum_I(u8 x, u8 y, int num,u8 numLength) �ú���ʵ����LCD5110ָ��������������ʵ�ֶ�������ʾλ�������ã�����ʾ������num��123��λ�������֣���numLengthӦ����3��������ʾ�����ŵ����numLengthӦ����4��

void LCD_printNum_F(u8 x, u8 y, float num,u8 numLength, u8 accuracy) �ú���ʵ����LCD5110ָ�����븡��������ʵ�ֶ�������ʾ����λ����С�������ʾ��λ�����á�numLengthΪ����λ����accuracyС��λ����
