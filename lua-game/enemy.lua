utils = require('utils') 
local NUM_ROWS = 30

local enemy = function (initialRow, initialColumn, windowWidth)
  local row, column = initialRow, initialColumn
  local width, height = 20, 20
  local numRows = windowWidth / width
  local direction = 1

  return {
    draw = function()
      local x, y = row * width, column * height
      love.graphics.setColor(255, 0, 0)
      love.graphics.rectangle("line", x, y, 20, 20)
      love.graphics.setColor(0, 0, 0)
    end,
    update = function()
      if row > 0 and row < numRows then
        row = row + direction 
      else
        direction = -1 * direction
        column = column + 1
        row = row + direction
      end
    end,
  }
end

return enemy