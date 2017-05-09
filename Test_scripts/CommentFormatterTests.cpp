#include <gtest\gtest.h>
#include "CommentFormatter.h"


TEST(CommentFormatterTesting, IsSortedCommentReply)
{
	std::vector<Comment> col1;
	std::vector<Comment> col2;

	CommentFormatter frm;

	col1.push_back(Comment("text 1", "1aa", "t3_a", false, 0.0, "user1"));
	col1.push_back(Comment("text 2", "2bb", "t3_1aa", true, 0.0, "user2"));
	col1.push_back(Comment("text 3", "3cc", "t3_2bb", true, 0.0, "user3"));
	col1.push_back(Comment("text 4", "4dd", "t3_1aa", true, 0.0, "user4"));
	col1.push_back(Comment("text 5", "5ee", "t3_4dd", true, 0.0, "user5"));

	col2.push_back(Comment("text 1", "1aa", "t3_a", false, 0.0, "user1"));
	col2.push_back(Comment("text 2", "2bb", "t3_1aa", true, 0.0, "user2"));
	col2.push_back(Comment("text 4", "4dd", "t3_1aa", true, 0.0, "user4"));
	col2.push_back(Comment("text 5", "5ee", "t3_4dd", true, 0.0, "user5"));
	col2.push_back(Comment("text 3", "3cc", "t3_2bb", true, 0.0, "user3"));


	std::vector<Comment> empty;

	col2 = frm.sortCommentList(col2[0], col2, empty, col2.size());
	ASSERT_EQ(col1, col2);
}