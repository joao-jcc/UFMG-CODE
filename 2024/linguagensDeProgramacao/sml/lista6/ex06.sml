fun comparador_comprimento(a, b) = 
    if String.size a <= String.size b then true 
    else false;


fun partition(pivot, [], left, right, comp) = (left, right)
  | partition(pivot, h::t, left, right, comp) =
    if comp(h, pivot) then partition(pivot, t, left @ [h], right, comp)
    else partition(pivot, t, left, right @ [h], comp);

fun quicksort([], comp) = []
  | quicksort([h], comp) = [h]
  | quicksort(h::t, comp) =
    let
      val (left, right) = partition(h, t, [], [], comp)
    in
      quicksort(left, comp) @ [h] @ quicksort(right, comp)
    end;
