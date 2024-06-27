// wugou.c 天下无狗


#include <combat.h>

inherit F_SSERVER;

string query_name() { return "天下"ZJBR"无狗"; }
string *pfm_type() { return ({ "staff", }); }

int query_cd() { return 4; }

int perform(object me, object target)
{
	object weapon;
 
 
 int  i, skill;

	if (userp(me) && ! me->query("can_perform/dagou-bang/wugou"))
		return notify_fail("你不会使用「天下无狗」。\n");

	if (! target)
	{
		me->clean_up_enemy();
		target = me->select_opponent();
	}
	if (! target || ! me->is_fighting(target))
		return notify_fail("「天下无狗」只能对战斗中的对手使用。\n");

	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "staff")
		return notify_fail("你使用的武器不对。\n");
		
	if (skill=(int)me->query_skill("dagou-bang", 1) < 150)
		return notify_fail("你的神丐棒法不够娴熟，不会使用「天下无狗」。\n");
				
	if ((int)me->query_skill("force") < 220)
		return notify_fail("你的内功修为不够高，难以运用「天下无狗」。\n");
			
	if ((int)me->query("neili") < 500)
		return notify_fail("你现在真气不够，不能使用「天下无狗」。\n");

	if (me->query_skill_mapped("staff") != "dagou-bang")
		return notify_fail("你没有激发神丐棒法，不能使用「天下无狗」。\n");

    if (! living(target))
	    return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

    message_vision(HIW"\n"HIW"$N"HIW"手中的" +weapon->name()+HIW "抖动，将一路“神丐棒法”使得变化万方，但见棒去如神龙夭矫，棒来又似灵蛇盘舞！\n",me);
    message_vision(HIG"这正是神丐棒法的绝招「天下无狗」,据说精妙绝伦，一招使出，劲力所至，四面八方全是棒影。\n",me);
    message_vision(HIG"此时纵是有几十条恶犬也可一并打死了，所谓“天下无狗”便是此意。"NOR"\n",me);

    me->add_temp("apply/damage", skill/4);
    me->add_temp("apply/attack", me->query("int") * 5);

	for (i = 0; i < 6; i++)
	{
		if (! me->is_fighting(target))
			break;
		COMBAT_D->do_attack(me, target, weapon, 0);
	}

    me->add_temp("apply/damage", -skill/4);	
    me->add_temp("apply/attack", -me->query("int") * 5);
	me->add("neili", -500);
	me->start_busy(1+random(5));

	return 1;
}
