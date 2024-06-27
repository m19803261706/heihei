// Room: /d/pk/ready.c

#include <ansi.h>

inherit ROOM;

void create()
{
	set("short", "竞技场休息室");
	set("long", @LONG
这里是侠客门比武以后休息的地方，地上还有一些粘满了血迹的布条，偶然也看得到断
了的长剑、钢刀什么的。
LONG
	);
	set("exits", ([
		"south" : __DIR__"entry",
	]));

	set("no_fight", 1);
	setup();
}

int valid_leave(object me, string dir)
{
	if (dir == "south")
		message_vision("$N溜出了休息室。\n", me);
	return 1;
}
