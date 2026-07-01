#ifndef BRICKBOX_H_INCLUDED
#define BRICKBOX_H_INCLUDED








#include <stdio.h>
#include <stdint.h>
#include <stddef.h>

#ifndef _WIN32
#include <unistd.h>
#elif
#error "we don't support Windows yet"
#endif

#define SEGMENT_BIT 0x7F
#define CONTINUE_BIT 0x80

#define DEBUG_FAIL(message, ...) printf("[-] %s:%s(): " message, __FILE__, __FUNCTION__, ##__VA_ARGS__)
#define DEBUG_PASS(message, ...) printf("[+] %s:%s(): " message, __FILE__, __FUNCTION__, ##__VA_ARGS__)
#define DEBUG_INFO(message, ...) printf("[!] %s:%s(): " message, __FILE__, __FUNCTION__, ##__VA_ARGS__)

















#endif
