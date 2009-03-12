#ifndef _INCLUDE_PRINT_R_
#define _INCLUDE_PRINT_R_

#include "r_types.h"
#include "r_util.h"

#define R_PRINT_FLAGS_COLOR   0x00000001
#define R_PRINT_FLAGS_ADDRMOD 0x00000002
#define R_PRINT_FLAGS_CURSOR  0x00000004
#define R_PRINT_FLAGS_HEADER  0x00000008

struct r_print_t {
	void *user;
	int (*read_at)(u64 addr, u8 *buf, int len, void *user);
	char datefmt[32];
	int (*printf)(const char *str, ...);
	/* TODO: add printf callback */
	int interrupt;
	int bigendian;
	int width;
	int cur_enabled;
	int cur;
	int ocur;
	int flags;
	int addrmod;
};

R_API struct r_print_t *r_print_new();
R_API struct r_print_t *r_print_free(struct r_print_t *p);
R_API void r_print_set_flags(struct r_print_t *p, int _flags);
R_API void r_print_set_width(struct r_print_t *p, int width);
R_API void r_print_addr(struct r_print_t *p, u64 addr);
R_API void r_print_hexdump(struct r_print_t *p, u64 addr, u8 *buf, int len, int step);
R_API void r_print_bytes(struct r_print_t *p, const u8* buf, int len, const char *fmt);
R_API void r_print_raw(struct r_print_t *p, const u8* buf, int len);
R_API void r_print_cursor(struct r_print_t *p, int cur, int set);
R_API void r_print_set_cursor(struct r_print_t *p, int curset, int ocursor, int cursor);
R_API void r_print_code(struct r_print_t *p, u64 addr, u8 *buf, int len);
R_API void r_print_format(struct r_print_t *p, u64 seek, const u8* buf, int len, const char *fmt);
R_API int r_print_string(struct r_print_t *p, const u8 *str, int len, int wide, int zeroend, int urlencode);

#endif
