-- Upgraded p10 with a new type definition
data RL a = Single a | Multiple Int a deriving (Show)

p9 :: Eq a => [a] -> [[a]]

p9 [] = []
p9 (x:xs) = (x : takeWhile (==x) xs) : p9 (dropWhile (== x) xs)

p10 :: Eq a => [a] -> [(Int, a)]

p10 xs = map (\z@(x:_) -> (length z, x)) (p9 xs)

p11 :: Eq a => [a] -> [RL a]
p11 xs = map conv (p10 xs) where
        conv (n,x)
                | n == 1    = Single x
                | otherwise = Multiple n x
