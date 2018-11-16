-- duplicate elements of a list

p14 :: [a] -> [a]

p14 [] = []
p14 (x:xs) = x : x : p14 xs
