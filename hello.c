#include <linux/bpf.h>
#include <bpf/bpf_helpers.h>
int counter = 0;

SEC("xdp")
int hello(void *ctx)
{
    bpf_printk("Hello World %d", counter);
    counter++;
    return XDP_PASS; // Переносим return внутрь функции
}

char LICENSE[] SEC("license") = "Dual BSD/GPL";