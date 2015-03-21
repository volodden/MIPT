let art = 
    [
        ['@';'.';'.';'@';'.';'.';'.';'.';'.';'.';'.';'.';'.';'.';'.';'.';'.';'.';'.';'.';'.';'.']
        ['.';'.';'@';'.';'.';'@';'.';'.';'.';'.';'.';'.';'.';'.';'.';'.';'.';'.';'.';'.';'.';'.']
        ['.';'.';'.';'.';'@';'.';'.';'@';'.';'.';'@';'@';'@';'@';'@';'@';'@';'@';'@';'@';'@';'@']
        ['.';'.';'.';'.';'.';'.';'@';'.';'.';'@';'.';'.';'.';'.';'.';'.';'.';'.';'.';'.';'.';'.']
        ['.';'.';'.';'.';'.';'.';'.';'.';'@';'.';'.';'@';'.';'.';'.';'.';'.';'.';'.';'.';'.';'.']
        ['.';'.';'.';'.';'.';'.';'@';'.';'.';'@';'.';'.';'.';'@';'.';'.';'@';'@';'@';'@';'@';'@']
        ['.';'.';'.';'.';'@';'.';'.';'@';'.';'.';'.';'.';'.';'.';'.';'@';'.';'.';'.';'.';'.';'.']
        ['.';'.';'@';'.';'.';'@';'.';'.';'.';'.';'.';'.';'.';'.';'.';'.';'.';'@';'.';'.';'.';'.']
        ['@';'.';'.';'@';'.';'.';'.';'.';'.';'.';'.';'.';'.';'.';'.';'.';'.';'.';'.';'@';'.';'.']
    ]

let flipV (image: List<List<char>>) = [for x in image do yield List.rev x]

let flipH (image: List<List<char>>) = List.rev image

let rotation180 image = flipV (flipH image)

let rec slice = function
    | [] -> ([], [])
    | h::t ->
        let (u, v) = slice t 
        ((List.head h)::u, (List.tail h)::v)

let rec trans = function
    | []::_ -> []
    | x ->
        let(h, r) = slice x
        h::(trans r)

let rec prov (L: List<List<char>>) = 
    match L with
    | [] -> true
    | h::[] -> true
    | h::t -> if (h.Length = t.Head.Length)
                then prov t
                else false

let rotation90 image = 
    if (prov image <> true)
    then failwith "Bad size"
    else trans (flipH image)

let rotation270 image = 
    if (prov image <> true)
    then failwith "Bad size"
    else trans (flipV image)

art
flipH art
flipV art
rotation90 art
rotation270 art
rotation180 art