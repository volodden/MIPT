let rec pascal c r = 
    if ((c < 0) || (r < 0) || (c > r))
    then 0
    else if ((c = 0) || (c = r))
         then 1
         else (pascal (c-1) (r-1)) + (pascal (c) (r-1))

let printIt n = 
  "[" +
  ([for x in 0..n do for y in 0..x do yield pascal y x] 
    |> List.map (fun x -> x.ToString())
    |> List.reduce (fun x y -> x + "," + y) )
  + "]"

let answer = printIt 20