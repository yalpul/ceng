-- take a slice from the list between indices n k

p18 :: [a] -> Int -> Int -> [a]
p18 xs n k = take (k-n+1) . drop (n-1) $ xs
