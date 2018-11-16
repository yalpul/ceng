-- find the k'th element of a list

p3 :: [a] -> Int -> a
p3 (x:xs) 1 = x
p3 (x:xs) n = p3 xs (n-1)
