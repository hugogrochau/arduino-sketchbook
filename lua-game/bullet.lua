local bullet = function (initialX, initialY)
  local x, y, width, height, vel = initialX, initialY, 20, 20, 10 
  return {
    update = coroutine.wrap ( function ()
      while true do
        y = y - vel
        coroutine.yield()
      end
    end),
    draw = function ()
      love.graphics.setColor(0, 255, 255)
      love.graphics.rectangle("line", x, y, 5, 20)
      love.graphics.setColor(0, 0, 0)
    end,
    shouldDispose = function ()
      return y < 0
    end
  }
end

return bullet
