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
  rect1 = retangulo(50, 200, 200, 150)
end

function naimagem(mx, my, x, y, w, h) 
  return (mx>x) and (mx<x+w) and (my>y) and (my<y+h)
end

function love.keypressed(key)
  rect1.keypressed(key)
end

function love.draw()
  rect1.draw()
end
