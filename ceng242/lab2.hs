module Lab2(LetterTree(Root, Letter), getWords, deleteWords) where

import Data.List

data LetterTree = Root [LetterTree] | Letter Char Bool [LetterTree] deriving (Eq) 

getWords :: LetterTree -> [String]
getLetterCounts :: LetterTree -> [(Char, Int)]
addWords :: LetterTree -> [String] -> LetterTree
deleteWords :: LetterTree -> [String] -> LetterTree
    
duplicate :: String -> Int -> String
duplicate string n = concat $ replicate n string

createSpaces :: Int -> String
createSpaces = duplicate " "

tree0 = Root []
tree1 = Root [Letter 'H' False [Letter 'e' False [Letter 'c' False [Letter 'k' True []],Letter 'l' False [Letter 'l' False [Letter 'o' True []],Letter 'p' True [Letter 'e' False [Letter 'd' True [],Letter 'r' True []],Letter 'i' False [Letter 'n' False [Letter 'g' True []]]]]]]]
tree2 = Root [Letter 'C' False [Letter 'a' False [Letter 'n' True [Letter 't' False [Letter 'e' False [Letter 'e' False [Letter 'n' True []]]]],Letter 'p' False [Letter 't' False [Letter 'a' False [Letter 'i' False [Letter 'n' True []]]]],Letter 'r' True [Letter 'r' False [Letter 'i' False [Letter 'e' False [Letter 'd' True [],Letter 's' True []]],Letter 'y' True []]]]],Letter 'H' False [Letter 'e' False [Letter 'c' False [Letter 'k' True []],Letter 'l' False [Letter 'l' False [Letter 'o' True []],Letter 'p' True [Letter 'e' False [Letter 'd' True [],Letter 'r' True []],Letter 'i' False [Letter 'n' False [Letter 'g' True []]]]]]]]
tree3 = Root [Letter 'F' False [Letter 'a' False [Letter 'l' False [Letter 's' False [Letter 'e' True []]]],Letter 'i' False [Letter 'a' False [Letter 's' False [Letter 'c' False [Letter 'o' True []]]],Letter 'l' False [Letter 'e' True []]]],Letter 'R' False [Letter 'e' False [Letter 'a' False [Letter 'p' False [Letter 'e' False [Letter 'r' True []]]],Letter 'p' False [Letter 'o' True [Letter 's' False [Letter 'i' False [Letter 't' False [Letter 'o' False [Letter 'r' False [Letter 'y' True []]]]]]]]]],Letter 'T' False [Letter 'a' False [Letter 'i' False [Letter 'l' True [Letter 'o' False [Letter 'r' True []]]],Letter 'p' True []],Letter 'e' False [Letter 's' False [Letter 'l' False [Letter 'a' True []]]]]]

-- DO NOT MODIFY ABOVE --

addLetter [] l = [(l,1)]
addLetter (c@(t,n):ts) l
        | t == l    = (t,n+1) : ts
        | otherwise = c       : addLetter ts l

instance Show LetterTree where
    show (Root tree) = concatMap (show' 0) tree where
        show' depth (Letter c True t) = concatMap (show' (depth+1)) t ++ createSpaces depth ++ [c] ++ "\n"
        show' depth (Letter c False t) =  (concatMap (show' (depth+1)) t) ++ createSpaces depth ++ [c] ++ "\n"

getWords (Root tree) = getwfroml tree where
    getwfroml [] = []
    getwfroml [Letter c True []] = [[c]]
    getwfroml  (Letter c True t:xs) = [c] :(map (c:) ( getwfroml t)) ++  getwfroml  xs
    getwfroml  (Letter c False t:xs) = map (c:) (getwfroml t) ++ getwfroml  xs

getLetterCounts (Root tree) = getLetters [] tree where
        getLetters l []     = l
        getLetters l (x:xs) = getLetters (getLetter l x) xs
        getLetter l (Letter c _ t) = getLetters (addLetter l c) t

addWords t [] = t
addWords (Root tree) (x:xs) = addWords (Root (addWord tree x)) xs where
        addWord [] (y:rest)
                | rest == [] = [Letter y True  []]
                | otherwise  = [Letter y False (addWord [] rest)]
        addWord lst@(letter@(Letter x bool tree) : xs) word@(y:rest)
                | x == y && rest == [] && bool == True  = lst
                | x == y && rest == [] && bool == False = Letter x True tree                        : xs
                | x >  y && rest == []                  = Letter y True []                 : letter : xs
                | x == y                                = Letter x bool (addWord tree rest)         : xs
                | x > y                                 = Letter y False (addWord [] rest) : letter : xs
                | otherwise                             = letter : addWord xs word

deleteWords t [] = t
deleteWords (Root tree) (x:xs) = deleteWords (Root (deleteWord tree x)) xs where
        deleteWord (Letter x True tree : xs)  (y:rest)
                | x == y && rest == [] && tree == [] = xs
                | x == y && rest == []               = Letter x False tree : xs
                | x == y                             = Letter x True (deleteWord tree rest) : xs

        deleteWord (Letter x False tree : xs) (y:rest)
                | x == y = let deleted = deleteWord tree rest
                           in case deleted of [] -> xs
                                              _  -> Letter x False deleted : xs

        deleteWord (letter:xs) word = letter : deleteWord xs word
        deleteWord []                        _        = []
