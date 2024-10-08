/**
 * @file book.h
 *
 * Header file for opening book management
 *
 * @date 1998 - 2017
 * @author Richard Delorme
 * @version 4.4
 */

#ifndef EDAX_BOOK_H
#define EDAX_BOOK_H

#include "base.h"
#include "board.h"
#include "game.h"
#include "search.h"
#include "util.h"
#include <stdbool.h>

/**
 * struct Book
 * @brief The opening book.
 */
typedef struct Book {
	struct {
		short year;
		char month, day;
		char hour, minute, second;
	} date;
	struct {
		int level;
		int n_empties;
		int midgame_error;
		int endcut_error;
		int verbosity;
	} options;
	struct {
		int n_nodes;
		int n_links;
		int n_todo;
	} stats;
	struct PositionArray *array;
	struct PositionStack* stack;
	int n;
	int n_nodes;
	bool need_saving;
	Random random[1];
	Search *search;
    volatile Stop count_bestpath_stop;  // add by lavox. 2021/8/24
} Book;

/**
 * struct GameStat
 * @brief Game statistics
 */
typedef struct GameStats {
 	unsigned long long n_wins;       /**< game win count */
	unsigned long long n_draws;      /**< game draw count */
	unsigned long long n_losses;     /**< game loss count */
	unsigned long long n_lines;      /**< unterminated line count */
} GameStats;

// moved from book.c for libEdax. by lavox 2018/1/18
/** struct Link
 * @brief a move (with its score) linking to another Position.
 */
typedef struct Link {
	signed char score; /**< move score */
	unsigned char move; /**< move coordinate */
} Link;

/**
 * struct Position
 * @brief A position stored in the book.
 */
typedef struct Position {
	Board board[1];            /**< (unique) board */
	Link leaf;                 /**< best remaining move */
    // changes variable order for the sake of memory reduction. 2022/6/12 by lavox
    //unsigned char done;        /**< done/undone flag */
    //unsigned char todo;        /**< todo flag */
    unsigned char flag;        /**< done/undone, todo flag*/
    unsigned short n_player_bestpaths;    /**< count of best paths for player */ // add for libedax by lavox. 2021/8/22
    unsigned short n_opponent_bestpaths;  /**< count of best paths for opponent */ // add for libedax by lavox. 2021/8/22
	Link* link;                /**< linking moves */
	unsigned int n_wins;       /**< game win count */
	unsigned int n_draws;      /**< game draw count */
	unsigned int n_losses;     /**< game loss count */
	unsigned int n_lines;      /**< unterminated line count */
	struct {
		short value, lower, upper;
	} score;                   /**< Position value & bounds */
	unsigned char n_link;      /**< linking moves number */
	unsigned char level;       /**< search level */
} Position;

#define FLAG_DONE 1
#define FLAG_TODO 2
#define FLAG_BESTPATH_BLACK 4

void book_init(Book*);
void book_free(Book*);
void book_preprocess(Book*);// add for libedax by lavox. 2021/1/23
void book_stats_clean(Book*);// add for libedax by lavox. 2022/6/12

void book_new(Book*, int, int);
void book_load(Book*, const char*);
void book_save(Book*, const char*);
void book_import(Book*, const char*);
void book_export(Book*, const char*);
void book_merge(Book*, const Book*);
void book_sort(Book *book);
void book_negamax(Book*);
void book_prune(Book*);
void book_deepen(Book*);
void book_correct_solved(Book*);
void book_link(Book*);
void book_fix(Book*);
void book_fill(Book *book, const int);
void book_deviate(Book*, Board*, const int, const int);
void book_enhance(Book*, Board*, const int, const int);
void book_subtree(Book*, const Board*);
void book_play(Book*);

void book_info(Book*);
void book_show(Book*, Board*);
void book_count_bestpath(Book*, Board*, Position*); // add for libedax by lavox. 2021/8/22
void book_stop_count_bestpath(Book*); // add for libedax by lavox. 2021/8/24
Position* book_show_for_api(Book*, Board*);// add for libedax by lavox. 2018/5/20
void book_count_board_bestpath(Book*, Board*, Position*, const int, const int, const int); // add for libedax by lavox. 2022/6/12
void book_stats(Book *book);
bool book_get_moves(Book*, const Board*, MoveList*);
int book_get_moves_with_position(Book*, const Board*, MoveList*, Position*);// add for libedax by lavox. 2020/2/24
bool book_get_random_move(Book*, const Board*, Move*, const int);
void book_get_game_stats(Book*, const Board*, GameStats*);
void book_get_line(Book*, const Board*, const Move*, Line*);

void book_add_board(Book*, const Board*);
void book_add_game(Book*, const Game*);
void book_add_base(Book*, const Base*);
void book_check_base(Book*, const Base*);

void book_extract_skeleton(Book*, Base*);
void book_extract_positions(Book*, const int, const int);

void book_feed_hash(const Book*, Board*, Search*);

#endif /* EDAX_BOOK_H */

