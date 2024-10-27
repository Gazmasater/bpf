#include <linux/bpf.h>
#include <bpf/bpf_helpers.h>
#include <bpf/bpf_endian.h>
#include <linux/socket.h>
#include <linux/ptrace.h>
#include <linux/sched.h>
#include <netinet/in.h>
#include <linux/ip.h>

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
    int family;
    int type;
    int protocol;
};

// Функция для обработки входящего сокета
SEC("tracepoint/syscalls/sys_enter_socket")
int bpf_socket_enter(struct sys_enter_sock *ctx)
{
    bpf_printk("Socket creation called\n");
    // TODO
    return 0; // Возврат 0, чтобы не прерывать выполнение функции
}

SEC("tracepoint/syscalls/sys_exit_socket")
int bpf_socket_exit(struct sys_exit_sock *ctx)
{
    pid_t pid;
    pid = bpf_get_current_pid_tgid() >> 32;
    // TODO
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

#define ETH_P_IP 0x0800 /* Internet Protocol packet	*/

SEC("socket")
int socket_handler(struct __sk_buff *skb)
{
    __u16 proto;

    bpf_skb_load_bytes(skb, 12, &proto, 2);
    proto = __bpf_ntohs(proto);
    if (proto != ETH_P_IP)
        return 0;
    if (skb->family == AF_INET)
    {
        bpf_printk("sa:%pI4 sp:%d", &skb->local_ip4, bpf_ntohs(skb->local_port));
        bpf_printk("da:%pI4 dp:%d", &skb->remote_ip4, bpf_ntohs(skb->remote_port));
    }
    else if (skb->family == AF_INET6)
    {
        bpf_printk("sa:%pI6 sp:%d", &skb->local_ip6, bpf_ntohs(skb->local_port));
        bpf_printk("da:%pI6 dp:%d", &skb->remote_ip6, bpf_ntohs(skb->remote_port));
    }
    // TODO

    return 0;
}

// TODO
/*
Кажется чтобы решить задачу придется воспользоваться несколькими точками трассировки и bpf Map для обмена данными между ними.
Я бы посмотрел в следующем направлении:
1. Создать точку трассировки на системные вызовы по установлению сетевого соединения, такие как kprobe/sys_accept
или kprobe/sys_connect, ну т.е. SEC("kprobe/sys_accept") (примеры можно погуглить в интернете)
2. Определение пида процесса. Использовать bpf_get_current_pid_tgid() для получения текущего PID и TGID (Thread Group ID)
при выполнении определенной программы BPF. И использовать BPF Maps для отслеживания связи между дескриптором сокета и PID процесса.
3. Отслеживание завершения процессов через точку kprobe на функцию do_exit() SEC("kprobe/do_exit") (примеры в сети).
Тут так же через bpf_get_current_pid_tgid() определять pid и через BPF Maps ассоциироваться с сетевым соединением

*/

// Лицензия для модуля
char LICENSE[] SEC("license") = "Dual BSD/GPL";
