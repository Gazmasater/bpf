#include <linux/bpf.h>
#include <bpf/bpf_helpers.h>
#include <linux/socket.h>
#include <linux/in.h>
#include <linux/types.h> // Для определения u32

SEC("tracepoint/syscalls/sys_enter_bind")
int bpf_bind_enter(void *ctx)
{
    struct sockaddr_in *addr;
    char comm[16];

    // Получаем имя процесса
    bpf_get_current_comm(&comm, sizeof(comm));

    // Получаем PID процесса
    __u32 pid = bpf_get_current_pid_tgid() >> 32;

    // Получаем указатель на структуру sockaddr_in
    addr = (struct sockaddr_in *)(ctx + sizeof(int));

    // Получаем IP-адрес
    __be32 ip = addr->sin_addr.s_addr;

    // Конвертируем IP в читаемый формат
    unsigned char *ip_bytes = (unsigned char *)&ip;

    // Выводим информацию: IP, PID, имя процесса
    bpf_printk("Binding on IP: %u.%u.%u.%u, PID: %u, Process: %s\n",
               ip_bytes[0], ip_bytes[1], ip_bytes[2], ip_bytes[3],
               pid, comm);

    return 0;
}

char LICENSE[] SEC("license") = "Dual BSD/GPL";
