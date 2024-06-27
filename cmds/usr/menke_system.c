
// 门客的最小执行力50，最大执行力100。
#define MIN_FORCE 50
#define MAX_FORCE 100

mapping name_list = ([
    "飞燕": "窈窕女子，眉目如画，气质高雅，身姿轻盈。",
    "铁手": "壮硕男子，浓眉大眼，一脸正气，肌肉结实。",
    "碧眼": "英俊少年，碧眼清澈，短发飘逸，阳光帅气。",
    "笑面虎": "中年文士，面容和善，眼神狡黠，风度翩翩。",
    "灵犀": "秀美女子，眼含秋水，温婉可人，柔若无骨。",
    "破浪": "魁梧大汉，肤色古铜，豪迈不羁，气势磅礴。",
    "血影": "冷峻青年，目光锐利，唇薄如剑，神秘莫测。",
    "随风": "苗条女子，长发及腰，举止轻盈，如仙子下凡。",
    "雷鸣": "魁梧汉子，须眉浓密，声如洪钟，威猛霸气。",
    "幽兰": "清秀女子，眉清目秀，气质清新，如一朵幽兰。",
    "断魂": "独眼刀客，刀疤满面，粗犷豪放，不拘小节。",
    "碧落": "绿衫少女，清新脱俗，眉目如画，宛若仙子。",
    "苍狼": "粗犷大汉，满脸络腮胡，目光犀利，野性十足。",
    "紫烟": "神秘女子，紫衣罩体，眼波流转，行事低调。",
    "残阳": "沧桑剑客，剑眉星目，热血衷肠，正直忠诚。",
    "幽灵": "白衣青年，面容俊秀，行踪诡异，神秘莫测。",
    "秋水": "柔美女子，眼神忧郁，善解人意，温婉可人。",
    "狂风": "豪放汉子，长发飘飘，性格直爽，酒量惊人。",
    "破晓": "英俊少年，眼神坚定，心怀光明，气宇轩昂。",
    "飞鸿": "矫健女子，眼神锐利，身手敏捷，英姿飒爽。",
    "天涯": "孤傲剑客，剑法独特，行踪不定，神秘莫测。",
    "落花": "娇媚女子，舞姿翩翩，眼波流转，妩媚动人。",
    "烈火": "豪迈汉子，满脸络腮胡，性格火爆，气势磅礴。",
    "青霜": "冷艳女子，白衣胜雪，剑法高超，不问世事。",
    "狂龙": "霸气男子，满脸横肉，性格狂傲，无人可敌。",
    "飞雪": "冰肌女子，白衣如雪，性格冷傲，冰清玉洁。",
    "雷动": "威猛汉子，满脸络腮胡，性格豪迈，气势如虹。",
    "寒星": "英俊少年，眼神锋利，短发利落，英姿飒爽。",
    "霜叶": "清秀女子，眉目如画，气质高雅，如霜如叶。",
    "夜叉": "粗犷大汉，满脸络腮胡，目光犀利，气势汹汹。",
    "碧云": "绿衫少女，清新脱俗，眉目如画，宛若仙子。",
    "赤炎": "豪迈汉子，满脸络腮胡，性格火爆，气势磅礴。",
    "紫霞": "神秘女子，紫衣罩体，眼波流转，行事低调。",
    "秋风": "沧桑剑客，剑眉星目，热血衷肠，正直忠诚。",
    "幽冥": "白衣青年，面容俊秀，行踪诡异，神秘莫测。",
]);

