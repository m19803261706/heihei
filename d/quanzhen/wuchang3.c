// wuchang2.c 武场
// By Lgg,1998.10



inherit ROOM;

void create()
{
	set("short", "武场");
	set("long", @LONG
这里是全真教的演武场，地下的青砖本来铺的整整齐齐，却
不知道被谁踩出了几十个大大小小的凹坑。看的出来，这里成年
累月的有弟子修炼掌法步法，天长日久，地下就踩出了凹坑。武
场中央立着几个练功用的木人。
LONG
	);
	set("outdoors", "quanzhen");
	set("exits", ([
		"north" : __DIR__"wuchang2",
	]));

	set("objects", ([
		"/clone/npc/mu-ren" : 3,
	]));

	set("for_family", "全真教");

	setup();
}
