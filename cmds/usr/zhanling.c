#define WAR_ORDER_SYSTEM "/adm/special_ob/zhanling"


//战令指令
int do_warorder(string arg)
{
    object me = this_player();
    int level = me->query("war_order/level");
    int exp = me->query("war_order/exp");
    int vip = me->query("war_order/vip");
    int next_exp = WAR_ORDER_SYSTEM->next_exp(me);
    string msg = ZJOBLONG;
    
    msg += "战令奖励分为普通奖励和豪侠奖励。普通奖励适合初入江湖的侠士，而豪侠奖励则更加丰厚，适合那些在江湖中已有一番成就的大侠。选择适合自己的奖励，让您的武侠之旅更加精彩。：\n";
    msg += HIC"【当战令等级】: "NOR + level + "\n";
    msg += HIG"【经验】: "NOR + exp + "/" + next_exp + "\n";
    msg += "【豪侠奖励】: " + (vip ? "是" : "否") + "\n";
    msg = replace_string(msg, "\n",ZJBR);
    msg += "\n" + ZJOBACTS2 + ZJMENUF(2, 2, 9, 30);
    msg += "查看战令奖励:zhanling look"ZJSEP;

    // 处理战令奖励
    if (level > 0) {
        msg += "领取战令奖励:zhanling getreward"ZJSEP;
    }

    msg += "战令升级:zhanling levelup";
    

    write(msg + "\n");
    return 1;
}

// 领取战令奖励
int do_claim(string arg) 
{
    object me = this_player();
    int level;

    if (arg) {
        level = to_int(arg);
    } else {
        tell_object(me, "你要领取哪一级的战令奖励？\n");
        return 1;
    }

    if (level > me->query("war_order/level")) {
        tell_object(me, "你的战令等级不够，无法领取该奖励。\n");
        return 1;
    }

    if (me->query("war_order/free_reward/" + level)) {
        tell_object(me, "你已经领取过该过奖励了。\n");
        return 1;
    }

    WAR_ORDER_SYSTEM->free_reward(me, level);
    return 1;
}

// 领取高级战令奖励
int do_claimvip(string arg)
{
    object me = this_player();
    int level;

    if (arg) {
        level = to_int(arg);
    } else {
        tell_object(me, "你要领取哪一级的战令奖励？\n");
        return 1;
    }

    if (level > me->query("war_order/level")) {
        tell_object(me, "你的战令等级不够，无法领取该奖励。\n");
        return 1;
    }

    if (me->query("war_order/vip_reward/" + level)) {
        tell_object(me, "你已经领取过该过奖励了。\n");
        return 1;
    }

    WAR_ORDER_SYSTEM->vip_reward(me, level);
    return 1;
}

// 升级战令
int do_levelup(string arg)
{
    object me = this_player();

    if (WAR_ORDER_SYSTEM->check_level(me)) {
        tell_object(me, "战令升级成功。\n");
        return 1;
    }

    tell_object(me, "战令升级失败。\n");
    return 1;
}


// 显示可以领取的战令奖励按键
int show_war_order_popup(object me)
{
    int level = me->query("war_order/level");
    string msg = ZJOBLONG + "请选择你要领取的战令奖励：\n";

    msg += ZJOBACTS2 + ZJMENUF(2, 2, 9, 30);

    //循环遍历战令等级
    for (int i = 1; i <= level; i++) {
        if (!me->query("war_order/free_reward/" + i)) {
            msg += "【" + i + "普通奖励】:zhanling claim " + i + ZJSEP;
        }
        if (me->query("war_order/vip") && !me->query("war_order/vip_reward/" + i)) {
            msg += "【" + i + "豪侠奖励】:zhanling claimvip " + i + ZJSEP;
        }
    }

    // 返回
    msg += "返回:zhanling";

    tell_object(me, msg + "\n");
    return 1;
}

int main(object me, string arg)
{
    if (!arg) {
        return do_warorder(arg);
    }

    // 领取免费zhanling claim <等级>，使用sscanf函数将字符串转换为整数
    if (sscanf(arg, "claim %d", arg)) {
        return do_claim(arg);
    }

    // 查看战令奖励
    if (arg == "look") {
        tell_object(me,WAR_ORDER_SYSTEM->show_war_order_msg(me));
        return 1;
    }

    // 开启豪侠奖励 参数on vip
    if (arg == "on vip") {
        
        // 是否已经开启，me->query("war_order/vip")
        if (me->query("war_order/vip")) {
            tell_object(me, "你已经开启了豪侠奖励。\n");
            return 1;
        }

        //需要花费680元宝 
        if (me->query("balance") < 680) {
            tell_object(me, "你的元宝不足，无法开启豪侠奖励。\n");
            return 1;
        }

        // 开启豪侠奖励
        me->add("balance", -680);
        me->set("war_order/vip", 1);
        tell_object(me, "你成功开启了豪侠奖励。\n");
        return 1;
    }

    // 领取高级战令奖励
    if (sscanf(arg, "claimvip %d", arg)) {
        return do_claimvip(arg);
    }

    // 领取战令奖励
    if (arg == "getreward") {
        return show_war_order_popup(me);
    }

    // 升级战令
    if (arg == "levelup") {
        return do_levelup(arg);
    }

    return 1;


}

// 帮助信息
int help(object me)
{
    write(@HELP
战令指令：
    warorder    查看战令信息
    claim <等级>     领取免费战令奖励
    claimvip <等级>  领取高级战令奖励
    levelup   升级战令
HELP);
    return 1;
}