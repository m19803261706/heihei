#include <ansi.h>

// 设置物品类型及其对应的权重
mapping item_types = ([
    "gem_list": 2, // 最贵的物品
    "skill_list": 5, // 技能
    "ob_list": 8, // 珍贵物品
    "pt_list": 85, // 一般物品
]);

// 物品列表
mapping items = ([
    "gem_list": ({
        "/clone/aoyi_book/aoyi_book",
    }),
    "skill_list": ({
        "qishang-quan",
        "baihua-quan",
        "hanbing-mianzhang",
        "xuanming-zhang",
        "sougu",
        "zhuihun-jian",
        "yunlong-bian",
        "hanxing-bada",
        "bizhen-qingzhang",
        "huanyin-zhi",
        "ningxue-shenzhao",
        "sanfen-jianshu",
        "zijinbagua-dao",
    }),
    "pt_list": ({
        "/clone/vip/baozhu",
        "/clone/vip/book_tianfu",
        "/clone/vip/book_wuliang",
        "/clone/vip/box_chuji",
        "/clone/vip/build_ling",
        "/clone/vip/dan_chongmai1",
        "/clone/vip/dan_chongmai2",
        "/clone/vip/dan_chongmai3",
        "/clone/vip/dan_chongmai4",
        "/clone/vip/dan_qingxin",
        "/clone/vip/dan_xieqi",
        "/clone/vip/dan_zhengqi",
        "/clone/vip/fushougao",
        "/clone/vip/jinsha",
        "/clone/vip/ling_wolong",
        "/clone/vip/lingzhi",
        "/clone/vip/lingzhi2",
        "/clone/vip/putao",
        "/clone/vip/tianling",
        "/clone/vip/tianxiang",
        "/clone/vip/yanzhi",
        "/clone/vip/yanzhi2",
        "/clone/vip/zyao1",
    }),
    "ob_list": ({
        "/clone/vip/avipcard",
        "/clone/vip/bianxingdan",
        "/clone/vip/butian",
        "/clone/vip/card_name",
        "clone/vip/dan_bianxing",
        "/clone/vip/dan_chongsu",
        "/clone/vip/dan_jiuzhuan",
        "/clone/vip/card_name",
        "/clone/vip/dan_wangyou",
        "/clone/vip/hantie",
        "/clone/vip/jinpiao",
        "/clone/vip/putao1",
        "/clone/vip/tiancs",
        "/clone/vip/wujins",
        "/clone/vip/xidianka",
        "/clone/vip/xuantie",
        "/clone/vip/dan_wangyou",
        "/clone/vip/dan_wangyou",
    }),
]);

int start_ken(object me);

int main(object me, string arg)
{
    string str;
    if (!arg)
    {
        str = ZJOBLONG "奖池当前有百分之二的几率抽到"HIR"意境卷轴"NOR"，百分之五的概率抽到"HIY"技能"NOR"，百分之八的概率抽到"HIM"珍贵物品"NOR"，百分之八十五的概率抽到"HIG"普通物品"NOR"。";
        str += ZJBR "100元宝抽一次, 1000元宝十连。";
        str += ZJBR "建议经验足够技能提升到180级再进行抽奖！";
        str += ZJBR "否则抽到公共技能下线等级会掉！！";
        str += ZJBR "建议抽到技能后到铁匠处进行离线挂机防止掉线！！";
        str += "\n" ZJOBACTS2 + ZJMENUF(4, 4, 8, 30);
        if (present("ten card", me))
            str += "十连抽:luckdraw ten" ZJSEP;
        if (present("one card", me))
            str += "单抽卡:luckdraw one" ZJSEP;
        str += "元宝单抽:luckdraw yuanbao" ZJSEP;
        str += "元宝十连:luckdraw yuanbao_sl";
        write(str + "\n");
        return 1;
    }
    if (arg == "yuanbao")
    {
        if (me->query("yuanbao") < 100)
            return notify_fail("请确保你有足够的元宝。\n");
        me->add("yuanbao", -100);
        start_ken(me);
    }

    if (arg == "yuanbao_sl")
    {
        int i;

        if (me->query("yuanbao") < 1000)
            return notify_fail("请确保你有足够的元宝。\n");

        me->add("yuanbao", -1000);
        for (i = 0; i < 10; i++)
        {
            start_ken(me);
        }
        return 1;
    }

    if (arg == "one")
    {
        object ob;
        if (!objectp(ob = present("one card", me)))
        {
            if (!ob->query("yuanbao"))
                return notify_fail("你又没有单抽卡，喵。\n");
        }
        if (!ob->query("yuanbao"))
            return notify_fail("你又没有单抽卡，喵。\n");
        ob->add_amount(-1);
        start_ken(me);
        return 1;
    }

    if (arg == "ten")
    {
        object ob;
        int i = 0;
        if (!objectp(ob = present("ten card", me)))
            return notify_fail("你又没有十连抽卡，喵。\n");
        ob->add_amount(-1);
        while (i < 10)
        {
            start_ken(me);
            i++;
        }
        return 1;
    }
    return 1;
}

int start_ken(object me)
{
    string item_type, skill;
    int random, i;
    object obj;
    int total_weight = 0;
    int current_weight = 0;
    // 计算总权重
    foreach (item_type in keys(item_types)) {
        total_weight += item_types[item_type];
    }

    random = secure_random(total_weight) + 1;  // 生成一个 1 到总权重的随机数

    // 根据权重选择物品类型
    foreach (item_type in keys(item_types)) {
        current_weight += item_types[item_type];
        if (random <= current_weight) {
            break;
        }
    }

    // 抽取物品
    if (item_type == "skill_list")
    {
        string *item_list = items[item_type];
        skill = item_list[random(sizeof(item_list))];

        // 如果me->query_skill($1)通过，代表我有这个技能，使用filter_array过滤掉我拥有的技能，如果过滤后数组大小为0，则回退200元宝
        if (sizeof(filter_array(item_list, (: $(me)->query_skill($1) > 0 :))) == sizeof(item_list)) //如果我拥有所有技能
        {
            me->add("yuanbao", 200);
            write("你已经拥有所有技能，退回200元宝。\n");
            return 1;
        }


        // 判断会的技能中有没有此技能

        if (sizeof(me->query_skills()))
        {
            while (member_array(skill, keys(me->query_skills())) != -1)
            {
                // 重新抽取
                skill = item_list[random(sizeof(item_list))];
            }
        }
        else
        {
            skill = item_list[random(sizeof(item_list))];
        }
        me->set_skill(skill, 180);

        skill = to_chinese(skill);

        log_file("luckdraw", ctime(time()) + "   " + me->name() + me->query("id") + "  抽到" + skill + "\n");
        write("恭喜抽到【" + skill + "】!\n");
        CHANNEL_D->do_channel(this_object(), "rumor", me->name() + "抽到了一个技能【" + skill + "】!\n");
        return 1;
    }
    else
    {
        string *item_list = items[item_type];
        string obj_path = item_list[random(sizeof(item_list))];

        obj = new_bind(obj_path);

        if (!objectp(obj))
        {
            // 如果无法创建物品，输出错误路径
            write("无法创建物品：" + obj_path + "\n");
            return 1;
        }

        log_file("luckdraw", ctime(time()) + "   " + me->name() + me->query("id") + "  抽到" + obj->name() + "\n");
       

        write("恭喜抽到【" + obj->query("name") + "】!\n");
        CHANNEL_D->do_channel(this_object(), "rumor", me->name() + "抽到了一个物品【" + obj->query("name") + "】!\n");
        obj->move(me);
        return 1;
    }

}