// Room: /city/wumiao2.c

#include <room.h>

inherit ROOM;
string look_shu();

void create()
{
	set("short", "武庙二楼");
	set("long", @LONG
这里是岳王庙的二楼，这里供的是岳飞的长子岳云和义子张宪，两尊塑像
金盔银铠，英气勃勃。
LONG );

	set("no_fight", 1);
	set("no_steal", 1);
	set("no_beg", 1);
	set("no_sleep_room", 1);

	set("exits", ([
		"south" : __DIR__"wumiao",
	]));
	setup();
}
