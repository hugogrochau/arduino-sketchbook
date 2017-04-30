newPlayer = require("player")
newBullet = require("bullet")
player = {} 
bullets = {}

function love.keypressed(key)
  if key == 'space' then
    local x, y = player.getCoords()
    local bullet = newBullet(x, y)
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
  if love.keyboard.isDown('right') then
    player.move(10, 0)
  end
  if love.keyboard.isDown('left') then
    player.move(-10, 0)
  end
  for i, bullet in pairs(bullets) do
    if bullet.shouldDispose() then
      table.remove(bullets, i)
    else
      bullet.update()
    end
  end
end
  