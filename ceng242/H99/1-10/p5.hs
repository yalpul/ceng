-- reverse a list

p5 :: [a] -> [a]
p5 [] = []
p5 (x:xs) = p5 xs ++ [x]
