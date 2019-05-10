# sorting

Sorting algorithms with a benchmarking tool to compare them.

To run, use `run.sh` script, don't forget to close all heavy applications. 

Results on my potato powered computer:

```
BS - bubble sort
SS - selection sort
IS - insertion sort
SHS - shell sort
            :          BS|          SS|          IS|         SHS|
           1:    0.000000|    0.000000|    0.000000|    0.000000|
           2:    0.000000|    0.000000|    0.000000|    0.000000|
           4:    0.000000|    0.000000|    0.000000|    0.000000|
           8:    0.000000|    0.000000|    0.000000|    0.000000|
          16:    0.000001|    0.000000|    0.000000|    0.000000|
          32:    0.000003|    0.000002|    0.000001|    0.000001|
          64:    0.000011|    0.000006|    0.000003|    0.000004|
         128:    0.000038|    0.000019|    0.000013|    0.000048|
         256:    0.000127|    0.000077|    0.000047|    0.000048|
         512:    0.000513|    0.000209|    0.000185|    0.000170|
        1024:    0.002178|    0.001240|    0.001481|    0.000749|
        2048:    0.008264|    0.003275|    0.002832|    0.002758|
        4096:    0.030416|    0.012708|    0.014740|    0.012139|
        8192:    0.126505|    0.039020|    0.041851|    0.035636|
       16384:    0.571176|    0.147189|    0.162166|    0.128356|
       32768:    2.577270|    0.587758|    0.642133|    0.504788|
       65536:   10.144623|    2.283414|    2.559717|    2.006735|
      131072:     timeout|   17.216245|   10.246810|    8.748301|
      262144:     timeout|     timeout|     timeout|     timeout|
```

Timeout means that execution took more than 15 seconds. Each case is repeated multiple times to measure real average case performance.