mapping menke_gender_mapping = ([
    "飞燕": "女性",
    "铁手": "男性",
    "碧眼": "男性",
    "笑面虎": "男性",
    "灵犀": "女性",
    "破浪": "男性",
    "血影": "男性",
    "随风": "女性",
    "雷鸣": "男性",
    "幽兰": "女性",
    "断魂": "男性",
    "碧落": "女性",
    "苍狼": "男性",
    "紫烟": "女性",
    "残阳": "男性",
    "幽灵": "男性",
    "秋水": "女性",
    "狂风": "男性",
    "破晓": "男性",
    "飞鸿": "女性",
    "天涯": "男性",
    "落花": "女性",
    "烈火": "男性",
    "青霜": "女性",
    "狂龙": "男性",
    "飞雪": "女性",
    "雷动": "男性",
    "寒星": "男性",
    "霜叶": "女性",
    "夜叉": "男性",
    "碧云": "女性",
    "赤炎": "男性",
    "紫霞": "女性",
    "秋风": "男性",
    "幽冥": "男性"
]);

mapping menke_skills_all_list = ([
    "武当":([
        "skill_list":({ "force","taiji-shengong","parry","dodge","tiyunzong","sword","taiji-jian","hand","paiyun-shou","unarmed","taiji-quan" }),
        "prepare_skill":([ "parry":"taiji-jian", "force":"taiji-shengong", "dodge":"tiyunzong", "sword":"taiji-jian", "hand":"paiyun-shou", "unarmed":"taiji-quan" ]),
        "weapon":"/clone/weapon/changjian"
    ]),
    "少林":([
        "skill_list":({ "force","hunyuan-yiqi","parry","dodge","shaolin-shenfa","sword","damo-jian","finger","nianhua-zhi","strike","sanhua-zhang" }),
        "prepare_skill":([ "parry":"damo-jian", "force":"hunyuan-yiqi", "dodge":"shaolin-shenfa", "sword":"damo-jian", "finger":"nianhua-zhi", "strike":"sanhua-zhang" ]),
        "weapon":"/clone/weapon/changjian"
    ]),
    "华山":([
        "skill_list":({ "force","zixia-shengong","parry","dodge","feiyan-huixiang","sword","huashan-sword","cuff","poyu-quan","strike","hunyuan-zhang" }),
        "prepare_skill":([ "parry":"huaxian-sword", "force":"zixia-shengong", "dodge":"feiyan-huixiang", "sword":"huashan-sword", "cuff":"poyu-quan", "strike":"hunyuan-zhang" ]),
        "weapon":"/clone/weapon/changjian"
    ]),
    "欧阳世家":([
        "skill_list":({ "force","hamagong","parry","dodge","chanchu-bufa","staff","lingshe-zhangfa","cuff","lingshe-quan","finger","shedu-qiqiao" }),
        "prepare_skill":([ "force":"hamagong", "parry":"lingshe-zhangfa", "dodge":"chanchu-bufa", "staff":"lingshe-zhangfa", "cuff":"lingshe-quan", "finger":"shedu-qiqiao" ]),
        "weapon":"/clone/weapon/gangzhang"
    ]),
    "丐帮":([
        "skill_list":({ "force","huntian-qigong","parry","dodge","feiyan-zoubi","staff","dagou-bang","strike","dragon-strike" }),
        "prepare_skill":([ "force":"huntian-qigong", "parry":"dagou-bang", "dodge":"feiyan-zoubi", "staff":"dagou-bang", "strike":"dragon-strike" ]),
        "weapon":"/clone/weapon/gangzhang"
    ]),
    "桃花岛":([
        "skill_list":({ "force","bibo-shengong","parry","dodge","anying-fuxiang","sword","yuxiao-jian","hand","lanhua-shou","finger","tanzhi-shentong" }),
        "prepare_skill":([ "parry":"yuxiao-jian", "force":"bibo-shengong", "dodge":"anying-fuxiang", "sword":"yuxiao-jian", "hand":"lanhua-shou", "finger":"tanzhi-shentong" ]),
        "weapon":"/clone/weapon/changjian"
    ]),
    "古墓":([
        "skill_list":({ "force","yunv-xinfa","parry","dodge","yunv-shenfa","unarmed","meinv-quan","strike","fireice-strike","tianluo-diwang","throwing","yufeng-zhen","sword","yunv-jian","quanzhen-jian" }),
        "prepare_skill":([ "force":"yunv-xinfa", "sword":"yunv-jian", "dodge":"yunv-shenfa", "parry":"meinv-quan", "unarmed":"meinv-quan", "strike":"tianluo-diwang", "throwing":"yufeng-zhen" ]),
        "weapon":"/clone/weapon/changjian"
    ]),
    "全真教":([
        "skill_list":({ "force","quanzhen-xinfa","parry","dodge","jinyan-gong","strike","haotian-zhang","chongyang-shenzhang","finger","zhongnan-zhi","sword","quanzhen-jian" }),
        "prepare_skill":([ "force":"quanzhen-xinfa", "sword":"quanzhen-jian", "dodge":"jinyan-gong", "parry":"haotian-zhang", "strike":"haotian-zhang", "finger":"zhongnan-zhi" ]),
        "weapon":"/clone/weapon/changjian"
    ]),
    "星宿派":([
        "skill_list":({ "force","huagong-dafa","guixi-gong","throwing","feixing-shu","dodge","zhaixinggong","strike","chousui-zhang","claw","sanyin-wugongzhao","whip","chanhun-suo","parry","staff","poison","tianshan-zhang" }),
        "prepare_skill":([ "force":"huagong-dafa", "dodge":"zhaixinggong", "strike":"chousui-zhang", "claw":"sanyin-wugongzhao", "whip":"chanhun-suo", "parry":"tianshan-zhang", "staff":"tianshan-zhang" ]),
        "weapon":"/clone/weapon/gangzhang"
    ]),
    "雪山派":([
        "skill_list":({ "force","longxiang","mizong-neigong","dodge","shenkong-xing","cuff","yujiamu-quan","hand","dashou-yin","parry","staff","xiangmo-chu","lamaism","hammer","riyue-lun" }),
        "prepare_skill":([ "force":"longxiang", "dodge":"shenkong-xing", "cuff":"yujiamu-quan", "hand":"dashou-yin", "parry":"riyue-lun", "sword":"xiangmo-chu", "hammer":"riyue-lun" ]),
        "weapon":"/d/xueshan/obj/yinlun"
    ]),
    "血刀门":([
        "skill_list":({ "lamaism","force","parry","blade","xue-dao","sword","mingwang-jian","dodge","mizong-neigong","xuehai-mogong","shenkong-xing","hand","dashou-yin","cuff","yujiamu-quan" }),
        "prepare_skill":([ "force":"xuehai-mogong", "dodge":"shenkong-xing", "hand":"dashou-yin", "cuff":"yujiamu-quan", "parry":"xue-dao", "blade":"xue-dao", "sword":"mingwang-jian" ]),
        "weapon":"/clone/weapon/gangdao"
    ]),
    "逍遥派":([
        "skill_list":({ "force","xiaoyao-xinfa","beiming-shengong","dodge","feiyan-zoubi","liuyang-zhang","parry","blade","ruyi-dao","zhemei-shou","hand","strike","literate" }),
        "prepare_skill":([ "force":"beiming-shengong", "dodge":"lingbo-weibu", "hand":"zhemei-shou", "strike":"liuyang-zhang", "parry":"ruyi-dao", "blade":"ruyi-dao" ]),
        "weapon":"/clone/weapon/gangdao"
    ]),
    "神龙教":([
        "skill_list":({ "force","shenlong-xinfa","dodge","yixingbu","hand","shenlong-bashi","strike","huagu-mianzhang","parry","staff","sword","shedao-qigong","literate" }),
        "prepare_skill":([ "force":"shenlong-xinfa", "dodge":"yixingbu", "hand":"shenlong-bashi", "strike":"huagu-mianzhang", "parry":"shedao-qigong", "staff":"shedao-qigong" ])
    ]),
]);

