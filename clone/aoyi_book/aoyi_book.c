

#define AOYI_D "/adm/daemons/aoyid"
inherit COMBINED_ITEM;

string query_autoload() { return query_amount() + ""; }

void autoload(string param)
{
	int amt;

	if (sscanf(param, "%d", amt) == 1)
		set_amount(amt);
}

void setup()
{
	set_amount(1);
	::setup();
}

void create()
{
	set_name(HIR "意境卷轴" NOR, ({"aoyi_book"}));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "这是一本意境卷轴，记录无数意境的奥秘。\n");
		set("base_unit", "卷");
		set("no_shop", 1);
		set("base_value", 50000);
		set("base_weight", 1);
		set("only_do_effect", 1);
	}
	setup();
}

int do_effect(object me)
{
	AOYI_D->lingwu(me, me->query("family/family_name"));
	add_amount(-1);

	return 1;
}
