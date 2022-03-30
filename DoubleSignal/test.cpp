//#include "pch.h"
#include "gtest/gtest.h"
#include "DouleSignal.h"
#include <sstream>
#include <ostream>

TEST(DoubleSignal_Constructor, Default_Constructor) {
	DoubleSignal db;
	ASSERT_NO_THROW(db);
}

TEST(DoubleSignal_Constructor, InitialOneSignal_Constructor) {
	DoubleSignal db('1');
	ASSERT_NO_THROW(db);
}

TEST(DoubleSignal_Constructor, InitialString_Constructor) {
	DoubleSignal db("110100");
	ASSERT_NO_THROW(db);
}

TEST(DoubleSignal_Methods, AddSignal) {
	DoubleSignal db("110");
	db.AddSignal('1', 50);
	ASSERT_EQ(53, db.GetCurrentTime());
	ASSERT_EQ(4, db.GetNumberOfElements());
}

TEST(DoubleSignal_Methods, Copy) {
	DoubleSignal db("110");
	db.Copy(3);
	ASSERT_NE(10, db.GetCurrentTime());
	ASSERT_EQ(12, db.GetNumberOfElements());
}

TEST(DoubleSignal_Methods, Reverse) {
	DoubleSignal db("110");
	db.Reverse();
	ASSERT_EQ("001", db.GetString());
}

TEST(DoubleSignal_Methods, AddOtherSignals)
{
	DoubleSignal db("110");
	DoubleSignal db2("000111");
	db += db2;
	ASSERT_EQ("110000111", db.GetString());
	ASSERT_EQ(9, db.GetCurrentTime());
}

TEST(DoubleSignal_Methods, Insert)
{
	DoubleSignal db("110");
	DoubleSignal other("11111");
	db.Insert(other, 2);
	ASSERT_EQ("11111110", db.GetString());
	ASSERT_NO_THROW(db.Insert(other, -10));
	ASSERT_NO_THROW(db.Insert(other, 100));
}

TEST(DoubleSignal_Methods, Delete)
{
	DoubleSignal db("110011");
	ASSERT_ANY_THROW(db.Delete(3, -9));
	ASSERT_ANY_THROW(db.Delete(-3, 9));
	db.Delete(2, 50);
	ASSERT_EQ("11", db.GetString());
}

TEST(DoubleSignal_Methods, Index)
{
	DoubleSignal db("110011");
	ASSERT_NO_THROW(db.operator[](3));
	ASSERT_ANY_THROW(db.operator[](10));
}

TEST(DoubleSignal_Methods, OST)
{
	std::ostringstream os;
	DoubleSignal db("110011");
	os << db;
	ASSERT_EQ("110011", os.str());
}

int main(int argc, char *argv[]) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}