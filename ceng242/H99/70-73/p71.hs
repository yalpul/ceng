-- find the internal path length of a n-ary tree

data Tree a = Node a [Tree a]

p71 :: Tree a -> Int
p71 = p71' 0 where
        p71' d (Node _ xs) = d + sum (map (p71' (d+1)) xs)
