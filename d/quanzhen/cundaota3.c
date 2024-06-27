// cundaota3.c 存道塔三层


inherit ROOM;

void create()
{
	set("short", "存道塔三层");
	set("long", @LONG
这里是存道塔的三层，塔梯绕着塔内向塔顶延伸。这里空空如
也，经书也许全被全真弟子们借去阅读了。
LONG
	);
	set("exits", ([
		"northup" : __DIR__"cundaota4",
		"southdown" : __DIR__"cundaota2",
	]));
	set("no_clean_up", 0);
	setup();
}
