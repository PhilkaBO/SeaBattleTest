#include "gtest/gtest.h"
#include "Ships.h"

/*���� �� ������������ ���-� ��������
* �� �������� �������� ��������� ������ 4 ������������ �������
* ������� ������� 5-�� ������������
* ����� �������� ������ ������� false
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

/*���� �� ������� ������� �������
* ������������ ����� ������� ���������� 4 ������
* ������� ��������� ������� � 5-� ��������
* ����� �������� ������ ������� false
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

/*�������� �� "�������������" �������
* ������� �� ������ ����� ������� � ���� ������ ������
* ����� �������� ���������� false
*/

TEST(CheckShipsTest, TornShip) {
	Ships shipsTest;
	shipsTest.SetCoord(0, 0, 0);
	shipsTest.SetCoord(0, 1, 0);
	shipsTest.SetCoord(0, 3, 0);
	shipsTest.SetCoord(0, 4, 0);

	EXPECT_EQ(shipsTest.CheckShip(0), 0);
}

/*��������� ���� ��������� ������� ������� �� ��������� 
* ����� �������� ������ ������� false
*/
TEST(CheckShipsTest, DiagonalShip) {
	Ships shipsTest;
	shipsTest.SetCoord(0, 0, 0);
	shipsTest.SetCoord(0, 1, 1);
	shipsTest.SetCoord(0, 2, 2);
	shipsTest.SetCoord(0, 3, 3);

	EXPECT_EQ(shipsTest.CheckShip(0), 0);
}

/*"��������" �������
* �������, � �������, ������ "�" �� ����� ���� ��������� �� ����
* ����� �������� ������ ������ false
*/
TEST(CheckShipsTest, FoldedShip) {
	Ships shipsTest;
	shipsTest.SetCoord(0, 5, 5);
	shipsTest.SetCoord(0, 5, 4);
	shipsTest.SetCoord(0, 5, 3);
	shipsTest.SetCoord(0, 4, 3);

	EXPECT_EQ(shipsTest.CheckShip(0), 0);
}

/*������� �������� �������� ������ ����
* ���������� ���-�� ��������
* ��������� �������� � ������� ��� ����:
* ������������ � �����������
* ����� ������ ���-�� ����� ��������
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

/*���� � ����� �������� ��� ������� 0
* �� �� ������ 0
* ��� ��� ��� ������ ������� � ����������� 0
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

/*��������� ��� 5
* ������ 0, ��� ��� ��� ��������  ������������ 5
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

/*����� ���� ������ ���������� ����� ��������
* ���� �� ������� �� �� ���������� ����� ������� 
* � ����� ������������
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

/*��� ����������� ����������� ���������, ���������� -1,
* ��� ��� �� ������ ������ ����������
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

/*� ������ ���� ���������� �� �������
* ���������� -1
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