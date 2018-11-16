-- tree to string with dot notation representing empty

data Tree a = Empty | Branch a (Tree a) (Tree a)

p69 :: Tree Char -> String
p69 Empty = "."
p69 (Branch a l r) = a : p69 l ++ p69 r
