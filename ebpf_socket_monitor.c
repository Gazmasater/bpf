#include <linux/bpf.h>
#include <bpf/bpf_helpers.h>
#include <linux/ptrace.h>

SEC("kprobe/__x64_sys_execve")
int trace_connect(struct pt_regs *ctx)
{
    // Получаем PID текущего процесса
    __u32 pid = bpf_get_current_pid_tgid() >> 32;

    // Выводим только PID
    bpf_trace_printk("PID: %d\n", pid);

    return 0;
}

char _license[] SEC("license") = "GPL";
