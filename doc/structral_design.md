# CrystalSpatial Document

## Design Structure

This library simplifies the linear algebra system and code structure by **strictly** seperating primitive types and classes that build upon them.
Primitive types are data types that have no ownership relations or responsibilities.
Classes may establish some sort of ownership relation or resposibilities **though it is not guaranteed**.

It is very easy to differenciate between the 2 types since the primitive types follow the snake naming scheme while the classes follow the pascal naming scheme.


Currently, primitive types include:
* `vec2f`
* `vec3f`
* `mat2f`
* `mat3f`
* `trans`

and classes include:
* `SubSpace`
* `Position`

## Implementations

### Primitives

All the primitive types are built based on the **GLM** linear algebra library so the functionalities are mostly preserved.
Only the extra functions or exceptions will be touched upon here since the rest should be very self explanatory.

#### trans
You can use the functional operator to apply a transformation to a vector like:
```c++
/* Mathematically $$TransformedVec = T \cdot vec$$. */
trans t{};
vec2f vec{1.0f, 2.0f};
auto transformed_vec = t(vec);
```
or to another transformation to get the composite transformation:
```c++
/* Mathematically $$CompositeTrans= T1 \cdot T2$$ */
trans t1{}, t2{};
t1.Rotate(123);
t2.Translate({4, 5})
auto composite_trans = t1(t2);
```

### Classes

Classes mostly establish some sort of owership relations so they require more effort in terms of structural design.

#### SubSpace

The subspace system workes independently as in it doesn't rely on any other **Classes** to work. It serves as a basis for other components to be build upon.

Currently a `SubSpace` object only contains:
* `Trans()` The transformation to be applied to all of its contents.
* `Parent()` A raw pointer to its parent subspace. This can be set to `nullptr` to indicate a root subspace.

The oddity in here is that a subspace object **does not** have any knowledge of its child subspaces.
This design choice is made due to the following reasons:
* Every subspace object occupies a constant space in memory.
* Memory management techniques can be applied more easily with objects with no ownership to memory.
* Currently there are no needs to access the children of a subspace.

With this design choice, the drawbacks are also very much apparent:
* Every subspace object is responsible for their own lifetime management. The classic c++ RAII idom can not be applied to enable automatic memory releasing by only deleting the root subspace.
* The child subspaces cannot be accessed from their parent.

To make up for the memory management hazard, it is recommended to use a monotonic memory buffer to store all subspaces that can be freed altogether to ensure memory safety and also performance.

There are also plans to implement some basic memory management of subspace to make the workflow more seemless.

#### Positions

This class is a component to the above subspace system.
A `Position` object contains:
* `SubSpace()` The subspace it belongs to.
* `Vec()` The relative coordinates in that subspace.

This class also does not have any memory ownership properties for reasons similar to that of subspaces.

