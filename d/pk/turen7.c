// Room: /d/pk/turen7.c

#include <ansi.h>

inherit ROOM;

void create()
{
	set("short", HIR "竞技场-庚" NOR);
	set("long", @LONG
这是一个很大的竞技场，参加武林竞技赛的侠客在这里比武。
LONG
	);
	set("exits", ([
		"east"  : __DIR__"turen8",
		"southeast" : __DIR__"turen11",
		"north" : __DIR__"turen3",
	]));
	set("no_learn", 1);

	setup();
}
