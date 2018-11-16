-- give coordinates to each node
-- in a binary tree

data Tree a = Empty | Branch a (Tree a) (Tree a) deriving Show

type Pos = (Int, Int)

p65 :: Tree a -> Tree (a,Pos)
p65 t = let depth Empty = 0
            depth (Branch _ l r) = max (depth l) (depth r) + 1

            ldepth Empty = 0
            ldepth (Branch _ l _) = ldepth l + 1

            d = depth t
            ld = ldepth t
            x = 2^(d-1) - 2^(d-ld) + 1
            sep = 2^(d-2)

        in  p65' x 1 sep t where
                p65' _ _ _ Empty = Empty
                p65' xc yc sp (Branch n l r) = 
                        Branch (n,(xc,yc))
                               (p65' (xc-sp) (yc+1) (div sp 2) l)
                               (p65' (xc+sp) (yc+1) (div sp 2) r)
