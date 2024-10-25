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
int bpf_sock_create(struct bpf_sock *sk, struct bpf_sock_create_args *ctx)
{
    char msg[64];
    unsigned long long data[3]; // Массив для хранения данных для форматирования

    // Заполняем массив данными
    data[0] = ctx->family;
    data[1] = ctx->type;
    data[2] = ctx->protocol;

    // Используем bpf_snprintf
    const char *fmt = "Socket created: family=%llu type=%llu protocol=%llu";
    bpf_snprintf(msg, sizeof(msg), fmt, data, sizeof(data));

    // Запись информации о созданном сокете в dmesg
    bpf_trace_printk(msg, sizeof(msg));

    return 0;
}

char _license[] SEC("license") = "GPL";
