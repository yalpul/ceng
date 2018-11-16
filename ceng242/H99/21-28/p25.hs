-- generate random permutations

import System.Random

p23 :: [a] -> Int -> [a]
p23 l n = do
	gen <- getStdGen
	return $ take n [l !! x | x <- randomRs (0, length l - 1) gen]

p25 :: [a] -> [a]
p25 l = p23 l (length l)
