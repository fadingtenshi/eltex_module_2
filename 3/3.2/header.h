
#ifndef HEADER
#define HEADER
#define IPV4_LEN 15

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

typedef struct {
    char **ips;
    size_t size;
} IPs;

char **allocMatrix(int size);
void IPs_push(IPs *ipv4s, char *ip);
IPs *generateIP(int ip_count);
unsigned int iptoBit(char *ip);
unsigned int masktoBit(int mask);
IPs *applyMask(IPs *ips, char *gateway, int mask, int size);
void clearmem(IPs *ptr, int size);

#endif