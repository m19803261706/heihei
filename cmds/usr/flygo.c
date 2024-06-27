// miss 追寻物品

#include <ansi.h>

inherit F_CLEAN_UP;

string *anjian = ({
    "主线任务:maintask",
    "签到:daysign",
    "礼包兑换:libao_duihuan",
    "贡献奖励:new_fanli",
    "绑定商城:bind_shop",
    "抽奖:luckdraw",
    "木剑砺锋:flygo caoren",
    "幽冥幻境:flygo moku",
    "回师门:walk 师傅",
    "地图:new_map",
    // "寻路:walk",
    "新手指南:help newbie",
    // "基本系统:help",
    
});
mapping where = ([
    "qiandao":"/d/city/wumiao",
     "lunjian":"/d/lunjian/enter",
]);

int main(object me, string str)
{

    if (environment(me)->query("no_magic", 1))
        return notify_fail("这里无法使用这个功能。\n");

    // if (!str)
    {
        string bynb, msg;

        msg = ZJOBLONG "萌新功能键，请选择\n" ZJOBACTS2 + ZJMENUF(4, 4, 8, 30);
        foreach (bynb in anjian)
        {
            msg += bynb + ZJSEP;
        }

        msg += "寻路:walk\n";
        tell_object(me, msg);
        return 1;
    }

    if (me->is_ghost())
        return notify_fail("你还是等还了阳再说吧。\n");
    if (me->is_busy())
        return notify_fail("你现在正忙。\n");
    if (me->is_fighting())
        return notify_fail("你正在战斗中。\n");

    { // 副本
        object room;



        if (str == "moku")
        {
            string msg;

            msg = ZJOBLONG "幽冥幻境极其危险，建议血量高于5000，技能等级不低于200级进行挑战，幻境内会随机产生四种不同的怪物，每种怪物属性，专属技能都不一致，请务必当心。"ZJBR;
            msg += "幽冥幻境奖励为："ZJBR;
            msg += "【基础奖励】：经验，潜能，银两，元宝。"ZJBR;
            msg += "【通关奖励】:黄金，元宝。"ZJBR;

            msg += "\n" ZJOBACTS2 + ZJMENUF(4, 4, 8, 30);
    
            msg += "进入:flygo moku_sure\n";
            tell_object(me, msg);
            return 1;
        }

        if (str == "caoren")
        {
            string msg;

            msg = ZJOBLONG "木剑砺锋为新手副本，建议技能等级100后进行挑战，危险程度低,怪物分为铁甲木人和机关木人，共十只。"ZJBR;
            msg += "木剑砺锋奖励为："ZJBR;
            msg += "【基础奖励】：经验，潜能。"ZJBR;
            msg += "【通关奖励】:分为"HIR"（无伤通关）"NOR"和"HIG"（限时通关）"NOR"，两个成就可以同时达成（大额奖励），全部未能达成无任何通关奖励。\n";
            msg += "\n" ZJOBACTS2 + ZJMENUF(4, 4, 8, 30);
    
            msg += "进入:flygo caoren_sure\n";
            tell_object(me, msg);
            return 1;
        }

        if (str == "moku_sure")
        {
            if (!objectp(room = new ("/d/fuben_moku/moku")))
            {
                write("副本开启失败。\n");
                return 1;
            }

            if (!room->start_fuben_moku(this_player()))
            {
                destruct(room);
            }

            return 1;
        }

        if (str == "caoren_sure")
		{
			if (!objectp(room = new ("/d/fuben_caoren/shilianchang")))
			{
				write("副本开启失败。\n");
				return 1;
			}
			if (!room->start_fuben_caoren(this_player()))
				destruct(room);
			return 1;
		}
    }

    if (stringp(where[str]))
    {
        me->move(where[str]);
    }
}