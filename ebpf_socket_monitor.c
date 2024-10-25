#include <linux/bpf.h>
#include <bpf/bpf_helpers.h>

// Определение структуры bpf_sock_create_args
struct bpf_sock_create_args
{
    __aligned_u64 sock;
    int family;
    int type;
    int protocol;
    int flags;
};

SEC("cgroup/sock_create")
int bpf_sock_create(struct bpf_sock_create_args *ctx)
{
    bpf_printk("Socket created: family=%d type=%d protocol=%d\n",
               ctx->family, ctx->type, ctx->protocol);

    return 0;
}

char _license[] SEC("license") = "GPL";
