// Room: /xiakedao/lin3.c

inherit ROOM;

void create()
{
	set("short", "树林");
	set("long", @LONG
这是一片茂密的树林，似乎有人在这里设计了一个迷阵，一走进
来，你就迷失了方向。
LONG );
	set("outdoors", "xiakedao");
	set("exits", ([
		"east" : __FILE__,
		"west" : __DIR__"lin2",
		"south" : __FILE__,
		"north" : __FILE__,
		"southeast" : __DIR__"lin4",
		"northeast" : __FILE__,
	]));
	setup();
}
