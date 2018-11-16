-- remove duplicates from a list

p8 :: Eq a => [a] -> [a]
p8 (x:xs@(y:_))
        | x == y    = p8 xs
        | otherwise = x : p8 xs
p8 xs = xs
