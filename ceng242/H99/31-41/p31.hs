-- determine if a number is prime

primes :: [Int]
primes = sieve [2..] where
        sieve (x:xs) = x : sieve [ z | z <- xs, mod z x /= 0 ]

p31 :: Int -> Bool
p31 n = n == (head . dropWhile (<n) $ primes)
