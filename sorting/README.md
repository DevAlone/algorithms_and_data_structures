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
          32:    0.000004|    0.000003|    0.000001|    0.000001|    0.000004|
          64:    0.000011|    0.000007|    0.000004|    0.000005|    0.000011|
         128:    0.000044|    0.000026|    0.000013|    0.000014|    0.000012|
         256:    0.000124|    0.000067|    0.000057|    0.000052|    0.000027|
         512:    0.000409|    0.000204|    0.000229|    0.000196|    0.000056|
        1024:    0.001747|    0.000850|    0.001082|    0.000977|    0.000141|
        2048:    0.005573|    0.002732|    0.003027|    0.003020|    0.000255|
        4096:    0.025926|    0.009250|    0.012666|    0.010338|    0.000389|
        8192:    0.125335|    0.037177|    0.044816|    0.036636|    0.000783|
       16384:    0.581393|    0.145114|    0.176691|    0.144689|    0.001571|
       32768:    2.509187|    0.578492|    0.715591|    0.578283|    0.003352|
       65536:     timeout|    5.374233|    2.802746|    2.701479|    0.007088|
      131072:     timeout|     timeout|     timeout|     timeout|    0.034977|
      262144:   21.567453|     timeout|     timeout|     timeout|    0.142111|
      524288:     timeout|     timeout|     timeout|     timeout|    0.468190|
     1048576:     timeout|     timeout|     timeout|     timeout|    0.933570|
     2097152:     timeout|     timeout|     timeout|     timeout|    2.528528|
```

Timeout means that execution took more than 10 seconds. Each case is repeated multiple times to measure real average case performance.
