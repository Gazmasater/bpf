#include <linux/bpf.h>
#include <bpf/bpf_helpers.h>
#include <bpf/bpf_endian.h>
#include <linux/socket.h>
#include <linux/ptrace.h>
#include <linux/sched.h>
#include <netinet/in.h>

struct sys_exit_sock
{
    unsigned short common_type;
    unsigned char common_flags;
    unsigned char common_preempt_count;
    int common_pid;
    int __syscall_nr;
    long ret;
};

struct sys_enter_sock
{
    unsigned short common_type;
    unsigned char common_flags;
    unsigned char common_preempt_count;
    int common_pid;
    int __syscall_nr;
    int family;   // Семейство сокета
    int type;     // Тип сокета
    int protocol; // Протокол сокета
};

// Функция для обработки входящего сокета
SEC("tracepoint/syscalls/sys_enter_socket")
int bpf_socket_enter(struct sys_enter_sock *ctx)
{
    __u32 pid = bpf_get_current_pid_tgid() >> 32; // Получаем PID

    bpf_printk("Socket creation called by PID: %d\n", pid);
    return 0; // Возврат 0, чтобы не прерывать выполнение функции
}

SEC("tracepoint/syscalls/sys_exit_socket")
int bpf_socket_exit(struct sys_exit_sock *ctx)
{
    __u32 pid = bpf_get_current_pid_tgid() >> 32; // Получаем PID

    bpf_printk("Socket created by PID: %d\n", pid);
    return 0;
}

SEC("sockops")
int sockops_handler(struct bpf_sock_ops *skops)
{
    switch (skops->op)
    {
    case BPF_SOCK_OPS_TCP_CONNECT_CB:
        // TODO
        break;
    case BPF_SOCK_OPS_TCP_LISTEN_CB:
        // TODO
        break;
    case BPF_SOCK_OPS_ACTIVE_ESTABLISHED_CB:
        // TODO
        if (skops->family == AF_INET)
        {
            bpf_printk("sa:%pI4 sp:%d", &skops->local_ip4, bpf_ntohs(skops->local_port));
            bpf_printk("da:%pI4 dp:%d", &skops->remote_ip4, bpf_ntohs(skops->remote_port));
        }
        else if (skops->family == AF_INET6)
        {
            bpf_printk("sa:%pI6 sp:%d", &skops->local_ip6, bpf_ntohs(skops->local_port));
            bpf_printk("da:%pI6 dp:%d", &skops->remote_ip6, bpf_ntohs(skops->remote_port));
        }
        break;
    case BPF_SOCK_OPS_PASSIVE_ESTABLISHED_CB:
        // TODO
        break;
    case BPF_SOCK_OPS_STATE_CB:
        // TODO
        break;
    default:
        break;
    }

    return 0;
}