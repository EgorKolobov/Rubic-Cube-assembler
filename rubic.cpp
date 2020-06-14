#include "rubic.h"
#include <algorithm>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>
/*=================== Крань кубика ===========================================*/
side::side(const char &ch) { cells.assign(3, std::vector<char>(3, ch)); }

std::ostream &operator<<(std::ostream &os, const side &s) {
  if (s.color)
    for (int i = 0; i < 3; i++) {
      for (auto j : s.cells[i])
        switch (j) {
        case 'g':
          os << GREEN << j << " ";
          break;
        case 'b':
          os << BLUE << j << " ";
          break;
        case 'r':
          os << RED << j << " ";
          break;
        case 'o':
          os << ORANGE << j << " ";
          break;
        case 'y':
          os << YELLOW << j << " ";
          break;
        case 'w':
          os << WHITE << j << " ";
          break;
        }
      os << RESET << "\n";
    }
  else
    for (int i = 0; i < 3; i++) {
      for (auto j : s.cells[i])
        os << j << " ";
      os << "\n";
    }
  return os;
}

char *side::copy_row(const int &row_ind) {
  char *row_copy = new char[3];
  for (int i = 0; i < 3; i++) {
    row_copy[i] = cells[row_ind][i];
  }
  return row_copy;
}

void side::swap_row(const int &row_ind1, char *row_copy) {
  for (int i = 0; i < 3; i++)
    cells[row_ind1][i] = row_copy[i];
}

char *side::copy_col(const int &col_ind) {
  char *col_copy = new char[3];
  for (int i = 0; i < 3; i++) {
    col_copy[i] = cells[i][col_ind];
  }
  return col_copy;
}

void side::swap_col(const int &col_ind, char *col_copy) {
  for (int i = 0; i < 3; i++)
    cells[i][col_ind] = col_copy[i];
}

void side::cw_move() {
  char *tmp1_copy = new char[3];
  char *tmp2_copy = new char[3];
  char *tmp3_copy = new char[3];
  char *cur_copy = new char[3];

  memcpy(cur_copy, this->copy_col(0), 3);
  memcpy(tmp1_copy, this->copy_row(0), 3);
  memcpy(tmp2_copy, this->copy_col(2), 3);
  memcpy(tmp3_copy, this->copy_row(2), 3);

  std::reverse(cur_copy, cur_copy + 3);
  this->swap_row(0, cur_copy);

  memcpy(cur_copy, tmp1_copy, 3);
  this->swap_col(2, cur_copy);

  memcpy(cur_copy, tmp2_copy, 3);
  std::reverse(cur_copy, cur_copy + 3);
  this->swap_row(2, cur_copy);

  memcpy(cur_copy, tmp3_copy, 3);
  this->swap_col(0, cur_copy);
}

void side::ccw_move() {
  char *tmp1_copy = new char[3];
  char *tmp2_copy = new char[3];
  char *tmp3_copy = new char[3];
  char *cur_copy = new char[3];

  memcpy(cur_copy, this->copy_col(0), 3);
  memcpy(tmp1_copy, this->copy_row(2), 3);
  memcpy(tmp2_copy, this->copy_col(2), 3);
  memcpy(tmp3_copy, this->copy_row(0), 3);

  this->swap_row(2, cur_copy);

  memcpy(cur_copy, tmp1_copy, 3);
  std::reverse(cur_copy, cur_copy + 3);
  this->swap_col(2, cur_copy);

  memcpy(cur_copy, tmp2_copy, 3);
  this->swap_row(0, cur_copy);

  memcpy(cur_copy, tmp3_copy, 3);
  std::reverse(cur_copy, cur_copy + 3);
  this->swap_col(0, cur_copy);
}

bool side::check() const {
  char color = cells[1][1];
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      if (cells[i][j] != color)
        return false;
  return true;
}

bool side::check_mid_row() const {
  return (cells[1][0] == cells[1][1] and cells[1][2] == cells[1][1]);
}
/*=================== Кубик ==================================================*/
//--- Конструктор добавляет  грани ---
cube::cube() {
  plane.push_back(side('g')); // зелёная грань (спереди) [0]
  plane.push_back(side('y')); // жёлтая грань (снизу) [1]
  plane.push_back(side('o')); // оранжевая грань (слева) [2]
  plane.push_back(side('r')); // краснаая грань (справа) [3]
  plane.push_back(side('w')); // белая грань (верх) [4]
  plane.push_back(side('b')); // синяя грань (сзади) [5]
}

//--- Вывод состояния кубика ---
void cube::write(std::ostream &os, bool colorize) {
  for (int i = 0; i < 6; i++) {
    if (colorize)
      plane[i].color = true;
    else
      plane[i].color = false;
    os << plane[i] << "\n";
  }
}

bool cube::done() const {
  return (plane[0].check() and plane[1].check() and plane[2].check() and
          plane[3].check() and plane[4].check() and plane[5].check());
}

//--- Правый поворот (по часовой) ---
void cube::R_rotate(const int &times) {
  if (enable_hint)
    hint.push_back("Сверху белая грань. Зелёная грань: R\n");
  int inds[4] = {0, 4, 5, 1};
  for (int i = 0; i < times % 4; i++) {
    char *tmp_copy = new char[3];
    char *cur_copy = new char[3];
    memcpy(tmp_copy, plane[0].copy_col(2), 3);
    for (int j = 0; j < 4; j++) {
      int cur_ind = inds[j % 4];
      int next_ind = inds[(j + 1) % 4];
      memcpy(cur_copy, tmp_copy, 3);
      if (next_ind == 5) {
        memcpy(tmp_copy, plane[next_ind].copy_col(0), 3);
        std::reverse(tmp_copy, tmp_copy + 3);
        std::reverse(cur_copy, cur_copy + 3);
        plane[next_ind].swap_col(0, cur_copy);
      } else {
        memcpy(tmp_copy, plane[next_ind].copy_col(2), 3);
        plane[next_ind].swap_col(2, cur_copy);
      }
    }
    // Проворачивает грань [3] (изначально она красная) по часовой
    plane[3].cw_move();
  }
}

