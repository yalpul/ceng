-- prints the table of values
-- applied to logic operators

and' = (&&)
or' = (||)
nand' a b = not (and' a b)
nor' a b = not (or' a b)

table :: (Bool -> Bool -> Bool) -> IO ()
table f = mapM_ putStrLn [show x ++ " " ++ show y ++ " " ++ show (f x y) | 
                                x <- [True, False], y <- [True, False] ]
