Для переустановки ядра Linux из исходного кода, потребуется скачать исходный код, сконфигурировать его, собрать, а затем установить. Вот пошаговая инструкция:

Установка необходимых зависимостей: Убедитесь, что у вас установлены компилятор GCC, необходимые заголовочные файлы и другие зависимости:


sudo apt update
sudo apt install build-essential libncurses-dev bison flex libssl-dev libelf-dev

Скачивание исходного кода ядра: Исходный код ядра можно загрузить с kernel.org, выбрав нужную версию.


wget https://cdn.kernel.org/pub/linux/kernel/v5.x/linux-5.x.x.tar.xz
tar -xvf linux-5.x.x.tar.xz
cd linux-5.x.x

Конфигурация ядра:

Вы можете использовать текущую конфигурацию, скопировав файл текущего ядра:


cp /boot/config-$(uname -r) .config

Затем запустите команду настройки конфигурации ядра:


make menuconfig

Это откроет интерфейс, где можно изменить параметры сборки, если необходимо.

Компиляция ядра и модулей:

Сначала выполните команду:


make -j$(nproc)

Это начнет сборку ядра, используя все доступные ядра процессора для ускорения процесса.

После этого соберите модули:


make modules -j$(nproc)

Установка ядра и модулей:

Установите модули с помощью команды:


sudo make modules_install

Установите ядро:


sudo make install

Обновление загрузчика: После установки ядра потребуется обновить загрузчик, чтобы новое ядро стало доступно для загрузки.


sudo update-grub

Перезагрузка системы: После успешной установки ядра перезагрузите систему, чтобы начать работу с новым ядром.


sudo reboot

После перезагрузки проверьте, что система загружена с новым ядром:


uname -r

Это покажет версию ядра, и вы сможете убедиться, что используется новое ядро.





