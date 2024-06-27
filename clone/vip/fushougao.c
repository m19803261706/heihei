// tianxiang.c 天香玉露



inherit COMBINED_ITEM;

void setup()
{
	set_amount(1);
	::setup();
}

void create()
{
	set_name(HIW "福寿膏" NOR, ({"fushou gao", "fushou", "gao"}));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("base_unit", "块");
		set("long", HIY "一块让人增加精神的膏药，来自于全真教。\n");
		set("base_value", 200000);
		set("yuanbao", 20);
		set("only_do_effect", 1);
	}
	setup();
}

int do_effect(object me)
{
	string force;

	message_vision(HIC"$N掏出一块"
		       NOR HIW"福寿膏，"NOR HIC"吃了下去，精神力大增，脸上露出满足的表情。"NOR"\n",
		       me);
	if (me->improve_jingli(50 + random(40)))
		me->set("jingli", me->query("max_jingli"));
		add_amount(-1);
	return 1;
}

