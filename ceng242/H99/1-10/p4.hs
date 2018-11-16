-- find the number of elements of a list

p4 :: [a] -> Int

p4 [] = 0
p4 (x:xs) = 1 + p4 xs
