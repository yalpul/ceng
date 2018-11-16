-- lotto take n elements from 1 to m

import System.Random

p23 :: [a] -> Int -> [a]
p23 l n = do
	gen <- getStdGen
	return $ take n [l !! x | x <- randomRs (0, length l - 1) gen]

p24 :: Int -> Int -> [Int]
p24 n m = p23 [1..m] n
