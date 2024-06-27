inherit COMBINED_ITEM;


void setup()
{
	set_amount(1);
	::setup();
}

void create()
{
	set_name(HIR"毁容丹"NOR, ({"huirong dan"}));
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("base_unit", "粒");
		set("base_weight", 10);
		set("base_value", 100000);
		set("yuanbao", 100);
		set("no_sell",1);
		set("long","这是一粒毁容丹，"ZJURL("cmds:use huirong dan")ZJSIZE(20)"服下"NOR"之后将有损容颜!\n");

	}
	setup();
}

void init()
{
    if (environment()==this_player())
    	add_action("on_used","use");
}

int on_used(string arg)
{
	object me=this_player();
	
	if (arg!="huirong dan")
      		return notify_fail("你要用什么?\n");  

        if (me->query("per")<11) return notify_fail("你的容貌已经极丑了。\n");

	me->add("per",-1-random(3));

        if (me->query("per")<11) me->set("per",10);

	write(YEL"你服下了一粒"HIR"毁容丹"YEL"，你的容颜大损！"NOR"\n你现在的容貌是："+me->query("per")+"。"NOR"\n");
	me->save();
	add_amount(-1);
	return 1;
}