//让门客在内存当中清除
int clean_menke(object me)
{
    object menke;
    // 检查玩家是否已经召唤门客，如果有清除这个门客
    if (objectp(menke = me->query("menke_system/summon")))
    {

        // 判断门客是否有收益如果有收益先结算奖励
        if (menke->query("menke_reward"))
        {
            // 结算门客收益
            MENKE_M->give_reward_master(menke, me);
        }

        destruct(menke);
        me->delete("menke_system/summon");
        tell_object(me, "你的门客已经离开。\n");
    }

    return 1;
}

// 遣散当前的门客
int qiansan_menke(object me)
{
    object menke;
    // 检查玩家是否已经召唤门客，如果有清除这个门客
    if (objectp(menke = me->query("menke_system/summon")))
    {
        tell_object(me, "你遣散了" + menke->name() + "。\n");
        destruct(menke);
        me->delete("menke_system");
    }
    else
    {
        tell_object(me, "你遣散了门客。\n");
        me->delete("menke_system");
    }

    return 1;
}

int parse_menke(object me)
{
    mapping menke_get_list = ([]);
    // 先清除原先的门客招募列表
    me->delete("menke_system/menke_get_list");

    // 每次最多3个门客
    while (sizeof(me->query("menke_system/menke_get_list")) < 3)
    {
        mapping menke_attr; // 随机生成门客
        string menke_name = keys(name_list)[random(sizeof(name_list))];
        string menke_desc = name_list[menke_name];
        // 门客的执行力
        int menke_force = random(MAX_FORCE - MIN_FORCE) + MIN_FORCE;
        string gender = menke_gender_mapping[menke_name];

        // 如果玩家已经招募过这个门客，则跳过
        if (me->query("menke_system/menke_get_list/" + menke_name))
        {
            continue;
        }

        // 门客的其他属性
        menke_attr = ([
            "name" : menke_name,
            "desc" : menke_desc,
            "force" : menke_force,
            "level" : 100,//初始等级 100
            "gender" : gender
        ]);

        // 初始化门客技能和派系，随机选择一个门派
        menke_attr["paixi"] = keys(menke_skills_all_list)[random(sizeof(menke_skills_all_list))];
        menke_attr["skills"] = menke_skills_all_list[menke_attr["paixi"]]["skill_list"];
        // 技能搭配信息
        menke_attr["prepare"] = menke_skills_all_list[menke_attr["paixi"]]["prepare_skill"];

        // 门客是否有武器
        if (menke_skills_all_list[menke_attr["paixi"]]["weapon"])
        {
            menke_attr["weapon"] = menke_skills_all_list[menke_attr["paixi"]]["weapon"];
        }
        

        // 将门客信息存入玩家的menke_system中
        me->set("menke_system/menke_get_list/" + menke_name, menke_attr);
    }
}


