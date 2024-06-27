#define TALNET_MASTER "/adm/special_ob/talnet_master"
int main(object me,string arg)
{
    // object pop;
    string msg;

    if (!arg)
    {

        string *list;

        // 读取/kungfu/special/目录下的所有文件的名称给list
        list = get_dir("/kungfu/special/");

        msg = ZJOBLONG"请选择一项天赋为你的初始天赋，" + (me->query("special_skill")?"你目前已经拥有天赋技能，请注意你的天赋技能会被清空覆盖，如果你有多项天赋技能，请谨慎执行此操作。":"你当前没有天赋技能。");
        msg += "\n";
        msg += ZJOBACTS2+ZJMENUF(3,3,8,30);
        // 遍历list中的每一个文件名
        foreach (string special_name in list)
        {
            string special_chinese_name;

            special_name = replace_string(special_name,".c","");

            if (!TALNET_MASTER->level_name(me,special_name))
                continue;
            
            special_chinese_name = TALNET_MASTER->level_name(me,special_name);

            msg += sprintf("%s:choose_tianfu %s"ZJSEP,special_chinese_name,special_name);
            
        }

        msg += sprintf("%s:choose_tianfu"ZJSEP,"刷新");

       write(msg +"\n");

       return 1;
    }


    if (arg)
    {

        string special_name,isSure;
        // 如果arg的格式为special_name sure

        if (sscanf(arg,"%s %s",special_name,isSure) == 2)
        {
            if (isSure == "sure")
            {
                if (me->query("is_choose_tianfu"))
                {
                    tell_object(me,pop_final("你已经选择了天赋"));
                    return 1;
                }

                if (me->query("special_skill"))
                {
                    me->delete("special_skill");
                }

                me->set("special_skill/" + special_name,1);
                me->set("is_choose_tianfu",1);
                tell_object(me,pop_final("你选择了" + TALNET_MASTER->level_name(me,special_name) + "作为你的初始天赋"));

                // me->force_me("tianfu");
            }
            else
            {
                tell_object(me,pop_final("你取消了选择" + TALNET_MASTER->level_name(me,special_name) + "作为你的初始天赋"));
            }
            return 1;
        }


        msg = ZJOBLONG"你是否确认选择" + TALNET_MASTER->level_name(me,arg) + "作为你的初始天赋\n介绍:\n" + TALNET_MASTER->level_desc(me,arg);
        msg = replace_string(msg,"\n",ZJBR);
        msg += "\n"ZJOBACTS2+ZJMENUF(2,2,8,30);
        msg += sprintf("%s:choose_tianfu %s sure"ZJSEP,"是",arg);
        msg += sprintf("%s:choose_tianfu %s no"ZJSEP,"否",arg);

        write(msg +"\n");

        return 1;
    }
}