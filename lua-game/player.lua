local player = function (initialX, initialY)
  local x, y, width, height = initialX, initialY, 20, 20
  return {
    draw = function ()
      love.graphics.setColor(0, 255, 0)
      love.graphics.rectangle("line", x, y, width, height)
      love.graphics.setColor(0, 0, 0)
    end,
    move = function(dx)
      x = x + dx
    end,
    getCoords = function()
      return x, y
    end
  }
end

return player