// 显示门客招募列表弹窗
int show_menke_get_pop(object me)
{
    string msg;
    string *menke_list;

    // 获取玩家的门客招募列表
    menke_list = keys(me->query("menke_system/menke_get_list"));

    // 如果没有门客招募列表，则返回
    if (!sizeof(menke_list))
    {
        return 0;
    }

    // 显示门客招募列表
    msg = ZJOBLONG + "当前可招募的门客如下:\n" + ZJOBACTS2 + ZJMENUF(4, 4, 8, 30);

    foreach (string menke_name in menke_list)
    {
        msg += sprintf("%s(%d):menke_system get %s show"ZJSEP, menke_name, me->query("menke_system/menke_get_list/" + menke_name + "/force"),menke_name) + ZJSEP;//门客名字和执行力
    }

    // 返回
    msg += "返回:menke_system\n";

    tell_object(me, msg);


    return 1;
}

// 显示门客信息并确认是否招募
int show_menke_get_pop_desc(object me, string menke_name)
{
    string msg;

    msg = ZJOBLONG + "待招募门客信息如下:"ZJBR;
    msg += sprintf("门客名字：%s\n", menke_name);
    msg += sprintf("门客描述：%s\n", me->query("menke_system/menke_get_list/" + menke_name + "/desc"));
    msg += sprintf("门客执行力：%d\n", me->query("menke_system/menke_get_list/" + menke_name + "/force"));
    msg += sprintf("门客等级：%d\n", me->query("menke_system/menke_get_list/" + menke_name + "/level"));
    msg += sprintf("门客性别：%s\n", me->query("menke_system/menke_get_list/" + menke_name + "/gender"));

    // 门客派系和技能
    msg += sprintf("门客派系：%s\n", me->query("menke_system/menke_get_list/" + menke_name + "/paixi"));
    msg += sprintf("门客技能：\n");

    foreach (string skill in me->query("menke_system/menke_get_list/" + menke_name + "/skills"))
    {
        msg += to_chinese(skill) + "\n";
    }

    // 门客是否有武器
    if (me->query("menke_system/menke_get_list/" + menke_name + "/weapon"))
    {
        msg += sprintf("门客武器：%s\n", me->query("menke_system/menke_get_list/" + menke_name + "/weapon")->query("name"));
    }

    // 招募花费
    msg += sprintf("招募花费：%d元宝\n", me->query("menke_system/menke_get_list/" + menke_name + "/force"));

    msg = replace_string(msg,"\n",ZJBR);//换行符替换

    msg += "是否招募该门客？\n";
    msg += ZJOBACTS2 + ZJMENUF(4, 4, 8, 30);
    msg += "招募:menke_system get " + menke_name + " confirm"ZJSEP;
    msg += "返回:menke_system get\n";

    tell_object(me, msg);

    return 1;
}

