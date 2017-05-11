local timeSinceStart = 0
local width, height = love.graphics.getDimensions( )

function newblip (vel)
  local x, y = 0, 0
  return {
    wakeTime = 0, 
    update = coroutine.wrap ( function (self, timeSinceStart)
      while true do
        x = x+vel
        if x > width then
        -- volta à esquerda da janela
          x = 0
        end
        coroutine.yield()
      end
    end),
    affected = function (pos)
      if pos>x-20 and pos<x+20 then
      -- "pegou" o blip
        return true
      else
        return false
      end
    end,
    draw = function ()
      love.graphics.rectangle("line", x, y, 10, 10)
    end,
    wait = function (self, time)
      self.wakeTime = timeSinceStart + time
    end
  }
end

function newplayer ()
  local x, y = 0, 200
  return {
  try = function ()
    return x
  end,
  update = function (dt)
    x = x + 0.5
    if x > width then
      x = 0
    end
  end,
  draw = function ()
    love.graphics.rectangle("line", x, y, 30, 10)
  end
  }
end

function love.keypressed(key)
  if key == 'a' then
    pos = player.try()
    for i in ipairs(listabls) do
      local hit = listabls[i].affected(pos)
      if hit then
        listabls[i]:wait(3) -- faz o blip esperar por 3 segundos
        return 
      end
    end
  end
end

function love.load()
  player =  newplayer()
  listabls = {}
  for i = 1, 5 do
    listabls[i] = newblip(i)
  end
end

function love.draw()
  player.draw()
  for i = 1,#listabls do
    listabls[i].draw()
  end
end

function love.update(dt)
  timeSinceStart = timeSinceStart + dt
  player.update(dt)
  for i = 1,#listabls do
    if listabls[i].wakeTime <= timeSinceStart then
      listabls[i]:update(timeSinceStart)
    end
  end
end
  