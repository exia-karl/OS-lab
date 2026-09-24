#ifndef __TYPES_H
#define __TYPES_H

typedef unsigned int   uint;
typedef unsigned short ushort;
typedef unsigned char  uchar;
typedef unsigned short wchar;
typedef long clock_t;
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int  uint32;
typedef unsigned long uint64;

typedef unsigned long uintptr_t;
typedef uint64 pde_t;

struct tms{
    clock_t tms_utime;  /* user time */
    clock_t tms_stime;  /* system time */
    clock_t tms_cutime; /* user time of children */
    clock_t tms_cstime;  
};

struct utsname{
    char sysname[65];  //the name of the system
	char nodename[65]; //
	char release[65];
	char version[65];
	char machine[65];
	char domainname[65];
};
// #define NULL ((void *)0)
#define NULL 0

#define readb(addr) (*(volatile uint8 *)(addr))
#define readw(addr) (*(volatile uint16 *)(addr))
#define readd(addr) (*(volatile uint32 *)(addr))
#define readq(addr) (*(volatile uint64 *)(addr))

#define writeb(v, addr)                      \
    {                                        \
        (*(volatile uint8 *)(addr)) = (v); \
    }
#define writew(v, addr)                       \
    {                                         \
        (*(volatile uint16 *)(addr)) = (v); \
    }
#define writed(v, addr)                       \
    {                                         \
        (*(volatile uint32 *)(addr)) = (v); \
    }
#define writeq(v, addr)                       \
    {                                         \
        (*(volatile uint64 *)(addr)) = (v); \
    }

#define NELEM(x) (sizeof(x)/sizeof((x)[0]))

#endif
