#define ROTATE_SPEED 30

/*
* Przykładowy zestaw poleceń
*/
Begin_Parallel_Actions
    Set Podstawa1 2 0 0 30 0 0 // Polozenie obiektu A
    Set Podstawa1.Ramie1 10 10 5 0 0 0 // Polozenie obiektu B
End_Parallel_Actions

Begin_Parallel_Actions
    Rotate Podstawa1 ROTATE_SPEED 40
End_Parallel_Actions

Begin_Parallel_Actions
    Pause 1000 /* Zawieszenie na 1 sek. */
End_Parallel_Actions

Begin_Parallel_Actions
    Move Podstawa1 10 10
    Rotate Podstawa1.Ramie1 ROTATE_SPEED 60 /* Rotate i Move wykonywane razem */
    Move Podstawa1.Ramie1 10 20 /* powodują jazdę po łuku */
End_Parallel_Actions
