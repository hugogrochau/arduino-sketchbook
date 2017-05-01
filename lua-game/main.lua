newPlayer = require('player')
newBullet = require('bullet')
newEnemy = require('enemy')
utils = require('utils')
level1 = require('levels/1')
player = {} 
bullets = {}
enemies = {}
speed = 1
local width, height = love.graphics.getDimensions()

function love.load()
  loadLevel(level1)
end

function love.keypressed(key)
  if key == 'space' then
    local x, y, _, _ = unpack(player.getBox())
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

  detectCollisions()

  if #enemies == 0 then
    speed = speed + 5 
    loadLevel(level1)
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

function loadLevel(level)
  player = newPlayer(width / 2, height - 50, width, height)
  bullets = {}
  enemies = {}
  for i, column in pairs(level) do
    for j, hasEnemy in pairs(column) do
      if hasEnemy == 1 then
        local enemy = newEnemy(j, i, speed, width)
        table.insert(enemies, enemy)
      end
    end
  end
end

function detectCollisions()
  for i, enemy in pairs(enemies) do
    local enemyBox = enemy.getBox()
    for j, bullet in pairs(bullets) do
      if utils.checkCollision(enemyBox, bullet.getBox()) then
        table.remove(enemies, i)
        table.remove(bullets, j)
      end
    end
    -- enemy touched player
    if enemyBox[2] > height - 70 then
      speed = 1
      loadLevel(level1)
    end
  end
end

  