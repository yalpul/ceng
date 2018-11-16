-- goldbach's conjectue
-- find two primes that sum up to a given even number
-- do this for all even numbers in a given interval

p40 :: Int -> (Int,Int)
p40 n = let primes = sieve [2..] where
                sieve (x:xs) = x : sieve [ z | z <- xs, mod z x /= 0 ]
            isPrime n = n == (head . dropWhile (<n) $ primes)
            m = head . filter f . takeWhile (<=n) $ primes where
                f x = isPrime (n-x)
        in (n-m,m)

p41 :: Int -> Int -> [(Int,Int)]
p41 a b = map p40 . filter even $ [a..b]

-- extension to that 
-- find all element where 
-- both goldbach conjectures are bigger than 50
-- which happens rarely

p41' :: Int -> Int -> [(Int,Int)]
p41' a b = filter (\(a,b) -> a > 50 && b > 50) (p41 a b)
