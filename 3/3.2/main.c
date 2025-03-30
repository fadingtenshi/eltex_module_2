
#include "header.h"

int main(int argc, char *argv[]) {
    if(argc != 4) {
        printf("Invalid argc count!\n");
        printf("Usage: %s [gateway] [mask] [ip_count]\n", argv[0]);
        return 1;
    }

    char *gateway = argv[1];
    int mask = strtol(argv[2], NULL, 10);
    int ip_count = strtol(argv[3], NULL, 10);
    IPs *ipv4s = generateIP(ip_count);

    IPs *result= applyMask(ipv4s, gateway, mask, ip_count);
    printf("Ips in local network:\n");
    size_t local_ips = result->size;
    for(size_t i = 0; i < local_ips; ++i) {
        printf("%s\n", result->ips[i]);
    }
    printf("Total count: %ld\n", local_ips);
    printf("Ips in remote network: %d\n", ip_count);
    printf("Ips percentage in local network: %.3f%%\n", (float)local_ips / ip_count * 100);
    printf("Ips percentage in remote network: %.3f%%\n", (float)(ip_count - local_ips) / ip_count * 100);
    clearmem(ipv4s, ipv4s->size);
    clearmem(result, result->size);
    return 0;
}