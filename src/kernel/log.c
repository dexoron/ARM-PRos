#include <log.h>
#include <drivers/framebuffer.h>
#include <drivers/lcd/ili9486.h>
#include <drivers/uart.h>
#include <stdint.h>

// ------ Serial: ANSI SGR escapes ------
#define ANSI_RESET  "\033[0m"
#define ANSI_GREEN  "\033[92m"
#define ANSI_RED    "\033[91m"
#define ANSI_ORANGE "\033[33m"

// ------ Framebuffer: 0xAARRGGBB ------
#define FB_GREEN  0xFF50AF4Cu
#define FB_RED    0xFF3333FFu
#define FB_ORANGE 0xFF4DB7FFu

#define LCD_FG_DEFAULT 0xFFE8E8E8u

static void emit_gfx_line(uint32_t color, const char *tag, const char *msg)
{
	if (fb_is_ready()) {
		fb_set_fg(color);
		fb_puts(tag);
		fb_putc(' ');
		fb_puts(msg);
		fb_puts("\n\r");
		fb_reset_fg();
	}

	if (lcd_is_ready()) {
		lcd_set_fg(color);
		lcd_puts(tag);
		lcd_putc(' ');
		lcd_puts(msg);
		lcd_puts("\n\r");
		lcd_set_fg(LCD_FG_DEFAULT);
	}
}

void log_okay(const char *msg)
{
	uart_puts(ANSI_GREEN);
	uart_puts("[  OKAY  ]");
	uart_puts(ANSI_RESET);
	uart_putc(' ');
	uart_puts(msg);
	uart_puts("\r\n");

	emit_gfx_line(FB_GREEN, "[  OKAY  ]", msg);
}

void log_error(const char *msg)
{
	uart_puts(ANSI_RED);
	uart_puts("[ ERROR ]");
	uart_puts(ANSI_RESET);
	uart_putc(' ');
	uart_puts(msg);
	uart_puts("\r\n");

	emit_gfx_line(FB_RED, "[ ERROR ]", msg);
}

void log_warn(const char *msg)
{
	uart_puts(ANSI_ORANGE);
	uart_puts("[  WARN  ]");
	uart_puts(ANSI_RESET);
	uart_putc(' ');
	uart_puts(msg);
	uart_puts("\r\n");

	emit_gfx_line(FB_ORANGE, "[  WARN  ]", msg);
}
