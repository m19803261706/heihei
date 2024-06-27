int main(object me,string arg)
{
    // 1.添加招式
    // 2.清除招式
    string r_pfm_name,r_pfm_use_msg;//待准备的信息

    if (!arg)
    {
        object pop;
        string msg;
        // pop弹窗，你目前的互搏招式为：招式1 招式2，如果没有招式，basic函数设置为：你没有互搏招式
        pop = new(POP1);
        msg = ZJOBLONG"你目前的互搏招式为：\n";

        if (mapp(me->query("my_hubo_skill_list")))
        {
            foreach (string pfm_name in keys(me->query("my_hubo_skill_list")))
            {
                msg += pfm_name + ZJBR;
            }

            // 如果我只有一个招式
            if (sizeof(me->query("my_hubo_skill_list")) == 1)
            {
                msg += "你只有一个互搏招式，在战斗中使用默认释放改招式两次。"ZJBR;
            }
            else
            // 如果我有两个招式
            if (sizeof(me->query("my_hubo_skill_list")) == 2)
            {
                msg += "你有两个互搏招式，在战斗中使用默认可以一次性释放两个不同的招式。"ZJBR;
            }
            else //招式数量错误
            {
                msg += "你的互搏招式数量错误，请联系巫师。"ZJBR;
            }

        }
        else
        {
            msg += "你没有互搏招式。"ZJBR;
        }

        msg += "\n"ZJOBACTS2 + ZJMENUF(4, 4, 8, 30);
        msg += "添加招式:hubo_skill add"ZJSEP;
        msg += "清除招式:hubo_skill delete"ZJSEP;
        write(msg + "\n");
        return 1;

    }

    if (arg == "add")
    {
        mapping skills = me->query_skill_map();
        mixed *data = ({});//data实际上是一个二维数组
        string *use_skills = ({});//玩家使用的技能
        object pop;


        foreach(mixed key in keys(skills))
       {
          string skill = skills[key];
          mixed *pfms = SKILL_D(skill)->skill_pfms(key);
            if (member_array(skill, use_skills) == -1 && pfms != ({}))
            {
                use_skills += ({ skill });
            }
            else
            {
                continue;
            }
        
          data += ({ pfms });
       }

       pop = new(POP1);
       pop->basic("你要添加那一个招式到你互搏招式中？",2);

       foreach (mapping *single_pfm_data_list in data)
       {
            foreach (mapping pfm_data in single_pfm_data_list)
            {
                string pfm_name,pfm_use_command;

                pfm_name = pfm_data["name"];
                pfm_use_command = pfm_data["command"];

                // 如果pfm_use_command中有exert,跳过
                if (strsrch(pfm_use_command,"exert") != -1)
                {
                    continue;
                }

                pfm_use_command = replace_string(pfm_use_command,"perform ","");
                pop->add_button(pfm_data["name"],"hubo_skill add " + pfm_name + "-" + pfm_use_command);

            }
       }

       write(pop->result() + "\n");
       return 1;
    }

    // 如果arg为delete，清除互搏招式
    if (arg == "delete")
    {
        me->delete("my_hubo_skill_list");
        write("你成功清除了你的互搏招式，你可以重新设置互搏招式了。\n");
        return 1;
    }

    // 如果arg的格式为招式名 招式msg设定到r_pfm_name r_pfm_use_msg中
    if (sscanf(arg,"add %s-%s",r_pfm_name,r_pfm_use_msg) == 2)
    {
        string pfm_name,pfm_use_command;

        pfm_name = r_pfm_name;
        pfm_use_command = r_pfm_use_msg;

        // 如果我存在my_hubo_skill_list这个参数并且这个参数是一个mapping并且超过2个招式，提示招式已满
        if (mapp(me->query("my_hubo_skill_list")) && sizeof(me->query("my_hubo_skill_list")) >= 2)
        {
            write("你的互搏招式已经满了，如果你想重新设置招式请先清除招式。\n");
            return 1;
        }

        // 已经有这个招式了
        if (me->query("my_hubo_skill_list/" + pfm_name))
        {
            write("你已经有这个招式了，如果你想重新设置招式请先清除招式。\n");
            return 1;
        }

        me->set("my_hubo_skill_list/" + pfm_name,([
            "name" : pfm_name,
            "command" : pfm_use_command,
        ]));

        write("你成功添加了招式" + pfm_name + "到你的互搏招式中。\n");
        return 1;
    }

    if (arg == "use")
    {
        string result_command;
        mapping hubo_skill_list = me->query("my_hubo_skill_list");


        // 非战斗中不可用
        if (!me->is_fighting())
        {
            write("你当前不在战斗中，无法使用互搏招式。\n");
            return 1;
        }

        // 忙乱中不可用
        if (me->is_busy())
        {
            write("你正在忙乱中，无法使用互搏招式。\n");
            return 1;
        }

        // 如果我不存在my_hubo_skill_list这个参数或者这个参数不是一个mapping或者这个mapping的招式数量小于1，提示招式不足,先设置招式
        if (!mapp(hubo_skill_list) || sizeof(hubo_skill_list) < 1)
        {
            write("你的互搏招式不足，如果你想设置招式请先设置招式。\n");
            return 1;
        }

        // 如果我只有一个招式
        if (sizeof(hubo_skill_list) == 1)
        {
            string *hubo_skill_name_list = ({});//互搏招式名字列表
            string pfm_one;//招式1

            hubo_skill_name_list = keys(hubo_skill_list);
            pfm_one = hubo_skill_name_list[0];

            result_command = "perform " + hubo_skill_list[pfm_one]["command"] + " twice";

        }
        else
        // 如果我有两个招式
        if (sizeof(hubo_skill_list) == 2)
        {
            string *hubo_skill_name_list = ({});
            string pfm_one,pfm_two;

            hubo_skill_name_list = keys(hubo_skill_list);
            pfm_one = hubo_skill_name_list[0];

            pfm_two = hubo_skill_name_list[1];

            result_command = "perform " + hubo_skill_list[pfm_one]["command"] + " and " + hubo_skill_list[pfm_two]["command"];

        }
        else //招式数量错误
        {
            write("你的互搏招式数量错误，请联系巫师。\n");
            return 1;
        }

        write("你开始使用你的互搏招式。\n");
        me->force_me(result_command);
        return 1;
    }

    return 1;



}