-- group same element of a list

p9 :: Eq a => [a] -> [[a]]

p9 [] = []
p9 (x:xs) = (x : takeWhile (==x) xs) : p9 (dropWhile (== x) xs)