//--- Правый обратный поворот (против часовой) ---
void cube::Rb_rotate(const int &times) {
  if (enable_hint)
    hint.push_back("Сверху белая грань. Зелёная грань: R'\n");
  int inds[4] = {0, 1, 5, 4};
  for (int i = 0; i < times % 4; i++) {
    char *tmp_copy = new char[3];
    char *cur_copy = new char[3];
    memcpy(tmp_copy, plane[0].copy_col(2), 3);
    for (int j = 0; j < 4; j++) {
      int cur_ind = inds[j % 4];
      int next_ind = inds[(j + 1) % 4];
      memcpy(cur_copy, tmp_copy, 3);
      if (next_ind == 5) {
        memcpy(tmp_copy, plane[next_ind].copy_col(0), 3);
        std::reverse(tmp_copy, tmp_copy + 3);
        std::reverse(cur_copy, cur_copy + 3);
        plane[next_ind].swap_col(0, cur_copy);
      } else {
        memcpy(tmp_copy, plane[next_ind].copy_col(2), 3);
        plane[next_ind].swap_col(2, cur_copy);
      }
    }
    // Проворачивает грань [3] (изначально она красная) против часовой
    plane[3].ccw_move();
  }
}

//--- Левый поворот (по часовой) ---
void cube::L_rotate(const int &times) {
  if (enable_hint)
    hint.push_back("Сверху белая грань. Зелёная грань: L\n");
  int inds[4] = {0, 1, 5, 4};
  for (int i = 0; i < times % 4; i++) {
    char *tmp_copy = new char[3];
    char *cur_copy = new char[3];
    memcpy(tmp_copy, plane[0].copy_col(0), 3);
    for (int j = 0; j < 4; j++) {
      int cur_ind = inds[j % 4];
      int next_ind = inds[(j + 1) % 4];
      memcpy(cur_copy, tmp_copy, 3);
      if (next_ind == 5) {
        memcpy(tmp_copy, plane[next_ind].copy_col(2), 3);
        std::reverse(tmp_copy, tmp_copy + 3);
        std::reverse(cur_copy, cur_copy + 3);
        plane[next_ind].swap_col(2, cur_copy);
      } else {
        memcpy(tmp_copy, plane[next_ind].copy_col(0), 3);
        plane[next_ind].swap_col(0, cur_copy);
      }
    }
    // Проворачивает грань [2] (изначально она оранжевая) по часовой
    plane[2].cw_move();
  }
}

//--- Левый обратный поворот (против часовой) ---
void cube::Lb_rotate(const int &times) {
  if (enable_hint)
    hint.push_back("Сверху белая грань. Зелёная грань: L'\n");
  int inds[4] = {0, 4, 5, 1};
  for (int i = 0; i < times % 4; i++) {
    char *tmp_copy = new char[3];
    char *cur_copy = new char[3];
    memcpy(tmp_copy, plane[0].copy_col(0), 3);
    for (int j = 0; j < 4; j++) {
      int cur_ind = inds[j % 4];
      int next_ind = inds[(j + 1) % 4];
      memcpy(cur_copy, tmp_copy, 3);
      if (next_ind == 5) {
        memcpy(tmp_copy, plane[next_ind].copy_col(2), 3);
        std::reverse(tmp_copy, tmp_copy + 3);
        std::reverse(cur_copy, cur_copy + 3);
        plane[next_ind].swap_col(2, cur_copy);
      } else {
        memcpy(tmp_copy, plane[next_ind].copy_col(0), 3);
        plane[next_ind].swap_col(0, cur_copy);
      }
    }
    // Проворачивает грань [2] (изначально она оранжевая) против часовой
    plane[2].ccw_move();
  }
}

//--- Поворот передней грани (по часовой) ---
void cube::F_rotate(const int &times) {
  if (enable_hint)
    hint.push_back("Сверху белая грань. Красная грань: L\n");
  int inds[4] = {4, 3, 1, 2};
  for (int i = 0; i < times % 4; i++) {
    char *tmp_copy = new char[3];
    char *cur_copy = new char[3];
    memcpy(tmp_copy, plane[4].copy_row(2), 3);
    for (int j = 0; j < 4; j++) {
      int cur_ind = inds[j % 4];
      int next_ind = inds[(j + 1) % 4];
      memcpy(cur_copy, tmp_copy, 3);
      switch (next_ind) {
      case 4:
        std::reverse(cur_copy, cur_copy + 3);
        memcpy(tmp_copy, plane[next_ind].copy_row(2), 3);
        plane[next_ind].swap_row(2, cur_copy);
        break;
      case 3:
        memcpy(tmp_copy, plane[next_ind].copy_col(0), 3);
        plane[next_ind].swap_col(0, cur_copy);
        break;
      case 1:
        std::reverse(cur_copy, cur_copy + 3);
        memcpy(tmp_copy, plane[next_ind].copy_row(0), 3);
        plane[next_ind].swap_row(0, cur_copy);
        break;
      case 2:
        memcpy(tmp_copy, plane[next_ind].copy_col(2), 3);
        plane[next_ind].swap_col(2, cur_copy);
        break;
      }
    }
    // Проворачивает грань [0] (изначаьно она зелёная) по часовой
    plane[0].cw_move();
  }
}

//--- Поворот передней грани (против часовой) ---
void cube::Fb_rotate(const int &times) {
  if (enable_hint)
    hint.push_back("Сверху белая грань. Красная грань: L'\n");
  int inds[4] = {4, 2, 1, 3};
  for (int i = 0; i < times % 4; i++) {
    char *tmp_copy = new char[3];
    char *cur_copy = new char[3];
    memcpy(tmp_copy, plane[4].copy_row(2), 3);
    for (int j = 0; j < 4; j++) {
      int cur_ind = inds[j % 4];
      int next_ind = inds[(j + 1) % 4];
      memcpy(cur_copy, tmp_copy, 3);
      switch (next_ind) {
      case 4:
        memcpy(tmp_copy, plane[next_ind].copy_row(2), 3);
        plane[next_ind].swap_row(2, cur_copy);
        break;
      case 2:
        std::reverse(cur_copy, cur_copy + 3);
        memcpy(tmp_copy, plane[next_ind].copy_col(2), 3);
        plane[next_ind].swap_col(2, cur_copy);
        break;
      case 1:
        memcpy(tmp_copy, plane[next_ind].copy_row(0), 3);
        plane[next_ind].swap_row(0, cur_copy);
        break;
      case 3:
        std::reverse(cur_copy, cur_copy + 3);
        memcpy(tmp_copy, plane[next_ind].copy_col(0), 3);
        plane[next_ind].swap_col(0, cur_copy);
        break;
      }
    }
    // Проворачивает грань [0] (изначально она зелёная) против часовой
    plane[0].ccw_move();
  }
}

