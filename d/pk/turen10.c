// Room: /d/pk/turen10.c

#include <ansi.h>

inherit ROOM;

void create()
{
	set("short", HIR "竞技场-癸" NOR);
	set("long", @LONG
这是一个很大的竞技场，参加武林竞技赛的侠客在这里比武。
LONG
	);
	set("exits", ([
		"southwest" : __DIR__"turen12",
		"west"  : __DIR__"turen9",
		"north" : __DIR__"turen6",
	]));
	set("no_learn", 1);

	setup();
}
