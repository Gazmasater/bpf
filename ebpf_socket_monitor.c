#include <linux/bpf.h>
#include <bpf/bpf_helpers.h>
#include <linux/socket.h>
#include <linux/ptrace.h>
#include <linux/sched.h>

SEC("tracepoint/syscalls/sys_enter_socket")
int bpf_socket_enter(struct pt_regs *ctx)
{
    __u32 pid = bpf_get_current_pid_tgid() >> 32;
    bpf_printk("Socket creation called by PID: %d\n", pid);
    return 0;
}

SEC("tracepoint/syscalls/sys_exit_socket")
int bpf_socket_exit(struct pt_regs *ctx)
{
    __u32 pid = bpf_get_current_pid_tgid() >> 32;
    bpf_printk("Socket created by PID: %d\n", pid);
    return 0;
}

char LICENSE[] SEC("license") = "Dual BSD/GPL";
