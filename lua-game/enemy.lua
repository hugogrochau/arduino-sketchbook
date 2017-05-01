local NUM_ROWS = 30

local enemy = function (initialRow, initialColumn, speed, windowWidth)
  local row, column = initialRow, initialColumn
  local timeBetweenUpdates = 0.001 * speed
  local width, height = 20, 20
  local numRows = windowWidth / width
  local direction = 1
  local lastUpdate = 0

  return {
    draw = function()
      local x, y = row * width, column * height
      love.graphics.setColor(255, 0, 0)
      love.graphics.rectangle("line", x, y, 20, 20)
      love.graphics.setColor(0, 0, 0)
    end,
    update = coroutine.wrap( function()
      while true do
        while lastUpdate + timeBetweenUpdates > os.clock() do
          coroutine.yield()
        end 
        if row > 0 and row < numRows then
          row = row + direction 
        else
          direction = -1 * direction
          column = column + 1
          row = row + direction
        end
        lastUpdate = os.clock()
        coroutine.yield()
      end
    end),
    getBox = function()
      return {row * width, column * height, width, height}
    end
  }
end

return enemy