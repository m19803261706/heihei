// sp.c


#include <mudlib.h>

inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
	object *players;

	players = users();

	foreach (object player in players)
	{
		player->set("guanggao/today",0);
		tell_object(player, "今天的广告次数已经清空。\n");
	}

	return 1;
}
