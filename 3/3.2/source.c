
#include "header.h"

char **allocMatrix(int size) {
    char **matrix = malloc(sizeof(char*) * size);
    for(int i = 0; i < size; ++i) {
        matrix[i] = malloc(sizeof(char) * IPV4_LEN);
    }
    return matrix;
}

void IPs_push(IPs *ipv4s, char *ip) {
    if(ipv4s->size == 0) {
        ipv4s->ips = malloc(sizeof(char*) * IPV4_LEN);
        ipv4s->size++;
        ipv4s->ips[ipv4s->size - 1] = ip;
    }
    else {
        ipv4s->ips = realloc(ipv4s->ips, sizeof(char*) * (++(ipv4s->size)));
        ipv4s->ips[ipv4s->size - 1] = ip;
    }
}

IPs *generateIP(int ip_count) {
    IPs *ipv4s = calloc(1, sizeof(IPs));
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
        IPs_push(ipv4s, ip);
    }
    return ipv4s;
}

unsigned int iptoBit(char *ip) {
    unsigned a, b, c, d;
    sscanf(ip, "%u.%u.%u.%u", &a, &b, &c, &d);
    return (a << 24) | (b << 16) | (c << 8) | d;
}

unsigned int masktoBit(int mask) {
    return (0xFFFFFFFF << (32 - mask)) & 0xFFFFFFFF;
}

IPs *applyMask(IPs *ips, char *gateway, int mask, int size) {
    IPs *ipv4s_result = calloc(1, sizeof(IPs));
    unsigned int mask_bit = masktoBit(mask);
    unsigned int gateway_bit_masked = iptoBit(gateway) & mask_bit;
    for(int i = 0; i < size; ++i) {
        unsigned int masked_ip = iptoBit(ips->ips[i]) & mask_bit;
        if(masked_ip == gateway_bit_masked) {
            char *result_ip = malloc(sizeof(char) * IPV4_LEN);
            memcpy(result_ip, ips->ips[i], sizeof(IPs));
            IPs_push(ipv4s_result, result_ip);
        }
    }
    return ipv4s_result;
}

void clearmem(IPs *ptr, int size) {
    for(int i = 0; i < size; ++i) {
        free(ptr->ips[i]);
    }
    free(ptr->ips);
    free(ptr);
}