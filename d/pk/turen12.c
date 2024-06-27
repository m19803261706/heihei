// Room: /d/pk/turen12.c

#include <ansi.h>

inherit ROOM;

void create()
{
	set("short", HIR "竞技场-宙" NOR);
	set("long", @LONG
这是一个很大的竞技场，参加武林竞技赛的侠客在这里比武。
LONG
	);
	set("exits", ([
		"northeast"  : __DIR__"turen10",
		"west"  : __DIR__"turen11",
		"north" : __DIR__"turen9",
	]));
	set("no_learn", 1);

	setup();
}
