function retangulo(x, y, w, h)
  local originalx, originaly, rx, ry, rw, rh = x, y, x, y, w, h
  return {
    draw = function()
      love.graphics.rectangle("line", rx, ry, rw, rh)
      end,
    keypressed = function(key)
      local mx, my = love.mouse.getPosition()
      if naimagem (mx, my, x, y, rw, rh) then
        if key == 'b' then 
          rx = 200
        elseif key == 'down' then
          ry = ry + 10
        elseif key == 'right' then
          rx = rx + 10
        end
      end
    end
  }
end


function love.load()
  rects = { retangulo(50, 200, 200, 150), retangulo(200, 50, 200, 150) }
end

function naimagem(mx, my, x, y, w, h) 
  return (mx>x) and (mx<x+w) and (my>y) and (my<y+h)
end

function love.keypressed(key)
  for i,rect in pairs(rects) do
    rect.keypressed(key)
  end
end

function love.draw()
  for i,rect in pairs(rects) do
    rect.draw()
  end
end

