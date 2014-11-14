/*******************************************************************
*
* Author: Louis Huang - hml1006@qq.com
*
* Last modified: 2012-12-14 12:17
*
* Filename: screen.h
*
* Description: 
*
*******************************************************************/


#ifndef _SCREEN_H
#define _SCREEN_H

#include "lock.h"
#include <stdint.h>

#define SCREEN_BASE_ADDR (0xc0000000+0xb8000)	//�Դ����ַ
#define MAX_LINE 25
#define MAX_COLUMN 80
#define DEFAULT_COLOR 0x07

//������ʾ�ַ�,��asciiֵ����ɫ�������
struct screen_char_t {
	union {
		struct {
			char ascii;
			char color;
		} ca;
		uint16_t color_ascii;
	};
}__attribute__((packed));
typedef struct screen_char_t screen_char;
//������ʾ״̬��Ϣ�������к��кź���
struct screen_t{
	spin_lock_t lock;
	int current_line;
	int current_column;
};

extern struct screen_t scr_stat;
extern void write_char(char c);
extern void clear_screen();

#endif
