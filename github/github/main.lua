require "comma"
require "global"
require "channel"
local luaext = require "luaext"

local func = loadfile("passwd")
if(func) then
	func()
end

func = loadfile("pendingmsg")
if(func) then
	func()
end

--hub_start("192.168.5.224",8000,10,60) --ip port max_accept max_accept_seconds
hub_start("localhost",8000,10,60) --ip port max_accept max_accept_seconds

--hub_start("10.105.46.193",8000,10,60)

-- get\r\nfile\r\nstart\r\nlength\r\n
-- put\r\nfile\r\nstart\r\nlength\r\n......\r\n
-- trans\r\nfile\r\nstart\r\nlength\r\n......\r\n
-- putkey\r\nid\r\nvalue\r\n
-- putkey\r\nid\r\nvalue\r\ngid\r\n
-- endof\r\nfile\r\n
-- filesize\r\nfile\r\ngid\r\n
-- login\r\nuser\r\npass\r\n
-- passwd\r\nuser\r\npass\r\nnewpass\r\n
-- reg\r\nuser\r\npass\r\ngid\r\nmail\r\nphone\r\n
-- sendmsg\r\ntouser\r\nmsg\r\n
-- rcvmsg\r\nfromuser\r\nmsg\r\ntime\r\n
-- subscribe\r\nchannelid\r\n
-- unsubscribe\r\nchannelid\r\n
-- sendchannel\r\nchannelid\r\nmsg\r\n
-- rcvchannel\r\nfrom\r\nchannelid\r\nmsg\r\ntime\r\n
-- ap2d\r\nid={};macs={}\r\n

local function auth_ap2d(msg,id,macs)
	local rs ="error!"
	if(id ~= "nil") then --id user
		if(usr[id] and usr[id].reg and not usr[id].macs) then --if reg user first login return md5(msg)
			usr[id].macs = {}
			----set usr[id].macs[mac] = true
      for k,v in pairs(macs) do
				usr[id].macs[v] = true
			end
			rs = msg
			trace_out("reg user first\n")
		elseif(usr[id] and usr[id].reg and usr[id].macs) then --if reg user login 
			local flag = false
			--if mac in usr[id].macs then ok
      for k,v in pairs(macs) do
			  if usr[id].macs[v] then flag = true end  -- need break ? one mac ok then ok?
			end
			if flag then rs = msg; trace_out("reg user and mac ok\n"); end
		else
			trace_out("not reg user :" .. id .. "\n")
		end
	else --id = "nil" macs user
		for k,v in pairs(macs) do
			if not usr[v] then -- if first mac user then set first time return mds(msg)
				usr[v] = {}
				usr[v].name = v
				usr[v].start = os.time()
				rs = msg
				trace_out("first mac user :" .. v .. "\n")
				comma.save_file("passwd",usr,"usr")
			elseif usr[v].start and os.time() - usr[v].start < 60*60*24*30*3 then -- if mac user and <90 days return md5(msg)
				trace_out("in 90 days mac user :" .. v .. "\n")
				rs = msg
			else
				trace_out(" >90 days mac user :" .. v .. "\n")
			end
		end
	end
	return rs
end
function cmds.ap2d(content,line)
	local msg = string.match(line,"(.*)\r\n")
	local info = {}
	local rs 
  if msg then
		local func = load(msg,"ap2d","bt",info)
		func()
		rs = auth_ap2d(msg,info.id,info.macs)
	end
	hub_send(content,luaext.md5(rs))	
end

function cmds.sendmsg(content,line)
	local to,msg = string.match(line,"([^\r\n]*)\r\n(.*)\r\n");
	local curtime = os.time()
	if link[content] then
		local from = link[content]
		local str = "rcvmsg" .. "\r\n" .. from .. "\r\n" .. msg .. "\r\n" .. tostring(curtime) .. "\r\n"
		if link[to] then
			send_str(link[to],str)	
		else
			pendingmsg[to] = pendingmsg[to] or {}
			table.insert(pendingmsg[to],str)
			comma.save_file("pendingmsg",pendingmsg,"pendingmsg")	
		end
	end
end

function cmds.login(content,line)
	local user,pass = string.match(line,"([^\r\n]*)\r\n([^\r\n]*)\r\n")
	local str = "login\r\n"
	local loginflag = false
	if user and pass and usr[user] and usr[user].pass and pass == usr[user].pass and usr[user].gid then
		str = str .. usr[user].gid .. "\r\n"	
		link[user] = content
		link[content] = user
		loginflag = true
	else
		str = str .. "-1\r\n"
	end
	local prefix = string.len(str) .. "\r\n" .. str
	hub_send(content,prefix)
	if loginflag and pendingmsg[user] then
		for i,str in ipairs(pendingmsg[user]) do
			send_str(content,str)
		end
		pendingmsg[user] = nil
	end
end