//确认招募门客
int confirm_menke_get(object me, string menke_name)
{
    // 一次性智能招募一个门客，信息存放到玩家的menke_system/menke_msg中
    mapping menke_attr;

    // 获取门客信息
    menke_attr = me->query("menke_system/menke_get_list/" + menke_name);

    // 招募门客需要花费价值等同于门客执行力的元宝
    if (me->query("yuanbao") < menke_attr["force"])
    {
        tell_object(me, "你的元宝不足，无法招募该门客。\n");
        return 0;
    }

    // 将门客信息存入玩家的menke_system中
    me->set("menke_system/menke_msg", menke_attr);

    // 从玩家的menke_system/menke_get_list中删除该门客
    me->delete("menke_system/menke_get_list/" + menke_name);

    // 扣除元宝
    me->add("yuanbao", -menke_attr["force"]);

    tell_object(me, "你成功招募了" + menke_name + "。\n");
    // 返回
    return 1;
}

//检查我是否有门客在内存中，比如当玩家离线以后，玩家身上的门客参数就会消失
int check_menke(object me)
{
    object *menke_list;
    object menke;
    // 读取内存当中所有的门客，然后查看我的门客是否在其中,menke->query("master_id") == me->query("id")
    menke_list = children("/adm/special_ob/menke/npc");

    // 过滤掉不是我的门客，使用filter_array
    menke_list = filter_array(menke_list, (: $1->query("master_id") == $(me)->query("id") :));

    // 如果没有门客，则返回1
    if (!sizeof(menke_list))
    {
        return 1;
    }

    // 如果有门客，赋值到我身上
    me->set("menke_system/summon", menke_list[0]);//理论只有一个门客


    return 1;
}

