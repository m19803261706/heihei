//room: changl9.c
inherit ROOM;

void create()
{
  set("short","画廊");
  set("long",@LONG
这是一条非常精美的长廊，柱子和栏杆是用华贵的紫檀木制成，上面
雕饰着美丽的图画，画工精巧，美不胜收。地板不知是用什么材料做的，
走在上面毫无声息，你只感到脚下软软的，非常舒服。
LONG );
  set("exits",([
      "east" : __DIR__"changl12",
      "west" : __DIR__"changl11",
      "south" : __DIR__"changl5",
  ]));
  set("no_clean_up", 0);
  setup();
  //replace_program(ROOM);
}
