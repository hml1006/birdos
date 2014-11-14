/*******************************************************************
*
* Author: Louis Huang - hml1006@qq.com
*
* Last modified: 2012-12-14 12:16
*
* Filename: screen.c
*
* Description: 
*
*******************************************************************/

#include <stdint.h>
#include "screen.h"
#include "lock.h"

struct screen_t scr_stat = {.lock = SPIN_UNLOCKED,
				.current_line = 0,
				.current_column = 0,};

screen_char blank_char = {
	.ca.ascii = ' ',
	.ca.color = DEFAULT_COLOR,
};

/************************************************
 *往显存写入一个字符,只打印可显示字符
 * ************************************************/
static inline void _write_char(int line, int column, screen_char color_ascii)
{
	if(color_ascii.ca.ascii < 32 || color_ascii.ca.ascii > 126)
		return;
	*((screen_char *)(SCREEN_BASE_ADDR + (line * MAX_COLUMN + column) * 2)) = color_ascii;
	return;
}

static inline screen_char _read_char(int line, int column)
{
	return *((screen_char *)(SCREEN_BASE_ADDR + (line * MAX_COLUMN + column) * 2));
}

static void roll_one_line()
{
	int line;
	int column;
	screen_char tmp;
	for(line = 0; line < MAX_LINE - 1; line++) {
		for(column = 0; column <= MAX_COLUMN; column++) {
			tmp = _read_char(line + 1, column);
			_write_char(line, column, tmp);
		}
	}
	for(column = 0; column < MAX_COLUMN; column++) {
		_write_char(MAX_LINE, column, blank_char);
	}
	return;
}

void write_char(char c)
{
	screen_char tmp;
	tmp.ca.color = DEFAULT_COLOR;
	tmp.ca.ascii = c;

	spin_lock(&(scr_stat.lock));

	if (c == '\n') {
		scr_stat.current_column = 0;
		scr_stat.current_line++;

		if (scr_stat.current_line == MAX_LINE) {
			roll_one_line();
			scr_stat.current_line = MAX_LINE - 1;
		}
		spin_unlock(&(scr_stat.lock));
		return;
	}

	if (scr_stat.current_column == MAX_COLUMN) {
		scr_stat.current_column = 0;
		scr_stat.current_line++;
	}
	if (scr_stat.current_line == MAX_LINE) {
		roll_one_line();
		scr_stat.current_line == MAX_LINE - 1;
	}
	_write_char(scr_stat.current_line, scr_stat.current_column, tmp);
	scr_stat.current_column++;

	spin_unlock(&(scr_stat.lock));

	return;
}

void clear_screen()
{
	int line;
	int column;

	spin_lock(&(scr_stat.lock));

	for(line = 0; line <= MAX_LINE; line++) {
		for(column = 0; column <= MAX_COLUMN; column++) {
			_write_char(line, column, blank_char);
		}
	}

	scr_stat.current_line = 0;
	scr_stat.current_column = 0;

	spin_unlock(&(scr_stat.lock));

	return;
}
