// Room: /d/pk/turen9.c

#include <ansi.h>

inherit ROOM;

void create()
{
	set("short", HIR "竞技场-壬" NOR);
	set("long", @LONG
这是一个很大的竞技场，参加武林竞技赛的侠客在这里比武。
LONG
	);
	set("exits", ([
		"east"  : __DIR__"turen10",
		"south" : __DIR__"turen12",
		"west"  : __DIR__"turen8",
		"north" : __DIR__"turen5",
	]));
	set("no_learn", 1);

	setup();
}
