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



\---

\[cite\_start]\*(Nota: Adjuntar aquí la captura de pantalla de la terminal mostrando la salida de cache\_detect.sh)\*