// 显示我的门客信息
int show_my_menke(object me)
{
    string msg;
    mapping menke_msg;
    msg = ZJOBLONG + "你的门客信息如下:\n";
    msg += HIC "≡" HIY "一一一一一一一一一一一一一一一一一一一一" HIC "≡"NOR"\n";
    // 获取玩家的门客信息
    menke_msg = me->query("menke_system/menke_msg");

    // 如果没有门客信息，则返回
    if (!mapp(menke_msg))
    {
        return 0;
    }

    // 显示门客信息
    msg += sprintf("门客名字：%s\n", menke_msg["name"]);
    msg += sprintf("门客描述：%s\n", menke_msg["desc"]);
    msg += sprintf("门客执行力：%d ", menke_msg["force"]);
    msg += sprintf("门客等级：%d\n", menke_msg["level"]);
    msg += sprintf("门客性别: %s ", menke_msg["gender"]);

    // 门客派系和技能
    msg += sprintf("门客派系：%s\n", menke_msg["paixi"]);
    msg += HIC "≡" HIY "一一一一一一一一一一一一一一一一一一一一" HIC "≡"NOR"\n";
    msg += sprintf("门客技能：\n");

    foreach (string skill in menke_msg["skills"])
    {
        msg += sprintf("【%s】\n", to_chinese(skill));
    }
    msg += HIC "≡" HIY "一一一一一一一一一一一一一一一一一一一一" HIC "≡"NOR"\n";
    // 门客是否有武器
    if (menke_msg["weapon"])
    {
        msg += sprintf("门客武器：%s\n", menke_msg["weapon"]->query("name"));
    }
    
    msg = replace_string(msg,"\n",ZJBR);//换行符替换
    msg += "\n" + ZJOBACTS2 + ZJMENUF(4, 4, 8, 30);


    msg += "召唤门客:menke_system summon"ZJSEP;
    msg += "收回门客:menke_system clean"ZJSEP;
    msg += "升级门客:menke_system levelup"ZJSEP;
    msg += "执行师门任务:menke_system task"ZJSEP;
    msg += "显示门客收获:menke_system repeat"ZJSEP;
    msg += "遣散门客:menke_system qiansan"ZJSEP;
    if (!me->query("menke_system/menke_msg"))
    {
        msg += "招募其他门客:menke_system get"ZJSEP;
    }
    // 如果是巫师可以前往门客处
    if (wizardp(me))
    {
        msg += "前往门客处:menke_system go\n";
    }



    // 返回
    tell_object(me, msg);

    return 1;

}

// 召唤门客
int summon_menke(object me)
{
    object menke;
    mapping menke_msg; 
    string menke_id;
    // 获取玩家的门客信息
    menke_msg = me->query("menke_system/menke_msg");
    menke = new("/adm/special_ob/menke/npc");
    menke_id = (me->query("id") + "_menke");

    // 设置门客的信息
    menke->set_name(menke_msg["name"], ({ menke_id }));
    // ta是xxx的门客， desc。
    menke->set("long", sprintf("%s是%s的门客，%s。",menke_msg["name"],me->name(), menke_msg["desc"]));
    menke->set("force", menke_msg["force"]);
    menke->set("level", menke_msg["level"]);
    menke->set("master_id", me->query("id"));
    menke->set("gender", menke_msg["gender"]);
    // 设定派系
    menke->set("paixi", menke_msg["paixi"]);
    //设置武器路径
    menke->set("weapon_path", menke_skills_all_list[menke_msg["paixi"]]["weapon"]);


    // 设置门客的技能
    foreach (string skill in menke_msg["skills"])
    {
        menke->set_skill(skill, menke_msg["level"]);
    }

    // 设置门客的技能搭配
    foreach (string prepare in keys(menke_msg["prepare"]))
    {
        menke->map_skill(prepare, menke_msg["prepare"][prepare]);
    }

    // 初始化门客属性，根据等级计算门客的各项属性
    menke->init_attr(menke_msg["level"]);

    if (objectp(menke_msg["weapon"]))
    // 设置门客的武器
    menke->carry_object(menke_skills_all_list[menke_msg["paixi"]]["weapon"])->wield();
    // 将门客放置在玩家身边
    menke->move(environment(me));

    //记录门客地址
    me->set("menke_system/summon", menke);

    menke->force_me("follow " + me->query("id"));
    menke->force_me("say 主公，吾愿为你效劳！");
    return 1;
}


