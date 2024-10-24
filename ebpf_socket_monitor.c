#include <linux/bpf.h>
#include <bpf/bpf_helpers.h>
#include <linux/in.h>
#include <linux/ptrace.h>

SEC("tracepoint/syscalls/sys_enter_connect")
int trace_connect(struct pt_regs *ctx)
{
    struct sockaddr_in *sockaddr;
    char msg[] = "IP: %d.%d.%d.%d, Port: %d, PID: %d, Protocol: %d\n";

    // Получаем указатель на структуру sockaddr
    sockaddr = (struct sockaddr_in *)ctx->di;  // для x86_64

    // Извлекаем IP-адрес и порт
    __u32 ip = sockaddr->sin_addr.s_addr;
    __u16 port = sockaddr->sin_port;

    // Получаем PID текущего процесса
    __u32 pid = bpf_get_current_pid_tgid() >> 32;

    // Получаем протокол (AF_INET или AF_INET6)
    __u16 protocol = sockaddr->sin_family;

    // Выводим данные
    bpf_trace_printk(msg, sizeof(msg),
                     (ip >> 24) & 0xFF, (ip >> 16) & 0xFF,
                     (ip >> 8) & 0xFF, ip & 0xFF,
                     bpf_htons(port), pid, protocol);

    return 0;
}

char _license[] SEC("license") = "GPL";