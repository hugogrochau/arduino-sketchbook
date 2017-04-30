local player = function (initialX, initialY)
  local x = initialX
  local y = initialY
  return {
    draw = function ()
      love.graphics.rectangle("line", x, y, 20, 20)
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