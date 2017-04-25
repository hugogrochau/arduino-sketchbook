local bullet = function (initialX, initialY)
  local x = initialX
  local y = initialY 
  local vel = 10 
  return {
    update = coroutine.wrap ( function ()
      while true do
        y = y + vel
        coroutine.yield()
      end
    end),
    draw = function ()
      love.graphics.rectangle("line", x, y, 5, 20)
    end
  }
end

return bullet
