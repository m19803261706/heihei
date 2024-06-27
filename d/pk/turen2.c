// Room: /d/pk/turen2.c

#include <ansi.h>

inherit ROOM;

void create()
{
	set("short", HIR "竞技场-乙" NOR);
	set("long", @LONG
这是一个很大的竞技场，参加武林竞技赛的侠客在这里比武。
LONG
	);
	set("exits", ([
		"southeast"  : __DIR__"turen6",
		"south" : __DIR__"turen5",
		"west"  : __DIR__"turen1",
	]));
	set("no_learn", 1);

	setup();
}
