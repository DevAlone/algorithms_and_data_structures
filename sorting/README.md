# sorting

Sorting algorithms with a benchmarking tool to compare them.

To run, use `run.sh` script

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
          32:    0.000003|    0.000025|    0.000001|    0.000001|
          64:    0.000009|    0.000005|    0.000003|    0.000004|
         128:    0.000031|    0.000014|    0.000011|    0.000011|
         256:    0.000099|    0.000048|    0.000044|    0.000039|
         512:    0.000392|    0.000185|    0.000187|    0.000157|
        1024:    0.001560|    0.000765|    0.000799|    0.000636|
        2048:    0.007001|    0.002520|    0.003352|    0.003053|
        4096:    0.027535|    0.009498|    0.010210|    0.008448|
        8192:    0.126185|    0.037109|    0.041137|    0.031906|
       16384:    0.581996|    0.143486|    0.161480|    0.125993|
       32768:    2.500702|    0.571442|    0.644068|    0.499283|
       65536:     timeout|    5.006619|    2.492432|    2.200105|
      131072:     timeout|     timeout|     timeout|     timeout|
```

Timeout means that execution took more than 10 seconds. Each case is repeated multiple times to measure real average case performance.