//--- Поворот задней грани (по часовой)---
void cube::B_rotate(const int &times) {
  if (enable_hint)
    hint.push_back("Сверху белая грань. Красная грань: R\n");
  int inds[4] = {4, 2, 1, 3};
  for (int i = 0; i < times % 4; i++) {
    char *tmp_copy = new char[3];
    char *cur_copy = new char[3];
    memcpy(tmp_copy, plane[4].copy_row(0), 3);
    for (int j = 0; j < 4; j++) {
      int cur_ind = inds[j % 4];
      int next_ind = inds[(j + 1) % 4];
      memcpy(cur_copy, tmp_copy, 3);
      switch (next_ind) {
      case 4:
        memcpy(tmp_copy, plane[next_ind].copy_row(0), 3);
        plane[next_ind].swap_row(0, cur_copy);
        break;
      case 2:
        std::reverse(cur_copy, cur_copy + 3);
        memcpy(tmp_copy, plane[next_ind].copy_col(0), 3);
        plane[next_ind].swap_col(0, cur_copy);
        break;
      case 1:
        memcpy(tmp_copy, plane[next_ind].copy_row(2), 3);
        plane[next_ind].swap_row(2, cur_copy);
        break;
      case 3:
        std::reverse(cur_copy, cur_copy + 3);
        memcpy(tmp_copy, plane[next_ind].copy_col(2), 3);
        plane[next_ind].swap_col(2, cur_copy);
        break;
      }
    }
    // Проворачивает грань [5] (изначаьно она синяя) по часовой
    plane[5].cw_move();
  }
}

//--- // Поворот задней грани (против часовой) ---
void cube::Bb_rotate(const int &times) {
  if (enable_hint)
    hint.push_back("Сверху белая грань. Красная грань: R'\n");
  int inds[4] = {4, 3, 1, 2};
  for (int i = 0; i < times % 4; i++) {
    char *tmp_copy = new char[3];
    char *cur_copy = new char[3];
    memcpy(tmp_copy, plane[4].copy_row(0), 3);
    for (int j = 0; j < 4; j++) {
      int cur_ind = inds[j % 4];
      int next_ind = inds[(j + 1) % 4];
      memcpy(cur_copy, tmp_copy, 3);
      switch (next_ind) {
      case 4:
        std::reverse(cur_copy, cur_copy + 3);
        memcpy(tmp_copy, plane[next_ind].copy_row(0), 3);
        plane[next_ind].swap_row(0, cur_copy);
        break;
      case 3:
        memcpy(tmp_copy, plane[next_ind].copy_col(2), 3);
        plane[next_ind].swap_col(2, cur_copy);
        break;
      case 1:
        std::reverse(cur_copy, cur_copy + 3);
        memcpy(tmp_copy, plane[next_ind].copy_row(2), 3);
        plane[next_ind].swap_row(2, cur_copy);
        break;
      case 2:
        memcpy(tmp_copy, plane[next_ind].copy_col(0), 3);
        plane[next_ind].swap_col(0, cur_copy);
        break;
      }
    }
    // Проворачивает грань [5] (изначально она  синяя) против часовой
    plane[5].ccw_move();
  }
}

//--- Поворот верхней грани (по часовой) ---
void cube::U_rotate(const int &times) {
  if (enable_hint)
    hint.push_back("Сверху белая грань. Зелёная грань: U\n");
  int inds[4] = {0, 2, 5, 3};
  for (int i = 0; i < times % 4; i++) {
    char *tmp_copy = new char[3];
    char *cur_copy = new char[3];
    memcpy(tmp_copy, plane[0].copy_row(0), 3);
    for (int j = 0; j < 4; j++) {
      int cur_ind = inds[j % 4];
      int next_ind = inds[(j + 1) % 4];
      memcpy(cur_copy, tmp_copy, 3);
      memcpy(tmp_copy, plane[next_ind].copy_row(0), 3);
      plane[next_ind].swap_row(0, cur_copy);
    }
    // Проворачивает грань [4] (изначально она белая) по часовой
    plane[4].cw_move();
  }
}

//--- Обратный поворот верхней грани (против часовой) ---
void cube::Ub_rotate(const int &times) {
  if (enable_hint)
    hint.push_back("Сверху белая грань. Зелёная грань: U'\n");
  int inds[4] = {0, 3, 5, 2};
  for (int i = 0; i < times % 4; i++) {
    char *tmp_copy = new char[3];
    char *cur_copy = new char[3];
    memcpy(tmp_copy, plane[0].copy_row(0), 3);
    for (int j = 0; j < 4; j++) {
      int cur_ind = inds[j % 4];
      int next_ind = inds[(j + 1) % 4];
      memcpy(cur_copy, tmp_copy, 3);
      memcpy(tmp_copy, plane[next_ind].copy_row(0), 3);
      plane[next_ind].swap_row(0, cur_copy);
    }
    // Проворачивает грань [4] (изначально она белая) против часовой
    plane[4].ccw_move();
  }
}

void cube::D_rotate(const int &times) {
  if (enable_hint)
    hint.push_back("Сверху жёлтая грань. Зелёная грань: U\n");
  int inds[4] = {0, 3, 5, 2};
  for (int i = 0; i < times % 4; i++) {
    char *tmp_copy = new char[3];
    char *cur_copy = new char[3];
    memcpy(tmp_copy, plane[0].copy_row(2), 3);
    for (int j = 0; j < 4; j++) {
      int cur_ind = inds[j % 4];
      int next_ind = inds[(j + 1) % 4];
      memcpy(cur_copy, tmp_copy, 3);
      memcpy(tmp_copy, plane[next_ind].copy_row(2), 3);
      plane[next_ind].swap_row(2, cur_copy);
    }
    plane[1].cw_move();
  }
}

//--- Поворот нижней грани (против часовой) ---
void cube::Db_rotate(const int &times) {
  if (enable_hint)
    hint.push_back("Сверху жёлтая грань. Зелёная грань: U'\n");
  int inds[4] = {0, 2, 5, 3};
  for (int i = 0; i < times % 4; i++) {
    char *tmp_copy = new char[3];
    char *cur_copy = new char[3];
    memcpy(tmp_copy, plane[0].copy_row(2), 3);
    for (int j = 0; j < 4; j++) {
      int cur_ind = inds[j % 4];
      int next_ind = inds[(j + 1) % 4];
      memcpy(cur_copy, tmp_copy, 3);
      memcpy(tmp_copy, plane[next_ind].copy_row(2), 3);
      plane[next_ind].swap_row(2, cur_copy);
    }
    plane[1].ccw_move();
  }
}

