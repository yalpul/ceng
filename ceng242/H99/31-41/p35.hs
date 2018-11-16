-- find the prime factors of a number

p35 n = f n primes where
        f n p@(x:xs)
                | n < 2 = []
                | mod n x == 0 = x : f (div n x) p
                | otherwise = f n xs
        primes = sieve [2..] where
                sieve (x:xs) = x : sieve [ z | z <- xs, mod z x /= 0 ]
