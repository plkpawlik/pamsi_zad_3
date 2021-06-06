#include "common.hh"

/*   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   */

struct Board {

    uint size;
    uint need;

    char ** board;

    /*   *   *   *   *   *   *   *   *   *   */

    Board( uint size, uint need );
    ~Board();

    /*   *   *   *   *   */

    bool isEmpty( coord c );
    bool isTie( char mark );
    bool isWin( char mark );

    /*   *   *   *   *   */

    void setSize( uint size );
    void setNeed( uint need );
    void setEmpty();
    void printAll();
};