void cube::right_combo(const int &plane_ind) {
  switch (plane_ind) {
  case 0:
    R_rotate(1);
    U_rotate(1);
    Rb_rotate(1);
    Ub_rotate(1);
    break;

  case 1:
    R_rotate(1);
    F_rotate(1);
    Rb_rotate(1);
    Fb_rotate(1);
    break;

  case 2:
    F_rotate(1);
    U_rotate(1);
    Fb_rotate(1);
    Ub_rotate(1);
    break;

  case 3:
    B_rotate(1);
    U_rotate(1);
    Bb_rotate(1);
    Ub_rotate(1);
    break;

  case 4:
    R_rotate(1);
    B_rotate(1);
    Rb_rotate(1);
    Bb_rotate(1);
    break;

  case 5:
    L_rotate(1);
    U_rotate(1);
    Lb_rotate(1);
    Ub_rotate(1);
    break;
  }
}

void cube::right_usd_combo(const int &plane_ind) {
  switch (plane_ind) {
  case 0:
    L_rotate(1);
    D_rotate(1);
    Lb_rotate(1);
    Db_rotate(1);
    break;

  case 1:
    L_rotate(1);
    B_rotate(1);
    Lb_rotate(1);
    Bb_rotate(1);
    break;

  case 2:
    B_rotate(1);
    D_rotate(1);
    Bb_rotate(1);
    Db_rotate(1);
    break;

  case 3:
    F_rotate(1);
    D_rotate(1);
    Fb_rotate(1);
    Db_rotate(1);
    break;

  case 4:
    L_rotate(1);
    F_rotate(1);
    Lb_rotate(1);
    Fb_rotate(1);
    break;

  case 5:
    R_rotate(1);
    D_rotate(1);
    Rb_rotate(1);
    Db_rotate(1);
    break;
  }
}

void cube::left_combo(const int &plane_ind) {
  switch (plane_ind) {
  case 0:
    Lb_rotate(1);
    Ub_rotate(1);
    L_rotate(1);
    U_rotate(1);
    break;

  case 1:
    Lb_rotate(1);
    Fb_rotate(1);
    L_rotate(1);
    F_rotate(1);
    break;

  case 2:
    Bb_rotate(1);
    Ub_rotate(1);
    B_rotate(1);
    U_rotate(1);
    break;

  case 3:
    Fb_rotate(1);
    Ub_rotate(1);
    F_rotate(1);
    U_rotate(1);
    break;

  case 4:
    Lb_rotate(1);
    Bb_rotate(1);
    L_rotate(1);
    B_rotate(1);
    break;

  case 5:
    Rb_rotate(1);
    Ub_rotate(1);
    R_rotate(1);
    U_rotate(1);
    break;
  }
}

void cube::left_usd_combo(const int &plane_ind) {
  switch (plane_ind) {
  case 0:
    Rb_rotate(1);
    Db_rotate(1);
    R_rotate(1);
    D_rotate(1);
    break;

  case 1:
    Rb_rotate(1);
    Bb_rotate(1);
    R_rotate(1);
    B_rotate(1);
    break;

  case 2:
    Fb_rotate(1);
    Db_rotate(1);
    F_rotate(1);
    D_rotate(1);
    break;

  case 3:
    Bb_rotate(1);
    Db_rotate(1);
    B_rotate(1);
    D_rotate(1);
    break;

  case 4:
    Rb_rotate(1);
    Fb_rotate(1);
    R_rotate(1);
    F_rotate(1);
    break;

  case 5:
    Lb_rotate(1);
    Db_rotate(1);
    L_rotate(1);
    D_rotate(1);
    break;
  }
}

void cube::randomize() {
  srand(time(NULL));
  // std::cout << time(NULL) << "\n";
  for (unsigned i = 0; i < 239; i++) {
    unsigned choice = rand() % 12;
    switch (choice) {
    case 0:
      R_rotate(i);
      break;

    case 1:
      Rb_rotate(i);
      break;

    case 2:
      L_rotate(i);
      break;

    case 3:
      Lb_rotate(i);
      break;

    case 4:
      F_rotate(i);
      break;

    case 5:
      Fb_rotate(i);
      break;

    case 6:
      B_rotate(i);
      break;

    case 7:
      Bb_rotate(i);
      break;

    case 8:
      U_rotate(i);
      break;

    case 9:
      Ub_rotate(i);
      break;

    case 10:
      D_rotate(i);
      break;

    case 11:
      Db_rotate(i);
      break;
    }
  }
}

bool cube::check_cross(const int &plane_ind, const char &color) const {
  return (plane[plane_ind].cells[0][1] == color and
          plane[plane_ind].cells[1][2] == color and
          plane[plane_ind].cells[2][1] == color and
          plane[plane_ind].cells[1][0] == color);
}

//--- Перемещает средние ("удобные") белые рёбра к жёлтому центру
void cube::move_mid_edges() {
  // Если нашли белое ребро на плоскости [0] в ячейке [1][2]
  if (plane[0].cells[1][2] == 'w') {
    // Если место не занято другим белым ребром
    if (plane[1].cells[1][2] != 'w')
      Rb_rotate(1);
    else
      // Иначе вращаем плоскость [1] пока не освободим место (макс 3 раза)
      for (int i = 1; i < 4; i++) {
        D_rotate(1);
        if (plane[1].cells[1][2] != 'w') {
          Rb_rotate(1);
          break;
        }
      }
  }
  // Если нашли белое ребро на плоскости [0] в ячейке [1][0]
  if (plane[0].cells[1][0] == 'w') {
    if (plane[1].cells[1][0] != 'w')
      L_rotate(1);
    else
      for (int i = 1; i < 4; i++) {
        D_rotate(1);
        if (plane[1].cells[1][0] != 'w') {
          L_rotate(1);
          break;
        }
      }
  }

  // Если нашли белое ребро на плоскости [5] в ячейке [1][2]
  if (plane[5].cells[1][2] == 'w') {
    if (plane[1].cells[1][0] != 'w')
      Lb_rotate(1);
    else
      for (int i = 1; i < 4; i++) {
        D_rotate(1);
        if (plane[1].cells[1][0] != 'w') {
          Lb_rotate(1);
          break;
        }
      }
  }
  // Если нашли белое ребро на плоскости [5] в ячейке [1][0]
  if (plane[5].cells[1][0] == 'w') {
    if (plane[1].cells[1][2] != 'w')
      R_rotate(1);
    else
      for (int i = 1; i < 4; i++) {
        D_rotate(1);
        if (plane[1].cells[1][2] != 'w') {
          R_rotate(1);
          break;
        }
      }
  }

  // Если нашли белое ребро на плоскости [2] в ячейке [1][2]
  if (plane[2].cells[1][2] == 'w') {
    if (plane[1].cells[0][1] != 'w')
      Fb_rotate(1);
    else
      for (int i = 1; i < 4; i++) {
        D_rotate(1);
        if (plane[1].cells[0][1] != 'w') {
          Fb_rotate(1);
          break;
        }
      }
  }
  // Если нашли белое ребро на плоскости [2] в ячейке [1][0]
  if (plane[2].cells[1][0] == 'w') {
    if (plane[1].cells[2][1] != 'w')
      B_rotate(1);
    else
      for (int i = 1; i < 4; i++) {
        D_rotate(1);
        if (plane[1].cells[2][1] != 'w') {
          B_rotate(1);
          break;
        }
      }
  }

  // Если нашли белое ребро на плоскости [3] в ячейке [1][2]
  if (plane[3].cells[1][2] == 'w') {
    if (plane[1].cells[2][1] != 'w')
      Bb_rotate(1);
    else
      for (int i = 1; i < 4; i++) {
        D_rotate(1);
        if (plane[1].cells[2][1] != 'w') {
          Bb_rotate(1);
          break;
        }
      }
  }
  // Если нашли белое ребро на плоскости [3] в ячейке [1][0]
  if (plane[3].cells[1][0] == 'w') {
    if (plane[1].cells[0][1] != 'w')
      F_rotate(1);
    else
      for (int i = 1; i < 4; i++) {
        D_rotate(1);
        if (plane[1].cells[0][1] != 'w') {
          F_rotate(1);
          break;
        }
      }
  }
}