function cmds.passwd(content,line)
	local user,pass,newpass = string.match(line,"([^\r\n]*)\r\n([^\r\n]*)\r\n([^\r\n]*)\r\n")
	local str = "passwd\r\n"		
	if user and usr[user] and usr[user].pass == pass then
		usr[user].pass = newpass
		str = str .. "ok\r\n"
		comma.save_file("passwd",usr,"usr")
	else
		str = str .. "error\r\n"
	end
	local prefix = string.len(str) .. "\r\n" .. str
	hub_send(content,prefix)
end

function cmds.reg(content,line)
	local user,pass,gid,mail,phone = string.match(line,"([^\r\n]*)\r\n([^\r\n]*)\r\n([^\r\n]*)\r\n([^\r\n]*)\r\n([^\r\n]*)\r\n")
	local str = "reg\r\n"
	if user and usr[user] then
		str = str .. "error\r\n"	
	elseif user then
		usr[user] = {}
		usr[user].name = user
		usr[user].pass = pass
		usr[user].gid = gid
		usr[user].mail = mail
		usr[user].phone = phone
		comma.save_file("passwd",usr,"usr")	
		str = str .. "ok\r\n"
	end
	local prefix = string.len(str) .. "\r\n" .. str
	hub_send(content,prefix)
end

function cmds.endof(content,line)
	local file = string.match(line,"([^\r\n]*)\r\n")
	if file then
		trace_out("endof file : " .. file .. "\n")
	end
end

function cmds.filesize(content,line)
	local file,gid = string.match(line,"(.*)\r\n(.*)\r\n")
	if file and gid then
		local dir = string.sub(file,1,2)
		local f = create_file(dir .. "\\" .. file,"r")
		local fs = getfilesize(f)
		close_file(f)
		if fs then
			local str = "result\r\n" .. gid .. "\r\n" .. fs .. "\r\n"
			send_str(content,str)
		end 
	end	
end

function cmds.get(content,line)

	local file,start_str,len_str = string.match(line,"([^\r\n]*)\r\n(%d+)\r\n(%d+)\r\n")

	if start_str then
		start = tonumber(start_str)
	end

	if len_str then
		len = tonumber(len_str)
	end

	if file and start and len and len >0 then
		local dir = string.sub(file,1,2)
		mkdir(dir)
		local f = create_file(dir .. "\\" .. file,"r")
		--local f = create_file(file,"r")
		local fs = getfilesize(f)
		if start < fs then
			lock_file(f,len,0,start,0)
			local str = read_file(f,len,start,0)
			unlock_file(f,len,0,start,0)
			close_file(f)
			local data = "put\r\n" .. file .. "\r\n" .. start .. "\r\n" .. len .. "\r\n" .. str .. "\r\n"
			local	prefix = string.len(data) .. "\r\n" .. data 
			hub_send(content,prefix)
		else
			close_file(f)
		end
	elseif file and start and len and len == 0 then
		local dir = string.sub(file,1,2)
		mkdir(dir)
		local f = create_file(dir .. "\\" .. file,"r")
		local fs = getfilesize(f)
		if start < fs then
			local c_len = 7*1024
			lock_file(f,c_len,0,start,0)
			local str = read_file(f,c_len,start,0)
			unlock_file(f,c_len,0,startt,0)
			local s = "trans\r\n" .. file .. "\r\n" .. start .. "\r\n" .. string.len(str) .. "\r\n" .. str .. "\r\n"
			local prefix = string.len(s) .. "\r\n" .. s
			hub_send(content,prefix)

		else
			local s = "endof\r\n" .. file .. "\r\n"
			local prefix = string.len(s) .. "\r\n" .. s
			hub_send(content,prefix)
		end

		close_file(f)
	else
		local sock = get_socket(content)
		close_socket(sock)
	end
end

function cmds.trans(content,line)

	local file,start_str,len_str,str = string.match(line,"([^\r\n]*)\r\n(%d+)\r\n(%d+)\r\n(.*)")

	local start,len,s

	if start_str then
		start = tonumber(start_str)
	end

	if len_str and str then
		len = tonumber(len_str)
		s = string.sub(str,1,len)
	end

	if file and start and len and str then
		--trace_out("trans  " .. file .. "::" .. start .. "::" .. len .. "\n")

		local dir = string.sub(file,1,2)
		mkdir(dir)
		local f = create_file(dir .. "\\" .. file,"w")
		--local f = create_file(file,"w")
		lock_file(f,len,0,start,0)
		write_file(f,s,start,0)
		unlock_file(f,len,0,start,0)
		close_file(f)
		local nextstr = "get\r\n" ..file .. "\r\n" .. start + len .. "\r\n" .. 0 .. "\r\n"
		local nextget = string.len(nextstr) .. "\r\n" .. nextstr
		hub_send(content,nextget) 
	else
		local sock = get_socket(content)
		close_socket(sock)
	end
end


