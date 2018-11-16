-- replicate a list in given number

p15 :: [a] -> Int -> [a]
p15 xs n = concat $ map (\x -> replicate n x) xs 
