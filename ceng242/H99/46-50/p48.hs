-- same as p46 and p47
-- use values as list elements

import Control.Monad

and' = (&&)
or' = (||)
nand' a b = not (and' a b)
nor' a b = not (or' a b)


tablen n f = mapM_ putStrLn [ show a ++ " => " ++ show (f a) | a <- args n] where
                args n = replicateM n [True,False]
