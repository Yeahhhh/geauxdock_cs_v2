#!/usr/bin/env python3

from time import sleep


last_idle = 0
last_total = 0

while 1:
    with open('/proc/stat') as f:
        fields = [float(column) for column in f.readline().strip().split()[1:]]
    total = sum(fields)
    idle = fields[3]
    idle_delta = idle - last_idle
    total_delta = total - last_total
    last_idle = idle
    last_total = total
    utilisation = (1.0 - idle_delta / total_delta) * 100.0

    print('%5.2f' % utilisation)
    sleep(0.2)
