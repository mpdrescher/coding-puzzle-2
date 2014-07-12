#include <vector>
#include <string>
#include <algorithm>
#include <functional>

#include <gtest/gtest.h>
#include <gtest/internal/gtest-internal.h> // for FloatingPoint::AlmostEquals

#include "article.hpp"


#define PRINT
#ifdef PRINT
# include <iostream>
# include <ostream>
#endif

using article::Article;

namespace tests
{
    class ArticleTest : public ::testing::Test
    {
    public:
        virtual void SetUp()
        {
            input_.push_back(Article("AA", 1, 100.00));
            input_.push_back(Article("BB", 1,  50.00));
            input_.push_back(Article("CC", 2,  75.00));
            input_.push_back(Article("AA", 1,  20.00));
            input_.push_back(Article("AA", 0, 100.00));
            input_.push_back(Article("BB", 2,  75.00));
            input_.push_back(Article("CC", 2,  80.00));
            input_.push_back(Article("AA", 0,  20.00));
        }

        std::vector<Article> input_;
    };

    struct CompareArticle : public std::binary_function<Article, Article, bool>
    {
        inline bool operator()(const Article& left, const Article& right) const
        {
            if (left.group == right.group && left.name == right.name)
            {
                typedef ::testing::internal::FloatingPoint<double> DoubleFP;

                const DoubleFP lhs(left.price);
                const DoubleFP rhs(right.price);
                if (lhs.AlmostEquals(rhs))
                {
                    return true;
                }
            }
            return false;
        }
    };

    template <typename T> inline void print(const T& cont, const char* msg)
    {
#ifdef PRINT
        std::cout << msg << std::endl;
        typedef typename T::const_iterator iter;
        for (iter it = cont.begin(); it != cont.end(); ++it)
        {
            std::cout << *it << std::endl;
        }
#else
        (void)cont; // No-op
        (void)msg;
#endif
    }

    TEST_F(ArticleTest, Foo)
    {
        std::vector<Article> expected;
        expected.push_back(Article("AA",     0, 100.00));
        expected.push_back(Article("AA",     0,  20.00));
        expected.push_back(Article("AA, BB", 1, 170.00));
        expected.push_back(Article("CC, BB", 2, 230.00));

        print(expected, "expected:");

        const std::vector<Article> output = article::combine(input_);
        print(output, "actual:");

        ASSERT_EQ(expected.size(), output.size());
        EXPECT_TRUE(std::equal(expected.begin(), expected.end(), output.begin(),
                               CompareArticle()));
    }
}
