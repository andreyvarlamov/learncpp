# 20.6 - Rethrowing exceptions

Useful when you want to log in one place, but not handle the error fully.

Don't rethrow the same exception like this (copy-initializes a copy).

```c++
...
catch (Base &exception)
{
    ...

    throw exception;
}
```

Rethrow it like this

```c++
catch (Base &exception)
{
    ...

    throw;
}
```
