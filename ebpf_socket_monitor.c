#include <bpf/bpf.h>
#include <bpf/bpf_helpers.h>
#include <linux/socket.h>
#include <linux/ptrace.h>
#include <linux/sched.h>
#include <linux/in.h>
#include <linux/inet.h>
#include <linux/ip.h>

SEC("tracepoint/syscalls/sys_enter_socket")
int bpf_socket_enter(void *ctx)
{
    bpf_printk("Socket creation called\n");
    return 0;
}

SEC("tracepoint/syscalls/sys_exit_socket")
int bpf_socket_exit(void *ctx)
{
    struct bpf_sock *sock;
    if (sock)
    {
        __be32 local_ip = sock->sk_rcv_saddr;
        __be16 local_port = sock->sk_num;

        // Печатаем адрес и порт
        bpf_printk("Socket created - Local IP: %d.%d.%d.%d, Local Port: %d\n",
                   (local_ip >> 0) & 0xFF,
                   (local_ip >> 8) & 0xFF,
                   (local_ip >> 16) & 0xFF,
                   (local_ip >> 24) & 0xFF,
                   ntohs(local_port));
    }

    return 0;
}

char LICENSE[] SEC("license") = "Dual BSD/GPL";