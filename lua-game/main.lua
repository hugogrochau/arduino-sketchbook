newPlayer = require("player")
newBullet = require("bullet")
player = {} 
bullets = {}

function love.keypressed(key)
  if key == 'right' then
    player.move(10, 0)
  end
  if key == 'left' then
    player.move(-10, 0)
  end
  if key == 'space' then
    local bullet = newBullet(player.x, player.y)
    table.insert(bullets, bullet)
  end
end

function love.load()
  width, height = love.graphics.getDimensions()
  player = newPlayer(width / 2, height - 50)
end

function love.draw()
  player.draw()
  for i = 1,#bullets do
    bullets[i].draw()
  end
end

function love.update(dt)
  for i = 1,#bullets do
    bullets[i].update()
  end
end
  