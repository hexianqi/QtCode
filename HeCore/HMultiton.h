#ifndef HMULTITON_H
#define HMULTITON_H

#include <map>
#include <string>
#include <memory>

using namespace std;

namespace He {
namespace Core {

template <class T, class K = string>
class HMultiton
{
public:
    template<typename... Args>
    static std::shared_ptr<T> instance(const K &key, Args&&... args)
    {
        return getInstance(key, std::forward<Args>(args)...);
    }

    template<typename... Args>
    static std::shared_ptr<T> instance(K&& key, Args&&... args)
    {
        return getInstance(key, std::forward<Args>(args)...);
    }

private:
    template<typename Key, typename... Args>
    static std::shared_ptr<T> getInstance(Key&& key, Args&&...args)
    {
        std::shared_ptr<T> instance = nullptr;
        auto it = __map.find(key);
        if (it == __map.end())
        {
            instance = std::make_shared<T>(std::forward<Args>(args)...);
            __map.emplace(key, instance);
        }
        else
            instance = it->second;
        return instance;
    }

private:
    HMultiton(void);
    ~HMultiton(void);
    HMultiton(const HMultiton&);
    HMultiton& operator = (const HMultiton&);

private:
    static map<K, std::shared_ptr<T>> __map;
};

template <class T, class K>
map<K, std::shared_ptr<T>> HMultiton<T, K>::__map;

} // Core
} // He

#endif // HMULTITON_H
