#!/usr/bin/python
import spidev
import time
spi = spidev.SpiDev()
spi.open(0,0)
spi.max_speed_hz=1000000


def readMCP3008(channel):
  adc = spi.xfer2([1,(8+channel)<<4,0])
  wert = ((adc[1]&3) << 8) + adc[2]
  return wert

if __name__ == "__main__":
  while 1 > 0:
    v1=(readMCP3008(0)/1023.0)*3.3
    distshort = 16.2537 * v1**4 - 129.893 * v1**3 + 382.268 * v1**2 - 512.611 * v1 + 301.439
    v2=(readMCP3008(1)/1023.0)*3.3
    distlong = 1.0 / (((v2*1000) - 1125.0)/137500)
    if distlong> 160:
        distshort = 9999
    else:
       if distshort < 110:
        distlong = 0

    print("Distanz short Sensor : %.2f cm  |  Distanz long Sensor : %.2f cm"   % (distshort,  distlong))
    time.sleep(0.1)







