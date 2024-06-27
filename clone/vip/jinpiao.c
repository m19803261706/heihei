inherit COMBINED_ITEM;
void setup()
{
	set_amount(1);
	::setup();
}

void create()
{
	set_name(HIY"金票"NOR, ({"jin piao"}));
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("base_value", 10000000);
		set("yuanbao", 200);
                set("no_sell",1);
		set("base_unit", "张");
		set("long","这是一张金票，"ZJURL("cmds:duihuan jin piao")ZJSIZE(20)"兑换"NOR"之后可以获得一千两黄金!\n");
		set("spectxt", "兑换后获得一千两黄金。\n");
	}
	setup();
}

void init()
{
    if (environment()==this_player())
    	add_action("do_use","duihuan");
}

int do_use(string arg)
{
	object me=this_player();

	if (arg!="jin piao")
      		return notify_fail("你要兑换什么?\n");  

        me->add("balance",10000000);
	write(YEL"兑换成功！你的钱庄账户新增了一千两黄金。"NOR"\n");
	add_amount(-1);
	return 1;
}

