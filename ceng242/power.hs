-- f n m computes n to the power m using optimization powers of 2
f :: Integral a => a -> a -> a
f n 0 = 1
f n m
 | odd m = n * (f (n*n) (div m 2))
 | even m = f (n*n) (div m 2)
