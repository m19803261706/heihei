inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }

// 广告奖励取得
int main(object me,string arg)
{

    string userName;
    int adType;
    object player;

    if (! is_root(me) && ! SECURITY_D->valid_grant(me, "(admin)"))
    return notify_fail("只有管理员才能使用授权命令。\n");

    if (!arg)
    {
        return notify_fail("指令格式：guanggao_obtain <玩家ID> <广告类型>\n");
    }

    if (sscanf(arg,"%s %d",userName,adType) != 2)
    {
        return notify_fail("指令格式：guanggao_obtain <玩家ID> <广告类型>\n");
    }

    player = find_player(userName);

    // 如果没有这个玩家，取消
    if (!player)
    {
        return notify_fail("没有这个玩家。\n");
    }

    // 如果广告类型不对，取消（1-10）
    if (adType < 1 || adType > 10)
    {
        return notify_fail("广告类型不对。\n");
    }



    // 处理次数登记，每日最多10次，每次奖励10点元宝。然后记录统计数据（每日，每周，总计）
    // 是否是新的一天，如果是，清空每日统计数据
    if (player->query("guanggao/last_time") / 86400 != time() / 86400)
    {
        player->set("guanggao/today",0);
    }

    // 是否是新的一周，如果是，清空每周统计数据
    if (same_week(player->query("guanggao/last_time"),time()) == 0)
    {
        player->set("guanggao/week",0);
    }

    // 已经超过了每日最大次数，取消
    if (player->query("guanggao/today") >= 10)
    {
        return notify_fail("已经超过了每日最大次数。\n");
    }

    // 登记次数
    player->add("guanggao/today",1);
    player->add("guanggao/week",1);
    player->add("guanggao/total",1);
    player->add("zjvip/all_pay",1);

    // 登记时间
    player->set("guanggao/last_time",time());

    if (adType)
    {
        // 1-3奖励10点元宝，4-7奖励5000潜能，8-10奖励5000体会
        if (adType >= 1 && adType <= 3)
        {
            player->add("yuanbao",10);
            player->add("combat_exp",5000);
            tell_object(player,pop_final("你获得了10点元宝,5000经验奖励。"));
        }

        if (adType >= 4 && adType <= 7)
        {
            player->add("yuanbao",10);
            player->add("potential",5000);
            tell_object(player,pop_final("你获得了10元宝，5000点潜能奖励。"));
        }


        if (adType >= 8 && adType <= 10)
        {
            player->add("yuanbao",10);
            player->add("experience",5000);
            tell_object(player,pop_final("你获得了10元宝,5000点实战体会奖励。"));
        }
    }

    // 第5次广告奖励额外奖励20点元宝，第10次广告奖励额外奖励30点元宝
    if (player->query("guanggao/today") == 5)
    {
        player->add("yuanbao",50);
        tell_object(player,pop_final("你获得了50点元宝奖励。"));
    }

    if (player->query("guanggao/today") == 10)
    {
        object onecard;
        player->add("yuanbao",50);

        onecard = new_bind("/clone/baiyi/onecard");
        onecard->set_amount(5);
        onecard->move(player);
        tell_object(player,pop_final("你获得了50点元宝奖励和5张单抽卡。"));

        player->delete("guanggao/today");
    }

    return 1;

}