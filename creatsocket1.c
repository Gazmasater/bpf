#include <linux/bpf.h>
#include <bpf/bpf_helpers.h>
#include <linux/socket.h>
#include <linux/ptrace.h>
#include <linux/sched.h>

SEC("tracepoint/syscalls/sys_enter_socket")
int bpf_socket_enter(struct bpf_sock_tuple *tuple)
{
    bpf_printk("Socket creation called\n");
    return 0;
}

SEC("tracepoint/syscalls/sys_exit_socket")
int bpf_socket_exit(struct bpf_sock_tuple *tuple)
{
    bpf_printk("Socket created\n");
    return 0; // Возврат 0, чтобы не прерывать выполнение функции
}

// Лицензия для модуля
char LICENSE[] SEC("license") = "Dual BSD/GPL";
