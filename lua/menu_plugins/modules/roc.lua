require("roc")

function RunOnClient(toRun)
	if not IsInGame() then return error("Not in game") end
	RunOnClientRaw(toRun)
end

concommand.Add("lua_run_client", function(ply, cmd, args, txt)
	RunOnClient(txt)
end)