-- construct complete binary tree
-- and iscompletetree function

data Tree a = Empty | Branch a (Tree a) (Tree a) deriving Show

p63 :: Int -> Tree Char
p63 n = p63' 1 where
        p63' x
                | x > n = Empty
                | otherwise = Branch 'x' (p63' (2*x)) (p63' (2*x+1))


-- iscompletetree

p63' :: Tree a -> Bool
p63' t = equal t (p63 (nodes t)) where
        nodes Empty = 0
        nodes (Branch _ l r) = 1 + nodes l + nodes r
        equal Empty Empty = True
        equal (Branch _ l1 r1) (Branch _ l2 r2) = (equal l1 l2) && (equal r1 r2)
        equal _ _ = False
