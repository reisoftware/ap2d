local modname = ...
local M = {}
_G[modname] = M
package.loaded[modname] = M

usr = {}
cs = {}
cmds = {}
link = {} --{cs=usrname;usrname=cs}
pendingmsg = {}

function send_str(content,str)
	local prefix = string.len(str) .. "\r\n" .. str
	hub_send(content,prefix)
end

function send_file(content,file)
	local f = create_file(file,"r")
	local len = 7*1024
	lock_file(f,len,0,0,0)
	local str = read_file(f,len,0,0)
	unlock_file(f,len,0,0,0)
	local s = "trans\r\n" .. file .. "\r\n0\r\n" .. string.len(str) .. "\r\n" .. str .. "\r\n"
	local prefix = string.len(s) .. "\r\n" .. s
	hub_send(content,prefix)
	close_file(f)
end


