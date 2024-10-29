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
    const char *comm = (const char *)bpf_get_current_comm();
    int domain = PT_REGS_PARM1(ctx);   // Домен (AF_INET, AF_INET6 и т.д.)
    int type = PT_REGS_PARM2(ctx);     // Тип сокета (SOCK_STREAM, SOCK_DGRAM и т.д.)
    int protocol = PT_REGS_PARM3(ctx); // Протокол (IPPROTO_TCP, IPPROTO_UDP и т.д.)

    // Выводим информацию о создании сокета
    bpf_printk("Socket creation by PID: %d, Command: %s, Domain: %d, Type: %d, Protocol: %d\n",
               pid, comm, domain, type, protocol);
    return 0; // Возврат 0, чтобы не прерывать выполнение функции
}

SEC("tracepoint/syscalls/sys_exit_socket")
int bpf_socket_exit(struct pt_regs *ctx)
{
    __u32 pid = bpf_get_current_pid_tgid() >> 32; // Получаем PID

    // Выводим сообщение о завершении создания сокета
    bpf_printk("Socket created by PID: %d\n", pid);
    return 0;
}

char _license[] SEC("license") = "GPL";
