mapping repeat_name_list = ([
    "combat_exp":"经验",
    "potential":"潜能",
    "experience":"实战体会",
    "shen":"正气",
    "score":"江湖阅历",
    "weiwang":"威望",
    "gongxian":"门派贡献",
    "shimen/today":"师门任务轮数"
]);


void create()
{
	seteuid(ROOT_UID);
}

// 不会被销毁
int clean_up() { return 1; }

mapping query_repeat_name_list()
{
    return repeat_name_list;
}

object *reward_object_list(object menke)
{
    object *obj_list;

    obj_list = all_inventory(menke);

    // 过滤出可以奖励的物品,如果该物品有"equipped"参数代表可以被过滤掉
    obj_list = filter_array(obj_list, (: !($1->query("equipped")) :));

    // 过滤掉师门信件，也就是letter
    obj_list = filter_array(obj_list, (: !($1->query("id") == "letter") :));

    return obj_list;
}


// 门客把收益给主人
int give_reward_master(object menke,object player)
{

    object *obj_list,obj;
    string msg = "门客开始结算奖励:\n";
    obj_list = reward_object_list(menke);

    if (menke->query("menke_reward"))
    {
        foreach (string attr in keys(repeat_name_list))
        {
            msg += sprintf("%s：%d\n", repeat_name_list[attr], menke->query("menke_reward/" + attr));
            player->add(attr, menke->query("menke_reward/" + attr));
        }
    }

    menke->delete("menke_reward");

    if (sizeof(obj_list) > 0)
    {
        msg += "物品：\n";
        foreach (obj in obj_list)
        {
            int amount;

            if (obj->query_amount())
            {
                amount = obj->query_amount();
            }
            else
            {
                amount = 1;
            }

            msg += sprintf("%s：%d\n", obj->name(), amount);
            obj->move(player);
        }
    }

    msg += "奖励结算完毕。\n";

    tell_object (player, msg);
    return 1;
}