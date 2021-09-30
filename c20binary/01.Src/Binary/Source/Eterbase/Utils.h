overwrite this:

template<typename C>
void string_join(const std::string& sep, const C& container, std::string* ret)
{
    unsigned int capacity = sep.length() * container.size() - 1;

    // calculate string sequence
    {
        for (auto i = container.begin(); i != container.end(); ++i)
            capacity += (*i).length();
    }

    string buf;
    buf.reserve(capacity);

    // join strings
    {
        auto cur = container.begin();
        auto end = container.end();
        --end;

        while (cur != end)
        {
            buf.append(*cur++);
            buf.append(sep);
        }
        buf.append(*cur);
    }

    swap(*ret, buf);
}

with:

template<typename C>
void string_join(const std::string& sep, const C& container, std::string* ret)
{
	unsigned int capacity = sep.length() * container.size() - 1;

    // calculate string sequence
    {
        for (auto i = container.begin(); i != container.end(); ++i)
            capacity += (*i).length();
    }

    std::string buf;
    buf.reserve(capacity);

    // join strings
    {
        auto cur = container.begin();
        auto end = container.end();
        --end;

        while (cur != end)
        {
            buf.append(*cur++);
            buf.append(sep);
        }
        buf.append(*cur);
    }

    swap(*ret, buf);
}