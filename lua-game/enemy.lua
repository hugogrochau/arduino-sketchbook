local enemy = function (initialX, initialY)
  local x, y, width, height = initialX, initialY, 20, 20
  return {
    draw = function ()
      love.graphics.setColor(255, 0, 0)
      love.graphics.rectangle("line", x, y, 20, 20)
      love.graphics.setColor(0, 0, 0)
    end,
    update = function()
      x = x + width 
    end,
    getCoords = function()
      return x, y
    end
  }
end

return enemy