//--- Делает белые верхние и нижние рёбра "удобными"
void cube::move_ud_edges() {
  // Нашлось верхнее или нижнее ребро
  if (plane[0].cells[0][1] == 'w' or plane[0].cells[2][1] == 'w') {
    if (plane[1].cells[0][1] != 'w')
      F_rotate(1);
    else
      for (int i = 1; i < 4; i++) {
        D_rotate(1);
        if (plane[1].cells[0][1] != 'w') {
          F_rotate(1);
          break;
        }
      }
  }

  if (plane[5].cells[0][1] == 'w' or plane[5].cells[2][1] == 'w') {
    if (plane[1].cells[2][1] != 'w')
      B_rotate(1);
    else
      for (int i = 1; i < 4; i++) {
        D_rotate(1);
        if (plane[1].cells[2][1] != 'w') {
          B_rotate(1);
          break;
        }
      }
  }

  if (plane[2].cells[0][1] == 'w' or plane[2].cells[2][1] == 'w') {
    if (plane[1].cells[1][0] != 'w')
      L_rotate(1);
    else {
      while (plane[1].cells[1][0] == 'w')
        D_rotate(1);
      L_rotate(1);
    }
  }
  if (plane[3].cells[0][1] == 'w' or plane[3].cells[2][1] == 'w') {
    if (plane[1].cells[1][2] != 'w')
      R_rotate(1);
    else {
      while (plane[1].cells[1][2] == 'w')
        D_rotate(1);
      R_rotate(1);
    }
  }
}

void cube::move_bot_edges() {
  if (plane[4].cells[0][1] == 'w') {
    if (plane[1].cells[2][1] != 'w')
      B_rotate(2);
    else {
      while (plane[1].cells[2][1] == 'w')
        D_rotate(1);
      B_rotate(2);
    }
  }

  if (plane[4].cells[2][1] == 'w') {
    if (plane[1].cells[0][1] != 'w')
      F_rotate(2);
    else {
      while (plane[1].cells[0][1] == 'w')
        D_rotate(1);
      F_rotate(2);
    }
  }

  if (plane[4].cells[1][0] == 'w') {
    if (plane[1].cells[1][0] != 'w')
      L_rotate(2);
    else {
      while (plane[1].cells[1][0] == 'w')
        D_rotate(1);
      L_rotate(2);
    }
  }

  if (plane[4].cells[1][2] == 'w') {
    if (plane[1].cells[1][2] != 'w')
      R_rotate(2);
    else {
      while (plane[1].cells[1][2] == 'w')
        D_rotate(1);
      R_rotate(2);
    }
  }
}

void cube::build_white_cross() {
  if (check_cross(4, 'w') and plane[0].cells[0][1] == 'g' and
      plane[2].cells[0][1] == 'o' and plane[3].cells[0][1] == 'r' and
      plane[5].cells[0][1] == 'b')
    return;
  while (!check_cross(1, 'w')) {
    // Проверяем средний слой на наличие белых рёбер
    move_mid_edges();
    // Проверяем верхний и нижний слои на наличие белых рёбер
    move_ud_edges();
    // Проверяем обратную сторону на наличие белых рёбер
    move_bot_edges();
  }
  // Совместили зелёно-белое ребро и зелёный центр
  while (plane[0].cells[2][1] != 'g' or plane[1].cells[0][1] != 'w')
    D_rotate(1);
  F_rotate(2);

  // Совместили красно-белое ребро и красный центр
  while (plane[3].cells[2][1] != 'r' or plane[1].cells[1][2] != 'w')
    D_rotate(1);
  R_rotate(2);

  // Совместили сине-белое ребро и синий центр
  while (plane[5].cells[2][1] != 'b' or plane[1].cells[2][1] != 'w')
    D_rotate(1);
  B_rotate(2);

  // Совместили оранжево-белое ребро и оранжевый центр
  while (plane[2].cells[2][1] != 'o' or plane[1].cells[1][0] != 'w')
    D_rotate(1);
  L_rotate(2);
}

bool cube::check_corner(const int &corner_ind) const {

  if (corner_ind == 0) // белый/синий/оранжевый
    return (plane[4].cells[0][0] == 'w' and plane[5].cells[0][2] == 'b' and
            plane[2].cells[0][0] == 'o');

  else if (corner_ind == 1) // белый/синий/красный
    return (plane[4].cells[0][2] == 'w' and plane[5].cells[0][0] == 'b' and
            plane[3].cells[0][2] == 'r');

  else if (corner_ind == 2) // белый/зелёный/красный
    return (plane[4].cells[2][2] == 'w' and plane[0].cells[0][2] == 'g' and
            plane[3].cells[0][0] == 'r');

  else // белый/зелёный/оранжевый
    return (plane[4].cells[2][0] == 'w' and plane[0].cells[0][0] == 'g' and
            plane[2].cells[0][2] == 'o');
}

bool cube::corner_has_color(const int &ind, const char &color) const {
  if (ind == 4) {
    return (plane[1].cells[0][0] == color or plane[0].cells[2][0] == color or
            plane[2].cells[2][2] == color);
  } else if (ind == 5) {
    return (plane[1].cells[0][2] == color or plane[0].cells[2][2] == color or
            plane[3].cells[2][0] == color);
  } else if (ind == 6) {
    return (plane[1].cells[2][2] == color or plane[5].cells[2][0] == color or
            plane[3].cells[2][2] == color);
  } else {
    return (plane[1].cells[2][0] == color or plane[5].cells[2][2] == color or
            plane[2].cells[2][0] == color);
  }
}

