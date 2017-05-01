utils = require('utils') 

local player = function (initialX, initialY, windowWidth, windowHeight)
  local x, y = initialX, initialY
  local width, height = 20, 20
  local windowWidth, windowHeight = windowWidth, windowHeight
  return {
    draw = function ()
      love.graphics.setColor(0, 255, 0)
      love.graphics.rectangle("line", x, y, width, height)
      love.graphics.setColor(0, 0, 0)
    end,
    move = function(dx)
      if utils.checkCollision({x + dx, y, width, height}, {0, 0, windowWidth, windowHeight}) then
        x = x + dx
      end
    end,
    getBox = function()
      return {x, y, width, height}
    end
  }
end

return player