-- sort by frequency
-- part a is simply qsort

import Data.List (groupBy)
import Data.Function (on)

qsort [] = []
qsort (x:xs) = let sf a b = length a < length b
                   lthan = [ z | z <- xs, sf z x ]
                   gthan = [ z | z <- xs, not (sf z x) ]
               in  qsort lthan ++ [x] ++ qsort gthan

p28 :: [[a]] -> [[a]]
p28 = concat . qsort . groupBy ((==) `on` length) . qsort 
