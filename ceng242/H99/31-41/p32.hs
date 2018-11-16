-- find the gcd of two numbers


p32 :: Int -> Int -> Int
p32 n m
        | rm > 0    = p32 m rm
        | otherwise = m where
                rm = rem n m
