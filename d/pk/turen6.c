// Room: /d/pk/turen6.c

#include <ansi.h>

inherit ROOM;

void create()
{
	set("short", HIR "竞技场-己" NOR);
	set("long", @LONG
这是一个很大的竞技场，参加武林竞技赛的侠客在这里比武。
LONG
	);
	set("exits", ([
		"south" : __DIR__"turen10",
		"west"  : __DIR__"turen5",
		"northwest" : __DIR__"turen2",
	]));
	set("no_learn", 1);

	setup();
}
