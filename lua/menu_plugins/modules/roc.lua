require("roc")

concommand.Add("lua_run_client", function(ply, cmd, args, txt)
	RunOnClient(txt)
end)

hook.Add("RunOnClient", "idk", function(path, torun)
	return file.Read("lua/overrides/"..path, "MOD") or torun
end)