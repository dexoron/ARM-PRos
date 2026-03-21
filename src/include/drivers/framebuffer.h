#ifndef DRIVERS_FRAMEBUFFER_H
#define DRIVERS_FRAMEBUFFER_H

#include <stdint.h>

int fb_init(unsigned width, unsigned height, unsigned depth_bits);
int fb_is_ready(void);
void fb_set_fg(uint32_t rgba);
void fb_reset_fg(void);
void fb_set_bg(uint32_t rgba);
void fb_clear(void);
void fb_putc(int c);
void fb_puts(const char *s);

#endif
