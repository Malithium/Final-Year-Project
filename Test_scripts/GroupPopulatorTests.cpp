#include <gtest\gtest.h>
#include "GroupPopulator.h"
#include "JSONReader.h"

TEST(GroupPopulatorTesting, AreCommentsEqual)
{
	Group grp1;
	Group grp2;

	Comment com1("test body 1", "1", "0", false, 0.1, "user1");
	Comment com2("test body 2", "2", "1", true, 0.2, "user2");
	Comment com3("test body 3", "3", "2", true, -0.3, "user3");

	std::vector<Comment> comsCol;

	comsCol.push_back(com1);
	comsCol.push_back(com2);
	comsCol.push_back(com3);

	std::vector<Topic> tops;

	Topic top("1", "Test topic", comsCol);

	tops.push_back(top);

	grp1 = Group("testSub", tops);

	JSONReader reader("test.json");

	GroupPopulator populator(reader.ReadJsonFile());
	grp2 = populator.PopulateGroup();
	ASSERT_EQ(grp1, grp2);
}