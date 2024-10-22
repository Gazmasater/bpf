#include <linux/bpf.h>
#include <linux/ptrace.h>
#include <linux/socket.h>
#include <linux/sched.h>
#include <bpf/bpf_helpers.h>

SEC("kprobe/__sock_create")
int sock_create(struct pt_regs *ctx, int family, int type, int protocol)
{
    bpf_trace_printk("Socket created with family %d, type %d, protocol %d\\n", family, type, protocol);
    return 0;
}

char _license[] SEC("license") = "GPL";
