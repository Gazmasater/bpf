#include <linux/bpf.h>
#include <bpf/bpf_helpers.h>

SEC("tracepoint/syscalls/sys_enter_socket")
int bpf_socket_enter(void *ctx)
{
    char comm[16];
    bpf_get_current_comm(&comm, sizeof(comm)); // Получаем имя процесса
    bpf_printk("Socket creation called by process: %s\n", comm);
    return 0;
}

char LICENSE[] SEC("license") = "Dual BSD/GPL";
