// promote.c
// updated by doing

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	object ob;
	string old_status, new_status;
 
	int sp_flag;

	if (! VERSION_D->is_release_server() && me->is_admin())
		sp_flag = 1;
	else
		sp_flag = 0;

	if (! sp_flag && ! SECURITY_D->valid_grant(me, "(arch)"))
		return 0;

	if (! arg || sscanf(arg, "%s %s", arg, new_status) != 2)
		return notify_fail("指令格式：promote <使用者> <等级>\n");

	if (wiz_level(new_status) < 0)
		return notify_fail("没有这种等级。\n");

	ob = UPDATE_D->global_find_player(arg);
	if (! objectp(ob))
		return notify_fail("你只能改变使用者的权限。\n");

	if (! sp_flag &&
	    (wiz_level(me) < wiz_level(new_status) ||
	     wiz_level(me) < wiz_level(ob)))
	{
		UPDATE_D->global_destruct_player(ob, 1);
		write("你没有这种权力。\n");
		return 1;
	}

	old_status = wizhood(ob);

	seteuid(getuid());
	if (! (SECURITY_D->set_status(ob, new_status)))
	{
		UPDATE_D->global_destruct_player(ob, 1);
		write("修改失败。\n");
		return 1;
	}

	message_vision("$N将$n的权限从 " + old_status + " 改为 " +
		       new_status + " 。\n", me, ob);
	seteuid(getuid());
	ob->setup();

	UPDATE_D->global_destruct_player(ob, 1);
	return 1;
}

int help(object me)
{
	write(@HELP
指令格式 : promote <某人> (权限等级)

用来提升权限等级, (player) (immortal) (apprentice) (wizard)
(arch) (admin)
一个 admin 能提升权限至任何等级, 而 arch 只能提升至 arch。
HELP );

	return 1;
}