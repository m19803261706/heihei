int main(object me, string arg)
{
    //读取kungfu/skill/目录下的所有的后缀名为.c的文件
    string *files = get_dir(SKILL_D(""));
    string *skis = ({});

    //遍历所有的.c文件,显示格式为技能名(文件名)然后输出
    foreach (string file in files)
    {
        if (sscanf(file, "%s.c", file))
        {
            file = replace_string(file, ".c", "");
            skis += ({ sprintf("%s(%s)", to_chinese(file), file)});
        }
    }

    write("你可以使用的技能有：\n" + implode(skis, "\n") + "\n");
    return 1;
}