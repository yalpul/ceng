-- decode a run-length output from p11
data RL a = Single a | Multiple Int a deriving (Show)

p12 :: [RL a] -> [a]
p12 xs = concat $ map conv xs where
        conv (Single x) = [x]
        conv (Multiple n x) = take n (repeat x)