function cmds.put(content,line)

	local file,start_str,len_str,str = string.match(line,"([^\r\n]*)\r\n(%d+)\r\n(%d+)\r\n(.*)")

	local start,len,s

	if start_str then
		start = tonumber(start_str)
	end

	if len_str and str then
		len = tonumber(len_str)
		s = string.sub(str,1,len)
	end

	if file and start and len and str then
		trace_out(file .. "::" .. start .. "::" .. len .. "\n")

		local dir = string.sub(file,1,2)
		mkdir(dir)
		local f = create_file(dir .. "\\" .. file,"w")
		--local f = create_file(file,"w")
		lock_file(f,len,0,start,0)
		write_file(f,s,start,0)
		unlock_file(f,len,0,start,0)
		close_file(f)
	else
		local sock = get_socket(content)
		close_socket(sock)
	end
end


function cmds.putkey(content,line)
	local id,value,gid = string.match(line,"(.*)\r\n(.*)\r\n(.*)\r\n")
	if not gid then
		id,value = string.match(line,"(.*)\r\n(.*)\r\n")
	end

	if id  and value then
		local result,status
		local dir = string.sub(id,1,2)
		--trace_out("dir:" ..dir .. "\n")
		mkdir(dir)
		local info = {}
		do
			local f = create_file(dir .. "\\" .. id,"r")
			local func
			if f then
				close_file(f)
				func = loadfile(dir .. "\\" .. id,"bt",info)		
				if(func) then
					--setfenv(func,info)
					--func()
					status,result = pcall(func)
				else
					result = "lua error Load@" .. id
				end
			else
				status = true -- file no exsit
			end
			func = load(value,"putkey","bt",info)
			if status and func then
				--setfenv(func,info)
				status,result = pcall(func)
			elseif status and not func then
				result = "lua:error Load@" .. value
				status = false
			end
		end
		if status then
			comma.save_file(dir .. "\\" .. id,info)	
		end
		if gid then
			result = result or "nil"
			local str = "result\r\n" .. gid .. "\r\n" .. tostring(result) .. "\r\n"
			send_str(content,str)
		end
	else
		local sock = get_socket(content)
		close_socket(sock)
	end
end

function process_cmd_imp(content,line)
	local fun,l = string.match(line,"([^\r\n]-)\r\n(.*)")
	if fun and l  and cmds[fun] then
		cmds[fun](content,l)
	elseif fun then
		--local sock = get_socket(content)
		--close_socket(sock)
		local ip,port = hub_addr(content)
		trace_out("unkown command :" .. fun .. "@" .. ip .. ":" .. port .. "\n")
	end
end

function process_data(content,line)
	--trace_out(string.sub(line,1,30) .. "\n")
	local len,l = string.match(line,"^(%d+)\r\n(.*)")
	--trace_out("len = " .. len .. "l.len=" .. string.len(l) .."\n")

	local num = 0

	if len then num = tonumber(len)
	end

	if len and l and num < string.len(l) then
		local str = string.sub(l,1,num)
		local left = string.sub(l,num +1)
		cs[content] = left
		process_cmd_imp(content,str)
		--trace_out(num .. "::" .. string.len(l) .. "   left\n")
		return false,left
	elseif len and l and num == string.len(l) then
		process_cmd_imp(content,l)
		cs[content] = true
		--trace_out(num .. "=\n")
		return true
	elseif len and l and num > string.len(l) then
		cs[content] = line
		--trace_out(num .. "need more\n")
		return true
	elseif string.len(line) > 10 then
		--trace_out("no len \n")
		local sock = get_socket(content)
		close_socket(sock)
		return true
	end
	return true
end

--local total_num = 0
function process_cmd(content,line)
	--total_num = total_num + string.len(line)
	--trace_out("recv len = " .. total_num .. "\n")
	local str 
	if type(cs[content]) == "boolean" then
		str = line
	elseif type(cs[content]) == "string" then
		str = cs[content] ..line
	end

	local result = false
	local s = str
	local s1
	repeat 
		result,s1 = process_data(content,s)	
		s = s1
	until result == true
	--local count = collectgarbage("count")
	--trace_out("total memory =" .. count .. "\n")
end

function do_accept(content,str)
	--ip,port = hub_addr(content)
	--trace_out("thread : " .. thread_num .. "\n")
	--trace_out("lua accept at " ..ip .. ":"  ..port .."  info:" .. str .. "\n")
	--hub_send(content,"welcome!")
	--trace_out("thread:" .. thread_num .. " in thread\n")
	--redirect(2,0,"accept",content,str)
	cs[content] = true
	process_cmd(content,str)
end

function do_recv(content,str)
	process_cmd(content,str)
end

function socket_quit(content)
	ip,port = hub_addr(content)
	local usrname = link[content]
	local exittime = os.date("%x %X")
	if usrname then
		link[usrname] = nil
		link[content] = nil
		trace_out(usrname .. " exit @" .. ip .. ":" .. port .. "---" .. exittime .. "\n")
	else
		trace_out("unkown client exit @" .. ip .. ":" .. port .. "---" .. exittime .. "\n")
	end
	cs[content] = nil
end

function on_quit()
	for k,v in cs do
		local usrname = link[k]
		if usrname then
			link[usrname] = nil
			link[k] = nil
		end
		remove_content(k)
	end	
end

