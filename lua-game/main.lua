newPlayer = require('player')
newBullet = require('bullet')
newEnemy = require('enemy')
player = {} 
bullets = {}
enemies = {}

function love.load()
  local width, height = love.graphics.getDimensions()
  player = newPlayer(width / 2, height - 50, width, height)
  local enemy = newEnemy(0, 0)
  table.insert(enemies, enemy) 
end

function love.keypressed(key)
  if key == 'space' then
    local x, y = player.getCoords()
    local bullet = newBullet(x, y)
    table.insert(bullets, bullet)
  end
end

function love.update(dt)
  -- keyboard events
  if love.keyboard.isDown('right') then
    player.move(10, 0)
  end
  if love.keyboard.isDown('left') then
    player.move(-10, 0)
  end

  local entityTypes = {bullets, enemies}
  for _, types in pairs(entityTypes) do
    for _, entity in pairs(types) do
      entity.update()
    end
  end
end

function love.draw()
  local entityTypes = {{player}, bullets, enemies}
  for _, types in pairs(entityTypes) do
    for _, entity in pairs(types) do
      entity.draw()
    end
  end
end
  