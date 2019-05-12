# sorting

Sorting algorithms with a benchmarking tool to compare them.

To run, use `run.sh` script, don't forget to close all heavy applications. 

Results on my potato powered computer:

```
BS - bubble sort
SS - selection sort
IS - insertion sort
SHS - shell sort
MS - merge sort
            :          BS|          SS|          IS|         SHS|          MS|
           1:    0.000000|    0.000000|    0.000000|    0.000000|    0.000000|
           2:    0.000000|    0.000000|    0.000000|    0.000000|    0.000000|
           4:    0.000000|    0.000000|    0.000000|    0.000000|    0.000001|
           8:    0.000000|    0.000000|    0.000000|    0.000000|    0.000001|
          16:    0.000001|    0.000001|    0.000000|    0.000000|    0.000002|
          32:    0.000003|    0.000002|    0.000001|    0.000002|    0.000004|
          64:    0.000011|    0.000007|    0.000004|    0.000005|    0.000009|
         128:    0.000044|    0.000022|    0.000016|    0.000016|    0.000013|
         256:    0.000133|    0.000080|    0.000059|    0.000055|    0.000025|
         512:    0.000491|    0.000251|    0.000273|    0.000223|    0.000061|
        1024:    0.001646|    0.001067|    0.001052|    0.000750|    0.000098|
        2048:    0.005338|    0.002867|    0.004232|    0.003943|    0.000286|
        4096:    0.025161|    0.010089|    0.013280|    0.011258|    0.000369|
        8192:    0.123100|    0.038104|    0.045078|    0.036316|    0.000764|
       16384:    0.587752|    0.146161|    0.177739|    0.141157|    0.001711|
       32768:    2.505613|    0.596141|    0.769226|    0.619196|    0.003761|
       65536:     timeout|    4.609645|    2.704045|    2.435770|    0.006356|
      131072:     timeout|     timeout|     timeout|     timeout|    0.037542|
      262144:   35.319527|     timeout|     timeout|     timeout|    0.131312|
      524288:     timeout|     timeout|     timeout|     timeout|    0.306569|
     1048576:     timeout|     timeout|     timeout|     timeout|    0.645738|

```

Timeout means that execution took more than 60 seconds. Each case is repeated multiple times to measure real average case performance.
