-- collect internal nodes
-- of a tree to a list

data Tree a = Empty | Branch a (Tree a) (Tree a)

p62 :: Tree a -> [a]
p62 n = p62' n [] where
        p62' Empty xs = xs
        p62' (Branch _ Empty Empty) xs = xs
        p62' (Branch a l r) xs = p62' l xs ++ p62' r (a:xs)
