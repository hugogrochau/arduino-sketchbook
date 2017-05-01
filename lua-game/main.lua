newPlayer = require('player')
newBullet = require('bullet')
newEnemy = require('enemy')
utils = require('utils')
level1 = require('levels/1')
player = {} 
bullets = {}
enemies = {}

function love.load()
  local width, height = love.graphics.getDimensions()
  player = newPlayer(width / 2, height - 50, width, height)
  loadLevel(level1)
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

  detectBulletCollisions()

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

function loadLevel(level)
  local width, _ = love.graphics.getDimensions()
  for i, column in pairs(level.enemies) do
    for j, hasEnemy in pairs(column) do
      if hasEnemy == 1 then
        local enemy = newEnemy(j, i, level.speed, width)
        table.insert(enemies, enemy)
      end
    end
  end
end

function detectBulletCollisions()
  for i, bullet in pairs(bullets) do
    local bulletBox = bullet.getBox()
    for j, enemy in pairs(enemies) do
      if utils.checkCollision(bulletBox, enemy.getBox()) then
        table.remove(bullets, i)
        table.remove(enemies, j)
      end
    end
  end
end

  