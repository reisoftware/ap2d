require "comma"
require "global"
local modname = ...
local M = {}
_G[modname] = M
package.loaded[modname] = M
---------------------------------------------
local usr = usr
local cmds = cmds 
local link = link
local pendingmsg = pendingmsg
local insert = table.insert
local curtime = os.time
local save_file = comma.save_file
local match = string.match
local pairs = pairs
local send_str = send_str
local trace_out = trace_out
---------------------------------------------
_ENV = M

local ids = {}

function process_channel(from,channel_id,msg)
	local save_flag = false
	for k,v in pairs(ids[channel_id]) do
		local str = "rcvchannel\r\n" .. from .. "\r\n" .. channel_id .. "\r\n" .. msg .. "\r\n" .. curtime() .. "\r\n"
		local rcv_cs = link[k]
		if rcv_cs then
			send_str(rcv_cs,str)
			--trace_out("send_str(" .. str .. ")\n")
		else
			pendingmsg[k] = pendingmsg[k] or {}
			insert(pendingmsg[k],str)
			save_flag = true
			--trace_out("pending(" .. str .. ")\n")
		end
	end
	if save_flag then
			save_file("pendingmsg",pendingmsg,"pendingmsg")
	end
end

function cmds.unsubscribe(content,line)
	local channel_id = match(line,"([^\r\n]*)\r\n");
	local subscriber = link[content]
	if subscriber and channel_id and ids[channel_id] then
		ids[channel_id][subscriber] = nil
	end
end

function cmds.subscribe(content,line)
	local channel_id = match(line,"([^\r\n]*)\r\n");
	local subscriber = link[content]
	if subscriber and channel_id then
		ids[channel_id] = ids[channel_id] or {}	
		--insert(ids[channel_id],subscriber)
		ids[channel_id][subscriber] = true
	end
end

function cmds.sendchannel(content,line)
	local channel_id,msg = match(line,"([^\r\n]*)\r\n(.*)\r\n");
	local from = link[content]
	if channel_id and msg and ids[channel_id] and from then
		process_channel(from,channel_id,msg)
	end
end
