// Room: /d/pk/entry.c

#include <ansi.h>

inherit ROOM;

void create()
{
	set("short", "竞技场入口");
	set("long", @LONG
这里就是武林竞技赛的入口了。西面望出去是宽阔敞亮的大街，让人无限向往。
LONG
	);
	set("exits", ([
		"north" : __DIR__"ready",
		"west"  : "/d/changan/yongtai-dadao2",
	]));

	set("objects", ([
		__DIR__"npc/wu" : 1,
	]));

	set("action_list", ([
		"随便玩玩" : "join",
		"报名参赛" : "sign",
	]));

	set("no_fight", 1);
	setup();
}

int valid_leave(object me, string dir)
{
	if (dir == "north")
		return notify_fail("千机客喝道：给我站住！那儿不能随意进入。\n");

	return ::valid_leave(me, dir);
}
