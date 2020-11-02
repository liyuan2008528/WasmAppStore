1、 将TA编译工程目录release/lib 或 Android工程目录vendor/thirdparty/secure_os/trustedcore/release/internal_tasks中的 elf_main_entry.o 备份。
2、 将调试用版本elf_main_entry.o 替换上面的目录中的.o
3、 重新编译TA，push到手机中， 重启手机。
4、 运行TA，使用adb shell tlogcat 查看log，进行调试。

这个版本会将访问TA的CA信息打印出来，方便查看鉴权失败原因。
