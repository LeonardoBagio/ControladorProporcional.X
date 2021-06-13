/* ########################################################################

   PICsim - PIC simulator http://sourceforge.net/projects/picsim/

   ########################################################################

   Copyright (c) : 2015  Luis Claudio Gambôa Lopes

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

   For e-mail suggestions :  lcgamboa@yahoo.com
   ######################################################################## */



#define LENA  PORTEbits.RE1
#define LDAT  PORTEbits.RE0
#define LPORT PORTD


#define L_ON	0x0F
#define L_OFF	0x08
#define L_CLR	0x01
#define L_L1	0x80
#define L_L2	0xC0
#define L_CR	0x0F		
#define L_NCR	0x0C
#define L_CFG   0x38

#define L1_digito1 0x80
#define L1_digito2 0x81
#define L1_digito3 0x82
#define L1_digito4 0x83
#define L1_digito5 0x84
#define L1_digito6 0x85
#define L1_digito7 0x86
#define L1_digito8 0x87
#define L1_digito9 0x88
#define L1_digito10 0x89

#define L2_digito1 0xC0
#define L2_digito2 0xC1
#define L2_digito3 0xC2
#define L2_digito4 0xC3
#define L2_digito5 0xC4
#define L2_digito6 0xC5
#define L2_digito7 0xC6
#define L2_digito8 0xC7
#define L2_digito9 0xC8
#define L2_digito10 0xC9

void lcd_init(void);
void lcd_cmd(unsigned char val); 
void lcd_dat(unsigned char val);
void lcd_str(const char* str);
