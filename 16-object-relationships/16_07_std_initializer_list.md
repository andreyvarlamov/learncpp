# 16.7 - `std::initializer_list`

```c++
IntArray(std::initializer_list<int> list)
    : IntArray(static_cast<int>(list.size())
{
    int count { 0 };
    for (int element : list)
    {
        m_data[count] = element;
        ++count;
    }
}
```

Allows to initialize with an initializer list:

```c++
IntArray array { 5, 4, 3, 2, 1 };
```

> **Best practice**<br>
> If you provide list *construction*, it's a good idea to provide list *assignment* as well.
