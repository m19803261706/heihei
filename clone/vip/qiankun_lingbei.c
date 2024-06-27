// huxin-dan.c 天王护心丹



inherit COMBINED_ITEM;
void setup()
{
	set_amount(1);
	::setup();
}

void init()
{
	add_action("do_eat", "pai bei");
}

void create()
{
	set_name(HIR"乾坤灵碑"NOR, ({"qiankun lingbei", "lingbei", "bei"}));
	set_weight(50);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long","乾坤灵碑，乃是以古老的炼气术，采五行之精，夺日月之华，凝练而成的一块神秘的石碑。碑身刻有复杂的阵法纹路，流动着淡淡的光晕，似乎蕴含着无穷的天地奥秘。使用者只需将内力注入灵碑，便能激活碑中的阵法，从而吸收天地间的灵气，迅速恢复自身的内力。\n");
		set("base_value", 2000);
		set("base_unit", "尊");
		set("numb", 99);
		set("yuanbao", 100);
		set("no_put", 1);
		set("no_get", 1);
		set("no_drop", 1);
		set("no_give", 1);
		set("no_sell", 1);
		set("only_do_effect", 1);
		set("no_steal", 1);
		set("no_beg", 1);
	  }
   	setup();
}

int do_effect(object me)
{
    int q, j;
	string *enemy;

    object ob;      
    ob=this_object();

	if(me->is_busy())
	{
		return notify_fail("你正忙着呢。\n");
	}
	
	enemy = filter_array(me->query_enemy(), (: userp($1) :));	
	
	if (sizeof(enemy) >0)	
		return notify_fail("正在和玩家对手战斗，不能使用"+ name() +"。\n");

	if(me->query("combat_exp", 1) > 1000000) 
		return notify_fail("乾坤灵碑已经对你失去了作用！\n");



	// if (me->query("neili") >= me->query("max_neili"))
	// {
	// 	return notify_fail("你内力已满，现在不需要使用"+name()+"。\n");
	// }

		// 恢复精神
		me->set("jing",me->query("max_jing"));
		me->set("neili",me->query("max_neili")*2);
		me->set("food", me->max_food_capacity());
		me->set("water", me->max_water_capacity());
		message_vision(HIG"$N手握乾坤灵碑，感受到其上传来的冰冷石质和刻印的古老纹路，你的内心不由得平静下来。你闭上双眼，凝神聚气，将内力缓缓注入碑中。随着你的内力流动，灵碑上的阵法逐渐亮起，散发出淡淡的光芒，仿佛与天地间的灵气产生了共鸣。"NOR"\n" , me);
		me->start_busy(2);
	
		return 1;
	
}