void cube::move_up_corners() {
  // Белый цвет в углу №4
  if (corner_has_color(4, 'w')) {
    if (corner_has_color(4, 'g') and corner_has_color(4, 'o'))
      while (!check_corner(3))
        right_usd_combo(0);
    else {
      D_rotate(1);
      if (corner_has_color(5, 'g') and corner_has_color(5, 'r'))
        while (!check_corner(2))
          right_usd_combo(3);
      else {
        D_rotate(1);
        if (corner_has_color(6, 'r') and corner_has_color(6, 'b'))
          while (!check_corner(1))
            right_usd_combo(5);
        else {
          D_rotate(1);
          if (corner_has_color(7, 'o') and corner_has_color(7, 'b'))
            while (!check_corner(0))
              right_usd_combo(2);
        }
      }
    }
  }
  // Белый цвет в углу №5
  else if (corner_has_color(5, 'w')) {
    if (corner_has_color(5, 'g') and corner_has_color(5, 'r'))
      while (!check_corner(2))
        right_usd_combo(3);
    else {
      D_rotate(1);
      if (corner_has_color(6, 'r') and corner_has_color(6, 'b'))
        while (!check_corner(1))
          right_usd_combo(5);
      else {
        D_rotate(1);
        if (corner_has_color(7, 'o') and corner_has_color(7, 'b'))
          while (!check_corner(0))
            right_usd_combo(2);
        else {
          D_rotate(1);
          if (corner_has_color(4, 'g') and corner_has_color(4, 'o'))
            while (!check_corner(3))
              right_usd_combo(0);
        }
      }
    }
  }
  // Белый цвет в углу №6
  else if (corner_has_color(6, 'w')) {
    if (corner_has_color(6, 'r') and corner_has_color(6, 'b'))
      while (!check_corner(1))
        right_usd_combo(5);
    else {
      D_rotate(1);
      if (corner_has_color(7, 'o') and corner_has_color(7, 'b'))
        while (!check_corner(0))
          right_usd_combo(2);
      else {
        D_rotate(1);
        if (corner_has_color(4, 'g') and corner_has_color(4, 'o'))
          while (!check_corner(3))
            right_usd_combo(0);
        else {
          D_rotate(1);
          if (corner_has_color(5, 'g') and corner_has_color(5, 'r'))
            while (!check_corner(2))
              right_usd_combo(3);
        }
      }
    }
  }
  // Белый цвет в углу №7
  else if (corner_has_color(7, 'w')) {
    if (corner_has_color(7, 'o') and corner_has_color(7, 'b'))
      while (!check_corner(0))
        right_usd_combo(2);
    else {
      D_rotate(1);
      if (corner_has_color(4, 'g') and corner_has_color(4, 'o'))
        while (!check_corner(3))
          right_usd_combo(0);
      else {
        D_rotate(1);
        if (corner_has_color(5, 'g') and corner_has_color(5, 'r'))
          while (!check_corner(2))
            right_usd_combo(3);
        else {
          D_rotate(1);
          if (corner_has_color(6, 'r') and corner_has_color(6, 'b'))
            while (!check_corner(1))
              right_usd_combo(5);
        }
      }
    }
  }
}

void cube::move_sbot_corners() {
  if (plane[2].cells[0][0] == 'w' or plane[5].cells[0][2] == 'w')
    right_usd_combo(2);

  else if (plane[0].cells[0][0] == 'w' or plane[2].cells[0][2] == 'w')
    right_usd_combo(0);

  else if (plane[3].cells[0][0] == 'w' or plane[0].cells[0][2] == 'w')
    right_usd_combo(3);

  else if (plane[5].cells[0][0] == 'w' or plane[3].cells[0][2] == 'w')
    right_usd_combo(5);
}

void cube::move_bot_corners() {
  if (plane[4].check()) {
    if (!check_corner(0))
      right_usd_combo(2);
    else if (!check_corner(1))
      right_usd_combo(5);
    else if (!check_corner(2))
      right_usd_combo(3);
    else if (!check_corner(3))
      right_usd_combo(0);
  }
}

void cube::build_white_layer() {
  while (!(plane[4].check() and check_corner(0) and check_corner(1) and
           check_corner(2) and check_corner(3))) {
    move_up_corners();
    move_sbot_corners();
    move_bot_corners();
  }
}

void cube::r_diagonal_move(const int &plane_ind) {
  D_rotate(1);
  right_usd_combo(plane_ind);
  switch (plane_ind) {
  case 0:
    left_usd_combo(2);
    break;
  case 2:
    left_usd_combo(5);
    break;
  case 5:
    left_usd_combo(3);
    break;
  case 3:
    left_usd_combo(0);
    break;
  }
}

void cube::l_diagonal_move(const int &plane_ind) {
  Db_rotate(1);
  left_usd_combo(plane_ind);
  switch (plane_ind) {
  case 0:
    right_usd_combo(3);
    break;
  case 3:
    right_usd_combo(5);
    break;
  case 5:
    right_usd_combo(2);
    break;
  case 2:
    right_usd_combo(0);
    break;
  }
}

bool cube::check_mid_layer() const {
  return (plane[0].check_mid_row() and plane[2].check_mid_row() and
          plane[5].check_mid_row() and plane[3].check_mid_row());
}

void cube::get_top_edges() {
  if ((plane[1].cells[0][1] == 'y' or plane[0].cells[2][1] == 'y') and
      (plane[1].cells[1][2] == 'y' or plane[3].cells[2][1] == 'y') and
      (plane[1].cells[2][1] == 'y' or plane[5].cells[2][1] == 'y') and
      (plane[1].cells[1][0] == 'y' or plane[2].cells[2][1] == 'y'))
    if (plane[0].cells[1][0] != 'g' and plane[2].cells[1][2] != 'o')
      r_diagonal_move(0);
    else if (plane[3].cells[1][0] != 'r' and plane[0].cells[1][2] != 'g')
      r_diagonal_move(3);
    else if (plane[5].cells[1][0] != 'b' and plane[3].cells[1][2] != 'r')
      r_diagonal_move(5);
    else if (plane[2].cells[1][0] != 'o' and plane[5].cells[1][2] != 'b')
      r_diagonal_move(2);
}

