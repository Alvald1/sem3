#ifndef GAME_HPP
#define GAME_HPP

#include <memory>
#include "json_parser.hpp"
#include "map/map.hpp"
#include "ui/board.hpp"
#include "ui/control.hpp"
#include "ui/view.hpp"

class Game {
  private:
    JsonParser parser_;
    std::unique_ptr<Map> game_map_;
    std::unique_ptr<Board> board_;

  public:
    Game();
    ~Game();
    void start();
    void load();
};

#endif // GAME_HPP
