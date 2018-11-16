-- goldbach's conjectue
-- find two primes that sum up to a given even number

p40 :: Int -> (Int,Int)
p40 n = let primes = sieve [2..] where
                sieve (x:xs) = x : sieve [ z | z <- xs, mod z x /= 0 ]
            isPrime n = n == (head . dropWhile (<n) $ primes)
            m = head . filter f . takeWhile (<=n) $ primes where
                f x = isPrime (n-x)
        in (n-m,m)
