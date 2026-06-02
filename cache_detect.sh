#!/bin/bash
# Ver tamaños de caché del CPU [cite: 20]

for i in 0 1 2 3; do [cite: 21]
  echo -n "Cache level $i: " [cite: 22]
  cat /sys/devices/system/cpu/cpu0/cache/index${i}/size 2>/dev/null || echo "N/A" [cite: 23]
done [cite: 24]