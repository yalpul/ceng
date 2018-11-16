data Tree a= Empty | Node a (Tree a) (Tree a)
createTree = Node "A"
        (Node "B"
                (Node "C" Empty Empty)
                (Node "D" Empty Empty)
        )
        (Node "E"
                (Node "F" Empty Empty)
                (Node "G" Empty (Node "H"
                        (Node "I" Empty Empty)
                        Empty
                ))
 )

leaves Empty = []
leaves (Node a Empty Empty) = [a]
leaves (Node a left right) = leaves left ++ leaves right
