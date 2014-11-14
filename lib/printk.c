#include "printk.h"
#include "screen.h"
#include "string.h"
#include <stdarg.h>
#include <stdint.h>

char *uitoa(uint32_t num, char *str, int radix)
{
	char  string[] = "0123456789abcdefghijklmnopqrstuvwxyz";
	char ptr[32];
	int i = -1;
	int j = 0;


	if (num == 0) {
		str[0] = '0';
		return str;
	}
	while (num) {
		i++;
		ptr[i] = string[num % radix];
		num /= radix;

		if (num < radix) {
			i++;
			ptr[i] = string[num];
			ptr[i + 1] = '\0';
			break;
		}
	}

	while (i >= 0) {
		str[j] = ptr[i];
		j++;
		i--;
	}

	return str;
}

char *itoa(int32_t num, char *str, int radix)
{
	if (num < 0) {
		num = 0 - num;
		str[0] = '-';
		str++;
		str = uitoa(num, str, radix);
		str--;
		return str;
	} else if (num == 0) {
		str[0] = '0';
		return str;
	}

	return uitoa(num, str, radix);
}

int print_str(char *str)
{
	int count = 0;
	while (*str != '\0') {
		write_char(*str);
		count++;
		str++;
	}

	return count;
}

int print_int(int32_t num)
{
	char str[32];
	memset(str, 0, 32);

	itoa(num, str, 10);

	return print_str(str);
}

int print_uint(uint32_t num)
{
	char str[32];
	memset(str, 0, 32);

	uitoa(num, str, 10);

	return print_str(str);
}

int print_hex(uint32_t num)
{
	int count = 0;
	char str[32];

	memset(str, 0, 32);
	count += print_str("0x");
	count += print_str(uitoa(num, str, 16));

	return count;
}

int printk(const char *str, ...)
{
	va_list ap;
	va_start(ap, str);

	const char *tmp = str;
	int count = 0;

	while (*tmp != '\0') {
		if (*tmp == '%') {
			tmp++;
			if (*tmp == '%') {
				write_char(*tmp);
				count++;
			} else if (*tmp == 's') {
				char *s = va_arg(ap, char *);
				count += print_str(s);
			} else if (*tmp == 'c') {
				int c = va_arg(ap, int);
				write_char((char)c);
				count++;
			} else if (*tmp == 'd') {
				int32_t tmp_int = va_arg(ap, int32_t);
				count += print_int(tmp_int);
			} else if (*tmp == 'u') {
				uint32_t tmp_uint = va_arg(ap, uint32_t);
				count += print_uint(tmp_uint);
			} else if (*tmp == 'x') {
				uint32_t tmp_x = va_arg(ap, uint32_t);
				count += print_hex(tmp_x);
			} else if (*tmp == 'p') {
				char *p = va_arg(ap, char *);
				uint32_t tmp_p = (uint32_t)p;
				count += print_hex(tmp_p);
			}
		} else {
			write_char(*tmp);
			count++;
		}
		tmp++;
	}
	va_end(ap);
	return count;
}