//门客升级函数
// 100 -200 级别每次升级需要的潜能为10000
// 200 -300 级别每次升级需要的潜能为30000
// 300 -400 级别每次升级需要的潜能为60000
// 400 -500 级别每次升级需要的潜能为100000
int menke_level_up(object me)
{
    mapping menke_msg;
    int level;
    int pot;
    int cost_pot;
    int max_level = 500;
    // 获取玩家的门客信息
    menke_msg = me->query("menke_system/menke_msg");
    level = menke_msg["level"];
    pot = me->query("potential");

    // 计算升级需要的潜能
    if (level < 200)
    {
        cost_pot = 10000;
    }
    else if (level < 300)
    {
        cost_pot = 30000;
    }
    else if (level < 400)
    {
        cost_pot = 60000;
    }
    else if (level < 500)
    {
        cost_pot = 100000;
    }
    else
    {
        tell_object(me, "你的门客已经达到最高等级，无法继续升级。\n");
        return 1;
    }

    // 检查潜能是否足够
    if ((me->query("potential") - me->query("learned_points")) < cost_pot)
    {
        tell_object(me, "你的潜能不足，无法升级门客。\n");
        return 0;
    }

    // 扣除潜能
    me->add("potential", -cost_pot);

    // 升级
    me->add("menke_system/menke_msg/level", 1);

    tell_object(me, "你的门客成功升级，当前等级为" + me->query("menke_system/menke_msg/level") + "级。\n");
    return 1;
}

// 显示门客当前收获
int show_menke_repeat(object me)
{
    object menke;
    mapping repeat_name_list = MENKE_M->query_repeat_name_list();

    object *menke_objects_list;//门客身上物品的列表
    string msg;
    // 检查玩家是否已经召唤门客
    if (!objectp(menke = me->query("menke_system/summon")))
    {
        tell_object(me, "你还没有召唤门客。\n");
        return 1;
    }

    menke_objects_list = MENKE_M->reward_object_list(menke);

    // 显示门客当前收获
    msg = ZJOBLONG + "你的门客当前收获如下:\n";
    msg += HIC "≡" HIY "一一一一一一一一一一一一一一一一一一一一" HIC "≡"NOR"\n";
    
    if (menke->query("menke_reward"))
    {
        foreach (string attr in keys(repeat_name_list))
        {
            msg += sprintf("%s：%d\n", repeat_name_list[attr], menke->query("menke_reward/" + attr));
        }
    }
    else
    {
        msg += "暂无修为收益\n";
    }
    
    msg += HIC "≡" HIY "一一一一一一一一一一一一一一一一一一一一" HIC "≡"NOR"\n";

    if (!sizeof(menke_objects_list))
    {
        msg += "暂无物品收益\n";
    }
    else
    {
        msg += "门客身上物品如下：\n";
        foreach (object ob in menke_objects_list)
        {
            int amount;

            if (ob->query_amount())
            {
                amount = ob->query_amount();
            }
            else
            {
                amount = 1;
            }

            msg += sprintf("%s：%d\n", ob->query("name"), amount);
        }
    }



    msg = replace_string(msg,"\n",ZJBR);//换行符替换
    msg += "\n" + ZJOBACTS2 + ZJMENUF(4, 4, 8, 30);
    // 返回
    msg += "返回:menke_system\n";
    tell_object(me, msg);
    return 1;
}

