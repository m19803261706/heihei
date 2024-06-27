// longbow.c



inherit __DIR__"bow";

void create()
{
	set_name("银月弓", ({ "yinyue bow", "bow", "yinyue", "gong" }));
	set_weight(5000);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "张");
		set("icon","05053");
		set("long", "一张长弓，打造得颇为精致，具有相当好的准确度。\n");
		set("value", 80000);
		set("power", 180000);   // 攻击威力
		set("accuracy", 150);   // 准确度150%
	}
	setup();
}
