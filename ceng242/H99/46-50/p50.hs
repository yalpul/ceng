-- huffman coding


import Control.Arrow
import Data.Ord
import Data.List

p50    :: [(Char,Int)] -> [(Char,String)]
p50    = 
        let shrink [(_,ys)] = sortBy (comparing fst) ys
            shrink (x:xs:ys) = shrink $ insertBy (comparing fst) (add x xs) ys

            add (p1, xs1) (p2,xs2) = 
                (p1+p2, map (second ('0':)) xs1 ++ map (second ('1':)) xs2)
        in shrink . map (\(c,f) -> (f, [(c,"")])) . sortBy (comparing snd)
