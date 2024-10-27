#include <linux/bpf.h>
#include <bpf/bpf_helpers.h>
#include <linux/socket.h>
#include <linux/in.h>

static inline __be16 my_ntohs(__be16 netshort)
{
    return (netshort << 8) | (netshort >> 8);
}

SEC("tracepoint/syscalls/sys_enter_bind")
int bpf_bind_enter(void *ctx)
{
    struct sockaddr_in *addr;
    int sockfd;
    char comm[16];

    // Получаем имя процесса
    bpf_get_current_comm(&comm, sizeof(comm));

    // Получаем файловый дескриптор сокета
    sockfd = *(int *)ctx;

    // Получаем адрес
    addr = (struct sockaddr_in *)(ctx + sizeof(int));

    // Получаем IP-адрес и порт
    __be32 ip = addr->sin_addr.s_addr;
    __be16 port = addr->sin_port;

    bpf_printk("Process: %s, IP: %u, Port: %u\n", comm, ip, my_ntohs(port));
    return 0;
}

char LICENSE[] SEC("license") = "Dual BSD/GPL";
