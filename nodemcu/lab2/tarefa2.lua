-- modules --

local newLed = function (port)
  -- declarations --
  local speed = 500
  local timer = tmr.create()

  local switchLed = function()
    if gpio.read(port) == gpio.HIGH then
      gpio.write(port, gpio.LOW)
    else
      gpio.write(port, gpio.HIGH)
    end
  end

  local changeSpeed = function(isSpeedingUp)
    -- restart the timer in case it is stopped
    timer:start()
    if isSpeedingUp then
      speed = speed - 50
      if speed < 50 then
        speed = 50
      end
    else
      speed = speed + 50
    end
    print("Current speed: "..speed)
    timer:interval(speed)
  end

  local stop = function()
    timer:stop()
  end


  -- init --
  gpio.mode(port, gpio.OUTPUT)
  gpio.write(port, gpio.LOW)
  timer:register(speed, tmr.ALARM_AUTO, switchLed)
  timer:start()


  -- exports --
  return {
    changeSpeed = changeSpeed,
    stop = stop
  }
end

local newButton = function (port, callback)
  -- declarations --
  local lastPressTime = 0
  local debounceTime = 1000000

  local callbackWrapper = function()
    local currentTime = tmr.now()
    if currentTime > lastPressTime + debounceTime then
      callback(lastPressTime)
      lastPressTime = currentTime
    end
  end

  -- init --
  gpio.mode(port, gpio.INT, gpio.PULLUP)
  gpio.trig(port, "down", callbackWrapper)

end

-- end modules --

-- globals --
local led1 = newLed(3)
local led2 = newLed(6)
local button1LastPressTime = 0
local button2LastPressTime = 0
local buttonInterval = 1000000


newButton(1,
  function(lastPressTime)
    local currentTime = tmr.now()
    print("Pressing button 1")
    if currentTime < button2LastPressTime + buttonInterval then
      print("stopping leds")
      led1.stop()
      led2.stop()
    else
      print("increasing speed")
      led1.changeSpeed(true)
      led2.changeSpeed(true)
    end

    button1LastPressTime = currentTime
  end)

newButton(2,
  function(lastPressTime)
    local currentTime = tmr.now()
    print("Pressing button 2")
    if currentTime < button1LastPressTime + buttonInterval then
      print("stopping leds")
      led1.stop()
      led2.stop()
    else
      print("decreasing speed")
      led1.changeSpeed(false)
      led2.changeSpeed(false)
    end
    button2LastPressTime = currentTime
  end)
