-- drop every k'yh element

p16 :: [a] -> Int -> [a]
p16 xs n = p16' xs n where
        p16' [] _ = []
        p16' (x:xs) 1 = p16 xs n
        p16' (x:xs) n = x : p16' xs (n-1)
