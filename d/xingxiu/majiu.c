//Room: majiu.c 马厩
#include <room.h>
inherit TRANS_ROOM;
void create()
{
	set("short", "马厩");
	set("long", @LONG
这是北疆小镇的马厩，常年供应新鲜草料。这里地处会疆，边民古朴
而好客，把所有远方来宾均作兄弟看待。马夫们会把马牵到马厩好生照看，
将它们喂饱饮足，再梳理得清清爽爽，一直伺候到客人上路。马厩旧木柱
上钉着一块破木牌。
    马厩中堆放著几堆草料，正中有一口泔槽。
LONG);
	set("outdoors", "xingxiu");
	set("no_fight", 1);
	set("objects", ([
		"/clone/horse/zaohongma": 1,
		"/clone/horse/huangbiaoma": 1,
		"/clone/horse/ziliuma": 1,
		"/clone/npc/mafu": 1,

	]));

	set("exits",([ /* sizeof() == 1 */
		"south"      : __DIR__"beijiang",
	]));
	setup();
	//replace_program(TRANS_ROOM);
}
