
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
    char **ips = malloc(sizeof(char*) * ip_count);

    generateIP(ips, ip_count);

    int result = applyMask(ips, gateway, mask, ip_count);
    printf("Ips in local network: %d\n", result);
    printf("Ips in remote network: %d\n", ip_count);
    printf("Ips percentage in local network: %.3f%%\n", (float)result / ip_count * 100);
    printf("Ips percentage in remote network: %.3f%%\n", (float)(ip_count - result) / ip_count * 100);
    clearmem(ips, ip_count);
    return 0;
}