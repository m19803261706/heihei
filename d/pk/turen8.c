// Room: /d/pk/turen8.c

#include <ansi.h>

inherit ROOM;

void create()
{
	set("short", HIR "竞技场-辛" NOR);
	set("long", @LONG
这是一个很大的竞技场，参加武林竞技赛的侠客在这里比武。
LONG
	);
	set("exits", ([
		"east"  : __DIR__"turen9",
		"south" : __DIR__"turen11",
		"west"  : __DIR__"turen7",
		"north" : __DIR__"turen4",
	]));
	set("no_learn", 1);

	setup();
}
