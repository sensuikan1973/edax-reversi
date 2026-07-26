/*
 * src/layout_check.c
 * Added for FFI layout verification: returns sizeof(Position) and offsets
 */
#include <stddef.h>
#include "book.h"
#include "ui.h"

// Exported function:
// int libedax_get_position_layout(int *out, int max_len)
//   out[0] = sizeof(Position)
//   out[1] = offsetof(Position, board)
//   out[2] = offsetof(Position, leaf)
//   out[3] = offsetof(Position, flag)
//   out[4] = offsetof(Position, n_player_bestpaths)
//   out[5] = offsetof(Position, n_opponent_bestpaths)
//   out[6] = offsetof(Position, link)
//   out[7] = offsetof(Position, n_wins)
//   out[8] = offsetof(Position, score)
//   out[9] = offsetof(Position, n_link)
//   out[10] = offsetof(Position, level)
// returns number of ints written (11) or -1 if max_len < needed
DLL_API int libedax_get_position_layout(int *out, int max_len)
{
    const int need = 11;
    if (max_len < need) return -1;
    out[0] = (int) sizeof(Position);
    out[1] = (int) offsetof(Position, board);
    out[2] = (int) offsetof(Position, leaf);
    out[3] = (int) offsetof(Position, flag);
    out[4] = (int) offsetof(Position, n_player_bestpaths);
    out[5] = (int) offsetof(Position, n_opponent_bestpaths);
    out[6] = (int) offsetof(Position, link);
    out[7] = (int) offsetof(Position, n_wins);
    out[8] = (int) offsetof(Position, score);
    out[9] = (int) offsetof(Position, n_link);
    out[10] = (int) offsetof(Position, level);
    return need;
}
