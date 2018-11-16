-- find totient-phi
-- the number of coprimes to a number less than it

p33 :: Int -> Int -> Bool
p33 a b = gcd' a b == 1 where
        gcd' a b
                | rm > 0    = gcd' b rm
                | otherwise = b where
                         rm = mod a b

p34 :: Int -> Int
p34 n = length [ z | z <- [1..n], p33 z n ]
