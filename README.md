\#Laboratorio: Midiendo el Efecto de la Caché



\## Objetivo de la Actividad

\[cite\_start]El estudiante implementa y ejecuta un benchmark en C que mide la latencia de acceso a memoria para arrays de distintos tamaños, observando empíricamente el efecto de la jerarquía de caché (L1, L2, L3, RAM) sobre el rendimiento de los programas, e interpreta los resultados en función de los conceptos de localidad espacial, líneas de caché y cache miss. \[cite: 13]



\## Entorno de Compilación

\* \[cite\_start]\*\*Sistema operativo:\*\* Linux (Ubuntu sobre WSL2 en Windows 10) \[cite: 15]

\* \[cite\_start]\*\*Compilador:\*\* GCC instalado con el paquete build-essential \[cite: 15]

\* \[cite\_start]\*\*Herramientas adicionales:\*\* time, linux-tools-generic, acceso a /sys/devices/system/cpu/cpu0/cache/ \[cite: 15]

\* \[cite\_start]\*\*Directorio de trabajo:\*\* \~/u10post1/ \[cite: 15]



\## Pasos de Ejecución - Checkpoint 1

1\. Se configuró el entorno nativo de Linux utilizando WSL2.

2\. \[cite\_start]Se creó el directorio de trabajo ejecutando `mkdir -p \~/u10post1 \&\& cd \~/u10post1`. \[cite: 19]

3\. \[cite\_start]Se creó y ejecutó el script `cache\_detect.sh` para consultar la topología de caché del sistema directamente en los archivos del hardware virtualizado. \[cite: 18]



\## Análisis de Resultados - Detección de Caché

La ejecución del script arrojó los siguientes tamaños para la jerarquía de memoria del procesador actual:

\* \*\*L1:\*\* 32K

\* \*\*L2:\*\* 512K

\* \*\*L3:\*\* 4096K (4MB)



\[cite\_start]Estos valores se registran ya que determinan los puntos de inflexión de latencia que se observarán durante la ejecución de los benchmarks en los siguientes pasos. \[cite: 26]


## Pasos de Ejecución - Checkpoint 2 (Acceso Secuencial)
1. Se creó el archivo `cache_bench.c` implementando la función `bench_seq` para realizar lecturas secuenciales sobre arrays de distintos tamaños (desde 4KB hasta 64MB).
2. Se compiló el código utilizando la bandera `-O0` (`gcc -O0 -o cache_bench cache_bench.c`). Esto es fundamental para deshabilitar las optimizaciones del compilador, evitando que elimine los accesos de prueba a la memoria.
3. Se ejecutó el benchmark midiendo el tiempo en nanosegundos por byte (`ns/byte`).

## Análisis de Resultados - Benchmark Secuencial
Al ejecutar el benchmark secuencial, los datos arrojan tiempos de latencia muy bajos mientras el tamaño del array se mantiene por debajo o igual a los 32KB. A partir de este punto, se evidencia el efecto de la jerarquía de caché sobre el rendimiento del programa:

* **Primer salto (L1 a L2):** Cuando el array supera los 32KB (tamaño de la L1), los datos ya no caben en este primer nivel, generando "cache misses" en L1. Las peticiones deben ir a la L2, lo que causa un primer incremento en la latencia.
* **Segundo salto (L2 a L3):** Al sobrepasar los 512KB (tamaño de la L2), observamos otro escalón en el tiempo de acceso, ya que se debe buscar en la caché L3, la cual es más lenta.
* **Tercer salto (L3 a RAM):** Finalmente, al superar los 4096KB (4MB, tamaño de la L3), ocurre un aumento significativo en la latencia. En este punto, los datos deben ser traídos directamente desde la memoria principal (RAM), demostrando que la penalización por un "cache miss" total es sustancial.

A pesar de los saltos, el acceso secuencial se beneficia del "prefetching" del procesador (aprovechando la localidad espacial), lo que mantiene la latencia relativamente controlada en comparación con lo que sería un acceso aleatorio.
