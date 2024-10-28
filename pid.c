#include <linux/bpf.h>
#include <bpf/bpf_helpers.h>
#include <bpf/bpf_endian.h>
#include <linux/socket.h>
#include <linux/ptrace.h>
#include <linux/sched.h>
#include <netinet/in.h>

// Функция для обработки входящего сокета
SEC("tracepoint/syscalls/sys_enter_socket")
int bpf_socket_enter(struct pt_regs *ctx)
{
    __u32 pid = bpf_get_current_pid_tgid() >> 32; // Получаем PID

    bpf_printk("Socket creation called by PID: %d\n", pid);
    return 0; // Возврат 0, чтобы не прерывать выполнение функции
}

SEC("tracepoint/syscalls/sys_exit_socket")
int bpf_socket_exit(struct pt_regs *ctx)
{
    __u32 pid = bpf_get_current_pid_tgid() >> 32; // Получаем PID

    bpf_printk("Socket created by PID: %d\n", pid);
    return 0;
}