void cube::move_top_edges() {
  // Проверка первого угла
  if (plane[1].cells[0][1] != 'y' and plane[0].cells[2][1] != 'y') {
    if (plane[0].cells[2][1] == 'g')
      if (plane[1].cells[0][1] == 'o')
        r_diagonal_move(0);
      else
        l_diagonal_move(0);
    else {
      D_rotate(1);
      if (plane[3].cells[2][1] == 'r')
        if (plane[1].cells[1][2] == 'g')
          r_diagonal_move(3);
        else
          l_diagonal_move(3);
      else {
        D_rotate(1);
        if (plane[5].cells[2][1] == 'b')
          if (plane[1].cells[2][1] == 'r')
            r_diagonal_move(5);
          else
            l_diagonal_move(5);
        else {
          D_rotate(1);
          if (plane[2].cells[2][1] == 'o')
            if (plane[1].cells[1][0] == 'b')
              r_diagonal_move(2);
            else
              l_diagonal_move(2);
        }
      }
    }
  }
  // Проверка второго угла
  else if (plane[1].cells[1][2] != 'y' and plane[3].cells[2][1] != 'y') {
    if (plane[3].cells[2][1] == 'r')
      if (plane[1].cells[1][2] == 'g')
        r_diagonal_move(3);
      else
        l_diagonal_move(3);
    else {
      D_rotate(1);
      if (plane[5].cells[2][1] == 'b')
        if (plane[1].cells[2][1] == 'r')
          r_diagonal_move(5);
        else
          l_diagonal_move(5);
      else {
        D_rotate(1);
        if (plane[2].cells[2][1] == 'o')
          if (plane[1].cells[1][0] == 'b')
            r_diagonal_move(2);
          else
            l_diagonal_move(2);
        else {
          D_rotate(1);
          if (plane[0].cells[2][1] == 'g')
            if (plane[1].cells[0][1] == 'o')
              r_diagonal_move(0);
            else
              l_diagonal_move(0);
        }
      }
    }
  }
  // Проверка третьего угла
  else if (plane[1].cells[2][1] != 'y' and plane[5].cells[2][1] != 'y') {
    if (plane[5].cells[2][1] == 'b')
      if (plane[1].cells[2][1] == 'r')
        r_diagonal_move(5);
      else
        l_diagonal_move(5);
    else {
      D_rotate(1);
      if (plane[2].cells[2][1] == 'o')
        if (plane[1].cells[1][0] == 'b')
          r_diagonal_move(2);
        else
          l_diagonal_move(2);
      else {
        D_rotate(1);
        if (plane[0].cells[2][1] == 'g')
          if (plane[1].cells[0][1] == 'o')
            r_diagonal_move(0);
          else
            l_diagonal_move(0);
        else {
          D_rotate(1);
          if (plane[3].cells[2][1] == 'r')
            if (plane[1].cells[1][2] == 'g')
              r_diagonal_move(3);
            else
              l_diagonal_move(3);
        }
      }
    }
  }
  // Проверка четвёртого угла
  else if (plane[1].cells[1][0] != 'y' and plane[2].cells[2][1] != 'y') {
    if (plane[2].cells[2][1] == 'o')
      if (plane[1].cells[1][0] == 'b')
        r_diagonal_move(2);
      else
        l_diagonal_move(2);
    else {
      D_rotate(1);
      if (plane[0].cells[2][1] == 'g')
        if (plane[1].cells[0][1] == 'o')
          r_diagonal_move(0);
        else
          l_diagonal_move(0);
      else {
        D_rotate(1);
        if (plane[3].cells[2][1] == 'r')
          if (plane[1].cells[1][2] == 'g')
            r_diagonal_move(3);
          else
            l_diagonal_move(3);
        else {
          D_rotate(1);
          if (plane[5].cells[2][1] == 'b')
            if (plane[1].cells[2][1] == 'r')
              r_diagonal_move(5);
            else
              l_diagonal_move(5);
        }
      }
    }
  }
}

void cube::build_mid_layer() {
  while (!check_mid_layer()) {
    get_top_edges();
    move_top_edges();
  }
}

void cube::if_line() {
  if (plane[1].cells[1][0] == 'y' and plane[1].cells[1][2] == 'y') {
    F_rotate(1);
    right_usd_combo(0);
    Fb_rotate(1);
  } else if (plane[1].cells[0][1] == 'y' and plane[1].cells[2][1] == 'y') {
    D_rotate(1);
    F_rotate(1);
    right_usd_combo(0);
    Fb_rotate(1);
  }
}

void cube::if_angle() {
  if (!check_cross(1, 'y'))
    if (plane[1].cells[1][0] == 'y' and plane[1].cells[0][1] == 'y') {
      B_rotate(1);
      right_usd_combo(5);
      right_usd_combo(5);
      Bb_rotate(1);
    } else if (plane[1].cells[0][1] == 'y' and plane[1].cells[1][2] == 'y') {
      Db_rotate(1);
      B_rotate(1);
      right_usd_combo(5);
      right_usd_combo(5);
      Bb_rotate(1);
    } else if (plane[1].cells[1][2] == 'y' and plane[1].cells[2][1] == 'y') {
      D_rotate(2);
      B_rotate(1);
      right_usd_combo(5);
      right_usd_combo(5);
      Bb_rotate(1);
    } else if (plane[1].cells[2][1] == 'y' and plane[1].cells[1][0] == 'y') {
      D_rotate(1);
      B_rotate(1);
      right_usd_combo(5);
      right_usd_combo(5);
      Bb_rotate(1);
    }
}

void cube::if_dot() {
  if (!check_cross(1, 'y'))
    if (plane[1].cells[0][1] != 'y' and plane[1].cells[1][2] != 'y' and
        plane[1].cells[2][1] != 'y' and plane[1].cells[1][0] != 'y') {
      B_rotate(1);
      right_usd_combo(5);
      right_usd_combo(5);
      Bb_rotate(1);
      if_line();
    }
}

void cube::build_yellow_cross() {
  if (check_cross(1, 'y'))
    return;
  if_line();
  if_angle();
  if_dot();
}

int cube::corners_matched() const {
  int ans = 0;
  if (corner_has_color(4, 'y') and corner_has_color(4, 'g') and
      corner_has_color(4, 'o'))
    ans++;
  if (corner_has_color(5, 'y') and corner_has_color(5, 'g') and
      corner_has_color(5, 'r'))
    ans++;
  if (corner_has_color(6, 'y') and corner_has_color(6, 'b') and
      corner_has_color(6, 'r'))
    ans++;
  if (corner_has_color(7, 'y') and corner_has_color(7, 'b') and
      corner_has_color(7, 'o'))
    ans++;
  return ans;
}

