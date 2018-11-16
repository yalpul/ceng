-- insert an element at a given point 
-- in a list

p21 :: a -> [a] -> Int -> [a]

p21 c l 1 = c:l
p21 c (l:ls) n = l : p21 c ls (n-1)
