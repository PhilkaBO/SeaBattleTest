#include "gtest/gtest.h"
#include "Ships.h"

/*Тест на недопустимое кол-в кораблей
* По правилам возможно поставить только 4 однопалубных корабля
* пробуем ставить 5-ый однопалубный
* метод проверки должен вернуть false
*/

TEST(CheckShipsTest, NumberOfShips) {
	Ships shipsTest;
	shipsTest.SetCoord(0, 0, 0);
	shipsTest.SetCoord(1, 2, 2);
	shipsTest.SetCoord(2, 4, 4);
	shipsTest.SetCoord(3, 6, 6);
	shipsTest.SetCoord(4, 8, 8);

  EXPECT_EQ(shipsTest.CheckShip(4), 0);
}

/*Тест на слишком длинный корабль
* максимальная длина корабля составляет 4 клетки
* пробуем поставить корабль с 5-ю палубами
* метод проверки должен вернуть false
*/
TEST(CheckShipsTest, BigShip) {
	Ships shipsTest;
	shipsTest.SetCoord(0, 0, 0);
	shipsTest.SetCoord(0, 1, 0);
	shipsTest.SetCoord(0, 2, 0);
	shipsTest.SetCoord(0, 3, 0);
	shipsTest.SetCoord(0, 4, 0);

	EXPECT_EQ(shipsTest.CheckShip(0), 0);
}

/*Проверка на "разорванность" корабля
* Корабль не должен иметь разрыва в виде пустой клетки
* Метод проверки возвращает false
*/

TEST(CheckShipsTest, TornShip) {
	Ships shipsTest;
	shipsTest.SetCoord(0, 0, 0);
	shipsTest.SetCoord(0, 1, 0);
	shipsTest.SetCoord(0, 3, 0);
	shipsTest.SetCoord(0, 4, 0);

	EXPECT_EQ(shipsTest.CheckShip(0), 0);
}

/*Правилами игры запрещено ставить корабль по диагонали 
* Метод проверки должен вернуть false
*/
TEST(CheckShipsTest, DiagonalShip) {
	Ships shipsTest;
	shipsTest.SetCoord(0, 0, 0);
	shipsTest.SetCoord(0, 1, 1);
	shipsTest.SetCoord(0, 2, 2);
	shipsTest.SetCoord(0, 3, 3);

	EXPECT_EQ(shipsTest.CheckShip(0), 0);
}

/*"Загнутый" корабль
* Корабль, к примеру, буквой "Г" не может быть поставлен на поле
* метод проверки должен венуть false
*/
TEST(CheckShipsTest, FoldedShip) {
	Ships shipsTest;
	shipsTest.SetCoord(0, 5, 5);
	shipsTest.SetCoord(0, 5, 4);
	shipsTest.SetCoord(0, 5, 3);
	shipsTest.SetCoord(0, 4, 3);

	EXPECT_EQ(shipsTest.CheckShip(0), 0);
}

/*Функция подсчета кораблей одного типа
* возвращает кол-во кораблей
* Попробуем передать в функцию два типа:
* однопалубный и двупалубный
* метод вернет кол-во таких кораблей
*/
TEST(CheckTypeTest, CheckShips) {
	Ships shipsTest;
	shipsTest.SetCoord(0, 0, 0);
	shipsTest.SetCoord(1, 2, 2);
	shipsTest.SetCoord(2, 4, 4);
	shipsTest.SetCoord(3, 7, 7);

	shipsTest.SetCoord(4, 0, 7);
	shipsTest.SetCoord(4, 0, 8);

	EXPECT_EQ(shipsTest.CheckType(1), 4);
	EXPECT_EQ(shipsTest.CheckType(2), 1);
}

/*Если в метод передать тип корабля 0
* то он вернет 0
* так как нет такого корабля с размерность 0
*/
TEST(CheckTypeTest, ZeroType) {
	Ships shipsTest;
	shipsTest.SetCoord(0, 0, 0);
	shipsTest.SetCoord(1, 2, 2);
	shipsTest.SetCoord(2, 4, 4);
	shipsTest.SetCoord(3, 7, 7);

	shipsTest.SetCoord(4, 0, 7);
	shipsTest.SetCoord(4, 0, 8);

	EXPECT_EQ(shipsTest.CheckType(0), 0);
}

/*Передадим тип 5
* вернет 0, так как нет кораблей  размерностью 5
*/
TEST(CheckTypeTest, IncorrectType) {
	Ships shipsTest;
	shipsTest.SetCoord(0, 0, 0);
	shipsTest.SetCoord(1, 2, 2);
	shipsTest.SetCoord(2, 4, 4);
	shipsTest.SetCoord(3, 7, 7);

	shipsTest.SetCoord(4, 0, 7);
	shipsTest.SetCoord(4, 0, 8);

	EXPECT_EQ(shipsTest.CheckType(5), 0);
}

/*Метод ищет данные координаты среди кораблей
* Если он находит их он возвращает номер корабля 
* с этими координатами
*/

TEST(FindPosTest, CorrectPos) {
	Ships shipsTest;
	shipsTest.SetCoord(0, 0, 0);
	shipsTest.SetCoord(1, 2, 2);
	shipsTest.SetCoord(2, 4, 4);
	shipsTest.SetCoord(3, 7, 7);

	shipsTest.SetCoord(4, 0, 7);
	shipsTest.SetCoord(4, 0, 8);

	EXPECT_EQ(shipsTest.FindPos(2, 2), 1);
}

/*При поступлении некоректных координат, возвращает -1,
* так как не найдет данные координаты
*/
TEST(FindPosTest, IncorrectPos) {
	Ships shipsTest;
	shipsTest.SetCoord(0, 0, 0);
	shipsTest.SetCoord(1, 2, 2);
	shipsTest.SetCoord(2, 4, 4);
	shipsTest.SetCoord(3, 7, 7);

	shipsTest.SetCoord(4, 0, 7);
	shipsTest.SetCoord(4, 0, 8);

	EXPECT_EQ(shipsTest.FindPos(-1, -1), -1);
}

/*В случае если координаты не найдены
* возвращает -1
*/
TEST(FindPosTest, NotFoundPos) {

	Ships shipsTest;
	shipsTest.SetCoord(0, 0, 0);
	shipsTest.SetCoord(1, 2, 2);
	shipsTest.SetCoord(2, 4, 4);
	shipsTest.SetCoord(3, 7, 7);

	shipsTest.SetCoord(4, 0, 7);
	shipsTest.SetCoord(4, 0, 8);

	EXPECT_EQ(shipsTest.FindPos(6, 6), -1);
}