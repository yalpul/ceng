-- given two numbers 
-- find primes in that range


p39 :: Int -> Int -> [Int]
p39 a b = takeWhile (<=b) . dropWhile (<a) $ primes where
        primes = sieve [2..] where
                sieve (x:xs) = x : sieve [ z | z <- xs, mod z x /= 0 ]
