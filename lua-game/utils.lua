local utils = {}

utils.checkCollision = function(box1, box2)
  local x1, y1, w1, h1 = unpack(box1)
  local x2, y2, w2, h2 = unpack(box2)
  return x1 < x2+w2 and
         x2 < x1+w1 and
         y1 < y2+h2 and
         y2 < y1+h1
end

return utils