-- group combinations af a list with given list of numbers

p27 :: [Int] -> [a] -> [[[a]]]

p27 [] _ = [[]]
p27 (x:xs) l = [ g:gs | (g,rs) <- p27' x l,
                        gs     <- p27 xs rs ] where
        p27' 0 xs = [([],xs)]
        p27' _ [] = []
        p27' n (x:xs) = ts ++ ds where
                ts = [ (x:ys, zs) | (ys,zs) <- p27' (n-1) xs ]
                ds = [ (ys, x:zs) | (ys,zs) <- p27' n xs ]
