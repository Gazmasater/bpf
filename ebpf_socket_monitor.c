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
    int protocol = ctx->protocol;                 // Получаем протокол из параметров

    bpf_printk("Socket creation called by PID: %d, Protocol: %d\n", pid, protocol);
    return 0; // Возврат 0, чтобы не прерывать выполнение функции
}

SEC("tracepoint/syscalls/sys_exit_socket")
int bpf_socket_exit(struct sys_exit_sock *ctx)
{
    __u32 pid = bpf_get_current_pid_tgid() >> 32; // Получаем PID

    bpf_printk("Socket created by PID: %d\n", pid);
    return 0;
}

// Обработчик операций с сокетом
SEC("sockops")
int sockops_handler(struct bpf_sock_ops *skops)
{
    __u32 pid = bpf_get_current_pid_tgid() >> 32; // Получаем PID
    bpf_printk("Socket operation by PID: %d, Operation: %d\n", pid, skops->op);
    return 0;
}

// Лицензия для модуля
char LICENSE[] SEC("license") = "Dual BSD/GPL";
