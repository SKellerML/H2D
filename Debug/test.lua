-- THE RIGHT ONE

-- number of entities
function definition()
	return 2
end

-- Police Car
function load0 ()
	-- Pos1,Pos2,Pos3,Pos4,Name,init function,update function, render function, renderLight function
	return 0, 0, 128, 192,"Police Car","init0","update0","render0",""
end

function init0 ()
	--print("init1 it!")
end

function update0 (key,mouse)
	local c = distanceSquared(0,0,100,100)
	print("Update it!",c)
	-- check if specific button was pressed (do not send the button input here, just send if the button to the specific button is pressed and then send it here)
	if key == true then print("Used it!") end
end

function render0 ()
	--print("Render it!")
end



-- C4
function load1 ()
	-- Pos1,Pos2,Pos3,Pos4,Name,init function,update function, render function, renderLight function
	return 148, 25, 24, 16,"C4","init1","update1","render1",""
end

function init1 ()
	--print("init1 it!")
end

function update1 (key,mouse)
	--print("Update it!")
	-- check if specific button was pressed (do not send the button input here, just send if the button to the specific button is pressed and then send it here)
	if key == true then print("Used it!") end
end

function render2 ()
	--print("Render it!")
end

-- Door
function load2 ()
	-- Pos1,Pos2,Pos3,Pos4,Name,init function,update function, render function, renderLight function
	return 148, 25, 24, 16,"C4","init2","update2","render2",""
end

function init2 ()
	--print("init1 it!")
end

function update2 (key,mouse)
	--print("Update it!")
	-- check if specific button was pressed (do not send the button input here, just send if the button to the specific button is pressed and then send it here)
	if key == true then print("Used it!") end
end

function render1 ()
	-



--function add (x,y)
--	return x + y
--end


--avg, sum = avg(10, 25.2225, 30.9243, 45.74822, 50)

--print("The average is ", avg)
--print("The sum is ", sum)
--
--print("The Nudel is ", dosth() )

