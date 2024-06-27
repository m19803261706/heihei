inherit F_CLEAN_UP;
// int check_send(object me);

// int main(object me,object)
// {
//     //每隔10秒发送一次: write("你可以继续使用"+ZJURL("cmds:use putao")+"神奇葡萄"+NOR+"。"NOR"\n");
//     int number;

//     number = me->query_temp("putao_test");

//     //如果number不为空，说明已经开始了，不再重复
//     if (number)
//     {
//         write("你已经开始了测试，不需要重复开始，目前已经停止，如果需要请再次执行命令。\n");
//         // me->delete_temp("putao_test");
//         return 1;
//     }

//     check_send(me);

//     return 1;
// }

// int check_send(object me)
// {
//     int number;

//     number = me->query_temp("putao_test");

//     write("你可以继续使用"+ZJURL("cmds:use putao")+"神奇葡萄"+NOR+"123141414141414144。"NOR".........."ZJURL("cmds:use putao")+"不吃神奇葡萄"+NOR"\n");

//     if (number < 100)
//     {
//         number++;
//         me->set_temp("putao_test", number);
//         call_out("check_send", 10, me);
//     }
//     else
//     {
//         me->delete_temp("putao_test");
//     }

//     return 1;
// }

mixed traverse_directory(string dir_path, string *file_list);
mapping query_items(string dir_path);

// 定义一个辅助函数，用于递归遍历目录及其子目录
mixed traverse_directory(string dir_path, string *file_list) {
    // 获取目录下的所有文件和子目录信息
    mixed *files = get_dir(dir_path, -1);

    // 输出这个files
    // write(implode(files[0], ", ") + "\n");

    foreach (mixed file_info in files) {
        string file_name = file_info[0];
        int file_size = file_info[1];
        string full_path = dir_path + file_name;

        if (file_size > 0 && sscanf(file_name, "%*s.c")) {
            // 如果是.c文件，添加到文件列表中
            file_list += ({ full_path });
        }
        // 如果是目录，调用函数
        else if (file_size == -2) {

            // 数组大小限定在1000个
            if (sizeof(file_list) >= 1000000) {
                break;
            }
            // 正在处理的目录
            write("正在处理目录：" + full_path + "\n");
            query_items(full_path + "/");

        } 
        
    }

    return file_list;
}

// 定义主函数，接受一个目录路径作为参数
void query_items(string dir_path) {
    // 定义数组
    mixed *items = ({});

    // 初始化文件列表
    string *file_list = ({});

    // 递归遍历目录及其子目录
    file_list = traverse_directory(dir_path, file_list);

    // 遍历每个文件
    foreach (string file_path in file_list) {
        // 定义物品类型
        string item_type;
        // 加载对象
        object obj = load_object(file_path);

        // 获取物品属性
        int yuanbao = obj->query("yuanbao");
        string unit = obj->query("unit");
        int value = obj->query("value");
        string name = obj->query("name");
        string long_desc = obj->query("long");

        if (!long_desc) {
            long_desc = "这是" + name + "的描述。";
        }

        // write(file_path + "\n");

        // 检查对象是否有效
        if (!obj) {
            continue;
        }

        // 判断物品类型
        if (inherits(ITEM, obj)) {
            item_type = "不可叠加物品";
        } else if (inherits(COMBINED_ITEM, obj)) {
            item_type = "可叠加物品";
        } else {
            // write("未知物品类型：" + file_path + "\n");
            continue;
        }

        // 将物品信息添加到mapping数组中
        items += ({ ([
            "文件路径": file_path,
            "物品类型": item_type,
            "元宝价值": yuanbao,
            "单位": unit,
            "铜钱价值": value,
            "名称": filter_color(name),
            "描述": filter_color(long_desc),
        ]) });
    }

    // 写入文件,以\n分隔每个元素
    write("正在写入文件...\n");
    // /llmdata/clone.txt

    foreach (mapping item in items) {
        string msg;
        
        msg = json_encode(item) + "\n";

        write_file("/llmdata/clone.txt", msg, 0);
    }

}

int main(object me, string arg) {

    query_items("/clone/");
    return 1;

}