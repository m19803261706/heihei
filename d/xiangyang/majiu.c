// Room: /d/xiangyang/majiu.c 马厩
#include <room.h>
inherit TRANS_ROOM;
void create()
{
	set("short","马厩");
	set("long",@LONG
这里是襄阳城内唯一一家车马行。你可花钱租辆马车到各
个地方去，能节约不少体力。近来因为郭夫人----黄帮主正在组
织人力四处搜集防城材料，马夫积极响应，免费提供推车来运
送各种防城材料。
    西边马厩雨檐下的烂木柱上钉着一块破木牌。
LONG);
	set("outdoors", "xiangyang");
	set("no_fight", 1);
	set("objects", ([
		"/clone/horse/zaohongma": 1,
		"/clone/horse/huangbiaoma": 1,
		"/clone/horse/ziliuma": 1,
		"/clone/npc/mafu": 1,

	]));

	set("exits",([ /* sizeof() == 1 */
		"south"  : __DIR__"northroad2",
	]));

	setup();
	//replace_program(TRANS_ROOM);
}
