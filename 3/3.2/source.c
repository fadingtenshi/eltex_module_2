
#include "header.h"

void generateIP(char **ips, int ip_count) {
    struct timeval tv;
    gettimeofday(&tv,NULL);
    srand(tv.tv_usec);
    for(int i = 0; i < ip_count; ++i) {
        char *ip = malloc(sizeof(char) * IPV4_LEN);
        for(int j = 0; j < 4; ++j) {
            char octet[5]; 
            sprintf(octet, "%d", rand()%256);
            strcat(ip, octet);
            if(j + 1 != 4) strcat(ip, ".");
        }
        ips[i] = ip;
    }
}

unsigned int iptoBit(char *ip) {
    unsigned a, b, c, d;
    sscanf(ip, "%u.%u.%u.%u", &a, &b, &c, &d);
    return (a << 24) | (b << 16) | (c << 8) | d;
}

unsigned int masktoBit(int mask) {
    return (0xFFFFFFFF << (32 - mask)) & 0xFFFFFFFF;
}

int applyMask(char **ips, char *gateway, int mask, int size) {
    unsigned int mask_bit = masktoBit(mask);
    unsigned int gateway_bit_masked = iptoBit(gateway) & mask_bit;
    int count = 0;
    for(int i = 0; i < size; ++i) {
        unsigned int masked_ip = iptoBit(ips[i]) & mask_bit;
        if(masked_ip == gateway_bit_masked) {
            count++;
        }
    }
    return count;
}

void clearmem(char **ptr, int size) {
    for(int i = 0; i < size; ++i) {
        free(ptr[i]);
    }
    free(ptr);
}