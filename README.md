Чтобы создать SSH-ключ для использования с GitHub, выполните следующие шаги:

Откройте терминал.

Сгенерируйте новый SSH-ключ. Введите следующую команду и замените your_email@example.com на свой адрес электронной почты, связанный с вашей учетной записью GitHub:

bash
Копировать код

ssh-keygen -t rsa -b 4096 -C "your_email@example.com"

Выберите расположение для сохранения ключа. По умолчанию ключ будет сохранен в

~/.ssh/id_rsa.

Если вы хотите использовать другое имя или местоположение, введите его, иначе просто нажмите Enter.

Введите пароль для ключа (по желанию). Вы можете ввести пароль для дополнительной безопасности или оставить это поле пустым и снова нажать Enter.

Добавьте SSH-ключ в ssh-agent. Запустите ssh-agent:

bash
Копировать код

eval "$(ssh-agent -s)"

Затем добавьте ваш SSH-ключ:

bash
Копировать код

ssh-add ~/.ssh/id_rsa

Скопируйте SSH-ключ в буфер обмена. Используйте следующую команду, чтобы скопировать ключ (предполагая, что вы сохранили его в стандартном месте):

bash
Копировать код

cat ~/.ssh/id_rsa.pub | xclip -selection clipboard

Если xclip не установлен, вы можете просто вывести ключ в терминал и скопировать его вручную:

bash
Копировать код

cat ~/.ssh/id_rsa.pub

Добавьте SSH-ключ в GitHub.

Перейдите на GitHub и войдите в свою учетную запись.
Нажмите на свой аватар в правом верхнем углу и выберите Settings.
В меню слева выберите SSH and GPG keys.
Нажмите на кнопку New SSH key.
Вставьте ваш SSH-ключ в поле "Key" и добавьте название в поле "Title" (например, "My Laptop").
Нажмите Add SSH key.
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#include <linux/bpf.h>
#include <bpf/bpf_helpers.h>
int counter = 0;

SEC("kprobes/accept4")
int probe_accept4(struct pt_regs *ctx)
{
    bpf_printk("Hello World KPROBES%d", counter);
    counter++;
    return 0;
}

char LICENSE[] SEC("license") = "Dual BSD/GPL";

gaz358@gaz358-BOD-WXX9:~/myprog/bpf$ sudo ./ecli run package.json
INFO [faerie::elf] strtab: 0x26d symtab 0x2a8 relocs 0x2f0 sh_offset 0x2f0
INFO [bpf_loader_lib::skeleton::preload::section_loader] User didn't specify custom value for variable counter, use the default one in ELF
libbpf: prog 'probe_accept4': missing BPF prog type, check ELF section name 'kprobes/accept4'
libbpf: prog 'probe_accept4': failed to load: -22
libbpf: failed to load object 'hellokprobes_bpf'
Error: Failed to run native eBPF program

Caused by:
    Bpf error: Failed to start polling: Bpf("Failed to load and attach: Failed to load bpf object\n\nCaused by:\n    System error, errno: 22"), RecvError