int main(object me, string arg)
{

    string msg;
    string *menke_list;
    // 门客不是一个具体的对象，而是一个抽象的概念，所以在玩家身上赋予参数即可。
    // me->query(menke_system)返回一个映射

    // 每1小时刷新一次门客信息
    if (time() - me->query("menke_system/last_get_time") > 3600)
    {
        parse_menke(me);
        me->set("menke_system/last_get_time", time());//记录最后一次刷新时间
    }

    //查看玩家是否有门客
    if (!arg)
    {
        msg = ZJOBLONG + "在这个武侠背景的门客系统中，玩家可以招募各具特色的门客，与他们一同闯荡江湖。门客们外貌各异，性别不同，他们各有自己的特点和故事。玩家可以通过完成任务、探索秘境等方式招募门客，并将他们培养成得力的助手。\n";

        // 检查玩家是否有门客
        if (mapp(me->query("menke_system/menke_msg")))
        {
            check_menke(me);
            show_my_menke(me);
            return 1;
        }
        else
        {
            msg += ZJOBACTS2 + ZJMENUF(4, 4, 8, 30);
            msg += "招募门客:menke_system get\n";
        }

        tell_object(me, msg);
        return 1;
    }

    if (arg == "get")
    {
        //如果已经有门客，不能招募
        if (mapp(me->query("menke_system/menke_msg")))
        {
            tell_object(me, "你已经招募了门客，无法再次招募。\n");
            return 1;
        }

        // 招募门客界面
        show_menke_get_pop(me);
        return 1;
    }

    if (sscanf(arg, "get %s show", arg))
    {
        // 显示门客信息并确认是否招募
        show_menke_get_pop_desc(me, arg);
        return 1;
    }

    if (sscanf(arg, "get %s confirm", arg))
    {
        // 确认招募门客
        confirm_menke_get(me, arg);
        return 1;
    }

    if (arg == "summon")
    {

        object menke;
        // 我是否已经有门客
        if (objectp(menke = me->query("menke_system/summon")))
        {

            // 查看门客的内存位置
            // tell_object(me, file_name(environment(menke)) + "\n");

           menke->keep_heart_beat(); //防止失活


            // 如果门客正在执行任务，则不能召回
            if (menke->query("doing_quest"))
            {

                //如果门客的任务对象丢失，直接返回
                if (!objectp(menke->query("quest/object")))
                {
                    menke->end_quest();
                    return 1;
                }

                // 门客正在执行任务，收到召回后，门客end_quest,本轮任务结束后自动返回。
                menke->set("end_quest", 1);
                tell_object(me, "你的门客正在执行任务，任务执行完毕后门客会自动返回。\n");
                return 1;
            }

            menke->move(environment(me));
            menke->delete("quest");
            msg = "门客已经返回，任务已经结束\n";
            tell_object(me, msg);
            return 1;

        }

        // 召唤门客
        summon_menke(me);
        return 1;
    }

    if (arg == "levelup")
    {
        // 门客升级
        menke_level_up(me);
        return 1;
    }

    // 安排门客执行任务
    if (arg == "task")
    {
        object menke;
        // 安排门客执行任务
        // 检查玩家是否已经召唤门客
        if (!objectp(menke = me->query("menke_system/summon")))
        {
            tell_object(me, "你还没有召唤门客。\n");
            return 1;
        }  

        // 如果玩家没有门派
        if (!me->query("family"))
        {
            tell_object(me, "你还没有门派，无法执行师门任务。\n");
            return 1;
        }

        // 如果玩家没有师傅
        if (!me->query("family/master_id"))
        {
            tell_object(me, "你还没有师傅，无法执行师门任务。\n");
            return 1;
        }

        menke->keep_heart_beat();
        // 安排门客执行任务
        menke->start_shimen_quest(me);

        return 1;
    }

    // 前往门客处
    if (arg == "go")
    {
        object menke;
        // 检查玩家是否已经召唤门客
        if (!objectp(menke = me->query("menke_system/summon")))
        {
            tell_object(me, "你还没有召唤门客。\n");
            return 1;
        }

        // 如果不是巫师直接return
        if (!wizardp(me))
        {
            return 1;
        }

        // 前往门客处
        me->move(environment(menke));
        return 1;
    }
    
    // 显示门客当前收获
    if (arg == "repeat")
    {
        show_menke_repeat(me);
        return 1;
    }

    // 遣散门客
    if (arg == "qiansan")
    {
        qiansan_menke(me);
        return 1;
    }

    // 收回
    if (arg == "clean")
    {
        clean_menke(me);
        return 1;
    }

    return 1;

    

}