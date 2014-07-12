#ifndef ARTICLE_HPP
#define ARTICLE_HPP

#include <string>
#include <vector>
#include <map>
#include <utility>

namespace article
{
    class Article
    {
    public:
        std::string name;
        int group;
        double price;

        Article() : name(), group(0), price(0.0) {}

        Article(const std::string& name_, int group_, double price_)
            : name(name_), group(group_), price(price_)
        {
        }
    };

    inline bool operator<(const Article& lhs, const Article& rhs)
    {
        return lhs.group < rhs.group;
    }

    inline std::ostream& operator<<(std::ostream& os, const Article& a)
    {
        return os << "Article('" << a.name << "', " << a.group << ", "
                  << a.price << ")";
    }

    class MapVal
    {
    public:
        std::string name;
        double price;

        MapVal(const std::string& name_, double price_)
            : name(name_), price(price_)
        {
        }
    };

    typedef std::map<int, MapVal> MapType;

    inline std::vector<Article> combine(const std::vector<Article>& articles)
    {
        std::vector<Article> res;
        res.reserve(articles.size());

        MapType map;
        for (std::vector<Article>::const_iterator article = articles.begin();
             article != articles.end(); ++article)
        {
            if (article->group != 0)
            {
                MapType::value_type val = std::make_pair(
                    article->group, MapVal(article->name, article->price));
                std::pair<MapType::iterator, bool> pr = map.insert(val);
                if (!pr.second)
                {
                    // Combine
                    MapType::iterator it = pr.first;

                    std::string& names = it->second.name;
                    if (std::search(names.begin(), names.end(),
                                    article->name.begin(),
                                    article->name.end()) == names.end())
                    {
                        names = it->second.name + ", " + article->name;
                    }

                    double sum = it->second.price + article->price;

                    it->second = MapVal(names, sum);
                }
            }
            else
            {
                res.push_back(*article);
            }
        }

        for (MapType::const_iterator it = map.begin(); it != map.end(); ++it)
        {
            res.push_back(
                Article(it->second.name, it->first, it->second.price));
        }

        std::sort(res.begin(), res.end());
        return res;
    }
}

#endif // ARTICLE_HPP
