# 13.7 - Non-static member initialization

Posssible to give normal class member variables (those that don't use the static keyword)
a default initialization value directly.

Also called in-class member initializers.

If a default initialization value is provided and the constructor initializes the member
via the member initializer list, the member initializer list will take precedence.
