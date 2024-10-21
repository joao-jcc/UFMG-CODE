fun partition(pivot, [], left, right) = (left, right)
  | partition(pivot, h::t, left, right) =
    if h < pivot then partition(pivot, t, left @ [h], right)
    else partition(pivot, t, left, right @ [h]);

fun quicksort([]) = []
  | quicksort([h]) = [h]
  | quicksort(h::t) =
    let
      val (left, right) = partition(h, t, [], [])
    in
      quicksort(left) @ [h] @ quicksort(right)
    end;
