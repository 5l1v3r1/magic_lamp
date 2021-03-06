#include <idc.idc>

static main()
{

    auto fd_kallsyms;
    auto kallsyms_file = AskFile(0, "*", "Select kallsyms file");

    Message("%s\n", kallsyms_file);
    fd_kallsyms = fopen(kallsyms_file, "r");

    if (fd_kallsyms == 0)
    {
        Message("open %s failed!\n", kallsyms_file);
        return;
    }
    while (1)
    {
        auto line = readstr(fd_kallsyms);
        auto line_len = strlen(line);
        if (line == -1)
            break;
        auto bb = strstr(line, " ");
        auto addr_str = line[0:bb];
        auto addr_str2 = line[bb + 1:-1];
        bb = strstr(addr_str2, " ");
        // auto name_len = line_len - 12;
        // auto func_name = substr(line, 11, 11 + name_len);
        auto func_name = addr_str2[bb + 1:-1];
        // print(addr_str);
        // print(func_name);
        auto addr = xtol(addr_str);
        // Message("addr_str=%s\n", addr_str);
        // Message("addr_str2=%s\n", addr_str2);
        // Message("func_name=%s\n", func_name);
        // Message("%s = %lx\n", func_name, addr);
        if (addr == 0)
        {
            continue;
        }
        // MakeName(addr, func_name);
        auto b_ret = MakeNameEx(addr, func_name, SN_NOCHECK);
        // break;
    }

    fclose(fd_kallsyms);
}