//#include <errno.h> not needed now
#include <limine.h>
#include <limits.h>
#include <flanterm.h>
#include <backends/fb.h>
#include <stddef.h>
#include <stdarg.h>
#include <utils.h>

void int_to_hex(unsigned long value, char *buffer) {
    const char hex_chars[] = "0123456789abcdef";
    int i = 0;

    do {
        buffer[i++] = hex_chars[value % 16];
        value /= 16;
    } while (value != 0);

    buffer[i] = '\0';

    // Обращаем строку, так как мы формировали ее с конца
    for (int j = 0; j < i / 2; j++) {
        char temp = buffer[j];
        buffer[j] = buffer[i - j - 1];
        buffer[i - j - 1] = temp;
    }
}

struct flanterm_context *ft_ctx = NULL;

int terminal_init(struct limine_framebuffer *fb) {
    ft_ctx = flanterm_fb_simple_init(
        fb->address,
        fb->width,
        fb->height,
        fb->pitch
    );

    flanterm_write(ft_ctx, "init framebuffer: ok\n", 21);

    return 0;
}

int print(const char* string, size_t len) {
    flanterm_write(ft_ctx, string, len);
	return 1;
}

int tprintf(const char* restrict format, ...) {
    //print(string, strlen(string));
    va_list parameters;
	va_start(parameters, format);

	int written = 0;

	while (*format != '\0') {
		size_t maxrem = INT_MAX - written;

		if (format[0] != '%' || format[1] == '%') {
			if (format[0] == '%')
				format++;
			size_t amount = 1;
			while (format[amount] && format[amount] != '%')
				amount++;
			if (maxrem < amount) {
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}
			if (!print(format, amount))
				return -1;
			format += amount;
			written += amount;
			continue;
		}

		const char* format_begun_at = format++;

		if (*format == 'c') {
			format++;
			char c = (char) va_arg(parameters, int /* char promotes to int */);
			if (!maxrem) {
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}
			if (!print(&c, sizeof(c)))
				return -1;
			written++;
		} else if (*format == 's') {
			format++;
			const char* str = va_arg(parameters, const char*);
			size_t len = strlen(str);
			if (maxrem < len) {
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}
			if (!print(str, len))
				return -1;
			written += len;
        } else if (*format == 'x') {
            format++;
            unsigned int value = va_arg(parameters, unsigned long);
            char buffer[20]; // предположим, что числа не будут очень большими
            int_to_hex(value, buffer);
            print(buffer, strlen(buffer));
            written += strlen(buffer);
		} else {
			format = format_begun_at;
			size_t len = strlen(format);
			if (maxrem < len) {
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}
			if (!print(format, len))
				return -1;
			written += len;
			format += len;
		}
	}

	va_end(parameters);
	return written;
}

void clear() {
	ft_ctx->clear(ft_ctx, false);
}