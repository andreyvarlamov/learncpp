# 16.2 - Composition

Building complex objects from simpler ones: object composition.

Has-a.

Structs and classes - **composite types**.

Types of object composition: composition and aggregation.

* The part (member) is part of the object (class).
* The part (member) can only belong to one object (class) at a time.
* The part (member) has its existence managed by the object (class). - "Death
  relationship".
* The part (member) does not know about the existence of the object (class). -
  undirectional relationship.

A good rule of thumb is that each class be built to accomplish a single task. That task
should either be the storage and manipulation of some kind of data (e.g. Point2D,
std::string), OR the coordination of its members (e.g. Creature). Ideally not both.
