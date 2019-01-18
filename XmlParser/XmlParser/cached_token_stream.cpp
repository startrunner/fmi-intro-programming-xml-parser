#include "pch.h"
#include <string>
#include "cached_token_stream.h"
using namespace std;

bool cached_token_stream::eof()
{
    return innerStream->eof() && peekCache.empty();
}

token cached_token_stream::next_token()
{
    if (!peekCache.empty())
    {
        token token = peekCache.front();
        peekCache.pop_front();
        return token;
    }

    return innerStream->next_token();
}

bool cached_token_stream::try_cache(int count)
{
    while (peekCache.size() < count && !innerStream->eof())
    {
        peekCache.push_back(innerStream->next_token());
    }

    return peekCache.size() >= count;
}

token cached_token_stream::peek(int index)
{
    if (!try_cache(index + 1))
    {
        throw runtime_error(
            "Can't peek" +
            to_string(index) + "'th item. "
            "There are only " + to_string(peekCache.size()) + 
            " items in cache."
        );
    }
    return peekCache[index];
}