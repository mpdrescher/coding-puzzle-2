#ifndef ARTICLE_HPP
#define ARTICLE_HPP

#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <numeric>
#include <functional>


namespace article
{
    struct Article
    {
        std::string name;
        int group;
        double price;

        Article()
            : name(), group(0), price(0.0)
        {}

        Article(const std::string& name_, int group_, double price_)
            : name(name_), group(group_), price(price_)
        {}
    };

    inline bool operator==(const Article& lhs, const Article& rhs) // !
    {
        return lhs.group == rhs.group;
    }

    inline bool operator<(const Article& lhs, const Article& rhs)
    {
        return lhs.group < rhs.group;
    }

    std::ostream& operator<<(std::ostream& os, const Article& a)
    {
        return os << "Article(" << a.name << "," << a.group << "," << a.price << ")";
    }

    namespace detail
    {
        struct Combiner : public std::binary_function<Article, Article, Article>
        {
            Article operator()(const Article& lhs, const Article& rhs) const
            {
                const std::string name = lhs.name + ", " + rhs.name;
                const double price = lhs.price + rhs.price;
                return Article(name, lhs.group, price);
            }
        };
    }

    inline std::vector<Article> combine(std::vector<Article> articles)
    {
        std::vector<Article> res;
        res.reserve(articles.size());
        std::sort(articles.begin(), articles.end());

        for (std::vector<Article>::iterator it = articles.begin();
                it != articles.end(); ++it)
        {
            if (it->group != 0)
            {
                const std::vector<Article>::iterator next
                    = std::lower_bound(it, articles.end(), *it);
//                std::cout << "-> lower bound" << *next << std::endl;

                const Article combined = std::accumulate(it, next, *it,
                        detail::Combiner());

                res.push_back(combined);
                it = next; // !
            }
            else
            {
                res.push_back(*it);
            }
        }

        return res;
    }
}

#endif // ARTICLE_HPP

