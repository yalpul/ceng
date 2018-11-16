-- encode run-length encoding use p9 (group)

p9 :: Eq a => [a] -> [[a]]

p9 [] = []
p9 (x:xs) = (x : takeWhile (==x) xs) : p9 (dropWhile (== x) xs)

p10 :: Eq a => [a] -> [(Int, a)]
p10 xs = map (\z@(x:_) -> (length z, x)) (p9 xs)
