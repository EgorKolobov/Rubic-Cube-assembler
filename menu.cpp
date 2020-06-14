#include "menu.h"
#include "rubic.h"
#include <fstream>
#include <iostream>
menu::menu() {}

void menu::turn_on() {
  int user = -1;
  cube rubic;
  std::cout << D_GREEN << "___________________ МЕНЮ _______________\n";
  std::cout << CYAN << "Создать случайную конфигурацию кубика: 1\n";
  std::cout << "Выбрать активную грань: 2\n";
  std::cout << "Показать кубик: 3\n";
  std::cout << "Собрать кубик: 4\n";
  std::cout << "Сохранить конфигурацию в файл: 5\n";
  std::cout << D_RED << "Выход: 0" << RESET << "\n";
  std::cin >> user;
  while (user != 0) {
    switch (user) {
    case 1:
      rubic.randomize();
      rubic.write();
      break;

    case 2:
      std::cout << CYAN << "Укажите цвет грани или 0 для выхода: ";
      char color;
      std::cin >> color;
      while (!(color == 'g' or color == 'b' or color == 'o' or color == 'r' or
               color == 'w' or color == 'y' or color == '0')) {
        std::cout << "Такого цвета нет! Выберите любой из " << GREEN << "g "
                  << BLUE << "b " << RED << "r " << ORANGE << "o " << WHITE
                  << "w " << YELLOW << "y\n"
                  << CYAN;
        std::cin >> color;
      }

      switch (color) {
      case 'g':
        std::cout << CYAN << "Повернуть правую сторону по часовой: 1\n";
        std::cout << "Повернуть правую сторону против часовой: 2\n";
        std::cout << "Повернуть левую сторону по часовой: 3\n";
        std::cout << "Повернуть левую сторону против часовой: 4\n";
        std::cout << "Повернуть верхнюю сторону по часовой: 5\n";
        std::cout << "Повернуть верхнюю сторону против часовой: 6\n";
        std::cout << "Повернуть нижнюю сторону по часовой: 7\n";
        std::cout << "Повернуть нижнюю сторону против часовой: 8\n";
        std::cout << D_RED << "Назад: 0\n" << RESET;
        std::cin >> user;
        while (user != 0) {
          switch (user) {
          case 1:
            rubic.R_rotate(1);
            rubic.write();
            break;
          case 2:
            rubic.Rb_rotate(1);
            rubic.write();
            break;
          case 3:
            rubic.L_rotate(1);
            rubic.write();
            break;
          case 4:
            rubic.Lb_rotate(1);
            rubic.write();
            break;
          case 5:
            rubic.U_rotate(1);
            rubic.write();
            break;
          case 6:
            rubic.Ub_rotate(1);
            rubic.write();
            break;
          case 7:
            rubic.D_rotate(1);
            rubic.write();
            break;
          case 8:
            rubic.Db_rotate(1);
            rubic.write();
            break;
          }
          std::cin >> user;
        }
        break;
      case 'b':
        std::cout << CYAN << "Повернуть правую сторону по часовой: 1\n";
        std::cout << "Повернуть правую сторону против часовой: 2\n";
        std::cout << "Повернуть левую сторону по часовой: 3\n";
        std::cout << "Повернуть левую сторону против часовой: 4\n";
        std::cout << "Повернуть верхнюю сторону по часовой: 5\n";
        std::cout << "Повернуть верхнюю сторону против часовой: 6\n";
        std::cout << "Повернуть нижнюю сторону по часовой: 7\n";
        std::cout << "Повернуть нижнюю сторону против часовой: 8\n";
        std::cout << D_RED << "Назад: 0\n" << RESET;
        std::cin >> user;
        while (user != 0) {
          switch (user) {
          case 1:
            rubic.L_rotate(1);
            rubic.write();
            break;
          case 2:
            rubic.Lb_rotate(1);
            rubic.write();
            break;
          case 3:
            rubic.R_rotate(1);
            rubic.write();
            break;
          case 4:
            rubic.Rb_rotate(1);
            rubic.write();
            break;
          case 5:
            rubic.U_rotate(1);
            rubic.write();
            break;
          case 6:
            rubic.Ub_rotate(1);
            rubic.write();
            break;
          case 7:
            rubic.D_rotate(1);
            rubic.write();
            break;
          case 8:
            rubic.Db_rotate(1);
            rubic.write();
            break;
          }
          std::cin >> user;
        }

        break;
      case 'r':
        std::cout << CYAN << "Повернуть правую сторону по часовой: 1\n";
        std::cout << "Повернуть правую сторону против часовой: 2\n";
        std::cout << "Повернуть левую сторону по часовой: 3\n";
        std::cout << "Повернуть левую сторону против часовой: 4\n";
        std::cout << "Повернуть верхнюю сторону по часовой: 5\n";
        std::cout << "Повернуть верхнюю сторону против часовой: 6\n";
        std::cout << "Повернуть нижнюю сторону по часовой: 7\n";
        std::cout << "Повернуть нижнюю сторону против часовой: 8\n";
        std::cout << D_RED << "Назад: 0\n" << RESET;
        std::cin >> user;
        while (user != 0) {
          switch (user) {
          case 1:
            rubic.B_rotate(1);
            rubic.write();
            break;
          case 2:
            rubic.Bb_rotate(1);
            rubic.write();
            break;
          case 3:
            rubic.F_rotate(1);
            rubic.write();
            break;
          case 4:
            rubic.Fb_rotate(1);
            rubic.write();
            break;
          case 5:
            rubic.U_rotate(1);
            rubic.write();
            break;
          case 6:
            rubic.Ub_rotate(1);
            rubic.write();
            break;
          case 7:
            rubic.D_rotate(1);
            rubic.write();
            break;
          case 8:
            rubic.Db_rotate(1);
            rubic.write();
            break;
          }
          std::cin >> user;
        }

        break;
      case 'o':
        std::cout << CYAN << "Повернуть правую сторону по часовой: 1\n";
        std::cout << "Повернуть правую сторону против часовой: 2\n";
        std::cout << "Повернуть левую сторону по часовой: 3\n";
        std::cout << "Повернуть левую сторону против часовой: 4\n";
        std::cout << "Повернуть верхнюю сторону по часовой: 5\n";
        std::cout << "Повернуть верхнюю сторону против часовой: 6\n";
        std::cout << "Повернуть нижнюю сторону по часовой: 7\n";
        std::cout << "Повернуть нижнюю сторону против часовой: 8\n";
        std::cout << D_RED << "Назад: 0\n" << RESET;
        std::cin >> user;
        while (user != 0) {
          switch (user) {
          case 1:
            rubic.F_rotate(1);
            rubic.write();
            break;
          case 2:
            rubic.Fb_rotate(1);
            rubic.write();
            break;
          case 3:
            rubic.B_rotate(1);
            rubic.write();
            break;
          case 4:
            rubic.Bb_rotate(1);
            rubic.write();
            break;
          case 5:
            rubic.U_rotate(1);
            rubic.write();
            break;
          case 6:
            rubic.Ub_rotate(1);
            rubic.write();
            break;
          case 7:
            rubic.D_rotate(1);
            rubic.write();
            break;
          case 8:
            rubic.Db_rotate(1);
            rubic.write();
            break;
          }
          std::cin >> user;
        }

        break;
      case 'w':
        std::cout << CYAN << "Повернуть правую сторону по часовой: 1\n";
        std::cout << "Повернуть правую сторону против часовой: 2\n";
        std::cout << "Повернуть левую сторону по часовой: 3\n";
        std::cout << "Повернуть левую сторону против часовой: 4\n";
        std::cout << "Повернуть верхнюю сторону по часовой: 5\n";
        std::cout << "Повернуть верхнюю сторону против часовой: 6\n";
        std::cout << "Повернуть нижнюю сторону по часовой: 7\n";
        std::cout << "Повернуть нижнюю сторону против часовой: 8\n";
        std::cout << D_RED << "Назад: 0\n" << RESET;
        std::cin >> user;
        while (user != 0) {
          switch (user) {
          case 1:
            rubic.R_rotate(1);
            rubic.write();
            break;
          case 2:
            rubic.Rb_rotate(1);
            rubic.write();
            break;
          case 3:
            rubic.L_rotate(1);
            rubic.write();
            break;
          case 4:
            rubic.Lb_rotate(1);
            rubic.write();
            break;
          case 5:
            rubic.B_rotate(1);
            rubic.write();
            break;
          case 6:
            rubic.Bb_rotate(1);
            rubic.write();
            break;
          case 7:
            rubic.F_rotate(1);
            rubic.write();
            break;
          case 8:
            rubic.Fb_rotate(1);
            rubic.write();
            break;
          }
          std::cin >> user;
        }

        break;
      case 'y':
        std::cout << CYAN << "Повернуть правую сторону по часовой: 1\n";
        std::cout << "Повернуть правую сторону против часовой: 2\n";
        std::cout << "Повернуть левую сторону по часовой: 3\n";
        std::cout << "Повернуть левую сторону против часовой: 4\n";
        std::cout << "Повернуть верхнюю сторону по часовой: 5\n";
        std::cout << "Повернуть верхнюю сторону против часовой: 6\n";
        std::cout << "Повернуть нижнюю сторону по часовой: 7\n";
        std::cout << "Повернуть нижнюю сторону против часовой: 8\n";
        std::cout << D_RED << "Назад: 0\n" << RESET;
        std::cin >> user;
        while (user != 0) {
          switch (user) {
          case 1:
            rubic.R_rotate(1);
            rubic.write();
            break;
          case 2:
            rubic.Rb_rotate(1);
            rubic.write();
            break;
          case 3:
            rubic.L_rotate(1);
            rubic.write();
            break;
          case 4:
            rubic.Lb_rotate(1);
            rubic.write();
            break;
          case 5:
            rubic.F_rotate(1);
            rubic.write();
            break;
          case 6:
            rubic.Fb_rotate(1);
            rubic.write();
            break;
          case 7:
            rubic.B_rotate(1);
            rubic.write();
            break;
          case 8:
            rubic.Bb_rotate(1);
            rubic.write();
            break;
          }
          std::cin >> user;
        }

        break;
      } // switch(color)
      break;

    case 3:
      rubic.write();
      break;
    case 4:
      rubic.assemble();
      rubic.write();
      rubic.save_hint();
      break;
    case 5:
      rubic.load();
      rubic.write();
      break;
    case 6:
      std::ofstream fout("saved_config.txt");
      rubic.write(fout, false);
      fout.close();
      break;
    }
    std::cout << D_GREEN << "___________________ МЕНЮ _______________\n";
    std::cout << CYAN << "Создать случайную конфигурацию кубика: 1\n";
    std::cout << "Выбрать активную грань: 2\n";
    std::cout << "Показать кубик: 3\n";
    std::cout << "Собрать кубик: 4\n";
    std::cout << "Считать конфигурацию из файла: 5\n";
    std::cout << "Сохранить конфигурацию в файл: 6\n";
    std::cout << D_RED << "Выход: 0" << RESET << "\n";
    std::cin >> user;
  }
}
