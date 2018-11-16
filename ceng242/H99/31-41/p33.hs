--determine if two numbers are coprime

p33 :: Int -> Int -> Bool
p33 a b = gcd' a b == 1 where
        gcd' a b
                | rm > 0    = gcd' b rm
                | otherwise = b where
                         rm = mod a b
