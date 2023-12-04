#define ROTATE_SPEED 10

/*
* Przykładowy zestaw poleceń
*/

Begin_Parallel_Actions
    Rotate Podstawa OZ ROTATE_SPEED 360 /* Rotate i Move wykonywane razem */
End_Parallel_Actions

Begin_Parallel_Actions
    Rotate Korpus OZ ROTATE_SPEED 360 /* Rotate i Move wykonywane razem */
    Move Korpus 10 10
    Move Korpus.Stozek 10 10
    Move Korpus.Lotka1 10 10
    Move Korpus.Lotka2 10 10
    Move Korpus.Lotka3 10 10
    Move Korpus.Lotka4 10 10
End_Parallel_Actions
