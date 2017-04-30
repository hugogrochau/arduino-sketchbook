local bullet = function (initialX, initialY)
  local x, y, width, height, vel = initialX, initialY, 5, 20, 10 
  return {
    update = coroutine.wrap ( function ()
      while true do
        y = y - vel
        coroutine.yield()
      end
    end),
    draw = function ()
      love.graphics.setColor(0, 255, 255)
      love.graphics.rectangle("line", x, y, width, height)
      love.graphics.setColor(0, 0, 0)
    end,
    shouldDispose = function ()
      return y < 0
    end,
    getBox = function()
      return {x, y, width, height}
    end
  }
end

return bullet
