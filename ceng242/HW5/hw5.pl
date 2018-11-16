:- module(hw5, [filled_area/2, filling_list/4]).
:- [tiles].

% DO NOT MODIFY THE UPPER CONTENT, WRITE YOUR CODE AFTER THIS LINE

filled_area([], 0). 
filled_area([H|T], Area) :-
  tile(H,X,Y,_),
  Prod is X*Y,
  filled_area(T, Rest),
  Area is Prod+Rest.
  
filling_list(Width,Height,Perc,Result) :-
  filling_list_fit(Width,Height, Result),
  filled_area(Result, Area),
  Area / (Width*Height) >= Perc.

filling_list_fit(Width, Height, [H]) :-
  Width >= 1, Height >= 1,
  tile(H,Width,Y,_),
  Height >= Y.
filling_list_fit(Width,Height, [H|T]) :-
  Width >= 1, Height >= 1,
  tile(H,X,Y,_),
  Height >= Y,
  NewW is Width - X,
  filling_list_fit(NewW, Height, T), 
  not(member(H,T)).