void cube::line_corners() {
  if ((corner_has_color(5, 'y') and corner_has_color(5, 'g') and
       corner_has_color(5, 'r')) and
      (corner_has_color(6, 'y') and corner_has_color(6, 'b') and
       corner_has_color(6, 'r'))) {
    right_usd_combo(0);
    right_usd_combo(0);
    right_usd_combo(0);
    left_usd_combo(2);
    left_usd_combo(2);
    left_usd_combo(2);
    while (corners_matched() < 2)
      D_rotate(1);
  } else if ((corner_has_color(6, 'y') and corner_has_color(6, 'b') and
              corner_has_color(6, 'r')) and
             (corner_has_color(7, 'y') and corner_has_color(7, 'b') and
              corner_has_color(7, 'o'))) {
    right_usd_combo(3);
    right_usd_combo(3);
    right_usd_combo(3);
    left_usd_combo(0);
    left_usd_combo(0);
    left_usd_combo(0);
    while (corners_matched() < 2)
      D_rotate(1);
  } else if ((corner_has_color(7, 'y') and corner_has_color(7, 'b') and
              corner_has_color(7, 'o')) and
             (corner_has_color(4, 'y') and corner_has_color(4, 'g') and
              corner_has_color(4, 'o'))) {
    right_usd_combo(5);
    right_usd_combo(5);
    right_usd_combo(5);
    left_usd_combo(3);
    left_usd_combo(3);
    left_usd_combo(3);
    while (corners_matched() < 2)
      D_rotate(1);
  } else if ((corner_has_color(4, 'y') and corner_has_color(4, 'g') and
              corner_has_color(4, 'o')) and
             (corner_has_color(5, 'y') and corner_has_color(5, 'g') and
              corner_has_color(5, 'r'))) {
    right_usd_combo(2);
    right_usd_combo(2);
    right_usd_combo(2);
    left_usd_combo(5);
    left_usd_combo(5);
    left_usd_combo(5);
    while (corners_matched() < 2)
      D_rotate(1);
  }
}

void cube::diagonal_corners() {
  if ((corner_has_color(4, 'y') and corner_has_color(4, 'g') and
       corner_has_color(4, 'o')) and
      (corner_has_color(6, 'y') and corner_has_color(6, 'b') and
       corner_has_color(6, 'r'))) {
    right_usd_combo(2);
    right_usd_combo(2);
    right_usd_combo(2);
    left_usd_combo(5);
    left_usd_combo(5);
    left_usd_combo(5);
    while (corners_matched() < 2)
      D_rotate(1);
  } else if ((corner_has_color(5, 'y') and corner_has_color(5, 'g') and
              corner_has_color(5, 'r')) and
             (corner_has_color(7, 'y') and corner_has_color(7, 'b') and
              corner_has_color(7, 'o'))) {
    right_usd_combo(5);
    right_usd_combo(5);
    right_usd_combo(5);
    left_usd_combo(3);
    left_usd_combo(3);
    left_usd_combo(3);
    while (corners_matched() < 2)
      D_rotate(1);
  }
}

void cube::match_corners() {
  while (corners_matched() < 2)
    D_rotate(1);
  diagonal_corners();
  line_corners();
}

void cube::buid_yellow_side() {
  for (int i = 0; i < 4; i++) {
    while (plane[1].cells[0][2] != 'y')
      right_combo(0);
    D_rotate(1);
  }
}

int cube::assembled_sides() const {
  int ans = 0;
  ans += plane[0].check();
  ans += plane[2].check();
  ans += plane[3].check();
  ans += plane[5].check();
  return ans;
}

void cube::match_edges() {
  if (assembled_sides() == 4)
    return;
  else if (assembled_sides() == 1) {
    if (plane[0].check())
      while (!done()) {
        right_usd_combo(0);
        left_usd_combo(0);
        right_usd_combo(0);
        right_usd_combo(0);
        right_usd_combo(0);
        right_usd_combo(0);
        right_usd_combo(0);
        left_usd_combo(0);
        left_usd_combo(0);
        left_usd_combo(0);
        left_usd_combo(0);
        left_usd_combo(0);
      }
    else if (plane[5].check())
      while (!done()) {
        right_usd_combo(5);
        left_usd_combo(5);
        right_usd_combo(5);
        right_usd_combo(5);
        right_usd_combo(5);
        right_usd_combo(5);
        right_usd_combo(5);
        left_usd_combo(5);
        left_usd_combo(5);
        left_usd_combo(5);
        left_usd_combo(5);
        left_usd_combo(5);
      }
    else if (plane[2].check())
      while (!done()) {
        right_usd_combo(2);
        left_usd_combo(2);
        right_usd_combo(2);
        right_usd_combo(2);
        right_usd_combo(2);
        right_usd_combo(2);
        right_usd_combo(2);
        left_usd_combo(2);
        left_usd_combo(2);
        left_usd_combo(2);
        left_usd_combo(2);
        left_usd_combo(2);
      }
    else if (plane[3].check())
      while (!done()) {
        right_usd_combo(3);
        left_usd_combo(3);
        right_usd_combo(3);
        right_usd_combo(3);
        right_usd_combo(3);
        right_usd_combo(3);
        right_usd_combo(3);
        left_usd_combo(3);
        left_usd_combo(3);
        left_usd_combo(3);
        left_usd_combo(3);
        left_usd_combo(3);
      }
  } else if (assembled_sides() == 0) {
    right_usd_combo(3);
    left_usd_combo(3);
    right_usd_combo(3);
    right_usd_combo(3);
    right_usd_combo(3);
    right_usd_combo(3);
    right_usd_combo(3);
    left_usd_combo(3);
    left_usd_combo(3);
    left_usd_combo(3);
    left_usd_combo(3);
    left_usd_combo(3);
    match_edges();
  }
}

void cube::assemble() {
  if (done())
    return;
  enable_hint = true;
  hint.clear();
  build_white_cross();
  build_white_layer();
  build_mid_layer();
  build_yellow_cross();
  match_corners();
  buid_yellow_side();
  match_edges();
  enable_hint = false;
}

void cube::save_hint() const {
  std::ofstream fout("hint.txt");
  fout << "Можно решить всего лишь за: " << hint.size() << " хода\n";
  for (auto command : hint)
    fout << command;
  fout.close();
}

void cube::load() {
  std::ifstream fin("saved_config.txt");

  for (int plane_ind = 0; plane_ind < 6; plane_ind++)
    for (int i = 0; i < 3; i++)
      for (int j = 0; j < 3; j++)
        fin >> plane[plane_ind].cells[i][j];

  fin.close();
}
