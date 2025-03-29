
#ifndef HEADER
#define HEADER
#define IPV4_LEN 15

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

void generateIP(char **ips, int ip_count);
unsigned int iptoBit(char *ip);
unsigned int masktoBit(int mask);
int applyMask(char **ips, char *gateway, int mask, int size);
void clearmem(char **ptr, int size);

#endif