#pragma once
#include <iostream>
#include <string>
#include <vector>
//Цвета настроенны под Unix и на других Windows могут не работать !
#define RESET "\x1b[0m"
#define RED "\x1b[91m"
#define GREEN "\x1b[92m"
#define YELLOW "\x1B[93m"
#define BLUE "\x1b[94m"
#define ORANGE "\x1b[33m"
#define CYAN "\x1b[36m"
#define WHITE "\x1B[97m"
#define GREY "\x1B[90m"
#define D_RED "\x1b[31m"
#define D_GREEN "\x1b[32m"

/*=================== Крань кубика ===========================================*/
struct side {
  bool color = true;
  std::vector<std::vector<char>> cells; // Клетки стороны
  side(const char &); // Конструктор грани по цвету
  char *copy_row(const int &); // Скопировать ряд грани (возвращает копию)
  void swap_row(const int &, char *); // Заменить ряд грани на другой(копию др.)
  char *copy_col(const int &); // Скопировать столбец грани (возвращает копию)
  void swap_col(const int &, char *);
  void cw_move(); // Провернуть все ячейки по часовой стрелке 1 раз
  void ccw_move(); // Провернуть все ячейки против часовой стрелки 1 раз
  bool check() const; // Проверить грань на сборку
  bool check_mid_row() const; // Проверить средний слой грани на сборку
};
/*=================== Кубик ==================================================*/
/*
Передняя грань [0] - зелёный
Задняя грань [5] - синий
Верхняя грань [4] - белый
Нижняя грань [1] - жёлтый
Левая грань [2] - оранжевый
Правая грань [3] - красный

Все повороты делаются относительно передней грани!
*/
class cube {
private:
  std::vector<std::string> hint;
  bool enable_hint = false;
  std::vector<side> plane; // 6 граней кубика
  bool check_cross(const int &, const char &) const;
  void move_mid_edges();
  void move_ud_edges();
  void move_bot_edges();
  void build_white_cross(); // Первый шаг: собрать правильный белый крест
  bool check_corner(const int &) const;
  bool corner_has_color(const int &, const char &) const;
  void right_combo(const int &);
  void right_usd_combo(const int &);
  void move_up_corners(); // Двигаем углы с жёлтого слоя к белому
  void move_sbot_corners(); // Передвигаем углы с белым цветом к жёлтому слою
  void move_bot_corners(); // Передвигаем неправильные углы с белым с б. к ж.
  void build_white_layer(); // Шаг второй: собрать верхний слой + белую сторону
  void left_combo(const int &);
  void left_usd_combo(const int &);
  void r_diagonal_move(const int &);
  void l_diagonal_move(const int &);
  bool check_mid_layer() const;
  void move_top_edges();
  void get_top_edges();
  void build_mid_layer(); // Шаг третий: собрать средний слой
  void if_line();
  void if_angle();
  void if_dot();
  void build_yellow_cross(); // Шаг четвёртый: собрать жёлтый крест
  int corners_matched() const;
  void line_corners();
  void diagonal_corners();
  void match_corners(); // Шаг пятый: поставить углы в правильное положение
  void buid_yellow_side(); // Шаг шестой: собрать жёлтую сторону
  int assembled_sides() const;
  void match_edges(); // Шаг семь: поставить рёбра на свои места

public:
  cube(); // Конструктор
  void write(std::ostream & = std::cout, bool = true);
  void randomize(); // Задать кубику случайное положение
  void save_hint() const; // Записать решение в файл
  void load();            // Загрузить решение из файла
  void assemble();        // Собрать кубик
  bool done() const;      // Проверка кубика на сборку
  //--- Тип поворота (кол-во поворотов) ---
  void R_rotate(const int &); // Поворот правой грани (по часовой)
  void Rb_rotate(const int &); // Обратный поворот правой грани (против часовой)
  void L_rotate(const int &); // Поворот левой грани (по часовой)
  void Lb_rotate(const int &); // Обратный поворот левой грани (против часовой)
  void F_rotate(const int &); // Поворот передней грани (по часовой)
  void Fb_rotate(const int &); // Поворот передней грани (против часовой)
  void B_rotate(const int &); // Поворот задней грани (по часовой)
  void Bb_rotate(const int &); // Поворот задней грани (против часовой)
  void U_rotate(const int &); // Поворот верхней грани (по часовой)
  void Ub_rotate(const int &); // Обратный поворот верхней грани(против часовой)
  void D_rotate(const int &); // Поворот нижней грани (по часовой)
  void Db_rotate(const int &); // Поворот нижней грани (против часовой)
};
